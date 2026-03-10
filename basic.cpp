#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int n;
    int memo[50001];

    int getNextIndex(vector<vector<int>> &array, int l, int currentJob)
    {
        int r = n - 1;
        int result = n + 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (array[mid][0] <= currentJob)
            {
                result = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return result;
    }

    int solve(vector<vector<int>> &arr, int idx)
    {
        if (idx >= n)
            return 0;

        if (memo[idx] != -1)
            return memo[idx];

        int next = getNextIndex(arr, idx + 1, arr[idx][2]);

        int taken = arr[idx][2] + solve(arr, next);
        int notTake = solve(arr, idx + 1);

        return memo[idx] = max(taken, notTake);
    }
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {

        n = startTime.size();
        memset(memo, -1, sizeof(memo));
        vector<vector<int>> arr(n, vector<int>(3, 0));
        for (int i = 0; i < n; i++)
        {
            arr[i][0] = startTime[i];
            arr[i][1] = endTime[i];
            arr[i][2] = profit[i];
        }

        sort(arr.begin(), arr.end());
        return solve(arr, 0);
    }
};