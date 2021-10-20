struct Node
{
	int data, height;
	Node *left, *right;
	Node(int x)
	{
		data = x;
		height = 1;
		left = right = NULL;
	}
};
class Solution{
  public:
    //height of current node
    int get_height(Node *root){
        if(root==NULL)return 0;
        return root->height;
    }
    Node *left_rotation(Node *node){
        Node *rl = node->right->left;
        Node *root = node->right;
        root->left = node;
        node->right = rl;
        node->height = 1+max(get_height(node->right),get_height(node->left));
        root->height = 1+max(get_height(root->right),get_height(root->left));
        return root;
    }
    Node *right_rotation(Node *node){
        Node *lr = node->left->right;
        Node *root = node->left;
        root->right = node;
        node->left = lr;
        node->height = 1+max(get_height(node->left),get_height(node->right));
        root->height = 1+max(get_height(root->left),get_height(root->right));
        return root;
    }
    /*
    1. insert new element like in BST
    2. get height and balance factor for ancestors (by recursion)
    3. fix the first unbalanced node => the tree is now an AVL tree
    */
    Node* insertToAVL(Node* node, int data)
    {
        if(node==NULL)return new Node(data);
        if(node->data>data) node->left = insertToAVL(node->left,data);
        else if(node->data<data)node->right = insertToAVL(node->right,data);
        else return node;//does not insert dup node
        node->height = 1+max(get_height(node->left),get_height(node->right));//update curr_height
        int balance_factor = (get_height(node->left)-get_height(node->right));
        if(balance_factor<=1 && balance_factor>=-1)return node;//balanced node
        if(balance_factor==2){
            Node *left = node->left;
            int balance_factor_left = (get_height(left->left)-get_height(left->right)); 
            if(balance_factor_left==1)return right_rotation(node);
            else{
                node->left = left_rotation(left);
                return right_rotation(node);
            }
        }else if(balance_factor==-2){
            Node *right = node->right;
            int balance_factor_right = (get_height(right->left)-get_height(right->right)); 
            if(balance_factor_right==-1)return left_rotation(node);
            else{
                node->right = right_rotation(right);
                return left_rotation(node);
            }
        }
        
    }
    /*
    1. delete the element like in BST
    2. get height and balance factor for ancestors (by recursion)
    3. fix all unbalanced nodes unlike in insertion
    */
    Node* deleteNode(Node* root, int data){
      if(root==NULL)return NULL;
      if(root->data < data)root->right = deleteNode(root->right,data);
      else if(root->data > data)root->left = deleteNode(root->left,data);
      else{//root->data==data
          if(root->left && root->right){//replace with inorder successor
              Node *temp = root->right;
              while(temp->left)temp = temp->left;
              root->data = temp->data;
              root->right = deleteNode(root->right,temp->data);
          }else{
              Node *temp = root->left? root->left:root->right;
              delete root;
              root = temp;
          }
      }
      if(root==NULL)return root;
      root->height = 1+ max(get_height(root->left),get_height(root->right));
      int balance_factor = get_height(root->left) - get_height(root->right);
      if(balance_factor>=-1 && balance_factor<=1)return root;//balanced node
      if(balance_factor==-2){
          Node *right = root->right;
          int right_balance_factor = get_height(right->left) - get_height(right->right);
          if(right_balance_factor==1)root->right = right_rotation(right);
          return left_rotation(root);
      }else{
          Node *left = root->left;
          int left_balance_factor = get_height(left->left) - get_height(left->right);
          if(left_balance_factor==-1)root->left = left_rotation(left);
          return right_rotation(root);
      }
  }
};
