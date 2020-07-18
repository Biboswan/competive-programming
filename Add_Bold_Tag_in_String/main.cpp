typedef pair<int,int> mp;

bool comparator(mp& p1, mp & p2) {
    return p1.first < p2.first;
}

class Solution {
public:
    /**
     * @param s: a string
     * @param dict: a list of strings
     * @return: return a string
     */
    void kmp(string& p, vector<int>& pat)  {
        int len = p.length();
        pat.resize(len,0);
        int a=0;
        for(int i=1;i<len;i++) {
            while(a>0 && p[a] != p[i]) {
                a=pat[a-1];
            }
            if (p[i] == p[a]) {
                pat[i]=++a;
            }
        }
    }

    string addBoldTag(string &s, vector<string> &dict) {
        // write your code here
        int len = s.length();
        int n = dict.size();
        int dlen;
        vector<int> pat;
        vector<mp> inter;
        string ss;
        for (int i=0;i<n;i++) {
            dlen=dict[i].length();
            if (dlen>len) {
                continue;
            }
            kmp(dict[i],pat);
            ss=dict[i];
            int pos=0;
            for(int j=0;j<len;j++) {
                while(pos > 0 && s[j] != ss[pos]) {
                    pos = pat[pos-1];
                }
                if (s[j]==ss[pos]) {
                    pos++;
                    if (pos == dlen) {
                        inter.push_back({j-dlen+1,j});
                        pos=pat[pos-1];
                    }
                }
            }
            pat.clear();
        }
        
        sort(inter.begin(),inter.end(),comparator);
       
        int tot = inter.size();
        if (tot == 0) {
            return s;
        }
        stack<mp> st;
        mp t,prev;
        st.push(inter[0]);
        for(int i=1;i<tot;i++) {
            prev=st.top();
            t=inter[i];
            if (t.first-prev.second>1) {
                st.push(t);
            } else {
                mp t3 = {prev.first,max(t.second,prev.second)};
                st.pop();
                st.push(t3);
            }
        }
        
        vector<int> marks(len,0);
        string bo="<b>";
        string bc="</b>";
        while(!st.empty()) {
            t=st.top();
            st.pop();
            marks[t.first]=1;
            marks[t.second]=-1;
        }
        
        vector<char> res;
        for(int i=0;i<len;i++) {
            if (marks[i]==0) {
                res.push_back(s[i]);
            } else if (marks[i]==1) {
                res.push_back(bo[0]);
                res.push_back(bo[1]);
                res.push_back(bo[2]);
                res.push_back(s[i]);
            } else {
                res.push_back(s[i]);
                res.push_back(bc[0]);
                res.push_back(bc[1]);
                res.push_back(bc[2]);
                res.push_back(bc[3]);
            }
        }
        
        string sres(res.begin(),res.end());
        return sres;
        
        
    }
};
