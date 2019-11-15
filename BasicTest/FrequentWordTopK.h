#pragma once
#include "tool.h"

class TopK {
public:
    struct sCount
    {
        sCount(string s1, int c1) { s = s1; count = c1; }
        string s;
        int count;
        bool operator<(const sCount& b) const
        {
            if (count != b.count)
                return count > b.count;
            else return s < b.s;
        }
    };

    /*
    * @param k: An integer
    */TopK(int k) {
    // do intialization if necessary
    k_ = k;
}

      /*
       * @param word: A string
       * @return: nothing
       */
      void add(string &word) {
          // write your code here
          if(wordCounts.find(word) == wordCounts.end())
          {
              wordCounts[word] = 1;
          }
          else
              ++wordCounts[word];
          sCount t(word, wordCounts[word]-1);
          if (topK_.find(t) != topK_.end())
          {
              topK_.erase(t); 
              ++t.count;
              topK_.emplace(t);
          }
          else if (topK_.size() < k_)
          {
              ++t.count;
              topK_.emplace(t);
          }
          else
          {
              auto it = topK_.end();
              for (int i = 0; i < k_; ++i)
              {
                  --it;
                  if (wordCounts[word] < it->count || (wordCounts[word] == it->count && word > it->s)) break;
                  else
                  {
                      topK_.erase(it);
                      ++t.count;
                      topK_.emplace(t);
                      break;
                  }
              }
          }
      }

      /*
       * @return: the current top k frequent words.
       */
      vector<string> topk() {
          // write your code here
          vector<string> res;
          for (auto it = topK_.begin(); it != topK_.end(); ++it)
          {
              res.push_back(it->s);
          }
          return res;
      }

      set<sCount> topK_;
      int k_;
      map<string, int> wordCounts;
};


class TopKElements
{
public:
    /**
     * @param nums: the given array
     * @param k: the given k
     * @return: the k most frequent elements
     */
    struct NumCounts {
        NumCounts(int v, int c) { val = v; count = c; }
        int val;
        int count;
        bool operator<(const NumCounts& other) const {
            if (count != other.count)
                return count > other.count;
            else
                return val > other.val;
        }
    };

    vector<int> topKFrequent(vector<int> &nums, int k) {
        // Write your code here
        map<int, int> numCounts;
        set<NumCounts> topK;
        for (auto val : nums)
        {
            if (numCounts.find(val) == numCounts.end())
                numCounts[val] = 1;
            else
                ++numCounts[val];

            NumCounts t(val, numCounts[val] - 1);
            if (topK.find(t) != topK.end())
            {
                topK.erase(t);
                ++(t.count);
                topK.emplace(t);
                cout << "change count" << endl;
            }
            else if (topK.size() < k)
            {
                ++(t.count);
                topK.emplace(t);
            }
            else
            {
                auto it = topK.end();
                it--;
                if (numCounts[val] < it->count || (numCounts[val] == it->count && val < it->val)); // do nothing
                else
                {
                    topK.erase(it);
                    ++(t.count);
                    topK.emplace(t);
                }
            }
        }

        vector<int> res;
        for (auto it = topK.begin(); it != topK.end(); ++it)
        {
            res.push_back(it->val);
        }
        return res;
    }

    void test()     
    {
        vector<int> v = { 1,1,1,2,2,3 };
        vector<int> res = topKFrequent(v,2);
        cout << "result:";
        for (auto v : res)
        {
            cout << v << "  ";
        }
        cout << endl;
    }
};


class TopKElements_new
{
public:
    /**
     * @param nums: the given array
     * @param k: the given k
     * @return: the k most frequent elements
     */
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int num : nums) {
            map[num]++;
        }

        vector<int> res;
        // pair<first, second>: first is frequency,  second is number
        priority_queue<pair<int, int>> pq;
        for (auto it = map.begin(); it != map.end(); it++) {

            pq.push(make_pair(it->second, it->first));
            if (pq.size() > (int)map.size() - k) {
                res.push_back(pq.top().second);
                pq.pop();
            }
        }
        return res;
    }
};