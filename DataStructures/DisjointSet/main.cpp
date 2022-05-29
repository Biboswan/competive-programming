class Disjoint
{
public:
    vector<int> parent, rank;
    Disjoint(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }

        parent[x] = find(parent[x]);
        return parent[x];
    }

    void UnionF(int x, int y)
    {
        int idx = find(x);
        int idy = find(y);
        if (idx == idy)
        {
            return;
        }

        if (rank[idx] > rank[idy])
        {
            parent[idy] = idx;
        }
        else if (rank[idx] < rank[idy])
        {
            parent[idx] = idy;
        }
        else
        {
            rank[idx]++;
            parent[idy] = idx;
        }
    }
};
