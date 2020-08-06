//Space: O(K)
//Time: O(M*K) (M is no. of moves i.e answer)M <=N therefore O(N*k))
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
        
        vector<int> A(K+1,1);
        A[0]=0;
        vector<int> B(K+1,0);
        
        int res=1;
        while(true) {
            res++;
            for(int i=1;i<=K;i++) {
                B[i]=1+A[i-1]+A[i];
                if (B[i] >=N) {
                    return res;
                }
            }
            swap(A,B);
        }
    }
};
