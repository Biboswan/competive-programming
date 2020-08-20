/**
Few things to keep in mind 
Reseting maxima when a new minima arises which is lesser than less than prev minima
Points when there is zero slope, partial maxima or partial minima kinda (such terms may not exist) though :)
**/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n<2) {
            return 0;
        }
        int mn,mx=INT_MIN;
        
        if (prices[0]>prices[1]) {
            mn=INT_MAX;
        } else {
            mn=prices[0];
        }
        
        int res=0;
        
        for(int i=1;i<n;i++) {
            if (prices[i]>prices[i-1] && (i+1 == n || prices[i]>=prices[i+1]) && prices[i]>=mx) {
                mx=prices[i];
                res=max(res,mx-mn);
            } else if (prices[i]<prices[i-1] && (i+1==n || prices[i]<=prices[i+1]) && prices[i]<mn) {
                mn = prices[i];
                mx=INT_MIN;
            } else;
        }
        
        return res;
    }
};
