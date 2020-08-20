#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long int LL;

void calcZth(vector<LL>& z, string& s) {
    LL len = s.length();
    z.resize(len,0);
    LL l=0,r=0;
     for(LL i=1;i<len;i++) {
        if (i<=r) {
            z[i]=min(z[i-l],r-i+1);
        }

       while(i+z[i]<len && s[z[i]] == s[z[i]+i]) {
           z[i]++;
       }
       if (i+z[i]-1>r) {
        l=i;
        r=i+z[i]-1;
       }
     }
}
// Complete the stringSimilarity function below.
LL stringSimilarity(string s) {
    LL sum=s.length();
    vector<LL> zth;
    calcZth(zth,s);
    cout << "zlen" << zth.size() << "\n";
    for(LL v: zth) {
        sum+=v;
    }

    return sum;
}

int main()
{
    //fstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        LL result = stringSimilarity(s);

        cout << result << "\n";
    }

    //fout.close();

    return 0;
}

//4999350028
//704382732