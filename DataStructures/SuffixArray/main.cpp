//https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/
//https://www.coursera.org/lecture/algorithms-on-strings/sortdouble-implementation-PXsgH
//g++ ./main.cpp -o ./main.out -std=c++11
//#include <bits/stdc++.h>
#include <vector>
#include <iostream>

using namespace std;
typedef long long int LL;

void sortCharacters(string &s, vector<int> &order)
{
    int len = s.length();
    vector<int> count(27, 0);
    count[0] = 1;
    for (int i = 0; i < len - 1; i++)
    {
        count[s[i] - 'a' + 1]++;
    }

    for (int i = 1; i < 27; i++)
    {
        count[i] = count[i - 1] + count[i];
    }

    int p = 0;
    order[0] = len - 1;
    for (int i = len - 2; i >= 0; i--)
    {
        p = s[i] - 'a' + 1;
        count[p]--;
        if (count[p] >= 0)
        {
            order[count[p]] = i;
        }
    }
}

vector<int> computeCharClasses(string &s, vector<int> &order)
{
    int len = s.length();
    vector<int> classEqv(len);
    int r = -1;
    char prev = 'R';
    for (int o : order)
    {
        if (prev != s[o])
        {
            r++;
        }
        classEqv[o] = r;
        prev = s[o];
    }

    return classEqv;
}

void sortDoubled(string &s, int l, vector<int> &order, vector<int> &classEqv)
{
    int len = s.length();
    vector<int> newOrder(len);
    int maxC = 0;

    for (int g : classEqv)
    {
        maxC = max(maxC, g);
    }

    vector<int> count(maxC + 1, 0);
    for (int g : classEqv)
    {
        count[g]++;
    }

    for (int i = 1; i <= maxC; i++)
    {
        count[i] = count[i - 1] + count[i];
    }

    int st, j;
    for (int i = len - 1; i >= 0; i--)
    {
        st = (order[i] - l + len) % len;
        j = classEqv[st];
        count[j]--;
        newOrder[count[j]] = st;
    }

    order = newOrder;
}

void upDateClasses(vector<int> &order, vector<int> &classEqv, int l)
{
    int p1 = -1, p2 = 1;
    int ed;
    int r = -1;
    int len = order.size();
    vector<int> newClassEqv(len);

    for (int o : order)
    {
        ed = (o + l + len) % len;
        if (!(classEqv[o] == p1 && classEqv[ed] == p2))
        {
            r++;
        }
        newClassEqv[o] = r;
        p1 = classEqv[o];
        p2 = classEqv[ed];
    }
    classEqv = newClassEqv;
}

void buildSuffixArray(string &s, vector<int> &order)
{
    sortCharacters(s, order);
    vector<int> classEqv = computeCharClasses(s, order);
    int l = 1;
    int len = s.length();

    while (l < len)
    {
        sortDoubled(s, l, order, classEqv);
        upDateClasses(order, classEqv, l);
        l <<= 1;
    }
}

//Kasai's algorithm
void buildLCP(vector<int> &order, vector<int> &lcp, string &s)
{
    int len = order.size();
    vector<int> invertedSuffix(len);
    for (int i = 0; i < len; i++)
    {
        invertedSuffix[order[i]] = i;
    }

    int p, p2, d = 0;
    //Last char is $ i.e empty string actually kinda
    for (int i = 0; i < len - 1; i++)
    {
        p = invertedSuffix[i];
        if (p == len - 1)
        {
            d = 0;
            continue;
        }
        p2 = order[p + 1];
        while (i + d < len && p2 + d < len && s[i + d] == s[p2 + d])
        {
            d++;
        }

        lcp[p] = d;
        if (d > 0)
        {
            d--;
        }
    }
}

/*
 * Complete the ashtonString function below.
 */
char ashtonString(string s, int k)
{
    s = s + '$';
    int len = s.length();
    vector<int> order(len);
    buildSuffixArray(s, order);

    vector<int> lcp(len, 0);
    buildLCP(order, lcp, s);

    LL tot;
    auto sum = [&](LL n) -> LL {
        return (n * (n + 1)) >> 1;
    };

    for (int i = 1; i < len; i++)
    {
        int l = len - 1 - order[i];
        tot = sum(l) - sum(lcp[i - 1]);
        if (k > tot)
        {
            k = k - tot;
        }
        else
        {
            int j = lcp[i - 1] + 1;
            while (j < k)
            {
                k = k - j;
                j++;
            }
            return s[order[i] + k - 1];
        }
    }

    return 'a';
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string s;
        getline(cin, s);

        int k;
        cin >> k;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        char res = ashtonString(s, k);

        cout << res << "\n";
    }

    //fout.close();

    return 0;
}
