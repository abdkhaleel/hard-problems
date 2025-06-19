const int MOD = 1e9 + 7;

class Solution {
    int dp[101][2][2][11];
    string num;

    int f(int pos, bool tight, bool leadingZero, int lastDigit) {
        if (pos == num.size()) return leadingZero ? 0 : 1;

        if (dp[pos][tight][leadingZero][lastDigit + 1] != -1)
            return dp[pos][tight][leadingZero][lastDigit + 1];

        int limit = tight ? num[pos] - '0' : 9;
        int res = 0;

        for (int d = 0; d <= limit; ++d) {
            bool newTight = tight && (d == limit);
            bool newLeadingZero = leadingZero && (d == 0);

            if (leadingZero || abs(d - lastDigit) == 1) {
                res = (res + f(pos + 1, newTight, newLeadingZero, d)) % MOD;
            }
        }

        return dp[pos][tight][leadingZero][lastDigit + 1] = res;
    }

    int count(string x) {
        num = x;
        memset(dp, -1, sizeof(dp));
        return f(0, true, true, -1);
    }

    string decrement(string s) {
        int i = s.size() - 1;
        while (i >= 0 && s[i] == '0') {
            s[i] = '9';
            i--;
        }
        if (i >= 0) s[i]--;
        if (s[0] == '0') s = s.substr(1);
        return s.empty() ? "0" : s;
    }
public:
    int countSteppingNumbers(string low, string high) {
        return (count(high) - count(decrement(low)) + MOD) % MOD;
    }

};
