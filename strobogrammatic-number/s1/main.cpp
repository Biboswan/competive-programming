class Solution {
public:
    /**
     * @param num: a string
     * @return: true if a number is strobogrammatic or false
     */
    bool isStrobogrammatic(string &num) {
        // write your code here
        int h = num.length()-1;
        int l=0;
        while(l<=h) {
            if ((num[l] == '6' && num[h] == '9') || (num[l] == '9' && num[h] == '6' ) || (num[l] == '8' && num[h]=='8') || (num[l]=='1' && num[h]=='1') || (num[l]=='0' && num[h]=='0')) {
                l++;
                h--;
            } else {
                return false;
            }
        }
        return true;
    }
};
