class Solution {
private:
    vector<int> pickMax(vector<int>& arr, int k){
        int drop = arr.size() - k;
        vector<int> monotonic;
        for(int& x: arr){
            while(!monotonic.empty() && drop > 0 && monotonic.back() < x){
                monotonic.pop_back();
                drop--;
            }
            monotonic.push_back(x);
        }
        monotonic.resize(k);
        return monotonic;
    }
    vector<int> merge(vector<int>& arr1, vector<int>& arr2){
        vector<int> res;
        int i = 0, j = 0;
        while(i < arr1.size() || j < arr2.size()){
            if(lexicographical_compare(
                arr1.begin() + i, arr1.end(), arr2.begin() + j, arr2.end())){
                res.push_back(arr2[j++]);
            }
            else{
                res.push_back(arr1[i++]);
            }
        }
        return res;
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> best;
        for(int i = 0; i <= k; i++){
            if(i > nums1.size() || k - i > nums2.size()) continue;

            auto pick1 = pickMax(nums1, i);
            auto pick2 = pickMax(nums2, k-i);
            auto merged = merge(pick1, pick2);

            best = max(best, merged);
        }
        return best;
    }
};