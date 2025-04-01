import pandas as pd
import numpy as np
DEBUG = False

input_excel = 'inputpromethee.xlsx'
output_excel = 'outputpromethee.xlsx'

# --- Preference function: Using the "Usual" preference function ---
def preference_function(d):
    """
    For a given difference d, returns:
       0 if d <= 0 (i.e., alternative a is not better than b)
       1 if d > 0  (i.e., alternative a is preferred to b)
    This is the simplest form of a preference function.
    """
    return 0 if d <= 0 else 1

# --- Read the evaluation matrix and alternative names from Excel ---
alternativenames_df = pd.read_excel(input_excel, sheet_name='alternativenames')
alternativematrix_df = pd.read_excel(input_excel, sheet_name='alternatives')

# Extract alternative names and the evaluation matrix as a NumPy array
alternativenames = alternativenames_df['Alternatives'].values
alternativematrix = alternativematrix_df.values

# --- Parameters ---
parameters_df = pd.read_excel(input_excel, sheet_name='parameters')
weights = parameters_df['Weight'].values

n, q = alternativematrix.shape
if len(weights) != q:
    raise ValueError("The number of weights must match the number of criteria (columns) in the evaluation matrix.")

# --- Step 1: Compute global pairwise preference indices ---
# Initialize a matrix to store the aggregated preference index π(a, b)
global_pref = np.zeros((n, n))

# For each ordered pair of alternatives (a, b), compute:
#   For each criterion j: d_j = X[a, j] - X[b, j]
#   Then p_j = preference_function(d_j)
#   Global preference: π(a, b) = sum_{j} [w_j * p_j]
for i in range(n):
    for j in range(n):
        if i != j:
            p_values = np.array([preference_function(alternativematrix[i, k] - alternativematrix[j, k]) for k in range(q)])
            global_pref[i, j] = np.dot(weights, p_values)
        # Else leave as 0 (no self-comparison)

# --- Step 2: Compute Outranking Flows ---
# Positive flow: average preference of alternative i over all others
phi_plus = np.sum(global_pref, axis=1) / (n - 1)

# Negative flow: average preference of all other alternatives over alternative i
phi_minus = np.sum(global_pref, axis=0) / (n - 1)

# Net flow for each alternative: φ = φ⁺ - φ⁻
phi_net = phi_plus - phi_minus

# --- Step 3: Rank Alternatives ---
# Create a DataFrame to hold the results
results = pd.DataFrame({
    'Alternative': alternativenames,
    'Phi_Plus': phi_plus,
    'Phi_Minus': phi_minus,
    'Phi_Net': phi_net
})

# Rank alternatives by descending net flow (higher is better)
results['Rank'] = results['Phi_Net'].rank(ascending=False, method='min').astype(int)
results = results.sort_values(by='Phi_Net', ascending=False)

# --- Step 4: Output the results to Excel ---
results.to_excel(output_excel, index=False)
print(f"PROMETHEE II ranking completed. Results saved to '{output_excel}'.", )
