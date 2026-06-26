import sys
import csv
import numpy as np
from sklearn.tree import DecisionTreeClassifier

def load_data(path):
    with open(path) as f:
        reader = csv.reader(f)
        header = next(reader)
        # pula a linha de cabecalho que tem n, p, k
        rows = [list(map(float, row)) for row in reader]
    
    x = np.array([r[:-1] for r in rows])
    y = np.array([int(r[-1]) for r in rows])
    return x, y

def main():
    if len(sys.argv) < 5:
        print("uso: python3 cart.py <train_csv> <val_csv> <max_depth> <min_samples>")
        sys.exit(1)

    train_path = sys.argv[1]
    val_path = sys.argv[2]
    max_depth = int(sys.argv[3])
    min_samples = int(sys.argv[4])

    x_train, y_train = load_data(train_path)
    x_val, y_val = load_data(val_path)

    clf = DecisionTreeClassifier(
        criterion='gini',
        max_depth=max_depth,
        min_samples_leaf=min_samples,
        random_state=42
    )
    clf.fit(x_train, y_train)

    train_err = 1.0 - clf.score(x_train, y_train)
    val_err = 1.0 - clf.score(x_val, y_val)
    n_branches = int(np.sum(clf.tree_.children_left != -1))

    # imprime os resultados separados por virgula para o c++ ler
    print(f"{train_err:.6f},{val_err:.6f},{n_branches}")

if __name__ == "__main__":
    main()
