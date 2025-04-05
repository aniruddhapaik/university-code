import pandas as pd
import numpy as np
import os

# --- Configuration ---
INPUT_FILE = 'inputhyper.xlsx'
OUTPUT_FILE = 'outputhyper.xlsx'

# Define which columns are criteria and their type (benefit/cost)
# Based on typical interpretations of these metrics:
CRITERIA_DEFINITION = {
  'SJR-index': 'benefit',
  'Cite Score': 'benefit',
  'H-index': 'benefit',
  'Best Subject Rank': 'cost',  # Lower rank is better
  'Total Docs': 'benefit',      # More can indicate influence/activity
  'Total Docs 3y': 'benefit',   # More recent activity
  'Total Refs': 'benefit',      # More refs *given* can indicate breadth
  'Total Cites 3y': 'benefit',  # Higher citation impact
  'Citable Docs 3y': 'benefit', # More citable content
  'Cites per Doc 2y': 'benefit',# Efficiency of citation impact
  'Refs per Doc': 'benefit',    # Depth of referencing per paper
  'Coverage': 'benefit'        # Wider coverage might be better
}

# Define default weights (Equal weighting)
# You can modify this dictionary to provide specific weights
# The code will normalize them to sum to 1 if they don't already
DEFAULT_WEIGHTS = {col: 1 for col in CRITERIA_DEFINITION.keys()}

# --- Helper Functions ---

def load_data(filepath):
  """Loads data from CSV, handling potential comma separators."""
  print(f"Loading data from: {filepath}")
  if not os.path.exists(filepath):
    raise FileNotFoundError(f"Error: Input file '{filepath}' not found.")
  try:
    df = pd.read_excel(filepath, sheet_name='alternatives')
    print("Data loaded successfully.")
    # Convert columns to numeric where possible, coercing errors
    for col in df.columns:
      df[col] = pd.to_numeric(df[col], errors='coerce')
    # Optional: Add an identifier column if one doesn't exist
    alternatives_df = pd.read_excel(filepath, sheet_name='alternativenames')
    alternatives = alternatives_df['Alternatives']
    if 'Alternative' not in df.columns:
      df.insert(0, 'Alternative', [f'{i}' for i in alternatives])
    print(df, end='\n\n')
    return df
  except Exception as e:
    print(f"Error loading data: {e}")
    raise

def calculate_normalized_weights(weights_dict):
  """Normalizes weights to sum to 1."""
  print("Calculating normalized weights...")
  # It receives DEFAULT_WEIGHTS here (e.g., {'SJR-index': 1, 'Cite Score': 1, ...})
  total_weight = sum(weights_dict.values())
  if total_weight == 0:
    print("Warning: Total weight is zero. Using equal weights.")
    num_criteria = len(weights_dict)
    return {k: 1/num_criteria if num_criteria > 0 else 0 for k in weights_dict.keys()}
  
  # This is where the actual 1/12 happens:
  normalized_weights = {k: v / total_weight for k, v in weights_dict.items()}
  # Example: {'SJR-index': 1/12, 'Cite Score': 1/12, ...}
  print("Weights normalized successfully.")
  return normalized_weights

def normalize_decision_matrix(df, criteria_def):
  """Normalizes the decision matrix using Min-Max scaling."""
  print("Normalizing decision matrix...")
  df_normalized = df.copy()
  criteria_cols = list(criteria_def.keys())
  
  # Check if criteria columns exist in the dataframe
  missing_cols = [col for col in criteria_cols if col not in df.columns]
  if missing_cols:
    raise ValueError(f"Error: Missing criteria columns in data: {missing_cols}")
    
  # Check for NaN values introduced by coercion or present in original data
  if df[criteria_cols].isnull().values.any():
    print("Warning: NaN values found in criteria columns. Attempting to handle by imputation (using column mean) or row removal.")
    # Simple imputation: fill with mean. More sophisticated methods could be used.
    for col in criteria_cols:
      if df_normalized[col].isnull().any():
        col_mean = df_normalized[col].mean()
        df_normalized[col].fillna(col_mean, inplace=True)
        print(f"NaNs in column '{col}' filled with mean ({col_mean:.2f}).")
    # Alternative: drop rows with NaNs
    # df_normalized.dropna(subset=criteria_cols, inplace=True)
    # print("Rows with NaN values in criteria columns removed.")

  for col in criteria_cols:
    min_val = df_normalized[col].min()
    max_val = df_normalized[col].max()
    
    # Avoid division by zero if all values in a column are the same
    if max_val == min_val:
      if criteria_def[col] == 'benefit':
        # If benefit and all same, could be max (1) or neutral (0.5?)
        # Let's assign 1, assuming it meets the single value threshold perfectly.
        df_normalized[col] = 1.0 
      elif criteria_def[col] == 'cost':
        # If cost and all same, could be min (0) or neutral (0.5?)
        # Let's assign 1.0 after inversion (so 0 before), meaning best possible cost.
        df_normalized[col] = 0.0 # Assign 0 for cost, as it's the best possible relative cost score
      else:
        df_normalized[col] = 0.5 # Assign neutral if type unknown or constant value has no clear benefit/cost implication
      print(f"Column '{col}' has constant value {min_val}. Assigned default normalized value.")
      continue # Skip further calculation for this column

    if criteria_def[col] == 'benefit':
      # Normalize benefit criteria: (value - min) / (max - min)
      df_normalized[col] = (df_normalized[col] - min_val) / (max_val - min_val)
    elif criteria_def[col] == 'cost':
      # Normalize cost criteria: (max - value) / (max - min)
      df_normalized[col] = (max_val - df_normalized[col]) / (max_val - min_val)
    else:
      print(f"Warning: Unknown criterion type for '{col}'. Skipping normalization.")
      
  print("Normalization complete.")
  return df_normalized[criteria_cols] # Return only the normalized criteria columns

def calculate_weighted_scores(df_normalized, normalized_weights):
  """Calculates the weighted sum score for each alternative."""
  print("Calculating weighted scores...")
  scores = np.zeros(len(df_normalized))
  
  # Ensure weights keys match normalized df columns
  relevant_weights = {k: v for k, v in normalized_weights.items() if k in df_normalized.columns}
  
  for col, weight in relevant_weights.items():
    scores += df_normalized[col] * weight
    
  print("Weighted scores calculated.")
  return scores

def rank_alternatives(df, scores):
  """Adds scores and ranks to the DataFrame."""
  print("Ranking alternatives...")
  df_ranked = df.copy().drop(df.columns[1:], axis=1)
  df_ranked['Score'] = scores
  # Rank descending (higher score is better)
  df_ranked['Rank'] = df_ranked['Score'].rank(ascending=False, method='min').astype(int)
  df_ranked = df_ranked.sort_values(by='Rank', ascending=True)
  print("Ranking complete.")
  return df_ranked

# --- Main Execution ---
if __name__ == "__main__":
  print("--- Starting Hypersoft Set Inspired MCDM Process ---")

  try:
    # Step 0 & 1 & 2: Load data (interpreting it as the decision matrix from the hypersoft set)
    df_original = load_data(INPUT_FILE)
    df_analysis = df_original.copy() # Keep original separate

    # Step 3: Assign and Normalize Weights
    weights = calculate_normalized_weights(DEFAULT_WEIGHTS)
    df_weights = pd.DataFrame(list(weights.items()), columns=['Criterion', 'Weight'])

    # Identify the actual criteria columns available in the loaded data
    available_criteria = {k: v for k, v in CRITERIA_DEFINITION.items() if k in df_analysis.columns}
    if not available_criteria:
      raise ValueError("No defined criteria found in the input file columns.")
    print(f"Using criteria: {list(available_criteria.keys())}")

    # Step 4 (Transform): Normalize the decision matrix
    df_normalized = normalize_decision_matrix(df_analysis, available_criteria)
    # Add identifier column back for reference if it was present
    if 'Alternative' in df_analysis.columns:
      df_normalized.insert(0, 'Alternative', df_analysis['Alternative'])

    # Step 4 (Aggregate): Calculate weighted scores
    # Need to pass the normalized data *without* the identifier column if added
    norm_cols_for_scoring = [col for col in available_criteria.keys() if col in df_normalized.columns]
    scores = calculate_weighted_scores(df_normalized[norm_cols_for_scoring], weights)

    # Step 6: Rank Alternatives
    df_final_ranking = rank_alternatives(df_analysis, scores) # Add score/rank to original data copy

    # --- Output Results ---
    print(f"Writing results to Excel file: {OUTPUT_FILE}")
    with pd.ExcelWriter(OUTPUT_FILE, engine='openpyxl') as writer:
      df_original.to_excel(writer, sheet_name='Original Data', index=False)
      df_weights.to_excel(writer, sheet_name='Criteria Weights', index=False)
      # Ensure normalized df aligns with original alternatives before saving
      if 'Alternative' in df_final_ranking.columns and 'Alternative' in df_normalized.columns:
        df_normalized_aligned = pd.merge(df_final_ranking[['Alternative']], df_normalized, on='Alternative', how='left')
        df_normalized_aligned.to_excel(writer, sheet_name='Normalized Data (0-1)', index=False)
      else:
        df_normalized.to_excel(writer, sheet_name='Normalized Data (0-1)', index=False)

      df_final_ranking.to_excel(writer, sheet_name='Final Ranking', index=False)

    print("--- Process Completed Successfully ---")
    print(f"Final ranking saved in '{OUTPUT_FILE}'.")

  except FileNotFoundError as e:
    print(e)
  except ValueError as e:
    print(e)
  except Exception as e:
    print(f"An unexpected error occurred: {e}")
