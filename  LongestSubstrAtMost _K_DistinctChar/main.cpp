class Solution {
public:
    /**
     * @param s: A string
     * @param k: An integer
     * @return: An integer
     */
    int lengthOfLongestSubstringKDistinct(string &s, int k) {
        // write your code here
        int res=0;
        int l=0;
        unordered_map<char,int> freq;
        int count=0;
        int len = s.length();
        char ch;
        for(int i=0;i<len;i++) {
            ch = s[i];
            if (freq.find(ch) == freq.end() || freq[ch]==0) {
                freq[ch]=1;
                count++;
                if (count>k) {
                    while(l<=i && --freq[s[l++]]>0);
                    count--;
                }
            } else {
                freq[ch]++;
            }
            if (l<=i) {
                res = max(i-l+1,res);
            }
        }
        return res;
    }
};