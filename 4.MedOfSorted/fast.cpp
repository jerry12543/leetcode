#include <algorithm>
#include <vector>
using namespace std;
auto findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) -> double {
    if (nums1.size() > nums2.size()) {
        swap(nums1, nums2);
    }
    size_t low = 0;
    size_t high = nums1.size();
    size_t const totalSize = nums1.size() + nums2.size();

    while (low <= high) {
        size_t const part1 = (low + high) / 2;
        size_t const part2 = (totalSize + 1) / 2 - part1;

        int const low1 = (part1 == 0) ? INT_MIN : nums1[part1 - 1];
        int const high1 = (part1 == nums1.size()) ? INT_MAX : nums1[part1];

        int const low2 = (part2 == 0) ? INT_MIN : nums2[part2 - 1];
        int const high2 = (part2 == nums2.size()) ? INT_MAX : nums2[part2];

        if (low1 > high2) {
            high = part1 - 1;
        } else if (low2 > high1) {
            low = part1 + 1;
        } else {
            if (totalSize % 2 == 0) {
                return static_cast<double>(max(low1, low2) + min(high1, high2)) / 2;
            }
            return max(low1, low2);
        }
    }
    return -1;
}