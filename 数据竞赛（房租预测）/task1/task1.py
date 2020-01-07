#!/usr/bin/env python
# coding: utf-8

# In[3]:


#coding:utf-8
#导入warnings包，利用过滤器来实现忽略警告语句。
import warnings
warnings.filterwarnings('ignore')

# GBDT
from sklearn.ensemble import GradientBoostingRegressor
# XGBoost
import xgboost as xgb
# LightGBM
import lightgbm as lgb

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns


# In[4]:


#载入数据
data_train = pd.read_csv('./train_data.csv')
data_train['Type'] = 'Train'
data_test = pd.read_csv('./test_a.csv')
data_test['Type'] = 'Test'
data_all = pd.concat([data_train, data_test], ignore_index=True)


# In[10]:


data_all


# In[12]:


data_all.head()


# In[13]:


data_all['rentType']


# ## 总体情况一览

# In[5]:


# 总体情况
print(data_train.info())
print(data_train.describe())
data_train.head()


# ## 分类特征和连续型特征

# In[6]:


# 根据特征含义和特征一览，大致可以判断出数值型和类别型特征如下
categorical_feas = ['rentType', 'houseType', 'houseFloor', 'region', 'plate', 'houseToward', 'houseDecoration',
    'communityName','city','region','plate','buildYear']
numerical_feas=['ID','area','totalFloor','saleSecHouseNum','subwayStationNum',
    'busStationNum','interSchoolNum','schoolNum','privateSchoolNum','hospitalNum',
    'drugStoreNum','gymNum','bankNum','shopNum','parkNum','mallNum','superMarketNum',
    'totalTradeMoney','totalTradeArea','tradeMeanPrice','tradeSecNum','totalNewTradeMoney',
    'totalNewTradeArea','tradeNewMeanPrice','tradeNewNum','remainNewNum','supplyNewNum',
    'supplyLandNum','supplyLandArea','tradeLandNum','tradeLandArea','landTotalPrice',
    'landMeanPrice','totalWorkers','newWorkers','residentPopulation','pv','uv','lookNum']


# ## 缺失值分析

# In[36]:


# 缺失值分析
def missing_values(df):
    alldata_na = pd.DataFrame(df.isnull().sum(), columns={'missingNum'})
    alldata_na['existNum'] = len(df) - alldata_na['missingNum']
    alldata_na['sum'] = len(df)
    alldata_na['missingRatio'] = alldata_na['missingNum']/len(df)*100
    alldata_na['dtype'] = df.dtypes
    #ascending：默认True升序排列；False降序排列
    alldata_na = alldata_na[alldata_na['missingNum']>0].reset_index().sort_values(by=['missingNum','index'],ascending=[False,True])
    alldata_na.set_index('index',inplace=True)
    return alldata_na

missing_values(data_train)


# In[63]:


alldata_na = pd.DataFrame(data_train.isnull().sum(), columns={'missingNum'})
print(alldata_na[alldata_na['missingNum']>0])
print(alldata_na[alldata_na['missingNum']>0]['missingNum'])


# 仅有pv、uv存在缺失值，后面再探究会发现缺失的都是属于同一个plate，可能是官方直接删除了该plate的pv、uv

# ## 单调特征列分析

# In[38]:


#是否有单调特征列(单调的特征列很大可能是时间)
def incresing(vals):
    cnt = 0
    len_ = len(vals)
    for i in range(len_-1):
        if vals[i+1] > vals[i]:
            cnt += 1
    return cnt

fea_cols = [col for col in data_train.columns]
for col in fea_cols:
    cnt = incresing(data_train[col].values)
    if cnt / data_train.shape[0] >= 0.55:
        print('单调特征：',col)
        print('单调特征值个数：', cnt)
        print('单调特征值比例：', cnt / data_train.shape[0])


# ## 特征nunique分布

# In[77]:


get_ipython().run_line_magic('matplotlib', 'inline')
# 特征nunique分布
for feature in categorical_feas:
    print(feature + "的特征分布如下：")
    print(data_train[feature].value_counts())
    if feature != 'communityName': # communityName值太多，暂且不看图表
        plt.hist(data_all[feature], bins=3)
        plt.show()


# In[14]:


print(data_train['communityName'].value_counts())
print(data_test['communityName'].value_counts())


# ## 统计特征值频次大于100的特征

# In[15]:


# 统计特征值出现频次大于100的特征
for feature in categorical_feas:
    df_value_counts = pd.DataFrame(data_train[feature].value_counts())
    df_value_counts = df_value_counts.reset_index()
    df_value_counts.columns = [feature, 'counts'] # change column names
    print(df_value_counts[df_value_counts['counts'] >= 100])


# ## Label分布

#  ### 房屋面积

# In[102]:


print(max(data_train['area']))
print(min(data_train['area']))
fig, axes = plt.subplots(2, 3, figsize=(20,6))
# fig.set_size_inches(20,6)
sns.distplot(data_train['area'], ax = axes[0][0])
sns.distplot(data_train[data_train['area']<=100]['area'], ax=axes[0][1])
sns.distplot(data_train[(data_train['area']>100) & (data_train['area']<=200)]['area'], ax=axes[0][2])
sns.distplot(data_train[(data_train['area']>200) & (data_train['area']<=300)]['area'], ax=axes[1][0])
sns.distplot(data_train[(data_train['area']>300) & (data_train['area']<=400)]['area'], ax=axes[1][1])
# sns.distplot(data_train[(data_train['area']>500) & (data_train['area']<=600)]['area'], ax=axes[1][2])
sns.distplot(data_train[(data_train['area']>500)]['area'], ax=axes[1][2])


# In[58]:


print(type(axes))
print(axes[0][0])
print(axes[0][1])


# In[66]:


# Labe 分布
fig,axes = plt.subplots(2,3,figsize=(20,5))
fig.set_size_inches(20,12)
sns.distplot(data_train['tradeMoney'],ax=axes[0][0])
sns.distplot(data_train[(data_train['tradeMoney']<=20000)]['tradeMoney'],ax=axes[0][1])
sns.distplot(data_train[(data_train['tradeMoney']>20000)&(data_train['tradeMoney']<=50000)]['tradeMoney'],ax=axes[0][2])
sns.distplot(data_train[(data_train['tradeMoney']>50000)&(data_train['tradeMoney']<=100000)]['tradeMoney'],ax=axes[1][0])
sns.distplot(data_train[(data_train['tradeMoney']>100000)]['tradeMoney'],ax=axes[1][1])


# In[76]:


data_train['tradeMoney']
# data_train['tradeMoney']<=10000
# data_train[(data_train['tradeMoney']<=10000)]['tradeMoney']


# In[19]:


print("money<=10000",len(data_train[(data_train['tradeMoney']<=10000)]['tradeMoney']))
print("10000<money<=20000",len(data_train[(data_train['tradeMoney']>10000)&(data_train['tradeMoney']<=20000)]['tradeMoney']))
print("20000<money<=50000",len(data_train[(data_train['tradeMoney']>20000)&(data_train['tradeMoney']<=50000)]['tradeMoney']))
print("50000<money<=100000",len(data_train[(data_train['tradeMoney']>50000)&(data_train['tradeMoney']<=100000)]['tradeMoney']))
print("100000<money",len(data_train[(data_train['tradeMoney']>100000)]['tradeMoney']))

