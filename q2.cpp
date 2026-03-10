#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

void buildKmpFailure(const vector<int> &a, int from, int length, vector<int> &fail)
{
    fail[0] = 0;
    for (int j = 1; j < length; ++j)
    {
        int k = fail[j - 1];
        while (k && a[from + j] != a[from + k])
            k = fail[k - 1];
        if (a[from + j] == a[from + k])
            k++;
        fail[j] = k;
    }
}

long long waysToSplit(const vector<int> &a, int from, int n,
                      const vector<long long> &ways, vector<int> &fail)
{
    int length = n - from;
    buildKmpFailure(a, from, length, fail);

    long long total = 0;
    for (int j = 0; j < length; ++j)
    {
        if (fail[j] == 0)
        {
            total += ways[from + j + 1];
            if (total >= MOD)
                total -= MOD;
        }
    }
    return total;
}

void solve(vector<int> &ans)
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<long long> ways(n + 1, 0);
    vector<int> fail(n, 0);
    ways[n] = 1;

    for (int i = n - 1; i >= 0; --i)
        ways[i] = waysToSplit(a, i, n, ways, fail);

    ans.push_back((int)(ways[0] % MOD));
}

int main()
{

    int t;
    cin >> t;

    vector<int> ans;
    ans.reserve(t);

    while (t--)
        solve(ans);

    for (int x : ans)
        cout << x << '\n';

    return 0;
}