The **Travelling Salesman Problem (TSP)**, when solved using a **Dynamic Programming (DP)** approach, is often analyzed for its time complexity based on how states and transitions are defined. Below is the reasoning behind its complexity:

---

### **Problem Description**

Given \(n\) cities and a cost matrix \(C[i][j]\) representing the cost of traveling from city \(i\) to city \(j\), the goal is to find the shortest possible route that visits every city exactly once and returns to the starting city.

---

### **Dynamic Programming Approach**

The **Dynamic Programming** approach to TSP uses **bit-masking** and **state representation**. It is commonly referred to as the **Held-Karp algorithm**. The key idea is to use a **subset of cities** and the current city as the state and recursively compute the minimum cost.

#### **State Representation**

Let:

- \(dp[mask][i]\): Minimum cost to visit all cities in the subset represented by \(mask\), ending at city \(i\).

Here:

- \(mask\) is a bitmask of size \(n\), where each bit represents whether a city is included in the subset.
- \(i\) is the last city visited.

---

#### **Recursive Formula**

1. Base Case:
   \[
   dp[1 << 0][0] = 0
   \]
   This represents starting at city 0 with only city 0 visited, at a cost of 0.

2. Transition:
   \[
   dp[mask][i] = \min(dp[mask \setminus (1 << i)][j] + C[j][i])
   \]
   Where:

   - \(mask \setminus (1 << i)\): Subset excluding city \(i\).
   - \(j\): Any city in the subset represented by \(mask\) before visiting \(i\).

3. Final Answer:
   The minimum cost of a complete tour returning to the starting city:
   \[
   \text{min} \left(dp[(1 << n) - 1][i] + C[i][0] \, \text{for all} \, i \in [1, n-1]\right)
   \]

---

### **Time Complexity Analysis**

#### **State Space**

1. \(mask\): There are \(2^n\) subsets of cities.
2. \(i\): For each subset, we can end the tour at any of the \(n\) cities.

Thus, there are \(O(2^n \cdot n)\) states.

#### **Transitions**

- For each state \(dp[mask][i]\), we iterate over all \(j\) cities in the subset \(mask\) to compute the transition cost.
- This takes \(O(n)\) time per state.

#### **Total Time Complexity**

- Total states: \(O(2^n \cdot n)\).
- Transition computation per state: \(O(n)\).

Thus, the overall time complexity is:
\[
O(2^n \cdot n^2)
\]

---

### **Space Complexity**

The space complexity is determined by the storage required for the DP table:

- \(dp[mask][i]\): \(O(2^n \cdot n)\).

---

### **Example Walkthrough**

#### Example Problem:

- Cities: 4 (\(n = 4\)).
- Cost matrix \(C\):
  \[
  \begin{bmatrix}
  0 & 10 & 15 & 20 \\
  10 & 0 & 35 & 25 \\
  15 & 35 & 0 & 30 \\
  20 & 25 & 30 & 0
  \end{bmatrix}
  \]

#### Key Steps:

1. Represent subsets using bitmask:
   - \(mask = 0011\): Cities 0 and 1 visited.
2. Solve for subsets of increasing size.
   - Start with base cases (\(dp[1][0] = 0\)).
   - Transition to larger subsets using the recursive formula.
3. Compute the final tour cost.

---

### **Conclusion**

The **Dynamic Programming** approach for TSP achieves a significant reduction in complexity compared to the brute-force \(O(n!)\) solution. However, its complexity of \(O(2^n \cdot n^2)\) still makes it computationally expensive for large \(n\). The use of bit-masking for subsets and recursion allows the algorithm to explore only valid paths, making it efficient for moderate-sized problems (e.g., \(n \leq 20\)).
