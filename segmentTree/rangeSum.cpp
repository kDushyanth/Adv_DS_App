#include<bits/stdc++.h>
using namespace std;
int fill(int *seg_tree,int arr[],int n,int left,int right,int curr_idx){
    if(left>right)return 0;
    if(left==right){
        seg_tree[curr_idx] = arr[left];
        return seg_tree[curr_idx];
    }
    int mid = (left+right)/2;
    seg_tree[curr_idx] = fill(seg_tree,arr,n,left,mid,2*curr_idx+1)+
                         fill(seg_tree,arr,n,mid+1,right,2*curr_idx+2);
    return seg_tree[curr_idx];
}
int *construct(int arr[],int n){
    int t = pow(2,ceil(log2(n)));
    int length = 2*t-1;
    /*
    int* x = new int[5];          // gv gv gv gv gv (gv - garbage value)
    int* x = new int[5]();        // 0  0  0  0  0 
    int* x = new int[5]{};        // 0  0  0  0  0  (Modern C++)
    int* x = new int[5]{1,2,3};   // 1  2  3  0  0  (Modern C++)
    */
    int *seg_tree = new int[length]{};
    fill(seg_tree,arr,n,0,n-1,0);
    /*
    DEBUG*/
    for(int i=0;i<length;i++)cout<<seg_tree[i]<<" ";
    cout<<endl;
    
    return seg_tree;
}
int rangeSum(int *seg_tree,int arr[],int n,int left,int right,int left_range,int right_range,int curr_idx){
    if(left_range>right || right_range<left)return 0;
    if(left_range<=left && right_range>=right)return seg_tree[curr_idx];
    int mid = (left+right)/2;
    
    return rangeSum(seg_tree,arr,n,left,mid,left_range,right_range,2*curr_idx+1)+
           rangeSum(seg_tree,arr,n,mid+1,right,left_range,right_range,2*curr_idx+2);
}
int main(){
    int n;cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];
    int *seg_tree = construct(arr,n);
    int Q;cin>>Q;
    while(Q--){
        int l,r;
        cin>>l>>r;
        cout<<rangeSum(seg_tree,arr,n,0,n-1,l,r,0)<<endl;
    }
}
/*
All levels of the segment tree will be completely filled except the last level. Also, the tree will be a Full Binary Tree.
FBT => n leaves + n-1 internal_nodes = 2*n-1 nodes
Time Complexity:
Tree construction is O(n).
Query is O(Logn). To query a sum, we process at most four nodes at every level and number of levels is O(Logn). 
Update is also O(Logn). To update a leaf value, we process one node at every level and number of levels is O(Logn).
size of segment tree array: (2*(2^⌈logn⌉))  – 1.
*/