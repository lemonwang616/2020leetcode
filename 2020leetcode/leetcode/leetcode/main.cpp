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
     //每次选当前最右，最高点加入ans中，若当前遍历得出的最右点，非最高点（既和上次ans相同），则不加入Q中，等待后续处理
     int count = 0;
     vector<vector<int>> res;
     int cur = 0, curx = -1, curh = -1,  len = buildings.size(); //cur-buildings' index
     priority_queue<pair<int, int>> Q;//0:height buildings[i][2] ; 1 : endx buildings[i][1]
     while(cur < len || !Q.empty()){
          // 如果是最开始处理建筑，或者出现建筑物不连续的情况
         curx = Q.empty() ? buildings[cur][0] : Q.top().second;//先确定横坐标curx，本次循环以它做基准
         if(cur >= len || curx < buildings[cur][0]){//讨论pop Q情况 此时curx不变，依旧是目前Q中最右侧的点
             while( !Q.empty() && curx >= Q.top().second){
                 //此处curx一定要取等号，否则最后buildings遍历结束无法Q.pop退出循环
                 Q.pop();
             }
         }
         else{
             /* pushQ;此时改变curx,进入到此else，说明buildings[i]的起始点不在当前Q.top线段中，此时可能会出现拐点，故改变curx*/
             curx = buildings[cur][0]; // 处理起始点相同的线段
             while(cur < len && curx == buildings[cur][0]){
                 Q.push(make_pair(buildings[cur][2], buildings[cur][1]));
                 cur ++;
             }
         }
         //输出最顶端的建筑物高度，如果当前pushQ的高度没有最顶端高，则后序再处理
         curh = Q.empty() ? 0 : Q.top().first;
         if(res.empty() || curh != res.back()[1]) {//res为空或者curh和上个答案的curh不一样
             //printf("count:%d x:%d y:%d\n",++count,curx,curh);
             vector<int> tmp;tmp.push_back(curx);tmp.push_back(curh);
             res.push_back(tmp);
         }
     }
     //等加入到ans时，再判断curx - h
     return res;
 }
int main(int argc, const char * argv[]) {
    // insert code here...
//    vector<int> v1;
//    v1.push_back(2);
//    v1.push_back(9);
//    v1.push_back(10);
    int a[3] = {2,9,10};
    int b[3] = {3,7,15};
    int c[3] = {5,12,12};
    int d[3] = {15,20,10};
    int e[3] = {19,24,8};
    vector<int> v1(a,a + 3);
    vector<int> v2(b,b + 3);
    vector<int> v3(c,c + 3);
    vector<int> v4(d,d + 3);
    vector<int> v5(e,e + 3);
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
    //std::cout << "Hello, World!\n";
    return 0;
}
