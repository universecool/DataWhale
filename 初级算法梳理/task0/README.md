# 机器学习综述

## 机器学习的发展
机器学习从上世纪五十年代开始至今，主要经历了推理期、连接主义、决策理论、统计学习、深度学习等阶段。

## 机器学习分类
1. 监督学习

监督学习是指利用一组已知类别的样本调整分类器的参数，使其达到所要求性能的过程，也称为监督训练或有教师学习。在监督学习的过程中会提供对错指示，通过不断地重复训练，使其找到给定的训练数据集中的某种模式或规律，当新的数据到来时，可以根据这个函数预测结果。监督学习的训练集要求包括输入和输出，主要应用于分类和预测。

2. 非监督学习

与监督学习不同，在非监督学习中，无须对数据集进行标记，即没有输出。其需要从数据集中发现隐含的某种结构，从而获得样本数据的结构特征，判断哪些数据比较相似。因此，非监督学习目标不是告诉计算机怎么做，而是让它去学习怎样做事情。

3. 半监督学习

半监督学习是监督学习和非监督学习的结合，其在训练阶段使用的是未标记的数据和已标记的数据，不仅要学习属性之间的结构关系，也要输出分类模型进行预测。

4. 强化学习

强化学习（Reinforcement Learning, RL），又称再励学习、评价学习或增强学习，是机器学习的范式和方法论之一，用于描述和解决智能体（agent）在与环境的交互过程中通过学习策略以达成回报最大化或实现特定目标的问题.

## 机器学习模型
机器学习 = 数据（data） + 模型（model） + 优化方法（optimal strategy）
### 机器学习算法导图 [1]
![机器学习算法导图](https://camo.githubusercontent.com/8ebf8c0ea16f2bfa972bfa1498fe4b6aba9b57ad/68747470733a2f2f626c6f672e6772696464796e616d6963732e636f6d2f636f6e74656e742f696d616765732f323031382f30342f6d616368696e656c6561726e696e67616c676f726974686d732e706e67)

### 常见的机器学习算法
1. Linear Algorithms
    1. Linear Regression
    2. Lasso Regression
    3. Ridge Regression
    4. Logistic Regression
2. Decision Tree
   1. ID3
   2. C4.5
   3. CART
3. SVM
4. Naive Bayes Algorithms
   1. Naive Bayes
   2. Gaussian Naive Bayes
   3. Multinomial Naive Bayes
   4. Bayesian Belief Network (BBN)
   5. Bayesian Network (BN)
5. kNN
6.  Clustering Algorithms
    1.  k-Means
    2.  k-Medians
    3.  Expectation Maximisation (EM)
    4.  Hierarchical Clustering

7.  K-Means
8.  Random Forest
9.  Dimensionality Reduction Algorithms
10. Gradient Boosting algorithms
    1.  GBM
    2.  XGBoost
    3.  LightGBM
    4.  CatBoost
11. Deep Learning Algorithms
    1.  Convolutional Neural Network (CNN)
    2.  Recurrent Neural Networks (RNNs)
    3.  Long Short-Term Memory Networks (LSTMs)
    4.  Stacked Auto-Encoders
    5.  Deep Boltzmann Machine (DBM)
    6.  Deep Belief Networks (DBN)

## 常见损失函数
1. 0-1损失函数
$$
L(y,f(x)) =
\begin{cases}
0, & \text{y = f(x)}  \\
1, & \text{y $\neq$ f(x)}
\end{cases}
$$
2. 绝对值损失函数
$$
L(y,f(x))=|y-f(x)|
$$
3. 平方损失函数
$$
L(y,f(x))=(y-f(x))^2
$$
4. log对数损失函数
$$
L(y,f(x))=log(1+e^{-yf(x)})
$$
5. 指数损失函数
$$
L(y,f(x))=exp(-yf(x))
$$
6. Hinge损失函数
$$
L(w,b)=max\{0,1-yf(x)\}
$$

## 主要优化方法
梯度下降是最常用的优化方法之一，它使用梯度的反方向$\nabla_\theta J(\theta)$更新参数$\theta$，使得目标函数$J(\theta)$达到最小化的一种优化方法，这种方法我们叫做梯度更新. 
1. (全量)梯度下降
$$
\theta=\theta-\eta\nabla_\theta J(\theta)
$$
2. 随机梯度下降
$$
\theta=\theta-\eta\nabla_\theta J(\theta;x^{(i)},y^{(i)})
$$
3. 小批量梯度下降
$$
\theta=\theta-\eta\nabla_\theta J(\theta;x^{(i:i+n)},y^{(i:i+n)})
$$
4. 引入动量的梯度下降
$$
\begin{cases}
v_t=\gamma v_{t-1}+\eta \nabla_\theta J(\theta)  \\
\theta=\theta-v_t
\end{cases}
$$
5. 自适应学习率的Adagrad算法
$$
\begin{cases}
g_t= \nabla_\theta J(\theta)  \\
\theta_{t+1}=\theta_{t,i}-\frac{\eta}{\sqrt{G_t+\varepsilon}} \cdot g_t
\end{cases}
$$
6. 牛顿法
$$
\theta_{t+1}=\theta_t-H^{-1}\nabla_\theta J(\theta_t)
$$
其中:
$t$: 迭代的轮数

$\eta$: 学习率

$G_t$: 前t次迭代的梯度和

$\varepsilon:$很小的数,防止除0错误

$H$: 损失函数相当于$\theta$的Hession矩阵在$\theta_t$处的估计

## 常用评价指标
1. MSE(Mean Squared Error)
$$
MSE(y,f(x))=\frac{1}{N}\sum_{i=1}^{N}(y-f(x))^2
$$
2. MAE(Mean Absolute Error)
$$
MSE(y,f(x))=\frac{1}{N}\sum_{i=1}^{N}|y-f(x)|
$$
3. RMSE(Root Mean Squard Error)
$$
RMSE(y,f(x))=\frac{1}{1+MSE(y,f(x))}
$$
4. Top-k准确率
$$
Top_k(y,pre_y)=\begin{cases}
1, {y \in pre_y}  \\
0, {y \notin pre_y}
\end{cases}
$$

5. 混淆矩阵

混淆矩阵|Predicted as Positive|Predicted as Negative
|:-:|:-:|:-:|
|Labeled as Positive|True Positive(TP)|False Negative(FN)|
|Labeled as Negative|False Positive(FP)|True Negative(TN)|

* 真正例(True Positive, TP):真实类别为正例, 预测类别为正例
* 假负例(False Negative, FN): 真实类别为正例, 预测类别为负例
* 假正例(False Positive, FP): 真实类别为负例, 预测类别为正例 
* 真负例(True Negative, TN): 真实类别为负例, 预测类别为负例

* 真正率(True Positive Rate, TPR): 被预测为正的正样本数 / 正样本实际数
$$
TPR=\frac{TP}{TP+FN}
$$
* 假负率(False Negative Rate, FNR): 被预测为负的正样本数/正样本实际数
$$
FNR=\frac{FN}{TP+FN}
$$

* 假正率(False Positive Rate, FPR): 被预测为正的负样本数/负样本实际数，
$$
FPR=\frac{FP}{FP+TN}
$$
* 真负率(True Negative Rate, TNR): 被预测为负的负样本数/负样本实际数，
$$
TNR=\frac{TN}{FP+TN}
$$
* 准确率(Accuracy)
$$
ACC=\frac{TP+TN}{TP+FN+FP+TN}
$$
* 精准率
$$
P=\frac{TP}{TP+FP}
$$
* 召回率
$$
R=\frac{TP}{TP+FN}
$$
* F1-Score
$$
\frac{2}{F_1}=\frac{1}{P}+\frac{1}{R}
$$
* ROC

ROC曲线的横轴为“假正例率”，纵轴为“真正例率”. 以FPR为横坐标，TPR为纵坐标，那么ROC曲线就是改变各种阈值后得到的所有坐标点 (FPR,TPR) 的连线，画出来如下。红线是随机乱猜情况下的ROC，曲线越靠左上角，分类器越佳. 


* AUC(Area Under Curve)

AUC就是ROC曲线下的面积. 真实情况下，由于数据是一个一个的，阈值被离散化，呈现的曲线便是锯齿状的，当然数据越多，阈值分的越细，”曲线”越光滑. 

<img src="https://gss3.bdstatic.com/-Po3dSag_xI4khGkpoWK1HF6hhy/baike/c0%3Dbaike80%2C5%2C5%2C80%2C26/sign=b9cb389a68d0f703f2bf9d8e69933a58/f11f3a292df5e0feaafde78c566034a85fdf7251.jpg">

用AUC判断分类器（预测模型）优劣的标准:

- AUC = 1 是完美分类器，采用这个预测模型时，存在至少一个阈值能得出完美预测。绝大多数预测的场合，不存在完美分类器.
- 0.5 < AUC < 1，优于随机猜测。这个分类器（模型）妥善设定阈值的话，能有预测价值.
- AUC < 0.5，比随机猜测还差；但只要总是反预测而行，就优于随机猜测.

## 机器学习模型选择

1. 交叉验证

所有数据分为三部分：训练集、交叉验证集和测试集。交叉验证集不仅在选择模型时有用，在超参数选择、正则项参数 [公式] 和评价模型中也很有用。

2. k-折叠交叉验证

- 假设训练集为S ，将训练集等分为k份:$\{S_1, S_2, ..., S_k\}$. 
- 然后每次从集合中拿出k-1份进行训练
- 利用集合中剩下的那一份来进行测试并计算损失值
- 最后得到k次测试得到的损失值，并选择平均损失值最小的模型

3. Bias与Variance，欠拟合与过拟合

**欠拟合**一般表示模型对数据的表现能力不足，通常是模型的复杂度不够，并且Bias高，训练集的损失值高，测试集的损失值也高.

**过拟合**一般表示模型对数据的表现能力过好，通常是模型的复杂度过高，并且Variance高，训练集的损失值低，测试集的损失值高.

<img src="https://pic3.zhimg.com/80/v2-e20cd1183ec930a3edc94b30274be29e_hd.jpg">

<img src="https://pic1.zhimg.com/80/v2-22287dec5b6205a5cd45cf6c24773aac_hd.jpg">

4. 解决方法

- 增加训练样本: 解决高Variance情况
- 减少特征维数: 解决高Variance情况
- 增加特征维数: 解决高Bias情况
- 增加模型复杂度: 解决高Bias情况
- 减小模型复杂度: 解决高Variance情况


## 机器学习参数调优

1. 网格搜索

一种调参手段；穷举搜索：在所有候选的参数选择中，通过循环遍历，尝试每一种可能性，表现最好的参数就是最终的结果

2. 随机搜索

与网格搜索相比，随机搜索并未尝试所有参数值，而是从指定的分布中采样固定数量的参数设置。它的理论依据是，如果随即样本点集足够大，那么也可以找到全局的最大或最小值，或它们的近似值。通过对搜索范围的随机取样，随机搜索一般会比网格搜索要快一些。

3. 贝叶斯优化算法

贝叶斯优化用于机器学习调参由J. Snoek(2012)提出，主要思想是，给定优化的目标函数(广义的函数，只需指定输入和输出即可，无需知道内部结构以及数学性质)，通过不断地添加样本点来更新目标函数的后验分布(高斯过程,直到后验分布基本贴合于真实分布。简单的说，就是考虑了上一次参数的信息，从而更好的调整当前的参数。

## 参考文献
[1] https://github.com/datawhalechina/team-learning/blob/master/%E5%88%9D%E7%BA%A7%E7%AE%97%E6%B3%95%E6%A2%B3%E7%90%86/Task1_ml_overvirew.md