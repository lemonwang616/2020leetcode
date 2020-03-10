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
#include <map>
#include<stdlib.h>
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
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int sum = 0;
    ListNode* res = NULL;
    ListNode** node = &res;
    
    while(l1 != NULL || l2 != NULL || sum > 0){
        if(l1 != NULL){
            sum = sum + l1 -> val;//注意listnode的遍历方式
            l1 = l1 -> next;
        }
        if(l2 != NULL){
            sum = sum + l2 -> val;
            l2 = l2 -> next;
        }
        (* node)= new ListNode(sum%10);
        sum = sum / 10;
        node = &((* node) -> next);
        
    }
    
    return res;
}
int lengthOfLongestSubstring(string s) {
    int len = s.length();
    //printf("%d\n",len);
    map<char,int> mp; // char + index，其中index为char对应字符的next下标，保证计算不重复长度时不会出错。
    int cur = 0,i= 0;// cur 表示 循环index,i 表示上次重复位置 ；
    int ans = 0;
    map<char,int>::iterator iter;
    for(int cur = 0; cur < len; cur ++){
        char c = s[cur];
        iter = mp.find(c);
        if(iter != mp.end()){
            i = i > iter -> second ? i : iter ->second;
            iter -> second = cur + 1;
        }
        else{
            
            mp.insert(make_pair(c,cur + 1));//注意，此处push cur要加1
        }
        ans = ans > (cur - i + 1) ? ans : (cur - i + 1);
    }
    return ans;
}
#define INF 0x7fffffff
int main(int argc, const char * argv[]) {
    string str;
    while(getline(cin,str)){
        int len = lengthOfLongestSubstring(str);
        printf("%d\n",len);
    }
        printf("hello lemon\n");

    return 0;
}
