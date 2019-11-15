#include <stdio.h>
#include <List>
#include <map>
#include <vector>
#include <stack>

#include "TrainsProblem.h"

using namespace std;

struct Route
{
    unsigned char end_;
    unsigned int  distance_ = 0;
};

struct StationInfo
{
    unsigned char start_;
    std::list<Route> routeInfo_;  // 重点，链表存放从start_出发的目的地，方便遍历
};

std::vector<std::string> LStrSplit(const char* str, size_t len, char c) {
    std::vector<std::string> vec;
    size_t i = 0;
    size_t j = 0;
    for (j = i; j < len; ++j)
    {
        std::string temp;
        if (c == str[j] || j + 1 == len)
        {
            for (size_t k = i; k < j; ++k)
                temp += str[k];
            i = j + 1;
            vec.push_back(temp);
        }
    }
    return vec;
}

void getTrainsInfo(std::map<unsigned char, StationInfo>& trainStationInfos)
{
    char strInfos[1024];
    memset(strInfos, 0, 1024);
    printf("Please intput:");
    scanf_s("%s", strInfos, 1024);
    printf("Input : %s\n", strInfos);

    std::vector<std::string> temp = LStrSplit(strInfos, 1024, ',');
    for (auto s : temp)
    {
        if (s.size() < 3)
            break;
        StationInfo startStation;
        startStation.start_ = s[0];
        if (trainStationInfos.find(s[0]) == trainStationInfos.end())
        {
            trainStationInfos[s[0]] = startStation;
        }
        Route route;
        route.end_ = s[1];
        route.distance_ = atoi( (std::string(s.begin()+2, s.end())).c_str() );
        trainStationInfos[s[0]].routeInfo_.push_back(route);
    }
}

// 返回-1代表路径不存在
int getRouteDistance(const std::map<unsigned char, StationInfo>& trainStationInfos, std::string route)
{
    if (route.size() < 2)
        return -1;

    auto it = trainStationInfos.find(route[0]);
    if (trainStationInfos.find(route[0]) == trainStationInfos.end())
        return -1;

    unsigned char start = route[0];
    for (auto endStation : it->second.routeInfo_)
    {
        if (endStation.end_ == route[1])
        {
            if (route.size() > 2)
            {
                int left = getRouteDistance(trainStationInfos, std::string(route.begin() + 1, route.end()));
                if (left >= 0)
                {
                    return endStation.distance_ + getRouteDistance(trainStationInfos, std::string(route.begin() + 1, route.end()));
                }
                else
                    return -1;
            }
            else
                return endStation.distance_;
        }
    }
    return -1;
}

std::string getRouteDistanceString(const std::map<unsigned char, StationInfo>& trainStationInfos, std::string route)
{
    int dis = getRouteDistance(trainStationInfos, route);
    if (dis >= 0)
    {
        char buf[256] = { 0 };
        sprintf_s(buf, "%d", dis);
        return std::string(buf);
    }
    return "NO SUCH ROUTE";   
}

int getTripNumbersFromStart2Less(const std::map<unsigned char, StationInfo>& trainStationInfos, char start, char end, int maximum)
{
    auto it = trainStationInfos.find(start);
    if (it == trainStationInfos.end())
        return 0;
    int numbers = 0;
    for (auto endStation : it->second.routeInfo_)
    {
        if (endStation.end_ == end)     // 发现终点
        {
            numbers++;
        }
        if (maximum > 1)
            numbers += getTripNumbersFromStart2Less(trainStationInfos, endStation.end_, end, maximum-1);
    }
    return numbers;
}

int getTripNumbersFromStart2Equl(const std::map<unsigned char, StationInfo>& trainStationInfos, char start, char end, int equal)
{
    auto it = trainStationInfos.find(start);
    if (it == trainStationInfos.end())
        return 0;
    int numbers = 0;
    for (auto endStation : it->second.routeInfo_)
    {
        if (endStation.end_ == end && equal == 1)     // 发现终点
        {
            numbers++;
        }
        if (equal > 1)
            numbers += getTripNumbersFromStart2Equl(trainStationInfos, endStation.end_, end, equal - 1);
    }
    return numbers;
}

int getShortestDistance_(const std::map<unsigned char, StationInfo>& trainStationInfos, char start, char end, int shortest, int nowDis, std::vector<char>& path)
{
    std::vector<char> shortestPath = path;
    auto it = trainStationInfos.find(start);
    if (it == trainStationInfos.end())
        return 0;
    for (auto endStation : it->second.routeInfo_)
    {
        if (endStation.end_ == end)     // 发现终点
        {
            if (nowDis + endStation.distance_ < shortest)
            {
                shortest = nowDis + endStation.distance_;
                shortestPath.push_back(endStation.end_);
            }
        }
    }
    for (auto endStation : it->second.routeInfo_)
    {
        if (endStation.end_ == end)     // 发现终点
        {
        }
        else if(nowDis + endStation.distance_ < shortest && path.size() <= trainStationInfos.size() )
        {
            std::vector<char> pathNew = path;
            pathNew.push_back(endStation.end_);
            int otherPathDis = getShortestDistance_(trainStationInfos, endStation.end_, end, shortest, nowDis + endStation.distance_, pathNew);
            if (otherPathDis < shortest)
            {
                shortest = otherPathDis;
                shortestPath = pathNew;
            }
        }
    }
    return shortest;
}

int getShortestDistance(const std::map<unsigned char, StationInfo>& trainStationInfos, char start, char end)
{
    std::vector<char> path;
    path.push_back(start);
    return getShortestDistance_(trainStationInfos, start, end, INT_MAX, 0, path);
}

int getTripNumbersFromStart2LessDistance(const std::map<unsigned char, StationInfo>& trainStationInfos, char start, char end, int maxDis)
{
    auto it = trainStationInfos.find(start);
    if (it == trainStationInfos.end())
        return 0;
    int numbers = 0;
    for (auto endStation : it->second.routeInfo_)
    {
        if (endStation.end_ == end && endStation.distance_ < maxDis)     // 发现终点
        {
            numbers++;
        }
        if (endStation.distance_ < maxDis)
            numbers += getTripNumbersFromStart2LessDistance(trainStationInfos, endStation.end_, end, maxDis - endStation.distance_);
    }
    return numbers;
}

void trainProblemTest()
{
    static std::map<unsigned char, StationInfo> info;
    getTrainsInfo(info);
    printf("The distance of the route A-B-C : %s\n", getRouteDistanceString(info, "ABC").c_str() );
    printf("The distance of the route A-D : %s\n", getRouteDistanceString(info, "AD").c_str());
    printf("The distance of the route A-D-C : %s\n", getRouteDistanceString(info, "ADC").c_str());
    printf("The distance of the route A-E-B-C-D : %s\n", getRouteDistanceString(info, "AEBCD").c_str());
    printf("The distance of the route A-E-D : %s\n", getRouteDistanceString(info, "AED").c_str());

    printf("The number of trips starting at C and ending at C with a maximum of 3 stops : %d \n", getTripNumbersFromStart2Less(info, 'C', 'C', 3) );
    printf("The number of trips starting at A and ending at C with exactly 4 stops : %d \n", getTripNumbersFromStart2Equl(info, 'A', 'C', 4));
    printf("The length of the shortest route from A to C : %d \n", getShortestDistance(info, 'A', 'C'));
    printf("The length of the shortest route from A to C : %d \n", getShortestDistance(info, 'B', 'B'));
    printf("The number of different routes from C to C with a distance of less than 30 : %d \n", getTripNumbersFromStart2LessDistance(info, 'C', 'C', 30));
}