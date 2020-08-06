class Solution {
public:
    vector<char> op;
    int calc(vector<string>& ev) {
        int t=0;
        stack<int> st;
        stack<char> ops;
        int size = ev.size();
        
        auto isOper = [&](int p) -> bool {
         return  ev[p]=="+" || ev[p]=="-" || ev[p]=="*" || ev[p] == "$";    
        };

        auto pred = [&](char ch) -> int {
            if (ch=='*') {
                return 1;
            }
            
            if (ch=='$') {
                return -1;
            }

            return 0;
        };
        
        auto evalu = [&](int x, int y, char ch) -> int {
            if (ch=='+') {
                return x+y;
            }
            
            if (ch=='-') {
                return x-y;
            }
            
            return x*y;
        };

       // Nice trick 
        ev.push_back("$");
        for(int i=0;i<=size;i++) {
            if (!isOper(i)) {
                st.push(stoi(ev[i]));
            } else {
                char ch = ev[i][0];
                while(!ops.empty() && pred(ops.top())>=pred(ch)) {
                    int b = st.top();
                    st.pop();
                    int a = st.top();
                    st.pop();
                    char o = ops.top();
                    ops.pop();
                    int r = evalu(a,b,o);
                    st.push(r);
                }
                ops.push(ch);
            }
        }
        
        ev.pop_back();
        return st.top();
    }

    void bk(string& num,int target,vector<string>& res,int p,vector<string>& ev) {
        int len = num.length();
        int c = len-p;
        for(int i=1;i<c;i++) {
            if(i==2 && num.at(p) == '0') {
               return;
            }
            ev.push_back(num.substr(p,i));
            for(char ch: op) {
                string sch(1,ch);
                ev.push_back(sch);
                bk(num,target,res,p+i,ev);
                ev.pop_back();
            }
            ev.pop_back();
        }
        
        if(c>1 && num.at(p) == '0') {
            return;
        }
        ev.push_back(num.substr(p,c));
        if (target == calc(ev)) {
            string ns;
            for (auto const& s : ev) { ns += s; }
            res.push_back(ns);
        }

        ev.pop_back();
    }

    vector<string> addOperators(string num, int target) {
        vector<string> res;
        if (num!="") {
            vector<string> ev;
            op = {'+','-','*'};
            bk(num,target,res,0,ev);
        }
        return res;
    }
};