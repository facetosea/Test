#pragma once
#include "tool.h"

class Poker
{
    struct pokerList
    {
        int start = 0;
        int end = 0;
    };
#define MAXPOKERNUM 9
    void helper(int start, int end, int listCount)
    {
        bool hasList = false;
        while (m_pokerMap[start] == 0 && start <= MAXPOKERNUM-4) ++start;
        if (start > MAXPOKERNUM - 4)
            start = MAXPOKERNUM;

        end = end > start ? end + 1 : start + 1;
        while (end <= MAXPOKERNUM && m_pokerMap[end] > 0 && end - start < 4)
        {
            end++;
        }
        if (end >= MAXPOKERNUM + 1)    //   已无合格List
        {
        }
        else if (m_pokerMap[end] == 0)
        {
            start = end;
            helper(start, end, listCount);
        }
        else
        {
            hasList = true;
            for (int j = start; j <= end; ++j)
            {
                m_pokerMap[j]--;
            }
            helper(start-1, start-1, listCount+1);
            for (int j = start; j <= end; ++j)
            {
                m_pokerMap[j]++;
            }
            helper(start, end, listCount);
        }
        if (!hasList)
        {
            for (auto p : m_pokerMap)
            {
                if (p.second > 0) listCount++;
            }
            if (listCount < m_lest)
                m_lest = listCount;
        }
    }

    int getAns(vector<int> &cards)
    {
        for (int i = 1; i <= MAXPOKERNUM; ++i)
        {
            m_pokerMap[i] = 0;
        }
        for (auto v : cards)
        {
            m_pokerMap[v]++;
        }
        helper(1, 1, 0);
        return m_lest;
    }

    map<int, int> m_pokerMap;
    int m_lest = 30;
public:
    void test() {
        vector<int> v = { 2,2,4,4,6,5,3,6,3,1,6 };
        cout << "minNum:" << getAns(v) << endl;
    }
};
