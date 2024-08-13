#include "../include/functions.h"

void FACT::initialize(const mc &n){
    size_t nl = num_length(n, 10);  

    B = min((long long) 100000, (long long) (300+ceil(exp(0.55*sqrt(num_length(n, 2)*log(2) * log(num_length(n, 2)*log(2)))))));
    intervalSize = 65536;
    MAX_IT = 100;

    if(nl > 56) intervalSize *= 3;
    if(nl > 94) intervalSize *= 3;
}

void FACT::createFB(const mc &n){
    factBase.clear();
    vector<bool> isp(B+1, 1);
    isp[0] = isp[1] = 0;

    for(ll i = 2; i < (ll)sqrt(B); i++) if(isp[i])
        for(ll j = i*i; j < B+1; j += i) isp[j] = false;

    for(ll i = 2; i < B+1; i++)
        if(isp[i] and legendre(n, mc(static_cast<unsigned long int>(i))) == 1) 
            factBase.eb(mc(static_cast<unsigned long int>(i))); 
}

void FACT::genSmooth(const mc &n, vm &smooth, vm &xlist){
    vm seq(intervalSize.get_ui()*2);
    mc res;

    for(mc i = root-intervalSize; i < root+intervalSize; i++)
        fexp(res, i, 2), seq.eb(res-n);

    vm sieved(seq);

    bool twob = (factBase[0] == 2);
    if(twob){
        int i = 0;
        while(sieved[i]%2 != 0) i++;

        mc two = 2;
        while(i < sz(sieved)) remove_fact(sieved[i], sieved[i], two), i += 2;
    }

    mc s1, s2, tmp;
    for(int i = twob ? 1 : 0; i < sz(factBase); i++){
        tonelliShanks(n, factBase[i], s1, s2);
        for (auto sol: {s1, s2}){
            mc t1 = (sol-root+intervalSize), t2 = factBase[i].get_ui();
            tmp = (t1%t2+t2)%t2;

            for(int j = tmp.get_ui(); j < sz(sieved); j += factBase[i].get_ui())
                remove_fact(sieved[j], sieved[j], factBase[i]);

            t1 = (sol-root+intervalSize), t2 = factBase[i];
            tmp = (t1%t2+t2)%t2+intervalSize;

            for (ll j = tmp.get_ui(); j > 0; j -= factBase[i].get_ui())
                remove_fact(sieved[j], sieved[j], factBase[i]);
        }
    }

    for(int i = 0; i < sz(sieved); i++){
        if(abs(sieved[i]) == 1) {
            smooth.eb(seq[i]);
            xlist.eb(i+root-intervalSize);
        }
    }
}

Matrix FACT::genMat(const vm &smooth, const mc &n){
    factBase.insert(factBase.begin(), -1);
    Matrix mat(sz(smooth), vm(factBase.size()));

    for(int i = 0; i < sz(smooth); i++){
        auto factors = get_pfactors(smooth[i], factBase);

        for (int j = 0; j < sz(factBase); j++)
            if(factors.find(factBase[j]) != factors.end())
                mat[i][j] = factors[factBase[j]]%2;
    }

    return transpose(mat);
}

void FACT::gauss(vector<vm> &a, vm& ans){
    ans = vm(a[0].size());

    for(int i = 0; i < sz(a); i++) for(int j = 0; j < sz(a[i]); j++) if(a[i][j]){
        ans[j] = true;
        for(int k = 0; k < sz(a); k++) if(k != i and a[k][j])
            for(size_t l = 0; l < sz(a[k]); l++)
                a[k][l] ^= a[i][l];

        break;
    }

    a = transpose(a);
}

vector<int> FACT::find_dep(const pair<vm, int> &solution, Matrix &mat, vm &ans){
    vector<int> sol_vec, indices;
    for(int i = 0; i < sz(solution.first); i++) if(solution.first[i] == 1)
        indices.push_back(i);

    for(int row = 0; row < sz(mat); row++)
        for(auto i : indices) if(mat[row][i] == 1 and ans[row])
            sol_vec.eb(row);

    sol_vec.eb(solution.second);
    return sol_vec;
}

bool FACT::quadSieve(const mc &n, mc &f1, mc &f2){
    big_sqrt(root, n);

    if(root*root == n){
        f1 = root, f2 = root;
        return true;
    }

    int is_p = mpz_probab_prime_p(n.get_mpz_t(), 50);
    if(is_p){
        f1 = 1, f2 = n;
        return true;
    }

    initialize(n);

    for(int ttt = 0; ttt < MAX_IT; ttt++){
        vm smooth, xlist;

        createFB(n);
        genSmooth(n, smooth, xlist);

        if(sz(smooth)){
            Matrix mat = genMat(smooth, n);

            vm ans;
            gauss(mat, ans);

            vector<pair<vm, int>> solRows;
            for(int i = 0; i < sz(ans); i++) if (!ans[i])
                solRows.eb({mat[i], i});

            mpz_class x, y;
            for (const auto &sol : solRows) {
                vector<int> solv = find_dep(sol, mat, ans);

                vm va, vb;
                for(auto i: solv) va.eb(smooth[i]), vb.eb(xlist[i]);
                
                x = 1;
                for(auto z: va) x *= z;
                x = abs(x);

                big_sqrt(x, x);

                y = 1;
                for(auto z: vb) y *= z;

                bgcd(f1, x-y, n);

                if(f1 != 1 and f1 != n) {
                    f2 = n/f1;
                    return true;
                }
            }
        }

        B += B/10, intervalSize += 500;
    }

    f1 = 1, f2 = n;
    return false;
}
