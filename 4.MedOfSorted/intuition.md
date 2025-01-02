Median of Two Sorted Arrays Intuition
====================================
We partition each array into two continguous subarrays: a left partition and a right partition. Notice that since the arrays are sorted, min(left partition) <= min(right partition) for each array.
There are two keys to this problem:
1) We will hold the combined size of the left partitions invariant and equal to (totalSize+1)/2, where totalSize is the size of the original arrays combined.
2) The median is found when:
* all of the elements of left partition 1 are less than all of the elements of right partition 2 and all of the elements of left partition 2 are less than all of the elements of right partition 1.
* if a partition is empty, we will assume the check it's involved in evaluates to true.

We just binary search for the left partition size in array 1 that satisfies the conditions. Once found, the median can be calculated as follows:
1) if totalSize is odd, the median is just the maximum element in the combined left partitions.
2) if totalSize is even, the median is the average between the maximum element in the combined left partitions and the minimum element in the combined right partitions.

This approach runs in O(log(n+m)) time and uses O(1) additional memory.