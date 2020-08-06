/**
* t=x
* nt=t+a 
* t=x+a
* nt=(t-x)b+x == x+ab
* t=x+ab
* nt=(t-x)c+x=x+abc
*/

typedef long long int LL;
class Solution {
public:
    vector<char> op;
    LL calc(LL a, LL b, char ch) {
        if (ch=='+') {
            return a+b;
        } 
        if (ch=='-') {
            return a-b;
        }
        
        if (ch=='*') {
            return a*b;
        }
        
        return 0;
    }

    void bk(string& num,int target,vector<string>& res,int p,vector<string>& ev, LL t, LL prev, char pch) {
        int len = num.length();
        int c = len-p;
        LL nprev,nt,b,a;
        string ns;
        
        if (pch == '+' || pch == '-') {
            nprev=t;
            a=t;
        } else if (pch == '*') {
            nprev=prev;
            a=t-prev;
        } else {
            nprev=0;
        }
        
        auto upDate = [&]() {
            if (pch == '+' || pch == '-') {
                nt = calc(a,b,pch);
            } else if (pch == '*') {
                nt=calc(a,b,pch)+prev;
            } else {
                nt=b;
            }
        };

        for(int i=1;i<c;i++) {
            if(i==2 && num.at(p) == '0') {
               return;
            }
            ns = num.substr(p,i);
            b = stoll(ns);
            upDate();
            ev.push_back(ns);
            for(char ch: op) {
                string sch(1,ch);
                ev.push_back(sch);
                bk(num,target,res,p+i,ev,nt,nprev,ch);
                ev.pop_back();
            }
            ev.pop_back();
        }
        
        if(c>1 && num.at(p) == '0') {
            return;
        }
        
        ns = num.substr(p,c);
        b = stoll(ns);
        upDate();
        ev.push_back(ns);
        if (target == nt) {
            ns="";
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
            bk(num,target,res,0,ev,0,0,'$');
        }
        return res;
    }
};
