class Solution1 {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> preSum(n+1, 0);
        for(int i = 1; i <= n; i++) preSum[i] = preSum[i-1] + nums[i-1];
        int mini = n+1;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j <= n; j++){
                if(preSum[j] - preSum[i] >= k) mini = min(mini, j-i); //key idea to optimize
            }
        }
        return mini == n+1? -1: mini;
    }
};

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> preSum(n+1, 0);
        for(int i = 1; i <= n; i++) preSum[i] = preSum[i-1] + nums[i-1];
        int mini = n+1;
        deque<int> dq;
        for(int i = 0; i <= n; i++){
            while(!dq.empty() && preSum[i] - preSum[dq.front()] >= k){
                mini = min(mini, i - dq.front());
                dq.pop_front();
            }
            while(!dq.empty() && preSum[i] <= preSum[dq.back()]){
                dq.pop_back();
            }
            dq.push_back(i);
        }
        return mini == n+1? -1: mini;
    }
};