class Solution {
public:
    /*
     * @param strs: a list of strings
     * @return: encodes a list of strings to a single string.
     */
    string encode(vector<string> &strs) {
        // write your code here
        vector<char> res;
        int len = strs.size();
        for(int i=0;i<len;i++) {
            for(char c: strs[i]) {
                if (c != '|' ) {
                    res.push_back(c);
                } else {
                    res.push_back('|');
                    res.push_back(c);
                }
            }
            if (i<len-1) {
                res.push_back('|');
                res.push_back(':');
            }
        }
        
        string sres(res.begin(),res.end());
        return sres;
    }

    /*
     * @param str: A string
     * @return: dcodes a single string to a list of strings
     */
    vector<string> decode(string &str) {
        // write your code here
        vector<string> res;
        vector<char> word;
        cout << "str " << str;
        int len = str.length();
        char ch;
        int i=0;
        while(i<len) {
            if (str[i] != '|') {
                word.push_back(str[i]);
                i++;
            } else if(str[i] == '|'  && str[i+1] == '|') {
                word.push_back(str[i]);
                i=i+2;
            } else {
                string s(word.begin(),word.end());
                cout << "word : " << s;
                res.push_back(s);
                word.clear();
                i=i+2;
            }
        }
        
        string s(word.begin(),word.end());
        res.push_back(s);

        return res;
    }
};