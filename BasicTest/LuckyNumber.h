#pragma once
#include "tool.h"

class LuckyNumber {
public:
    /**
     * @param n: the n
     * @return: the smallest lucky number  that is not less than n
     */
    string luckyNumber(string &n) {
        // Write your code here.
        if (n.size() % 2 == 1)
        {
            string s(n.size() + 1, '3');
            n = s;
        }
        else
        {
            n = getNextLuckyNumer(n);
        }
        while (!isAswer(n))
        {
            getNextLuckyBuLucky(n);
        }
        return n;
    }

    bool isAswer(string& n)
    {
        int count3 = 0;
        int count5 = 0;
        for (auto c : n)
        {
            if (c == '3')
                ++count3;
            else
                ++count5;
        }
        return count3 == count5;
    }

    string getNextLuckyNumer(string& n)
    {
        int len = n.size();
        bool find = false;
        int i = 0;
        for (; i <= len - 1; ++i)
        {
            if (n[i] > '5')
            {
                while (--i >= 0)
                {
                    if (n[i] == '3')
                    {
                        n[i] = '5';
                        find = true;
                        break;
                    }
                }
                if (!find)
                {
                    string s(len + 1, '3');
                    return s;
                }
                break;
            }
            else if (n[i] == '5')
            {
            }
            else if (n[i] > '3' && n[i] < '5')
            {
                n[i] = '5';
                find = true;
                break;
            }
            else if (n[i] == '3')
            {

            }
            else
            {
                n[i] = '3';
                find = true;
                break;
            }
        }
        if (find)
        {
            while (++i <= len - 1) n[i] = '3';
        }
        return n;
    }

    void getNextLuckyBuLucky(string& n)
    {
        int len = n.size();
        bool find = false;
        int i = len - 1;
        for (; i >= 0; --i)
        {
            if (n[i] == '3')
            {
                n[i] = '5';
                find = true;
                break;
            }
        }
        if (!find)
        {
            n += "3";
            n[0] = '3';
            i = 0;
        }
        while (++i <= len - 1) n[i] = '3';
    }

    void test()
    {
        string s = "5123435353";
        cout << s << " : ";
        cout << luckyNumber(s) << endl;
    }
};
