#include <vector>
using namespace std;

class Solution {
public:
    static auto twoSum(vector<int>& nums, int target) -> vector<int> {
        unordered_map<int, int> complements;
        complements.reserve(nums.size());
        for (size_t i = 0; i < nums.size(); ++i) {
            if (complements.find(target - nums[i]) != complements.end()) { // case 1
                return { complements[target - nums[i]], static_cast<int>(i) };
            }
            complements[nums[i]] = static_cast<int>(i); // case 2
        }
        return { -1, -1 };
    }
};
