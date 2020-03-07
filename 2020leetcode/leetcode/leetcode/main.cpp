//
//  main.cpp
//  leetcode
//
//  Created by lemon_wang on 2020/3/7.
//  Copyright © 2020 lemon_wang. All rights reserved.
//
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stack>
#include <queue>
#include <math.h>
#include <fstream>
using namespace std;
 vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<vector<int>>res;
     int cur = 0,cur_x,cur_h = -1,len = buildings.size();
     priority_queue<pair<int,int>> Q;//0：height;bulidings[i][2];1:X_end,building[i][1]
     while(cur < len || !Q.empty()){
         cur_x = Q.empty()? buildings[cur][0]:Q.top().second;//最高建筑结束点.
         if(cur >= len || buildings[cur][0] > cur_x){//cur >= len此时已经遍历完所有buildings
             while(! Q.empty() && Q.top().second <= cur_x){
                 Q.pop();
             }
         }
         else{
             cur_x = buildings[cur][0];
             while(cur < len && buildings[cur][0] == cur_x){// 处理同一点开始的建筑物
                 Q.push(make_pair(buildings[cur][2],buildings[cur][1]));
                 cur ++;
                 
             }
         }
         cur_h = Q.empty() ? 0 : Q.top().first;
         if(res.empty() || res.back()[1] != cur_h){
             vector<int> tmp;
             tmp.push_back(cur_x);
             tmp.push_back(cur_h);
             res.push_back(tmp);
         }
            
     }
    return res;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> v1;
    v1.push_back(2);
    v1.push_back(9);
    v1.push_back(10);
    vector<int> v2;
    v2.push_back(3);
    v2.push_back(7);
    v2.push_back(15);
    vector<int> v3;
    v3.push_back(5);
    v3.push_back(12);
    v3.push_back(12);
    vector<int> v4;
    v4.push_back(15);
    v4.push_back(20);
    v4.push_back(10);
    vector<int> v5;
    v5.push_back(19);
    v5.push_back(24);
    v5.push_back(8);
    vector<vector<int>> input;
    input.push_back(v1);
    input.push_back(v2);
    input.push_back(v3);
    input.push_back(v4);
    input.push_back(v5);
    vector<vector<int>> res;
    res = getSkyline(input);
    for(int i = 0; i < res.size(); i ++){
        for(int j = 0 ; j < res[i].size() ; j++){
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
    std::cout << "Hello, World!\n";
    return 0;
}
