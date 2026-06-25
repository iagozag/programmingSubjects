#include "cart.h"
#include "datagen.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

CARTResult runCART(const Dataset& train,
                   const Dataset& val,
                   int max_depth,
                   int min_samples_leaf) {
    // Write datasets to temp files
    saveDataset(train, "/tmp/cart_train.csv");
    saveDataset(val,   "/tmp/cart_val.csv");

    // Write a small Python script
    std::ofstream pyf("/tmp/run_cart.py");
    pyf << "import sys\n"
        << "import csv\n"
        << "from sklearn.tree import DecisionTreeClassifier\n"
        << "import numpy as np\n"
        << "\n"
        << "def load(path):\n"
        << "    with open(path) as f:\n"
        << "        reader = csv.reader(f)\n"
        << "        header = next(reader)\n"
        << "        n, p, K = int(header[0]), int(header[1]), int(header[2])\n"
        << "        rows = [list(map(float, row)) for row in reader]\n"
        << "    X = np.array([r[:-1] for r in rows])\n"
        << "    y = np.array([int(r[-1]) for r in rows])\n"
        << "    return X, y\n"
        << "\n"
        << "X_train, y_train = load('/tmp/cart_train.csv')\n"
        << "X_val,   y_val   = load('/tmp/cart_val.csv')\n"
        << "\n"
        << "clf = DecisionTreeClassifier(\n"
        << "    criterion='gini',\n"
        << "    max_depth=" << max_depth << ",\n"
        << "    min_samples_leaf=" << min_samples_leaf << ",\n"
        << "    random_state=42\n"
        << ")\n"
        << "clf.fit(X_train, y_train)\n"
        << "\n"
        << "train_err = 1.0 - clf.score(X_train, y_train)\n"
        << "val_err   = 1.0 - clf.score(X_val,   y_val)\n"
        << "n_branches = clf.tree_.node_count // 2  # internal nodes\n"
        << "\n"
        << "print(f'{train_err:.6f},{val_err:.6f},{n_branches}')\n";
    pyf.close();

    // Run the script
    int ret = system("python3 /tmp/run_cart.py > /tmp/cart_out.txt 2>/tmp/cart_err.txt");
    if (ret != 0) {
        std::ifstream ef("/tmp/cart_err.txt");
        std::string errmsg((std::istreambuf_iterator<char>(ef)), std::istreambuf_iterator<char>());
        throw std::runtime_error("CART python script failed:\n" + errmsg);
    }

    std::ifstream outf("/tmp/cart_out.txt");
    std::string line;
    std::getline(outf, line);
    std::istringstream ss(line);
    std::string tok;

    CARTResult res;
    std::getline(ss, tok, ','); res.train_error = std::stod(tok);
    std::getline(ss, tok, ','); res.val_error   = std::stod(tok);
    std::getline(ss, tok, ','); res.n_branches  = std::stoi(tok);
    return res;
}
