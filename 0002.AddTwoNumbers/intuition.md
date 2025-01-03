Add Two Numbers Intuition
==========================
We will process the digits of the numbers and add them together one by one, starting from the least significant digit. For each pair of digits, if their sum is larger than 9, we will store the excess in a carry integer, which will be added to the next pair of digits in subsequent iterations.
Notice that when adding two numbers, the resulting number can have at most one more digit than the longer of the two numbers. This happens when the final sum includes a leftover carry. Thus, after processing all digits, we will add another node to our sum with val 1 if our carry is 1.

We stop looping after going through all of the digits of the longer number, so our solution is $O(\text{max}(m,n))$.We will add at most 1 extra node, so we are using $O(1)$ memory.
