typedef pair<int,int> pii;//pair of <int,int>
class LRUCache
{
    private:
       int max_cap;
       unordered_map<int,list<pii>::iterator> mp;//key -> iterator
       list<pii> lst;//(key,value) pairs list, rear: LRU
    public:
    //Constructor for initializing the cache capacity with the given value.
    LRUCache(int cap)
    {
        // code here
        max_cap = cap;
    }
    
    //Function to return value corresponding to the key.
    int get(int key)
    {
        if(mp.find(key)==mp.end())return -1;//key not in map
        auto itr = mp[key];
        pii curr = *itr;
        lst.erase(itr);//remove 
        lst.push_front(curr);//append at front, LRU
        mp[key] = lst.begin();//update map
        return curr.second;
    }
    
    //Function for storing key-value pair.
    void set(int key, int value)
    {
        // your code here   
        if(mp.find(key)==mp.end()){//key not found
            if(mp.size()==max_cap){//cache max_cap reached
                int del_key = lst.back().first;//requires key to delete the LRU entry
                auto itr = mp[del_key];//get itr
                lst.erase(itr);//remove LRU item
                mp.erase(del_key);
                lst.push_front({key,value});
                mp[key] = lst.begin();
            }else{//has space in cache
                lst.push_front({key,value});
                mp[key] = lst.begin();
            }
        }else{// entry in already cache => update and rearrange for LRU
            auto itr = mp[key];
            pii curr = *itr;
            curr.second = value;
            lst.erase(itr);
            lst.push_front(curr);
            mp[key] = lst.begin();//update map
        }
    }
};
