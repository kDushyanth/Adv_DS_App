#include<bits/stdc++.h>
using namespace std;
//curr_idx in the seg_tree holds the sum of arr elements in range: [left,right]
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
    int length = 2*t-1;// length of segment tree
    /*
    int* x = new int[5];          // gv gv gv gv gv (gv - garbage value)
    int* x = new int[5]();        // 0  0  0  0  0 
    int* x = new int[5]{};        // 0  0  0  0  0  (Modern C++)
    int* x = new int[5]{1,2,3};   // 1  2  3  0  0  (Modern C++)
    */
    int *seg_tree = new int[length]{};
    fill(seg_tree,arr,n,0,n-1,0);// populate the segment tree
    /*
    DEBUG*/
    for(int i=0;i<length;i++)cout<<seg_tree[i]<<" ";
    cout<<endl;
    
    return seg_tree;
}
//find the sum of elements in range [left_range,right_range] in arr.
//[left,right]: current range covered by node (denoted by curr_idx) in seg_tree.
int rangeSum(int *seg_tree,int arr[],int n,int left,int right,int left_range,int right_range,int curr_idx){
    if(left_range>right || right_range<left)return 0;//no overlap
    if(left_range<=left && right_range>=right)return seg_tree[curr_idx];//total overlap
    int mid = (left+right)/2;
    //partial overlap
    return rangeSum(seg_tree,arr,n,left,mid,left_range,right_range,2*curr_idx+1)+
           rangeSum(seg_tree,arr,n,mid+1,right,left_range,right_range,2*curr_idx+2);
}
//update the 'update_idx' of arr by 'diff';
void update(int *seg_tree,int arr[],int n,int update_idx,int diff,int left,int right,int curr_idx){
    if(update_idx <left || update_idx > right)return;//no overlap
    if(left==right){
        seg_tree[curr_idx]+=diff;
        return;
    }
    int mid = (left+right)/2;
    seg_tree[curr_idx]+=diff;
    update(seg_tree,arr,n,update_idx,diff,left,mid,2*curr_idx+1);
    update(seg_tree,arr,n,update_idx,diff,mid+1,right,2*curr_idx+2);
}
int main(){
    int n;cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];
    //use segment tree when there are alomost same number of update and range Queries; update: arr[i] = new_value.
    int *seg_tree = construct(arr,n);
    int Q;cin>>Q;
    cout<<"0:range sum & 1:update\n";
    while(Q--){//Queries
        int op;cin>>op;
        int l,r,idx,val;
        switch (op)
        {
        case 0: cin>>l>>r;//rangeSUM
                cout<<rangeSum(seg_tree,arr,n,0,n-1,l,r,0)<<endl;
                break;
        case 1: cin>>idx>>val;//update idx with val
                arr[idx] = val;
                update(seg_tree,arr,n,idx,val-arr[idx],0,n-1,0);
                break;
        default:cout<<"done";exit(0);//exited without error
                break;
        }
        //cout<<rangeSum(seg_tree,arr,n,0,n-1,l,r,0)<<endl;
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