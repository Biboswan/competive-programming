class Solution {
public:
    void dfs(int v, vector<vector<int>>& adj,vector<bool>& visited,vector<int>& st,vector<int>& ed,vector<vector<int>>& res,int& time, int par) {
        visited[v]=true;
        st[v]=++time;
        ed[v]=st[v];
        for(int c: adj[v]) {
            if (visited[c]==false) {
                dfs(c,adj,visited,st,ed,res,time,v);
            }
            if (c!=par) {
                int t = ed[c];
                ed[v]=min(ed[c],ed[v]);
                if (t>st[v]) {
                    vector<int> p;
                    p.push_back(v);
                    p.push_back(c);
                    res.emplace_back(p);
                }
            }
        }
        
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> res;
        vector<vector<int>> adj(n);
        if (n==2) {
            return {{0,1}};
        }

        int e = connections.size();
        for(int i=0;i<e;i++) {
            int x = connections[i][0];
            int y = connections[i][1];
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        
        vector<bool> visited(n,false);
        vector<int> st(n,0);
        vector<int> ed(n);
        int time=0;
                
        dfs(0,adj,visited,st,ed,res,time,0);
        
        return res;
    }
};
