# Optimal Classification Trees — CPLEX/C++ Implementation

## Assignment: Module 3 — Optimal Classification Trees (Bertsimas & Dunn, 2017)

---

## Project Structure

```
oct_project/
├── include/
│   ├── tree.h          # TreeStructure, OCTSolution types
│   ├── datagen.h       # Dataset generation / IO
│   ├── oct_model.h     # OCT CPLEX model interface
│   └── cart.h          # CART wrapper (calls sklearn via Python)
├── src/
│   ├── tree.cpp        # Tree structure + prediction logic
│   ├── datagen.cpp     # Synthetic data generation
│   ├── oct_model.cpp   # ILP model (Concert Technology / IloCplex)
│   ├── cart.cpp        # sklearn CART runner
│   └── main.cpp        # Experiment loop + CSV output
├── Makefile
├── analyze_results.py  # Python analysis script (generates plots + LaTeX table)
├── data/               # Generated datasets (created at runtime)
└── results/            # Output CSV (created at runtime)
```

---

## Requirements

### C++ side
- g++ with C++17 (`std=c++17`)
- IBM ILOG CPLEX Studio 22.1.2 (or compatible)
  - Adjust `CPLEX_HOME` and `CONCERT_HOME` in `Makefile` if needed

### Python side (for CART + analysis)
```bash
pip install scikit-learn pandas numpy matplotlib
```

---

## Build

```bash
# From oct_project/ directory:
make
```

If your CPLEX is installed elsewhere, edit the `Makefile`:
```makefile
CPLEX_HOME   = /path/to/your/cplex
CONCERT_HOME = /path/to/your/concert
```

---

## Run Experiments

```bash
# Run all experiments (seed=42 by default):
make test

# Or with a custom seed:
make run SEED=123

# Or directly:
./main 42
```

The experiment loop runs over all combinations of:
- `p ∈ {2, 6}` features
- `n ∈ {100, 200}` total samples (80/20 train/val split)
- `α ∈ {0, 2/n}` complexity penalty
- `D ∈ {1, 2, 3}` model depth
- `ntrees = 5` random instances per configuration

Each OCT instance has a **20-minute time limit** (configurable in `main.cpp`).

---

## Analyze Results

After running, generate tables and plots:

```bash
python3 analyze_results.py
# Outputs go to report/ directory
```

This generates:
- `report/solver_stats.csv` — % optimal, mean/max time, avg MIP gap
- `report/error_stats.csv` — mean train/val errors for OCT and CART
- `report/results_table.tex` — LaTeX table ready for your report
- `report/errors_n*.png` — Error comparison bar charts per (n, α)
- `report/effect_of_n_p.png` — Effect of n and p on validation error
- `report/branch_complexity.png` — Effect of α on number of active branches

---

## Model Description

The implementation follows the OCT formulation from:

> Bertsimas, D., & Dunn, J. (2017). *Optimal classification trees*. Machine Learning, 106, 1039–1082.

### Variables
| Variable | Type | Meaning |
|----------|------|---------|
| `a[m][j]` | Binary | Feature j used at branching node m |
| `b[m]` | Continuous [0,1] | Threshold at branching node m |
| `d[m]` | Binary | Branching node m is active |
| `z[i][t]` | Binary | Sample i assigned to leaf t |
| `l[t]` | Binary | Leaf t is active |
| `c[k][t]` | Binary | Leaf t predicts class k |
| `N_kt` | Continuous | Count of class-k samples at leaf t |
| `N_t` | Continuous | Total samples at leaf t |
| `L_t` | Continuous | Misclassification count at leaf t |

### Objective (minimised)
```
(1/n) * Σ_t L_t  +  α * Σ_m d_m
```

### Key constraints
- Branching node activated iff exactly one feature is selected (eq. 2)
- Threshold bounded by activity (eq. 3)
- Child can only be active if parent is active (eq. 5)
- Each sample assigned to exactly one leaf (eq. 6)
- Leaf active only if it gets ≥ Nmin samples (eq. 8)
- Routing constraints: samples follow splits correctly (eqs. 9–10)
- d_m forced active if any sample is routed through its left subtree (eq. 11)
- Misclassification count bounds (eqs. 15–16)

---

## Notes

### CART comparison
CART is run via `sklearn.tree.DecisionTreeClassifier` with:
- `criterion="gini"`, `max_depth=D`, `min_samples_leaf=Nmin`
- Called via Python subprocess; output (train/val error) is read back into C++

### Adjusting time limit
In `src/main.cpp`:
```cpp
const double time_limit = 1200.0; // 20 minutes — change to 3600.0 for 1 hour
```

### GLPK alternative
If you don't have CPLEX, the model can be reimplemented with GLPK via `glpk.h` or using Pyomo + GLPK. The model structure is identical; only the solver API changes.

---

## What to Report

Per the assignment, your report should include:

1. **Tables**: Mean train/val error for OCT and CART, per `(D, p, n, α)`
2. **Solver stats**: % optimal, mean time, max time, avg MIP gap
3. **Discussion**:
   - Effect of increasing D on train vs val error
   - Effect of α on number of active branches (complexity)
   - Effect of n and p on OCT vs CART gap
   - When does D=Dtrue lead to zero training error?
   - When does the OCT model outperform CART?
