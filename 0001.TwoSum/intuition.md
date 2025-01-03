Two Sum Intuition
=================
We will loop through the elements in nums and do the following
1) Check if we have seen the complement of current number before. If we have, return the current index along with the index of its complement.
2) Otherwise, store the current number along with its index.




On average, the map insert and lookup are both $O(1)$ time.
We do each O(n) times, so this solution is $O(n)$ time.

The map is $O(n)$ memory, so this solution is also $O(n)$ memory.
