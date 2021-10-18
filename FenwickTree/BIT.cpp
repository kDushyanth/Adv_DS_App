/*Binary Indexed Tree or Fenwick Tree
We have an array arr[0 . . . n-1]. We would like to 
1 Compute the sum of the first i elements. 
2 Modify the value of a specified element of the array arr[i] = x where 0 <= i <= n-1.*/
//In this case: Compared with Segment Tree, Binary Indexed Tree requires less space and is easier to implement
//update and the query operation in O(log(N))
//best resource:https://www.youtube.com/watch?v=BHPez138yX8
#include<bits/stdc++.h>
using namespace std;
void update(int *BITree,int val,int n,int idx){
    int curr_idx = idx+1;
    while(curr_idx<=n){
        BITree[curr_idx]+=val;
        //propagate upward
        curr_idx+=curr_idx & (-curr_idx);
    }
}
int *construct(int arr[],int n){
    int *BITree = new int[n+1]{};
    //BITree[0] is dummy node
    for(int i=0;i<n;i++){
        update(BITree,arr[i],n,i);
    }
    return BITree;
}
int getSum(int *BITree,int idx){
    int curr_idx = idx+1;
    int sum=0;
    while(curr_idx){
        sum+=BITree[curr_idx];
        //accumulate by moving down
        curr_idx -= (curr_idx)&(-curr_idx);
    }
    return sum;
}
int main(){
    int n;cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];
    int *BITree = construct(arr,n);
    cout<<"#Queries:";
    int Q;cin>>Q;
    cout<<"0:prefix sum 1:update\n";
    while(Q--){
        int idx,val,r,op;
        cin>>op;
        switch (op)
        {
        case 0: cin>>idx;cout<<getSum(BITree,idx)<<endl;
                break;
        case 1: cin>>idx>>val;update(BITree,-arr[idx]+val,n,idx);
                break;
        default: cout<<"done\n";exit(0);
        }
    }
}
/*
TIme complexity:
construction: O(nlogn) since update called on n elements.
update: O(logn)
get sum: O(logn)
*/