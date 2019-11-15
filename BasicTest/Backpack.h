#pragma once
#include "tool.h"

class Backpack {
public:
    /**
     * @param n: the money of you
     * @param prices: the price of rice[i]
     * @param weight: the weight of rice[i]
     * @param amounts: the amount of rice[i]
     * @return: the maximum weight
     */
    struct riceInfo
    {
        riceInfo(int p, int w, int a) :price_(p), weight_(w), amount_(a) { w_unit_price_ = (float)weight_ / price_; }
        int price_;
        int weight_;
        int amount_;
        float w_unit_price_;
        bool operator<(const riceInfo& other) const
        {
            return w_unit_price_ > other.w_unit_price_;
        }
    };

    void helper(int n, set<riceInfo>& infoSet, set<riceInfo>::iterator it, int ownWeight)
    {
        if (n == 0) findMax = true;
        if (n == 0 || it == infoSet.end()){
            if (ownWeight > maxWeight)
                maxWeight = ownWeight;
            else
            {
                if (ownWeight + n * ceil(infoSet.begin()->w_unit_price_) < maxWeight)
                    findMax = true;
            }
            return;
        }
        set<riceInfo>::iterator next = ++it;
        it--;
        int i = min(n / it->price_, it->amount_);
        for (; i >= 0 && findMax != true; --i)
        {
            helper(n - it->price_ * i, infoSet, next, ownWeight + it->weight_ * i);
        }
    }

    int backPackVII(int n, vector<int> &prices, vector<int> &weight, vector<int> &amounts) {
        // write your code here
        set<riceInfo> riceInfoSet;
        for (int i = 0; i < prices.size(); ++i)
        {
            riceInfo t(prices[i], weight[i], amounts[i]);
            riceInfoSet.emplace(t);
        }
        helper(n, riceInfoSet, riceInfoSet.begin(), 0);
        return maxWeight;
    }

    bool findMax = false;
    int maxWeight = 0;

    void test()
    {
        vector<int> prices{ 4, 20, 8, 3, 9, 1, 13, 15, 6, 12, 2, 8, 5, 11, 13, 14, 6, 15, 2, 5, 14, 13, 14, 4, 3, 13, 4, 9, 14, 3 };
        vector<int> weights{ 14,79,43,115,94,128,140,95,112,167,57,106,20,109,194,176,41,51,178,80,86,169,157,131,33,15,110,184,64,84 };
        vector<int> amounts{ 16, 1, 19, 13, 1, 6, 16, 15, 19, 15, 4, 1, 4, 8, 14, 9, 1, 3, 18, 17, 17, 15, 7, 15, 14, 16, 15, 18, 17, 14 };
        cout << "result:" << backPackVII(62, prices, weights, amounts);
    }
};

// 贪心算法DFS，效率低，增加提前退出会有遗漏
class BackpackII {
public:
    /**
     * @param n: the money of you
     * @param prices: the price of rice[i]
     * @param weight: the weight of rice[i]
     * @param amounts: the amount of rice[i]
     * @return: the maximum weight
     */
    struct StoneInfo
    {
        StoneInfo(int p, int w) :price_(p), weight_(w){ w_unit_price_ = (float)price_ / weight_; }
        int price_;
        int weight_;
        float w_unit_price_;
        bool operator<(const StoneInfo& other) const
        {
            return w_unit_price_ > other.w_unit_price_;
        }
    };

    void helper(int m, set<StoneInfo>& infoSet, set<StoneInfo>::iterator it, int ownPrice)
    {
        if (m == 0) findMax = true;
        if (m == 0 || it == infoSet.end()) {
            if (ownPrice > maxPrice)
                maxPrice = ownPrice;
            else
            {
                if (ownPrice + m * ceil(infoSet.begin()->w_unit_price_) < maxPrice)
                    findMax = true;
            }
            return;
        }
        if (findMax)
            return;
        set<StoneInfo>::iterator next = ++it;
        it--;
        if(m >= it->weight_)
            helper(m - it->weight_, infoSet, next, ownPrice + it->price_);
        helper(m, infoSet, next, ownPrice);

    }

    int backPackII(int m, vector<int> &A, vector<int> &V) {
        // write your code here
        set<StoneInfo> stoneInfoSet;
        for (int i = 0; i < A.size(); ++i)
        {
            StoneInfo t(V[i], A[i]);
            stoneInfoSet.emplace(t);
        }
        helper(m, stoneInfoSet, stoneInfoSet.begin(), 0);
        return maxPrice;
    }

    bool findMax = false;
    int maxPrice = 0;

    void test()
    {
        vector<int> A{ 3,68,24,80,76,9,24,2,46,75,56,41,95,46,23,34,64,76,6,48,25,73,87,67,58,7,93,66,55,75,38,27,53,6,100,36,26,17,53,88,21,9,34,90,32,47,4,6,57,50,30,25,41,24,12,74,92,17,32,96,35,76,52,93,64,55,1,70,26,35,2,97,82,22,41,37,63,28,90,13,18,55,28,58,59,74,71,32,71,66,4,5,48,52,70,62,28,36,39,48 };
        vector<int> V{ 38,16,29,47,22,25,17,49,15,15,75,11,56,99,51,92,59,37,13,98,61,50,32,17,44,79,41,53,45,29,62,64,2,23,31,45,57,68,57,26,51,26,86,83,94,20,98,24,91,89,1,63,21,46,74,56,64,72,58,8,74,24,27,35,94,49,65,21,16,25,1,45,63,4,37,25,39,68,49,11,31,95,5,79,20,21,52,50,8,19,67,21,24,89,28,88,38,96,64,84 };
        cout << "result:" << backPackII(1000, A, V);
    }
};

// 动态规划解决
//if (m >= it->weight_)
//    helper(m - it->weight_, infoSet, next, ownPrice + it->price_);
//helper(m, infoSet, next, ownPrice);
// 具备转化为动态数组的逻辑，得到状态转移方程
// f[i][v]=max{ f[i-1][v],f[i-1][v-w[i]]+c[i] }
// 只考虑子问题“将前 i 个物品放入容量为 v 的背包中的最大价值”
class BackpackII_DP {
public:
    // A representing the size of each item and array V representing the value of each item
    int backPackII(int m, vector<int> &A, vector<int> &V) {
        // write your code here
        int itemCount = A.size();   //count of items
        vector<vector<int>> dp(itemCount, vector<int>(m+1, 0)); 
        dp[0][0] = 0;
        for (int i = 0; i <= itemCount-1; ++i)
        {
            for (int j = 0; j <= m; ++j)
            {
                if (i - 1 < 0)
                {
                    dp[i][j] = A[i] <= j ? V[i] : 0;
                }
                else if (j - A[i] >= 0)
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - A[i]] + V[i]);
                }
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        return dp[itemCount-1][m];
    }

    void test()
    {
        vector<int> A{ 3,68,24,80,76,9,24,2,46,75,56,41,95,46,23,34,64,76,6,48,25,73,87,67,58,7,93,66,55,75,38,27,53,6,100,36,26,17,53,88,21,9,34,90,32,47,4,6,57,50,30,25,41,24,12,74,92,17,32,96,35,76,52,93,64,55,1,70,26,35,2,97,82,22,41,37,63,28,90,13,18,55,28,58,59,74,71,32,71,66,4,5,48,52,70,62,28,36,39,48 };
        vector<int> V{ 38,16,29,47,22,25,17,49,15,15,75,11,56,99,51,92,59,37,13,98,61,50,32,17,44,79,41,53,45,29,62,64,2,23,31,45,57,68,57,26,51,26,86,83,94,20,98,24,91,89,1,63,21,46,74,56,64,72,58,8,74,24,27,35,94,49,65,21,16,25,1,45,63,4,37,25,39,68,49,11,31,95,5,79,20,21,52,50,8,19,67,21,24,89,28,88,38,96,64,84 };
        cout << "result:" << backPackII(1000, A, V);
    }
};


// 动态规划解决
// 重点:状态转移方程
// dp[i][j] 
class BackpackVII_DP {
public:
    int backPackVII(int n, vector<int> &prices, vector<int> &weight, vector<int> &amounts){
        // write your code here
        int itemCount = prices.size();   //count of items
        vector<vector<int>> dp(itemCount, vector<int>(n + 1, 0));
        dp[0][0] = 0;
        for (int i = 0; i <= itemCount - 1; ++i)
        {
        }

        return dp[itemCount - 1][n];
    }

    void test()
    {
    }
};