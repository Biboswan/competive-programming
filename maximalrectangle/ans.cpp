class Solution {
public:
    
    int maxAreaHist(vector<int> h) {
         stack<int> rec;
         int i=0,top;
         int mxar=0,area;
         rec.push(i);
         h.push_back(0);
         i++;
         int size = h.size();
         while (i != size && !rec.empty()) {
           if (h[i] >= h[rec.top()]) {
             rec.push(i);
             i++;
           } else {
             top = rec.top();
             rec.pop();
             if (rec.empty()) {
               area = h[top] * i;
               rec.push(i);
               i++;
             } else {
               area = h[top] * (i - rec.top() - 1);
             }
             if (area > mxar) {
               mxar = area;
             }
           }
        }
        return mxar;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int r = matrix.size();
        if (r==0) {
            return 0;
        }
        
        int c = matrix[0].size();
        
        if (c==0) {
            return 0;
        }

        vector<int> dp(c,0);
        int res=0;
        
        for(int i=0;i<r;i++) {
            for(int j=0;j<c;j++) {
                if (matrix[i][j] == '1') {
                    dp[j]++;
                } else {
                    dp[j]=0;
                }
            }
            
            int area = maxAreaHist(dp);
            if (area > res) {
                res=area;
            }
        }

        return res;
    }
};