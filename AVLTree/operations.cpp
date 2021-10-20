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
    /*You are required to complete this method */
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
};
