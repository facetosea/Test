#pragma once
#include "tool.h"

class Flights {
public:
    /**
     * @param n: a integer
     * @param flights: a 2D array
     * @param src: a integer
     * @param dst: a integer
     * @param K: a integer
     * @return: return a integer
     */

    void test()
    {
        vector<int> f1 = { 0,1,100 };
        vector<int> f2 = { 1,2,100 };
        vector<int> f3 = { 0,2,500 };
        vector<vector<int>> flights;
        flights.push_back(f1);
        flights.push_back(f2);
        flights.push_back(f3);
        cout << findCheapestPrice(3, flights, 0, 2, 4) << endl;
    }

    struct Route
    {
        int end_;
        unsigned int  distance_ = 0;
    };

    struct StationInfo
    {
        int start_;
        list<Route> routeInfo_;  // 重点，链表存放从start_出发的目的地，方便遍历
    };

    void getFlightsInfo(vector<vector<int>> &flights)
    {
        for (auto s : flights)
        {
            StationInfo startStation;
            startStation.start_ = s[0];
            if (flightsInfo_.find(s[0]) == flightsInfo_.end())
            {
                flightsInfo_[s[0]] = startStation;
            }
            Route route;
            route.end_ = s[1];
            route.distance_ = s[2];
            flightsInfo_[s[0]].routeInfo_.push_back(route);
        }
    }
    void helper(int src, int dst, int K, int price) {
        if (dst == src)
        {
            if (chapestPrice == -1 || chapestPrice > price)
                chapestPrice = price;
            return;
        }
        if (K < 0)
        {
            return;
        }
        for (auto route : flightsInfo_[src].routeInfo_)
        {
            helper(route.end_, dst, K - 1, price + route.distance_);
        }
    }
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
        // write your code here
        getFlightsInfo(flights);
        helper(src, dst, K, 0);
        return chapestPrice;
    }
    map<int, StationInfo> flightsInfo_;
    int chapestPrice = -1;
};