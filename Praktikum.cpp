/**
 *
 * Kelompok 7 Teori Graf E
 * 1. Aria Nalini Farzana       - 5025221016
 * 2. Abillidya Nofianto Putri  - 5025221164
 * 3. Bianca Shaummaya Aryan    - 5025221184
 * 
 * Implementasikan sebuah program untuk menyelesaikan permasalahan 
 * "Largest Monotonically Increasing Subsequence"
 * 
 * **/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    vector<int> dp(n, 1);
    int maxLength = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLength = max(maxLength, dp[i]);
    }

    return maxLength;
}

int main() {
    vector<int> arr = {4, 1, 13, 7, 0, 2, 8, 11, 3};
    int lisLength = lengthOfLIS(arr);

    cout << "Panjang LIS: " << lisLength << endl;
    return 0;
}
