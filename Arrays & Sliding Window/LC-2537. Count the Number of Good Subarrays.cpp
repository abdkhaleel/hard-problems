class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long ans = 0;
        unordered_map<int, int> freq;
        long long pairs = 0;
        int left = 0;
        int n = nums.size();
        for(int right = 0; right < n; right++){
            pairs += freq[nums[right]]++;
            while(pairs >= k){
                ans += n - right;
                pairs -= --freq[nums[left]];
                left++;
            }
        }
        return ans;
    }
};