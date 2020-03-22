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
int myAtoi(string str) {
    long long res = 0;
    int len = str.size();
    bool firstsign = true;
    int  sign = 1;
    for(int i = 0;i < len;i ++){
        if(firstsign == true && str[i] == ' '){
            continue;
        }
        else if(firstsign == true && (str[i] == '-' || str[i] == '+')){
            firstsign = false;
            if(str[i] == '-'){
                sign = -1;
            }
            
        }
        else if(str[i] >= '0' && str[i] <= '9'){
            if(firstsign == true)
            {
                firstsign = false;
            }
            res = res * 10 + (str[i] - '0');
            if(res * sign > INT_MAX)
                return INT_MAX;
            if(res * sign < INT_MIN)
                return INT_MIN;
        }
        else
            return res * sign;
    }
    res = res * sign;
    if(res > INT_MAX){
        res = INT_MAX;
    }
    if(res < INT_MIN){
        res = INT_MIN;
    }
    return res;
}
bool isMatch(string s, string p) {
    int m = s.size(),n = p.size();
    vector<vector<bool>> dp(m + 1,vector<bool>(n+1,false));
    dp[0][0] = true;
    for(int i = 0; i <= m; i ++){
        for(int j = 1; j <= n; j++){
            if(p[j-1] == '*'){
                dp[i][j] = dp[i][j - 2] ||
                (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
            }
            else{
                dp[i][j] = i && dp[i - 1][j - 1] &&
                (s[i - 1] == p[j - 1] || p[j - 1] == '.');
            }
        }
    }
    return dp[m][n];
    /* special condition for dp[i-1][j] = false
      123456
      adacbbc
      adc*c
        i = 4,j=4;
     */

}
int maxArea(vector<int>& height) {
    int maxarea = 0;
    for(int i = 0; i < height.size(); i ++){
        for(int j = i + 1; j < height.size();j ++){
            int temp = (height[i] < height[j] ? height[i] : height[j])*(j -i);
            maxarea = maxarea > temp ? maxarea : temp;
        }
    }
    return maxarea;
}
int romanToInt(string s) {
    int n = s.length();
    if(n == 0) return 0;
    map<char,int> mp;
    mp.insert(pair<char, int>('I',1));
    mp.insert(pair<char,int>('V',5));
    mp.insert(pair<char, int>('X',10));
    mp.insert(pair<char,int>('L',50));
    mp.insert(pair<char,int>('C',100));
    mp.insert(pair<char, int>('D',500));
    mp.insert(pair<char, int>('M',1000));
    int res = 0;
    int index = n - 1;
    while(index >= 0){
        int t = mp.find(s[index])->second;
        res += t;
        if(index != 0){ //judge next
            int next = mp.find(s[index - 1]) -> second;
            if(next < t){
                res -= next;
                index --;
            }
        }
        index --;
    }
    return res;
}
string longestCommonPrefix(vector<string>& strs) {
    int len = strs.size();
    if(len == 0)
        return "";
    string prefix = strs[0];
    for(int i = 1; i < len; i ++){
        while(strs[i].find(prefix) != 0){
            prefix = prefix.substr(0,prefix.size() - 1);
        }
        if(prefix.size() == 0)
            return "";
    }
    return prefix;
}
vector<vector<int>> threeSum(vector<int>& nums) {
    int len = nums.size();
    vector<vector<int>> rs;
    if(len == 0)
        return rs;
    sort(nums.begin(),nums.end());
    for(int i = 0; i < len; i ++){
        if(i != 0 && nums[i] == nums[i - 1]){
           continue;//去重 if-continue去重比while循环简单，不用判断下标
        }
        int j = i + 1, k = len - 1;
        while(j < k){
            if(nums[i] + nums[j] + nums[k] == 0){
                rs.push_back({nums[i],nums[j],nums[k]});
                j ++;
                k --;
                while(j < k && nums[j] == nums[j - 1]){//j < k可保证三元组&&数组下标
                    j ++;
                }
                while(j < k && nums[k] == nums[k + 1]){
                    k --;
                }
            }
            else if(nums[i] + nums[j] + nums[k] > 0){
                k --;
            }
            else{
                j ++;
            }
        }

    }
    return rs;
}
//map<char,string> mp;

vector<string> vec;
void getlettercombination(string digits,string str,int n,int cur){
    string table[] = {"","","abc","def","ghi","jkl","mno",
    "pqrs","tuv","wxyz"};
    string t = table[digits[cur] - '0'];
    if(cur == n - 1)
       {//做最后处理，同时加入vec；
           
           for(int i = 0; i < t.size(); i ++){
               vec.push_back(str + t[i]);
           }
       }
    else{
        for(int i = 0; i < t.size(); i ++){
            getlettercombination(digits, str + t[i], n, cur + 1);
        }
    }
}
vector<string> letterCombinations(string digits) {
    int len = digits.size();
    if( len == 0)
        return vec;
    getlettercombination(digits, "", len, 0);
    return vec;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if( head -> next == NULL && n == 1){
        return NULL;
    }
    ListNode* p = head;
    ListNode* q = head;
    while(-- n>= 0){
        p = p -> next;
        if(p == NULL)
            p = head;
    }
    printf("P:%d\n",p -> val);
    while(p ->next != NULL){
        p = p -> next;
        q = q -> next;
    }
     printf("q:%d\n",q -> val);
    if(q -> next == NULL){
        head = head -> next;
    }
    else{
        q -> next = q ->next -> next;
    }
    return head;
}
bool isValid(string s) {
    int len = s.size();
    if(len == 0)
        return true;
    stack<char> sp;
    for(int i = 0;i < len;i++){
        if(s[i] == '('|| s[i] == '[' || s[i] == '{'){//进栈
            sp.push(s[i]);
        }
        else{//出栈
            if(sp.empty() == true)
                return false;
            char c = sp.top();
            sp.pop();
            switch (s[i]) {
                case ')':
                    if(c == '(')
                     break;
                    else
                        return false;
                case ']':
                    if(c == '[')
                        break;
                    else
                        return false;
                case '}':
                    if(c == '{')
                        break;
                    else
                        return false;
            }
        }
    }
    if(sp.empty() == true)
        return true;
    else
        return false;
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* h;
    ListNode* r;
    if(l1 == NULL && l2 == NULL)
        return NULL;
    if(l1 == NULL)
        return  l2;
    if(l2 == NULL)
        return l1;
    if(l1 -> val < l2 -> val){//不带头链表，先确定头指针，再确定遍历的指针.
        h = l1;
        r = h;
        l1 = l1 -> next;
    }
    else{
        h = l2;
        r = h;
        l2 = l2 -> next;
    }
    while(l1 != NULL && l2 != NULL){
        if(l1 -> val < l2 -> val){
            r -> next = l1;
            r = r -> next;
            l1 = l1 -> next;
        }
        else{
            r -> next = l2;
            r = r -> next;
            l2 = l2 -> next;
        }
    }
    r -> next = l1 ? l1 : l2;
    return h;
 }
#define INF 0x7fffffff
int main(int argc, const char * argv[]) {
    ListNode *l;
    ListNode* *node = &l;
    (*node) = new ListNode(1);
    node = &((*node) -> next);
    (*node) = new ListNode(2);
    node = &((*node) -> next);
    (*node) = new ListNode(4);
    node = &((*node) -> next);
    (*node) = new ListNode(7);
    node = &((*node) -> next);
    ListNode *l2;
    node = &l2;
    (*node) = new ListNode(1);
    node = &((*node) -> next);
    (*node) = new ListNode(3);
    node = &((*node) -> next);
    (*node) = new ListNode(4);
    node = &((*node) -> next);

    ListNode *res = mergeTwoLists(l,l2);
    while(res != NULL){
        printf("%d\n",res -> val);
        res = res -> next;
    }
    printf("hello lemon\n");
    return 0;
}
