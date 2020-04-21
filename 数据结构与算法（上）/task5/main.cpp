#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/* 1. 无重复字符的最长子串 */
class Solution1
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.size() == 0)
            return 0;

        int max_len = 0;
        int left = 0;
        unordered_set<char> lookup;
        for (int i = 0; i < s.size(); i++)
        {
            while (lookup.find(s[i]) != lookup.end())
            {
                lookup.erase(s[left]);
                left++;
            }
            lookup.insert(s[i]);
            max_len = max_len < lookup.size()? lookup.size() : max_len;
        }
        return max_len ;
    }
};

/* 2. 串联所有单词的子串 */
class Solution2
{
public:
    vector<int> findSubstring(string s, vector<string>& words)
    {
        if (s.empty() || words.empty())
            return {};
        
        vector<int> result;
        int n = s.size();
        int one_word = words[0].size();
        int word_num = words.size();

        unordered_map<string, int> mWords;
        for(const auto& w: words)
            mWords[w]++;

        if (n < one_word || n < one_word * word_num)
            return result;
        for (int i = 0; i < one_word; i++)
        {
            int left = i;
            int right = i;
            int cur_count = 0;
            unordered_map<string, int> hashmap;
            while (right + one_word <= n)
            {
                string w = s.substr(right, one_word);
                right += one_word;
                if (!mWords.count(w))
                {
                    hashmap.clear();
                    left = right;
                    cur_count = 0;
                }
                else
                {
                    hashmap[w]++;
                    cur_count++;
                    while (hashmap[w] > mWords[w]) 
                    {
                        string left_w = s.substr(left, one_word);
                        left += one_word;
                        hashmap[left_w]--;
                        cur_count--;
                    }
                    if (cur_count == word_num)
                        result.push_back(left);
                }
            }
        }
        return result;
    }
};

/* 3. 替换子串得到平衡字符串 */
class Solution3
{
public:
    int balancedString(string s)
    {
        int n = s.size();
        int res = n;
        int avg = n / 4;
        unordered_map<char, int> sq;
        for(auto &w : s)
            sq[w]++;
        
        bool balance = true;
        string chars = "QWER";
        for (auto &ch : chars)
        {
            if (sq[ch] != avg)
            {
                balance = false;
                break;
            }
        }
        if (balance)
            return 0;
        int left = 0;
        int right = 0;
        for (right = 0; right < n; right++)
        {
            sq[s[right]]--;
            bool find = true;            
            for (auto &ch : chars)
                {
                    if (sq[ch] > avg)
                    {
                        find = false;
                        break;
                    }
                }          
            while (left < n && find)
            {
                res = min(res, right - left + 1);
                sq[s[left]]++;
                left++;
                for (auto &ch : chars)
                    {
                        if (sq[ch] > avg)
                        {
                            find = false;
                            break;
                        }
                    } 
            }
        }
        return res;
    }
};