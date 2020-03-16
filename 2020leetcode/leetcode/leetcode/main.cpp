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
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(),n = nums2.size();
    //采用二分法
    if(m > n){  //保证nums1 <= nums2，通过nums1下标来找nums2下标,若nums1 > nums2,计算出的nums2下标可能为负数
        vector<int> temp = nums1;
        nums1 = nums2;
        nums2 = temp;
        int templ = m;
        m = n;
        n = templ;
    }
    /*
     遍历nums1来寻找i，j=halflen-i,i,j分别把 nums1,nums分成左右两部分，
     nums1[0]..nums1[i-1],nums1[i]..nums1[m - 1]和 nums2[0]..nums2[j - 1],nums[j]..num[n - 1]，其中nums1左+nums2左 = nums2右+nums右(+1) 奇数时左>右
     寻找满足A[i - 1] < B[j] && B[j - 1] < A[j]
     当 n + m = 偶数时，此时 i + j = m - i + n - j;即  j = (m+n)/2-i
     当 n + m = 奇数时，设左部分>右部分,则有 i + j - 1 = m - i + n - j;即j=(m+n+1)/2-i
     当m+n=偶数时，(m+n)/2=(m+n+1)/2，故halflen = （m+n+1)/2
     */
    int iMin = 0,iMax = m,halflen = (m + n + 1) / 2;
    while(iMin <= iMax){
        int i = (iMin + iMax) / 2;
        int j = halflen - i;
        if(i > iMin && nums1[i - 1] > nums2[j]){//先要检验下标合法性&&左1max>右2min
            iMax = iMax - 1;//要把i变小
        }
        else if(i < iMax && nums1[i] < nums2[j-1]){//下标合法&&左2max>右1min
            iMin = iMin + 1;
        }
        else{//i match(1)左1max<右2min && 左2min<右1max (2)special condition
            //printf("i:%d j:%d m:%d n:%d halflen=%d\n",i,j,m,n,halflen);
            int maxleft;//若为n+m 为odd,直接返回
            if(i == 0){
                maxleft = nums2[j - 1];//左1为空
            }
            else if(j == 0){
                maxleft = nums1[i - 1];//左2为空
            }
                else{
                    maxleft = nums1[i - 1] > nums2[j - 1]? nums1[i - 1]: nums2[j - 1];
                }
            if((n + m) % 2 == 1){
                return maxleft;
            }
            int minright;//n+m为even,return(maxleft+minright)/2.0
            if(i == m){
                minright = nums2[j];//右1为空
            }
            else if(j == n){
                minright = nums1[i]; //右2为空
            }
                else{
                    minright = nums1[i] < nums2[j] ? nums1[i] : nums2[j];
                }
            return (maxleft + minright)/2.0;
        }
    }
    return 0.0;
}
string longestPalindrome(string s){
    int len = s.length();
    int max = 0,ibegin = 0,iend = 0;
    bool flag[len][len];//flag[i][j]记录从str从i到j是否是回文序列.a
    /* str[i] == str[j] && flag[i+1][j-1]==true,则flag[i][j]也为回文序列,故i递减遍历，j递增遍历*/
    for(int i = 0;i < len;i ++){
        for(int j = 0;j < len;j ++){
            flag[i][j] = false;
        }
    }
    for(int i = len - 1;i >= 0;i --){
        for(int j = i;j < len;j ++){
            if(s[i] == s[j] && (j-i <=2 || flag[i+1][j-1] == true)){
                flag[i][j] = true;
                if(j- i >= max){
                    max = j - i + 1;
                    ibegin = i;
                    iend = j;
                }
            }
        }
    }
    return s.substr(ibegin,max);
}
string convert(string s, int numRows) {
    if(numRows == 1)
        return s;
    string res;
    int len = s.size();
    int cur = 2* numRows - 2;
    for(int i = 0;i < numRows; i ++){
        for(int j = 0;i + j < len;j = j + cur){
            res +=s[j+i];
            if(i != 0 && i != numRows - 1 && cur + j - i < len){
                res += s[cur+j-i];
            }
        }
    }
    return res;
}
int reverse(int x){
    long long res = 0;
    while(x != 0){
        res = 10 * res + x % 10;
        x /= 10;
    }
    return (res > INT_MAX || res < INT_MIN) ? 0 : res;
}
#define INF 0x7fffffff
int main(int argc, const char * argv[]) {
    int num;
    while(scanf("%d",&num) != EOF){
        int res = reverse(num);
        printf("%d\n",res);
    }
    printf("lemon\n");
    /*
    0123456789 10 11 12 13
    PAYPALISHI R  I  N  G
    P     I     N
    A   L S   I G
    Y A   H R
    P     I
     */
    return 0;
}
