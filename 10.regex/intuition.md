Regex Matching Intuition
========================
We will check to see which prefixes of the pattern match increasingly long prefixes of the string.
We'll first consider the base cases -- when the string prefix is '', we will only consider the pattern prefix '' and any prefix with the pattern ".*" repeating.

Then, we'll continue to add letters from the string one by one to the current string prefix. We'll denote the newly added letter as currchar.
Every time we add a letter, we'll check to see if it matches any of the pattern prefixes. A string prefix matches a pattern prefix if either of the following holds:
1) currchar matches the last character of the pattern prefix (including '.') and the string prefix without currchar matches the pattern prefix without the last character
2) the last character of the pattern prefix is '*' and either
i) the string prefix matches the pattern prefix without the ".*" suffix
ii) the string prefix without currchar matches the current pattern prefix and currchar matches the second to last character of the pattern prefix (including '.')

We return true iff the entire pattern matches the entire string
