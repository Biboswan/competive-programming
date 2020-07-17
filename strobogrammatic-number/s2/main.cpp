typedef pair<char,char> mp;
class Solution {
public:
    /**
     * @param n: the length of strobogrammatic number
     * @return: All strobogrammatic numbers
     */
    void buildNum(vector<mp>& mir, vector<string>& res,vector<char>& sch,int l,int h) {
        if (l==h) {
            vector<int> nums {'0','1','8'};
            for(int i : nums) {
                sch[l]=i;
                string s(sch.begin(),sch.end());
                res.push_back(s);
            }
            return;
        }
    
        if (l>h) {
            string s(sch.begin(),sch.end());
            res.push_back(s);
            return;
        }
    
        mp p;
        for (int i=0;i<mir.size();i++) {
            p = mir[i];
            sch[l]=p.first;
            sch[h]=p.second;
            buildNum(mir,res,sch,l+1,h-1);
        }
    }
    
    vector<string> findStrobogrammatic(int n) {
        // write your code here
        if (n==0) {
            return {""};
        }
        
        if (n==1) {
            return {"0","1","8"};
        }
        vector<string> res;
        vector<char> sch(n);
        mp p;
        vector<mp> mir{{'0','0'},{'1','1'},{'6','9'},{'8','8'},{'9','6'}};
        for (int i=1;i<mir.size();i++) {
            p = mir[i];
            sch[0]=p.first;
            sch[n-1]=p.second;
            buildNum(mir,res,sch,1,n-2);
        }
        return res;
    }
};
