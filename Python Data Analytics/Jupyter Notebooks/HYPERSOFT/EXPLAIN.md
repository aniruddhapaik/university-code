Given the input data structure (a flat table where columns are metrics/criteria), we will adapt the steps:

1. **Step 0/1 (Interpret Data as Hypersoft Set):** We'll interpret the input CSV/Excel file directly. The rows are the alternatives (`U`), and the columns are the parameters (which we'll treat as the result of the `E x Θ` combination, even if `E` and `Θ` aren't explicitly separated in this data). The cell values `x_ij` are the evaluations.
2. **Step 2 (Decision Matrix):** The input DataFrame *is* our decision matrix `X`.
3. **Step 3 (Weights):** We'll assign weights (`w_j`) to each column (parameter/criterion). We'll define default weights (equal weighting) but also identify which criteria are "benefit" (higher is better) and which are "cost" (lower is better) for normalization.
4. **Step 4 (Transform and Aggregate):**
    * **Transform (`phi`):** We'll use Min-Max normalization to scale values to [0, 1]. This handles different scales and the benefit/cost nature, effectively acting as the transformation function `phi`.
    * **Aggregate:** We'll use the Weighted Sum Model (WSM) for aggregation (`S(A_i)`).
5. **Step 5 (Ideal Solution):** We'll skip the optional ideal solution step for simplicity.
6. **Step 6 (Rank):** We'll rank alternatives based on the aggregated scores (`S(A_i)`).

The program will read data from `inputhyper.xlsx`, perform these steps, and write the original data, weights, normalized data, scores, and final ranking to an Excel file (`outputhyper.xlsx`).

---

**1. Prepare the Input File**

Ensure you have the data saved as `inputhyper.xlsx` in the same directory as the Python script. The content should look like the text you provided. Pandas `read_excel` should handle the commas in numbers correctly if specified.

---

**2. Python Code**
...

---

**3. How to Use**

1. **Save the code:** Save the Python code above as a `.py` file (e.g., `HYPERSOFT.py`).
2. **Place the data:** Make sure the `inputhyper.xlsx` file (containing the journal data you provided) is in the same directory as the Python script.
3. **Install libraries:** If you don't have pandas, numpy, or openpyxl (for Excel writing), install them:

    ```bash
    pip install pandas numpy openpyxl
    ```

4. **Run the script:** Execute the script from your terminal:

    ```bash
    python HYPERSOFT.py
    ```

5. **Check the output:** A file named `outputhyper.xlsx` will be created in the same directory. It will contain four sheets:
    * `Original Data`: Your input data.
    * `Criteria Weights`: The weights used for each criterion (default equal weights, normalized).
    * `Normalized Data (0-1)`: The decision matrix after Min-Max normalization (values between 0 and 1, with cost criteria inverted).
    * `Final Ranking`: The original data along with the calculated `Score` for each alternative and its final `Rank`.

**Explanation of Simplifications/Adaptations:**

* **Cartesian Product (Step 0):** We didn't explicitly create a Cartesian product `E x Θ`. Instead, we treated the existing columns in your input excel data (`SJR-index`, `Cite Score`, etc.) as the final parameters resulting from such a step. Each column represents a specific dimension of evaluation.
* **Hypersoft Set Mapping (Step 1):** The input data itself is considered the realization of the hypersoft set mapping `F`. The values in the CSV are the (crisp, not multi-valued) evaluations `x_ij` for alternative `A_i` under parameter `C_j`.
* **Transformation `phi` (Step 4):** We used Min-Max normalization as our `phi` function. It converts the diverse scales of the input criteria into a common [0, 1] range and handles the directionality (benefit vs. cost), making them suitable for aggregation.
* **Aggregation (Step 4):** We implemented the straightforward Weighted Sum Model.
* **Multi-valued Entries:** The original Hypersoft description allows for entries like sets or fuzzy numbers (`P([0,1])`). Our implementation uses the crisp numeric data provided. If your data were fuzzy or interval-based, the normalization and aggregation steps would need different techniques (e.g., fuzzy arithmetic, specific defuzzification methods).

This program provides a practical MCDM implementation based on the core ideas of weighting criteria, normalizing data, and aggregating scores.
