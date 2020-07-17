class TwoSum {
public:
    unordered_map<int,int> nums;
    /**
     * @param number: An integer
     * @return: nothing
     */
    void add(int number) {
        // write your code here
        if (nums.find(number) == nums.end()) {
            nums[number]=1;
        } else {
            nums[number]++;
        }
    }

    /**
     * @param value: An integer
     * @return: Find if there exists any pair of numbers which sum is equal to the value.
     */
    bool find(int value) {
        // write your code here
        for (auto it=nums.begin();it!=nums.end();it++) {
            if (it->first == (value-it->first)) {
                if (it->second >= 2) {
                    return true;
                }
            }else if (nums.find(value-it->first) != nums.end()){
                return true;
            } else;
        }
        return false;
    }
};
