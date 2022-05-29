vector<int> py(n, 0);

int j = 0;
for (int i = 1; i < n; i++)
{
    j = py[i - 1];
    while (j > 0 && s[i] != s[j])
    {
        j = py[j - 1];
    }
    if (s[i] == s[j])
    {
        j++;
    }
    py[i] = j;
}
