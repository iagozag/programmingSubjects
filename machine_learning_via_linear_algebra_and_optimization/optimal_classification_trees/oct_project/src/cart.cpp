#include "cart.h"
#include "datagen.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>

CARTResult runCART(const Dataset& train, const Dataset& val, int max_depth, int min_samples_leaf) {
    saveDataset(train, "/tmp/cart_train.csv");
    saveDataset(val, "/tmp/cart_val.csv");

    // invoca o arquivo python externo
    std::string cmd = "python3 cart.py /tmp/cart_train.csv /tmp/cart_val.csv " + 
                      std::to_string(max_depth) + " " + std::to_string(min_samples_leaf) + 
                      " > /tmp/cart_out.txt 2>/tmp/cart_err.txt";

    if (system(cmd.c_str()) != 0) {
        throw std::runtime_error("erro ao rodar o script python do cart");
    }

    std::ifstream outf("/tmp/cart_out.txt");
    std::string line, tok;
    std::getline(outf, line);
    std::istringstream ss(line);

    CARTResult res;
    std::getline(ss, tok, ','); res.train_error = std::stod(tok);
    std::getline(ss, tok, ','); res.val_error = std::stod(tok);
    std::getline(ss, tok, ','); res.n_branches = std::stoi(tok);
    
    return res;
}