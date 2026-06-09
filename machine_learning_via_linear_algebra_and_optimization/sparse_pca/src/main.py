# global variables
Q = None
K = 0
n = 0
maxDepth = 0
deadSize = 0
eps = 0.000001
eigMaxIter = 500
eigConv = 0.00001
num_nodes = 0
iter_nodes = 0
first_ub = 0
nodes = []
INF = float('inf')


# represents a node in the SPCA Branch-and-Bound tree
class Node:
    def __init__(self, l, u, lower, upper):
        self.l = l
        self.u = u
        self.lower = lower
        self.upper = upper
        self.alive = 1


# initializes global parameters for SPCA execution
def init(Q_, K_, maxDepth_, eps_):
    global Q, K, n, maxDepth, deadSize, eps, num_nodes, iter_nodes, first_ub, nodes
    Q = Q_
    K = K_
    n = Q.shape[0]
    maxDepth = maxDepth_
    deadSize = 5000
    eps = eps_
    num_nodes = 0
    iter_nodes = 0
    first_ub = 0
    nodes = []


# keeps the k most relevant entries respecting branching constraints
def trunc(s, l, u, k):
    I1 = np.where(l == 1)[0]
    need = k-len(I1)
    
    if need > 0:
        free = np.where((l == 0) & (u == 1))[0]
        s2 = np.abs(s[free])
        sorted_idx = np.argsort(s2)[::-1]
        top_idx = sorted_idx[:need]
        I2 = free[top_idx]
    else:
        I2 = np.array([], dtype=int)
        
    I = np.concatenate((I1, I2)).astype(int)
    
    ans = np.zeros_like(s)
    ans[I] = s[I]

    return ans


# restricts Q to the currently feasible support
def q_hat(mat, u):
    Q = mat.copy()

    y_del = (u == 0)
    Q[y_del, :] = 0
    Q[:, y_del] = 0

    return Q


# power method with Rayleigh quotient
def max_eig(Q, maxIter = eigMaxIter):
    global n, eigConv

    lam_prev = None
    x = np.ones(n)
    x = x / np.linalg.norm(x)

    for i in range(maxIter):
        y = Q @ x

        if np.linalg.norm(y) == 0: 
            return 0, x
            
        x = y / np.linalg.norm(y)
        lam = (x.T @ (Q @ x)).item()

        if lam_prev is not None and abs(lam-lam_prev) < eigConv:
            break
        
        lam_prev = lam

    return lam, x


# terminal nodes correspond to fixed supports
def isTerminal(node):
    global K
    return sum(node.l) >= K or sum(node.u) <= K


# depth-first selection when node list becomes large
def depthSelect():
    global num_nodes, nodes
    nd = num_nodes - 1
    while isTerminal(nodes[nd]) or not nodes[nd].alive:
        nd = nd - 1
        if nd == -1:
            return nd
    return nd


# best-bound node selection
def bestSelect():
    global num_nodes, nodes
    nd = -1
    ma = 0
    for i in range(num_nodes):
        node = nodes[i]
        if node.alive and ma < node.upper:
            nd = i
            ma = node.upper
    return nd


# hybrid node selection strategy from the assignment
def select_node():
    global nodes, num_nodes, maxDepth
    n_alive = sum(node.alive for node in nodes[:num_nodes])
    if n_alive == 0:
        return -1

    if n_alive > maxDepth:
        return depthSelect()

    return bestSelect()


# branch on the largest magnitude entry of the leading eigenvector
def select_idx(node):
    global Q

    qh = q_hat(Q, node.u)
    _, v = max_eig(qh)
    
    idx = -1
    ma = -1
    for i in range(n):
        if node.l[i] == 0 and node.u[i] == 1:
            if abs(v[i]) > ma:
                ma = abs(v[i])
                idx = i
                
    return idx if idx != -1 else 0


# first lower bound based on truncated dominant eigenvector
def calc_lb1(node):
    global Q, n, K

    qh = q_hat(Q, node.u)

    val, vec = max_eig(qh)
    vec = trunc(vec, node.l, node.u, K)
    y = np.where(vec != 0)[0]
    new_u = np.zeros(n)
    for i in y:
        new_u[i] = 1

    qh2 = q_hat(qh, new_u)
    lb, v = max_eig(qh2)

    return v, lb


# iterative sparse power method lower bound
def calc_lb2(node, maxIter = eigMaxIter):
    global Q, n, K, eps

    qh = q_hat(Q, node.u)
    _, v = max_eig(qh)
    x = trunc(v, node.l, node.u, K)
    x = x / np.linalg.norm(x)

    x_prev = np.zeros(n)

    for _ in range(maxIter):
        if np.linalg.norm(x - x_prev) < eps:
            break

        x_prev = x.copy()
        
        y = Q @ x
        y2 = trunc(y, node.l, node.u, K)
        x = y2 / np.linalg.norm(y2)

    lb = x.T @ Q @ x
    return x, lb


# uses the best available lower bound
def calc_lower(node):
    x1, lb1 = calc_lb1(node)
    x2, lb2 = calc_lb2(node)
    
    if lb1 > lb2:
        return x1, lb1

    return x2, lb2


# spectral upper bound
def calc_ub1(node):
    global Q
    
    qh = q_hat(Q, node.u)
    val, _ = max_eig(qh)

    return val


# diagonal-based upper bound
def calc_ub2(node):
    global Q, K

    s = np.diag(Q)
    ans = trunc(s, node.l, node.u, K)
    
    return np.sum(ans)


# column-sum upper bound
def calc_ub3(node):
    global Q, K, n
    ans = 0
    
    for j in range(n):
        if node.u[j] == 1:
            s = np.abs(Q[:, j])
            arr = trunc(s, node.l, node.u, K)
            cur = np.sum(arr)
            
            ans = max(ans, cur)
                
    return ans


# final upper bound is the minimum among valid bounds
def calc_upper(node):
    return min(calc_ub1(node), calc_ub2(node), calc_ub3(node))


# SPCA Branch-and-Bound procedure
def branchAndBound():
    global Q, n, eps, deadSize, nodes, num_nodes, iter_nodes, first_ub

    # instantiate first node
    node_0 = Node(np.zeros(n), np.ones(n), 0, INF)
    nodes.append(node_0)
    num_nodes = 1

    x_hat = np.zeros(n)

    lb = 0
    ub, _ = max_eig(Q)
    first_ub = ub

    # while is not optimal, try a new node
    while (ub - lb)/ub > eps:
        # select node
        selected_node = select_node()
        if selected_node == -1:
            break

        iter_nodes = iter_nodes+1

        # select a index to branch
        idx = select_idx(nodes[selected_node])

        lower_revised = False
        
        for val in range(2):
            new_node = copy.deepcopy(nodes[selected_node])
            
            # branching decision
            if val == 0:
                new_node.u[idx] = 0
            else:
                new_node.l[idx] = 1

            if isTerminal(new_node):
                # terminal nodes reduce to classical PCA on fixed support
                supp = new_node.l if sum(new_node.l) >= K else new_node.u

                qh = q_hat(Q, supp)
                lam, vec = max_eig(qh)
                new_node.lower = lam
                new_node.upper = lam
                x = vec
            else:
                x, new_node.lower = calc_lower(new_node)
                new_node.upper = calc_upper(new_node)

            # updates incumbent solution
            if lb < new_node.lower:
                lb = new_node.lower
                x_hat = x
                lower_revised = True
                
                # prunes dominated nodes
                for i in range(num_nodes):
                    if nodes[i].upper <= lb:
                        nodes[i].alive = 0

            if new_node.upper > lb:
                nodes.append(new_node)
                num_nodes += 1
        
        nodes[selected_node].alive = 0

        # periodic cleanup of dead nodes
        if lower_revised or len(nodes) > deadSize:
            nodes = [n for n in nodes if n.alive and n.upper > lb]
            num_nodes = len(nodes)
        
        if num_nodes > 0:
            ub = max(n.upper for n in nodes)
        else:
            ub = lb

    return x_hat


def read_input(file_path, is_cov = False, label_col_index=None, normalize=True, top_features=None, skip_first_row=False):
    # loads dataset and builds covariance matrix
    if skip_first_row:
        df = pd.read_csv(file_path, skiprows=1, header=None)
    else:
        df = pd.read_csv(file_path, header=None)

    if is_cov:
        Sigma = df.values.astype(float)
        return Sigma
    
    if label_col_index is not None:
        X = df.drop(df.columns[label_col_index], axis=1).values
    else:
        X = df.values
        
    X = X.astype(float)

    # feature filtering for colon dataset
    if top_features is not None:
        variances = np.var(X, axis=0, ddof=1)
        top_idx = np.argsort(variances)[::-1][:top_features]
        X = X[:, top_idx]
    
    # standardization before covariance computation
    if normalize:
        mean_vec = np.mean(X, axis=0)
        std_vec = np.std(X, axis=0, ddof=1)
        std_vec[std_vec == 0] = 1.0
        X = (X - mean_vec) / std_vec
    else:
        X = X - np.mean(X, axis=0)
        
    Sigma = np.cov(X, rowvar=False)
    
    return Sigma


def main():
    if len(sys.argv) < 3:
        print("Usage: python3 main.py <filename> <K>")
        sys.exit(1)

    filename = sys.argv[1]
    K = int(sys.argv[2])

    try:
        if filename == "pitprops":
            filepath = "../datasets/pitprops/pitprops.csv"
            Q = read_input(filepath, is_cov=True)
        elif filename == "wine":
            filepath = "../datasets/wine/wine.data"
            Q = read_input(filepath, is_cov=False, label_col_index=0, normalize=True)
        elif filename == "spambase":
            filepath = "../datasets/spambase_uci/spambase.data"
            Q = read_input(filepath, is_cov=False, label_col_index=-1)
        elif filename == "colon":
            filepath = "../datasets/colon_microarray_alon/colon.csv"
            Q = read_input(filepath, is_cov=False, label_col_index=[0, -1], top_features=80, skip_first_row=True)
    except FileNotFoundError:
        print(f"File not found.")
        return

    init(Q, K, 50, 0.0001)

    output_dir = f"../data/{filename}"
    os.makedirs(output_dir, exist_ok=True)

    output_file_path = f"{output_dir}/{filename}_{K}.data"
    original_stdout = sys.stdout

    sys.stdout = open(output_file_path, 'w')
    
    print(f"Starting SPCA for K={K}...\n")

    global iter_nodes

    old_Q = Q.copy()
    total_variance = np.trace(old_Q)
    
    components = []
    ratio = 0.0
    r = 0
    total_nodes = 0
    total_time = 0

    # extract sparse components until 70% explained variance
    while ratio < 0.70:
        r += 1
        print(f"\Component {r}:")
        
        init(Q, K, 50, 0.0001)

        iter_nodes = 0

        start = time.time()
        x_hat = branchAndBound()
        end = time.time()

        x_hat[np.abs(x_hat) < 1e-9] = 0
        components.append(x_hat)
        total_nodes = total_nodes+iter_nodes
        total_time = total_time+(end-start)

        obj_val = x_hat.T @ Q @ x_hat
        nonzero_idx = np.where(x_hat != 0)[0]
        
        print(f"Non-zero features: {len(nonzero_idx)}")
        print(f"Selected Indices: {nonzero_idx}")
        print(f"Weights: {x_hat[nonzero_idx]}")
        print(f"Obj Val: {obj_val:.6f}")
        print(f"Time: {end - start:.2f} seconds")
        print(f"Nodes Explored: {iter_nodes}")
        
        gap = ((first_ub - obj_val) / first_ub) * 100 if first_ub > 0 else 0
        print(f"Gap: {gap:.4f}%\n")
        
        # deflation step
        z = x_hat.reshape(-1, 1)
        I = np.eye(n)
        P = I - (z @ z.T)
        Q = P @ Q @ P 
        
        # QR-based explained variance computation
        W_r = np.column_stack(components)
        U_r, _ = np.linalg.qr(W_r)
        
        explained_var = np.trace(U_r.T @ old_Q @ U_r)
        ratio = explained_var / total_variance
        
        print(f"accumulated variance ratio: {ratio:.4f} ({(ratio*100):.2f}%)\n")


    print(f"Total time: {total_time:.2f} seconds")
    print(f"Total nodes explored: {total_nodes}\n")

    sys.stdout.close()
    sys.stdout = original_stdout


if __name__ == "__main__":
    main()