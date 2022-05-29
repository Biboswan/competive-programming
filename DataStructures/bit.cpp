class NumArray {
public:
    vector<int> tree;
    vector<int> nums;
    NumArray(vector<int>& nums) {
         int n = nums.size();
         this->nums = nums;
         tree.resize(n+1,0);
         for(int i=0;i<n;i++) {
             addVal(i,nums[i]);
         }
    }
    
    void addVal(int i, int val) {
        int ind=i+1;
        int size = tree.size();
        while(ind<size) {
            tree[ind]+=val;
            ind+=ind&(-ind);
        }
    }
    
    void update(int i, int val) {
        int add = val-nums[i];
        nums[i]=val;
        addVal(i,add);
    }
    
    int sumRange(int i, int j) {
        auto sumFromZ = [&](int x) -> int {
            x++;
            int s=0;
            while(x>0) {
                s+=tree[x];
                x-=x&(-x);
            }
            
            return s;
        };
        
        return sumFromZ(j)-sumFromZ(i-1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */