import pandas as pd
import numpy as np
import itertools
import sys

# -------------------------------
# ELECTRE III functions
# -------------------------------

def partial_concordance(v_a, v_b, q, p):
  """
  Compute the partial concordance index for a single criterion.
  
  Parameters:
    v_a: performance of alternative a on the criterion.
    v_b: performance of alternative b on the criterion.
    q: indifference threshold.
    p: preference threshold.
  
  Returns:
    The partial concordance c_j(a,b) in [0, 1].
  """
  diff = v_a - v_b
  if diff >= -q:
    return 1.0
  elif diff <= -p:
    return 0.0
  else:
    # Linear interpolation between -p and -q
    return (diff + p) / (p - q)

def partial_discordance(v_a, v_b, q, p):
  """
  Compute the partial discordance index for a single criterion.
  
  Parameters:
    v_a: performance of alternative a on the criterion.
    v_b: performance of alternative b on the criterion.
    q: indifference threshold.
    p: preference threshold.
    
  Returns:
    The partial discordance d_j(a,b) in [0, 1].
  """
  diff = v_a - v_b
  if diff >= -q:
    return 0.0
  elif diff <= -p:
    return 1.0
  else:
    # Linear interpolation between -q and -p
    return (-diff - q) / (p - q)

def compute_credibility(C_ab, discordances, concordances):
  """
  Compute the overall credibility index sigma(a,b) for a pair of alternatives.
  
  The formula is:
    sigma(a,b) = C(a,b) * ∏_{j where d_j > c_j} ((1 - d_j) / (1 - C(a,b)))
    
  Parameters:
    C_ab: Global concordance index for the pair (a, b).
    discordances: dict of {criterion: d_j(a,b)} for all criteria.
    concordances: dict of {criterion: c_j(a,b)} for all criteria.
    
  Returns:
    sigma(a,b)
  """
  sigma = C_ab
  for crit in discordances.keys():
    d_j = discordances[crit]
    c_j = concordances[crit]
    if d_j > c_j:
      # Avoid division by zero if C_ab == 1
      if 1 - C_ab > 1e-6:
        sigma *= (1 - d_j) / (1 - C_ab)
      else:
        sigma *= (1 - d_j)
  return sigma

# -------------------------------
# Main program
# -------------------------------

if __name__ == '__main__':
  input_excel = "inputelectre.xlsx"
  output_excel = "outputelectre.xlsx"
  # Read the Excel file
  try:
    alternatives_df = pd.read_excel(input_excel, sheet_name='alternatives')
    parameters_df = pd.read_excel(input_excel, sheet_name='parameters')
    alternativenames_df = pd.read_excel(input_excel, sheet_name='alternativenames')
  except Exception as e:
    sys.exit(f"Error reading the Excel file: {e}")
  
  # Extract alternative names and the evaluation matrix as a NumPy array
  alternativenames = alternativenames_df['Alternatives'].values
  alternativematrix = alternatives_df

  # Ensure that the criteria in parameters match the alternative names columns
  criteria = parameters_df["Criterion"].tolist()
  missing = [crit for crit in criteria if crit not in alternativematrix.columns]
  if missing:
    sys.exit(f"The following criteria are missing in the alternatives data: {missing}")
  
  # Extract parameter values for each criterion and store in a dictionary for easy access
  params = {}
  for _, row in parameters_df.iterrows():
    crit = row["Criterion"]
    params[crit] = {
      "weight": row["Weight"],
      "q": row["q"],
      "p": row["p"],
      "v": row.get("v", None)  # veto threshold if provided
    }
  
  # Optionally: Normalize data per criterion if scales differ.
  # Here we assume criteria are comparable; if not, uncomment normalization below.
  # for crit in criteria:
  #   col = data[crit]
  #   data[crit] = col / np.sqrt((col**2).sum())
  
  altlength = len(alternativenames)
  criterialength = len(criteria)
  
  # Initialize matrices to store global concordance, credibility (outranking), and optionally discordance.
  concordance_matrix = pd.DataFrame(np.zeros((altlength, altlength)), index=alternativenames, columns=alternativenames)
  credibility_matrix = pd.DataFrame(np.zeros((altlength, altlength)), index=alternativenames, columns=alternativenames)
  discordance_matrices = {}  # for each criterion, we can store partial discordance
  for crit in criteria:
    discordance_matrices[crit] = pd.DataFrame(np.zeros((altlength, altlength)), index=alternativenames, columns=alternativenames)
  
  # For each ordered pair of alternatives (a,b)
  for i, a in enumerate(alternativenames):
    for j, b in enumerate(alternativenames):
      if a == b:
        concordance_matrix.loc[a, b] = np.nan
        credibility_matrix.loc[a, b] = np.nan
        for crit in criteria:
          discordance_matrices[crit].loc[a, b] = np.nan
        continue
      concordances = {}
      discordances = {}
      weighted_sum = 0.0
      
      # For each criterion, compute partial indices
      for crit in criteria:
        v_a = alternativematrix.loc[alternativematrix.index[i], crit]
        v_b = alternativematrix.loc[alternativematrix.index[j], crit]
        q = params[crit]["q"]
        p = params[crit]["p"]
        weight = params[crit]["weight"]
        
        # Compute partial concordance and discordance
        c_val = partial_concordance(v_a, v_b, q, p)
        d_val = partial_discordance(v_a, v_b, q, p)
        concordances[crit] = c_val
        discordances[crit] = d_val
        # Accumulate weighted concordance
        weighted_sum += weight * c_val
        
        # Store partial discordance per criterion
        discordance_matrices[crit].loc[a, b] = d_val
      
      # Global concordance for (a,b)
      globalconcordance_ab = weighted_sum
      concordance_matrix.loc[a, b] = globalconcordance_ab
      
      # Compute overall credibility sigma(a,b)
      sigma_ab = compute_credibility(globalconcordance_ab, discordances, concordances)
      credibility_matrix.loc[a, b] = sigma_ab
  
  # -------------------------------
  # Final Ranking using Net Flow
  # -------------------------------
  # Compute net flow for each alternative:
  net_flows = {}
  for a in alternativenames:
    flow_out = credibility_matrix.loc[a, :].sum(skipna=True)
    flow_in = credibility_matrix.loc[:, a].sum(skipna=True)
    # Divide by (n-1) to average over comparisons
    net_flow = (flow_out - flow_in) / (altlength - 1)
    net_flows[a] = net_flow

  ranking_df = pd.DataFrame(list(net_flows.items()), columns=["Alternative", "Net_Flow"])
  ranking_df.sort_values(by="Net_Flow", ascending=False, inplace=True)
  ranking_df.reset_index(drop=True, inplace=True)
  ranking_df["Rank"] = ranking_df.index + 1

  # Write outputs to an Excel file with separate sheets
  with pd.ExcelWriter(output_excel) as writer:
    concordance_matrix.to_excel(writer, sheet_name="Global_Concordance")
    credibility_matrix.to_excel(writer, sheet_name="Credibility")
    # Write each discordance matrix into its own sheet
    for crit, df in discordance_matrices.items():
      sheet_name = f"Discordance_{crit}"
      # Ensure the sheet name is not longer than Excel allows
      df.to_excel(writer, sheet_name=sheet_name[:31])
    # Write the final ranking
    ranking_df.to_excel(writer, sheet_name="Final_Ranking", index=False)
  
  print(f"Computation complete. Results saved to '{output_excel}'.")
