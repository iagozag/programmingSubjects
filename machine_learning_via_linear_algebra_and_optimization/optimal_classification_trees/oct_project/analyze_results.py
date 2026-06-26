"""
analyze_results.py
==================
Reads results/oct_results.csv produced by the C++ experiment runner
and generates:
  - Summary tables (mean/max time, % optimal, mean errors)
  - Comparison plots (OCT vs CART train/val errors)
  - LaTeX tables for the report

Usage:
    python3 analyze_results.py [--results results/oct_results.csv] [--out report/]
"""

import argparse
import os
import sys
import pandas as pd
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker

# ─── CLI ────────────────────────────────────────────────────────────────────
parser = argparse.ArgumentParser()
parser.add_argument("--results", default="results/oct_results.csv")
parser.add_argument("--out",     default="report")
args = parser.parse_args()

os.makedirs(args.out, exist_ok=True)
OUTDIR = args.out

# ─── Load Data ──────────────────────────────────────────────────────────────
df = pd.read_csv(args.results)
print(f"Loaded {len(df)} rows from {args.results}")
print(df.dtypes)
print(df.head())

# Derived columns
df["alpha_label"] = df["alpha"].apply(lambda a: "0" if a == 0.0 else "2/n")

# ─── 1. Solver Statistics Table ─────────────────────────────────────────────
print("\n=== Solver Statistics ===")
grp = df.groupby(["D", "p", "n", "alpha_label"])
solver_stats = grp.agg(
    n_instances   = ("tree_instance", "count"),
    pct_optimal   = ("oct_optimal",  lambda x: 100 * x.mean()),
    mean_time_s   = ("oct_solve_time", "mean"),
    max_time_s    = ("oct_solve_time", "max"),
).reset_index()

# mean MIP gap only for instances not solved to optimality
df_subopt = df[df["oct_optimal"] == 0]
if not df_subopt.empty:
    gap_stats = df_subopt.groupby(["D", "p", "n", "alpha_label"])["oct_mip_gap"].mean().reset_index(name="mean_mip_gap")
    solver_stats = solver_stats.merge(gap_stats, on=["D", "p", "n", "alpha_label"], how="left")
else:
    solver_stats["mean_mip_gap"] = float("nan")

print(solver_stats.to_string(index=False))

solver_stats.to_csv(f"{OUTDIR}/solver_stats.csv", index=False)

# ─── 2. Error Comparison Table ───────────────────────────────────────────────
print("\n=== Error Comparison (means over ntrees instances) ===")
error_stats = grp.agg(
    oct_train_mean = ("oct_train_error", "mean"),
    oct_val_mean   = ("oct_val_error",   "mean"),
    cart_train_mean= ("cart_train_error","mean"),
    cart_val_mean  = ("cart_val_error",  "mean"),
    oct_active_br  = ("oct_active_branches", "mean"),
    cart_branches  = ("cart_n_branches", "mean"),
).reset_index()
print(error_stats.to_string(index=False))
error_stats.to_csv(f"{OUTDIR}/error_stats.csv", index=False)

# ─── 3. LaTeX Table ──────────────────────────────────────────────────────────
def fmt(v, pct=False):
    if pd.isna(v): return "N/A"
    if pct: return f"{v:.1f}\\%"
    return f"{v:.3f}"

latex_rows = []
for _, row in error_stats.iterrows():
    # Find solver stats row
    sr = solver_stats[
        (solver_stats["D"] == row["D"]) &
        (solver_stats["p"] == row["p"]) &
        (solver_stats["n"] == row["n"]) &
        (solver_stats["alpha_label"] == row["alpha_label"])
    ]
    pct_opt = sr["pct_optimal"].values[0] if len(sr) else float("nan")
    mt = sr["mean_time_s"].values[0] if len(sr) else float("nan")
    mxt = sr["max_time_s"].values[0] if len(sr) else float("nan")
    gap = sr["mean_mip_gap"].values[0] if len(sr) else float("nan")

    latex_rows.append(
        f"{int(row['D'])} & {int(row['p'])} & {int(row['n'])} & ${row['alpha_label']}$ & "
        f"{fmt(row['oct_train_mean'])} & {fmt(row['oct_val_mean'])} & "
        f"{fmt(row['cart_train_mean'])} & {fmt(row['cart_val_mean'])} & "
        f"{fmt(pct_opt, pct=True)} & {mt:.1f}s & {mxt:.1f}s & {fmt(gap)} \\\\"
    )

latex_header = r"""\begin{table}[h]
\centering
\small
\caption{Comparison of OCT (optimal) and CART on synthetic datasets. Mean over 5 instances.}
\label{tab:results}
\begin{tabular}{cccc|cc|cc|cccc}
\hline
$D$ & $p$ & $n$ & $\alpha$ & \multicolumn{2}{c|}{OCT Error} & \multicolumn{2}{c|}{CART Error} & \multicolumn{4}{c}{Solver Stats} \\
    &     &     &          & Train & Val & Train & Val & \% Opt & Mean time & Max time & Avg Gap \\
\hline"""

latex_footer = r"""\hline
\end{tabular}
\end{table}"""

with open(f"{OUTDIR}/results_table.tex", "w") as f:
    f.write(latex_header + "\n")
    for row in latex_rows:
        f.write(row + "\n")
    f.write(latex_footer + "\n")

print(f"\nLaTeX table saved to {OUTDIR}/results_table.tex")

# ─── 4. Plots ────────────────────────────────────────────────────────────────
COLORS = {"OCT train": "#2563eb", "OCT val": "#93c5fd",
          "CART train": "#dc2626", "CART val": "#fca5a5"}

def make_error_plot(sub_df, title, outpath):
    """Bar chart comparing OCT vs CART errors for a given (n, alpha) slice."""
    fig, axes = plt.subplots(1, 2, figsize=(12, 4), sharey=True)
    for ax, p_val in zip(axes, [2, 6]):
        pdata = sub_df[sub_df["p"] == p_val]
        if pdata.empty:
            ax.set_title(f"p={p_val} (no data)")
            continue
        D_vals_plot = sorted(pdata["D"].unique())
        x = np.arange(len(D_vals_plot))
        w = 0.2
        oct_tr  = [pdata[pdata["D"]==d]["oct_train_mean"].values[0] for d in D_vals_plot]
        oct_va  = [pdata[pdata["D"]==d]["oct_val_mean"].values[0]   for d in D_vals_plot]
        cart_tr = [pdata[pdata["D"]==d]["cart_train_mean"].values[0] for d in D_vals_plot]
        cart_va = [pdata[pdata["D"]==d]["cart_val_mean"].values[0]   for d in D_vals_plot]
        ax.bar(x - 1.5*w, oct_tr,  w, label="OCT train",  color=COLORS["OCT train"])
        ax.bar(x - 0.5*w, oct_va,  w, label="OCT val",    color=COLORS["OCT val"])
        ax.bar(x + 0.5*w, cart_tr, w, label="CART train", color=COLORS["CART train"])
        ax.bar(x + 1.5*w, cart_va, w, label="CART val",   color=COLORS["CART val"])
        ax.set_xticks(x)
        ax.set_xticklabels([f"D={d}" for d in D_vals_plot])
        ax.set_ylabel("Error rate")
        ax.set_title(f"p={p_val} features")
        ax.set_ylim(0, 0.6)
        ax.legend(fontsize=8)
        ax.yaxis.set_major_formatter(mticker.PercentFormatter(xmax=1.0))
    fig.suptitle(title, fontsize=13, fontweight="bold")
    plt.tight_layout()
    plt.savefig(outpath, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  Saved {outpath}")

print("\nGenerating plots ...")
for n_val in df["n"].unique():
    for alpha_lbl in df["alpha_label"].unique():
        sub = error_stats[
            (error_stats["n"] == n_val) &
            (error_stats["alpha_label"] == alpha_lbl)
        ]
        if sub.empty: continue
        title = f"Train vs Validation Error — n={n_val}, α={alpha_lbl}"
        fname = f"errors_n{n_val}_alpha{alpha_lbl.replace('/','')}".replace(" ","_") + ".png"
        make_error_plot(sub, title, f"{OUTDIR}/{fname}")

# ─── 5. Effect of n and p: fixed D=Dtrue ─────────────────────────────────────
def make_effect_plot(error_stats, outpath):
    """How do errors change as we vary n and p for D=Dtrue?"""
    fig, axes = plt.subplots(1, 2, figsize=(12, 4))
    for ax, alpha_lbl in zip(axes, ["0", "2/n"]):
        sub = error_stats[(error_stats["D"] == 3) & (error_stats["alpha_label"] == alpha_lbl)]
        if sub.empty: continue
        for p_val, ls in [(2, "-o"), (6, "-s")]:
            pdata = sub[sub["p"] == p_val].sort_values("n")
            ax.plot(pdata["n"], pdata["oct_val_mean"],  ls, color="#2563eb",
                    label=f"OCT val p={p_val}", linewidth=2)
            ax.plot(pdata["n"], pdata["cart_val_mean"], ls, color="#dc2626",
                    label=f"CART val p={p_val}", linewidth=2, linestyle="--")
        ax.set_xlabel("Training set size (n)")
        ax.set_ylabel("Validation error")
        ax.set_title(f"Effect of n (D=Dtrue=3, α={alpha_lbl})")
        ax.legend(fontsize=8)
        ax.yaxis.set_major_formatter(mticker.PercentFormatter(xmax=1.0))
    plt.tight_layout()
    plt.savefig(outpath, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  Saved {outpath}")

make_effect_plot(error_stats, f"{OUTDIR}/effect_of_n_p.png")

# ─── 6. Effect of α on active branches ───────────────────────────────────────
def make_branch_plot(error_stats, outpath):
    fig, axes = plt.subplots(1, 2, figsize=(11, 4))
    for ax, n_val in zip(axes, [100, 200]):
        sub = error_stats[error_stats["n"] == n_val]
        for p_val, mk in [(2, "o"), (6, "s")]:
            for alpha_lbl, ls in [("0", "-"), ("2/n", "--")]:
                pdata = sub[(sub["p"] == p_val) & (sub["alpha_label"] == alpha_lbl)].sort_values("D")
                if pdata.empty: continue
                ax.plot(pdata["D"], pdata["oct_active_br"], marker=mk, linestyle=ls,
                        label=f"p={p_val}, α={alpha_lbl}")
        ax.set_xlabel("Tree depth D")
        ax.set_ylabel("Avg active branching nodes (OCT)")
        ax.set_title(f"Complexity penalty effect (n={n_val})")
        ax.legend(fontsize=8)
        ax.set_xticks([1, 2, 3])
    plt.tight_layout()
    plt.savefig(outpath, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  Saved {outpath}")

make_branch_plot(error_stats, f"{OUTDIR}/branch_complexity.png")

# ─── Summary ────────────────────────────────────────────────────────────────
print(f"\n✓ All outputs in: {OUTDIR}/")
print("Files generated:")
for f in sorted(os.listdir(OUTDIR)):
    print(f"  {f}")
