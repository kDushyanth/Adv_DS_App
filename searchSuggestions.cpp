//TrieNode structure
//https://leetcode.com/problems/search-suggestions-system/
class TrieNode{
    public:
        bool isEnd;
        TrieNode *child[26];
        //2 overloaded constructors
        TrieNode(bool isEnd){
            this->isEnd = isEnd;
            for(int i=0;i<26;i++){
                (this->child)[i] = NULL;
            }
        }
        TrieNode(){
            isEnd = false;
            for(int i=0;i<26;i++){
                (this->child)[i] = NULL;
            }
        }
};
class Trie{
    public:
        TrieNode *root;
        void insert(string &str){
            TrieNode *curr = root;
            for(int i=0;i<str.length();i++){
                if(curr->child[str[i]-'a']==NULL){
                    curr->child[str[i]-'a'] = new TrieNode();
                    curr = curr->child[str[i]-'a'];
                }else{
                    curr = curr->child[str[i]-'a'];
                }
            }
            curr->isEnd = true;
        }
        //print TrieNode - preorder traversal
        void print(TrieNode *curr){
            if(curr==NULL)return;
            for(int i=0;i<26;i++){
                if(curr->child[i]){
                    cout<<((char)('a'+i));
                    print(curr->child[i]);
                }
            }
        }
        //constructor to create tree for list of strs.
        Trie(vector<string>&products){
            root = new TrieNode();
            for(string x:products){
                insert(x);//insert into Trie
            }
            TrieNode *curr = root;
            //verify
            //print(curr);
        }
        //Runs a DFS on trie starting with given prefix and adds all the words in the result, limiting result size to 3
        void dfs(vector<string> &temp,string word,TrieNode *curr){
            if(temp.size()==3)return;
            if(curr->isEnd){
                temp.push_back(word);
            }
            for(int i=0;i<26;i++){
                if(curr->child[i]){
                    word+=(char)('a'+i);
                    dfs(temp,word,curr->child[i]);
                    word.pop_back();
                }
            }
        }
        void suggestions(vector<vector<string>> &ans,vector<string> &products,string &searchWord){
            TrieNode *curr = root;
            string word = "";
            for(int i=0;i<searchWord.length();i++){
                if(curr->child[searchWord[i]-'a']==NULL){
                    //no suggestions => just add empty strings
                    while(i<searchWord.length()){
                        ans.push_back(vector<string>());i++;
                    }
                    continue;
                }
                curr = curr->child[searchWord[i]-'a'];
                word+=searchWord[i];
                vector<string> temp;
                dfs(temp,word,curr);
                ans.push_back(temp);
            }
        }
        
    
};
class Solution {
public:
    //at each entered char of 'serchWord' atmost 3 suggestions were displayed.
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> ans;
        Trie obj(products);
        obj.suggestions(ans,products,searchWord);
        return ans;
    }
};
