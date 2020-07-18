class Solution {
public:
    /**
     * @param N: an integer
     * @return: return an integer
     */
    int maxA(int N) {
        // write your code here

        if (N<7) {
            return N;
        }
        vector<int> dp(N+1,0);
        for(int i=0;i<=6;i++) {
            dp[i]=i;
        }
        
        int cur=0;
        for(int i=7;i<=N;i++) {
            dp[i] = i;
            for(int j=1;j<=i-3;j++) {
                cur = dp[j]*(i-j-1);
                dp[i]=max(dp[i],cur);
            }
            
        }

        return dp[N];
        
    }
};

//dp[i] = max({dp[i-3]*2, dp[i-4]*3,dp[i-5]*4});   O(n) solution