// Time Complexity : O(N*K*N)
class Solution {
public:
    int superEggDrop(int K, int N) {
        if (K==1) {
            return N;
        }
        if (N==1) {
            return 1;
        }
        if (K==0) {
            return 0;
        }
        vector<vector<int>> dp(K+1,vector<int>(N+1,0));
        
        for(int i=1;i<=N;i++) {
            dp[1][i]=i;
        }
        
        for(int i=1;i<=K;i++) {
            dp[i][1]=1;
        }
        
        int t;
        for(int i=2;i<=K;i++) {
            for(int j=2;j<=N;j++) {
                t=INT_MAX;
                for(int k=1;k<=j;k++) {
                    t = min(t,max(dp[i][j-k],dp[i-1][k-1]));
                }
                dp[i][j]=1+t;
            }
        }
        
        return dp[K][N];
    }
};
