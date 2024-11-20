The **Knapsack Problem** has a **greedy method** variant called the **Fractional Knapsack Problem**, where the goal is to maximize the total value by selecting items that fit in a knapsack of limited capacity. The greedy method is efficient and is used only when fractions of items can be taken.

---

### **Fractional Knapsack Problem**

#### **Problem Description**

1. Each item \(i\) has:
   - **Weight**: \(w_i\)
   - **Value**: \(v_i\)
2. Knapsack has a maximum capacity \(W\).
3. Objective: Maximize the total value in the knapsack by choosing items, including fractional portions, if necessary.

#### **Greedy Approach**

1. Calculate the **value-to-weight ratio** for each item:
   \[
   r_i = \frac{v_i}{w_i}
   \]
2. Sort all items in descending order of \(r_i\).
3. Pick items with the highest \(r_i\) first, adding as much as possible to the knapsack.
4. If the knapsack cannot fit an item entirely, take a fraction of the item.

---

### **Time Complexity Analysis**

The time complexity of the greedy approach involves the following steps:

#### **1. Computing Value-to-Weight Ratios**

- For \(n\) items, calculate \(r_i = \frac{v_i}{w_i}\) for each item.
- Complexity: \(O(n)\).

#### **2. Sorting the Items**

- Items are sorted by their value-to-weight ratio (\(r_i\)) in descending order.
- Sorting complexity: \(O(n \log n)\).

#### **3. Picking Items**

- Traverse through the sorted list and keep adding items to the knapsack:
  - For each item, check if it fits entirely or partially in the remaining capacity.
  - Complexity: \(O(n)\), as we iterate over all items once.

---

### **Total Time Complexity**

Combining all steps:
\[
O(n) + O(n \log n) + O(n) = O(n \log n)
\]

---

### **Space Complexity**

- Sorting requires \(O(1)\) or \(O(n)\) auxiliary space depending on the sorting algorithm used.
- Thus, the space complexity is typically \(O(1)\).

---

### **Why is Greedy Approach Not Used for 0/1 Knapsack?**

The greedy approach works for **Fractional Knapsack** because we can take fractions of items. However, for **0/1 Knapsack**, where items can only be included or excluded entirely:

- A greedy solution may fail to find the optimal result, as it doesn't account for combinations of items.

For example:

- Items: \((v_1=60, w_1=10), (v_2=100, w_2=20), (v_3=120, w_3=30)\)
- Capacity: \(W = 50\).

Greedy picks \(v_3, v_2\) (total value \(220\)), but the optimal solution (using \(v_2, v_1\)) gives \(260\).

---

### **Conclusion**

- **Greedy Method Time Complexity**: \(O(n \log n)\), dominated by the sorting step.
- **Applicability**: Works optimally for Fractional Knapsack but not for 0/1 Knapsack.
