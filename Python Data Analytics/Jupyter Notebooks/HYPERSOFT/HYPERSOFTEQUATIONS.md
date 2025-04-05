Below is an extended explanation of a hypersoft set MCDM method that includes the initial Cartesian product step. Note that various researchers may structure the process somewhat differently, but one common framework involves the following steps:

---

### **Step 0. Define the Parameter Structure via Cartesian Product**

**0.1. Identify the Sets of Criteria and Sub-Attributes**

- **Criteria Set:**  
  \[
  E = \{C_1, C_2, \dots, C_n\}
  \]
- **Sub-Attributes:** For each criterion \(C_j\), there is a set of associated sub-attributes (or features). Denote the universal set of all sub-attributes as:  
  \[
  \Theta = \{t_1, t_2, \dots, t_k\}.
  \]

**0.2. Construct the Cartesian Product**

One of the initial steps is to form the Cartesian product between the criteria set \(E\) and the sub-attributes set \(\Theta\). This yields:
\[
E \times \Theta = \{(C_j, t_l) \mid C_j \in E, \, t_l \in \Theta\}.
\]
Each pair \((C_j, t_l)\) represents a specific combination where the criterion \(C_j\) is evaluated in the light of sub-attribute \(t_l\). This forms the basic building block of the hypersoft set and helps in capturing the multidimensional nature of the decision problem.

---

### **Step 1. Construct the Hypersoft Set**

**1.1. Mapping Alternatives to Parameter Combinations**

Let the set of alternatives be:
\[
U = \{A_1, A_2, \dots, A_m\}.
\]
Now, define a mapping that assigns to every criterion–sub-attribute pair a set of values (or membership degrees) for each alternative. Formally, this mapping is:
\[
F: E \times \Theta \rightarrow \mathcal{P}([0,1]),
\]
where \(F(C_j, t_l)\) gives the evaluation (often in the form of a set, interval, or fuzzy number) of how alternative \(A_i\) performs with respect to the pair \((C_j, t_l)\).

---

### **Step 2. Build the Decision Matrix**

After constructing the hypersoft set, a decision matrix \(X\) is formed. Unlike classical matrices where each entry is a single value, here each entry \(x*{ij}^{(l)}\) corresponds to the evaluation of alternative \(A_i\) under the criterion–sub-attribute pair \((C_j, t_l)\). This matrix could be visualized as multi-layered:
\[
X^{(l)} = \begin{bmatrix}
x*{11}^{(l)} & x*{12}^{(l)} & \cdots & x*{1n}^{(l)} \\
x*{21}^{(l)} & x*{22}^{(l)} & \cdots & x*{2n}^{(l)} \\
\vdots & \vdots & \ddots & \vdots \\
x*{m1}^{(l)} & x*{m2}^{(l)} & \cdots & x*{mn}^{(l)}
\end{bmatrix}, \quad \text{for each } t*l \in \Theta.
\]
Here, \(x*{ij}^{(l)}\) comes directly from the hypersoft set mapping \(F(C_j, t_l)\).

---

### **Step 3. Assign Weights to the Criteria and/or Sub-Attributes**

Since both criteria and their sub-attributes might not contribute equally to the decision, you assign weights:

- **Criteria Weights:**  
  \[
  W = \{w*1, w_2, \dots, w_n\} \quad \text{with } \sum*{j=1}^{n} w_j = 1.
  \]
- **Sub-Attribute Weights:**  
   \[
  V = \{v*1, v_2, \dots, v_k\} \quad \text{with } \sum*{l=1}^{k} v_l = 1.
  \]
  These weights help in aggregating the multi-dimensional evaluations later in the process.

---

### **Step 4. Transform and Aggregate the Evaluations**

Because the entries \(x*{ij}^{(l)}\) are often multi-valued (e.g., fuzzy numbers or sets), you typically introduce a transformation function:
\[
\phi: x*{ij}^{(l)} \mapsto \phi(x\_{ij}^{(l)}) \in [0, 1].
\]
This transformation “crispifies” the evaluation, making it suitable for aggregation.

**Aggregation Example: Weighted Sum Approach**

Aggregate the evaluations across both criteria and sub-attributes:
\[
S(A*i) = \sum*{j=1}^{n} \sum*{l=1}^{k} w_j \, v_l \, \phi\left(x*{ij}^{(l)}\right).
\]
Here:

- \(S(A_i)\) is the overall score for alternative \(A_i\),
- \(w_j\) is the weight for criterion \(C_j\),
- \(v_l\) is the weight for sub-attribute \(t_l\),
- \(\phi\left(x\_{ij}^{(l)}\right)\) is the crisp evaluation.

An alternative aggregation method might use a weighted product:
\[
P(A*i) = \prod*{j=1}^{n} \prod*{l=1}^{k} \left[\phi\left(x*{ij}^{(l)}\right)\right]^{w_j v_l}.
\]

---

### **Step 5. Compare Alternatives via an Ideal Solution (Optional)**

In some MCDM models, you define an ideal solution \(A^*\) with ideal evaluations \(x\_{j}^{*(l)}\) for each pair \((C*j, t_l)\). You then calculate the distance of each alternative from this ideal. For example, using a Euclidean distance:
\[
D(A_i, A^\*) = \sqrt{\sum*{j=1}^{n} \sum*{l=1}^{k} w_j \, v_l \left[\phi\left(x*{ij}^{(l)}\right) - \phi\left(x\_{j}^{*(l)}\right)\right]^2 }.
\]
A lower \(D(A_i, A^*)\) means the alternative \(A_i\) is closer to the ideal.

---

### **Step 6. Rank the Alternatives**

Finally, rank the alternatives based on the aggregated score or distance:

- **Score Method:** Rank in descending order of \(S(A_i)\).
- **Distance Method:** Rank in ascending order of \(D(A_i, A^\*)\).

The best alternative is the one with the highest aggregated score or the smallest distance to the ideal solution.

---

### **Summary of Terms and Relationships**

- **\(E\) and \(\Theta\):** Represent the criteria and their sub-attributes, respectively.
- **Cartesian Product \(E \times \Theta\):** Generates all criterion–sub-attribute pairs to capture multi-dimensional decision data.
- **\(U\):** Set of alternatives being evaluated.
- **\(F\):** Hypersoft set mapping that assigns multi-valued evaluations to each \((C_j, t_l)\) for every alternative.
- **\(x\_{ij}^{(l)}\):** Evaluation of alternative \(A_i\) under criterion \(C_j\) and sub-attribute \(t_l\).
- **\(\phi\):** Transformation function that converts multi-valued data into a crisp value.
- **Weights \(w_j\) and \(v_l\):** Reflect the importance of each criterion and sub-attribute.
- **\(S(A_i)\) and \(P(A_i)\):** Aggregated scores using weighted sum or product models.
- **\(D(A_i, A^\*)\):** Distance metric for comparing alternatives to an ideal solution.

---

This process, starting with the Cartesian product, ensures that every possible combination of criteria and sub-attributes is considered, providing a detailed and flexible evaluation framework for decision-making in environments with complex and multi-valued information.
