In **heapsort**, the process involves several steps, and understanding the time complexities at each stage is key.

---

### **Steps of Heapsort:**

1. **Building the heap**:

   - We first arrange the given array to satisfy the max-heap property using a process called _heapify_.
   - For a binary heap, this involves:
     - Starting from the last non-leaf node and moving upwards.
     - Ensuring that the subtree rooted at each node satisfies the heap property.
   - The time complexity for building the heap is **O(n)** (not \( O(n \log n) \) as it might intuitively seem). This is because:
     - The number of nodes at depth \( d \) is \( \frac{n}{2^{d+1}} \).
     - The work done per node decreases as you move up the tree.
     - The sum of work forms a geometric series that sums to \( O(n) \).

2. **Sorting**:
   - Once the max-heap is built, repeatedly remove the root (the maximum element), move it to the end of the array, and reheapify the reduced heap.
   - Each removal takes \( O(\log n) \) time for reheapifying (as the height of the tree is \( \log n \)).
   - Since we do this \( n - 1 \) times (for all elements except the last one), the total complexity is \( O(n \log n) \).

---

### **Heapify:**

Heapify is the process of adjusting a subtree to satisfy the heap property.

- **Time Complexity for Heapify:**
  - For a single node, the time complexity of heapify is proportional to the height of the node in the tree, which is \( O(\log n) \) in the worst case.

---

### **Overall Time Complexity of Heapsort:**

1. **Building the heap**: \( O(n) \)
2. **Sorting**: \( O(n \log n) \)

Thus, the total time complexity of heapsort is:
\[
O(n) + O(n \log n) = O(n \log n)
\]

---

### **Summary:**

- **Heapify**: \( O(\log n) \) for a single operation.
- **Heapsort**: \( O(n \log n) \) for the full sorting process.
