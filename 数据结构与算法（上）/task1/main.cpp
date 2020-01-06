#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution1
{
public:
    Solution1(int n):m_nN(n)
    {
        m_pArr = new int [m_nN];
    }
    ~Solution1()
    {
        delete[] m_pArr;
    }
    int *fun()
    {
        if (m_nN < 2)
        {
            throw "N should be larger than 2!";
        }
        for (int i = 2; i <= m_nN; i++)
        {
            if (i % 5 == 0 || i % 7 == 0)
            {
                m_pArr[m_nJ++] = i;
            }
        }
        return m_pArr;
    }
    int get_len()
    {
        return m_nJ;
    }
private:
    int * m_pArr;
    int m_nN, m_nJ = 0;
};


class Solution2
{
public:
    bool isToeplitzMatrix(int** arr, int d1, int d2)
    {
        bool flag = true;
        for (int i = 1; i < d1; i++)
        {
            for (int j = 1; j < d2; j++)
            {
                if (*((int*)arr+i*d2+j) != *((int*)arr+(i-1)*d2+j-1))
                    flag = false;
            }
        }
        return flag;
    }
};


class Solution3 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.empty() || nums.size() < 3)
            return ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0)
                {
                    ans.push_back({ nums[i], nums[left], nums[right] });
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1])
                        left++;
                    while (left < right && nums[right] == nums[right + 1])
                        right--;
                }
                else if (sum < 0)
                {
                    left++;
                    // while(left<right && nums[left]==nums[left-1])
                    //     left++;
                }
                else
                {
                    right--;
                    //  while(left<right && nums[right]==nums[right+1])
                    //     right--;
                }
            }
        }
        return ans;
    }
};

int main()
{
    // #1
    Solution1 solution1(100);
    int *arr1 = solution1.fun();
    int N = solution1.get_len();
    for (int i = 0; i < N; i++)
    {
        cout << arr1[i] << ' ';
    }
    cout << endl << endl << "**************" << endl << endl;

    // #2
    Solution2 solution2;
    int arr2[][4] = { 1,2,3,4,5,1,2,3,9,5,1,2 };
    bool flag = solution2.isToeplitzMatrix((int **)arr2, 3, 4);
    cout << flag;
    cout << endl << endl << "**************" << endl << endl;

    // #3
    Solution3 solution3;
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result;
    result = solution3.threeSum(nums);
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
            cout << result[i][j] << ' ';
        cout << endl;
    }        

    return 0;
}