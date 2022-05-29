#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
vector<int> parent;
vector<int> heavy;
vector<int> depth;
vector<int> head;
vector<int> pos;
int curr_pos;
// Complete the solve function below.
void init(int n)
{
    parent.resize(n);
    heavy.resize(n, -1);
    depth.resize(n);
    head.resize(n);
    pos.resize(n);
    curr_pos = 0;
}

int dfs(vector<vector<int>> &adj, int p)
{
    int maxSize = 0;
    int size = 1;
    int ts;

    for (int c : adj[p])
    {
        if (c != parent[p])
        {
            parent[c] = p;
            depth[c] = depth[p] + 1;
            ts = dfs(adj, c);
            size += ts;
            if (ts > maxSize)
            {
                maxSize = ts;
                heavy[p] = c;
            }
        }
    }

    return size;
}

void decompose(int v, int h, vector<vector<int>> &adj)
{
    head[v] = h;
    pos[v] = curr_pos++;

    if (heavy[v] != -1)
    {
        decompose(heavy[v], h, adj);
    }

    for (int c : adj[v])
    {
        if (heavy[v] != c && parent[v] != c)
        {
            decompose(c, c, adj);
        }
    }
}

class SegmentTree
{
public:
    vector<int> segment;

    SegmentTree(int len)
    {
        double x = log2(len);
        if (x == int(x))
        {
            segment.resize((len << 1) - 1);
        }
        else
        {
            segment.resize(((int)pow(2, (int)x + 1) << 1) - 1);
        }
    }

    void update(int v, int ind, int pos, int low, int high)
    {
        if (low == high)
        {
            segment[pos] = v;
        }
        else
        {
            int mid = (low + high) >> 1;
            if (ind <= mid)
            {
                update(v, ind, (pos << 1) + 1, low, mid);
            }
            else
            {
                update(v, ind, (pos << 1) + 2, mid + 1, high);
            }
            segment[pos] = max(segment[(pos << 1) + 1], segment[(pos << 1) + 2]);
        }
    }

    int query(int qi, int qj, int low, int high, int pos)
    {
        if ((qi < low && qj < low) || (qi > high && qj > high))
        {
            return 0;
            // No overlap
        }

        if (qi <= low && qj >= high)
        {
            return segment[pos];
            // total overlap
        }

        int mid = (low + high) >> 1;
        int l = query(qi, qj, low, mid, 2 * pos + 1);
        int r = query(qi, qj, mid + 1, high, 2 * pos + 2);
        return max(l, r);
    }
};

int maxQuery(int a, int b, SegmentTree *st, int n)
{
    int maxR = 0;
    int p = a;
    int q = b;
    while (head[p] != head[q])
    {
        if (depth[head[p]] < depth[head[q]])
            swap(p, q);
        maxR = max(maxR, st->query(pos[head[p]], pos[p], 0, n, 0));
        p = parent[head[p]];
    }

    if (pos[p] > pos[q])
        swap(p, q);
    maxR = max(maxR, st->query(pos[p], pos[q], 0, n, 0));

    return maxR;
}

vector<int> solve(vector<vector<int>> tree, vector<vector<int>> queries)
{
    int n = tree.size() + 1;
    vector<vector<int>> adj(n);
    init(n);
    //vector<int> vis(n,0);
    for (int i = 0; i < tree.size(); i++)
    {
        adj[tree[i][0]].push_back(tree[i][1]);
        adj[tree[i][1]].push_back(tree[i][0]);
        //vis[tree[i][1]]++;
    }

    //int root=-1;
    //while(vis[++root]!=0);

    dfs(adj, 0);
    parent[0] = 0;
    decompose(0, 0, adj);
    SegmentTree *sTree = new SegmentTree(n);

    int qsize = queries.size();
    vector<int> res;

    for (int i = 0; i < qsize; i++)
    {
        switch (queries[i][0])
        {
        case 1:
            sTree->update(queries[i][2], pos[queries[i][1]], 0, 0, n);
            break;
        case 2:
            res.push_back(maxQuery(queries[i][1], queries[i][2], sTree, n));
            break;
        }
    }

    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nq_temp;
    getline(cin, nq_temp);

    vector<string> nq = split_string(nq_temp);

    int n = stoi(nq[0]);

    int q = stoi(nq[1]);

    vector<vector<int>> tree(n - 1);
    for (int tree_row_itr = 0; tree_row_itr < n - 1; tree_row_itr++)
    {
        tree[tree_row_itr].resize(2);

        for (int tree_column_itr = 0; tree_column_itr < 2; tree_column_itr++)
        {
            cin >> tree[tree_row_itr][tree_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<vector<int>> queries(q);
    for (int queries_row_itr = 0; queries_row_itr < q; queries_row_itr++)
    {
        queries[queries_row_itr].resize(3);

        for (int queries_column_itr = 0; queries_column_itr < 3; queries_column_itr++)
        {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = solve(tree, queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++)
    {
        fout << result[result_itr];

        if (result_itr != result.size() - 1)
        {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
    {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
