class Solution_brute_force {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        int count = 0;
        for(int i = 0; i < n; i++){
            long sum = 0;
            for(int j = i; j < n; j++){
                sum += nums[j];
                if(sum >= lower && sum <= upper) count++;
            }
        }
        return count;
    }
};
class Solution_better_approach {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        int count = 0;
        multiset<long> prefixSet;
        prefixSet.insert(0);
        long prefixSum = 0;
        for(int i = 0; i < n; i++){
            prefixSum += nums[i];

            auto low = prefixSet.lower_bound(prefixSum - upper);
            auto high = prefixSet.upper_bound(prefixSum - lower);

            count += distance(low, high);

            prefixSet.insert(prefixSum);
        }
        return count;
    }
};
class Solution_optimal {
private:
    int lower, upper, count = 0;
    vector<long> prefixSum;
    void mergeSort(int low, int high){
        if(low >= high) return;
        int mid = (low + high) / 2;

        mergeSort(low, mid);
        mergeSort(mid+1, high);

        int i, j;
        i = j = mid+1;
        for(int k = low; k <= mid; k++) {
            while(i <= high && prefixSum[i] - prefixSum[k] < lower) i++;
            while(j <= high && prefixSum[j] - prefixSum[k] <= upper) j++;

            count += j - i;
        }

        merge(low, mid, high);
    }

    void merge(int low, int mid, int high){
        vector<long> helper(high-low+1);
        for(int i = low; i <= high; i++){
            helper[i-low] = prefixSum[i];
        }
        int i = low, j = mid+1;
        int idx = low;
        while(i <= mid && j <= high){
            if(helper[i-low] < helper[j-low]){
                prefixSum[idx] = helper[i++-low];
            }else{
                prefixSum[idx] = helper[j++-low];
            }
            idx++;
        }
        while(i <= mid){
            prefixSum[idx++] = helper[i++-low];
        }
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        this->lower = lower;
        this->upper = upper;
        prefixSum.resize(n+1);
        prefixSum[0] = 0;
        for(int i = 0; i < n; i++){
            prefixSum[i+1] = prefixSum[i] + nums[i];
        }

        mergeSort(0, n);
        return count;
    }
};