void fill_lps(vector<int> &lps,string &ptrn){
        int length=0;
        for(int i=1;i<ptrn.size();i++){
            if(ptrn[length]==ptrn[i]){
                length++;
                lps[i] = length;
            }else{
                if(length!=0){
                    length = lps[length-1];
                    i--;
                }
            }
        }
}
int kmp(string txt, string ptrn) {
        vector<int> lps(ptrn.size(),0);
        fill_lps(lps,ptrn);
        int i=0,j=0;
        while(i<txt.size() && j<ptrn.size()){
            if(txt[i]==ptrn[j]){
                i++;j++;
            }
            if(j==ptrn.size()){ 
                cout<<"found at:"<<i-ptrn.size()<<endl;
                j = lps[j-1];
            }else if(i!=txt.size() && txt[i]!=ptrn[j]){
                if(j){
                    j = lps[j-1];
                }else i++;
            }
        }
        return -1;
}
