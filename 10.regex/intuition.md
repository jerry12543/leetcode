Regex Matching Intuition
========================
We will check to see which prefixes of the pattern match increasingly long prefixes of the string.
We'll first consider the base cases -- when the string prefix is '', we will only consider the pattern prefix '' and any prefix with the pattern ".*" repeating.

Then, we'll continue to add letters from the string one by one to the current string prefix. We'll denote the newly added letter as currchar.
Every time we add a letter, we'll check to see if it matches any of the pattern prefixes. A string prefix matches a pattern prefix if either of the following holds:
1) the last character of the pattern prefix is '\*' and either
i) the string prefix matches the pattern prefix without the ".*" suffix
ii) the string prefix without currchar matches the current pattern prefix and currchar matches the second to last character of the pattern prefix (including '.')
2) currchar matches the last character of the pattern prefix (including '.') and the string prefix without currchar matches the pattern prefix without the last character


We return true iff the entire pattern matches the entire string

Let n denote the length of s and m denote the length of p.
Inside the nested for loop, we do O(1) operations. We do each O(n * m) times, so this solution is O(n * m) time.
In both the most optimal and best solution, we use O(m) memory.