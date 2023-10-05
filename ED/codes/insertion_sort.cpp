#include<bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

int main(){ _
    int n; cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i];

    int j, key;
    for(int i = 1; i < n; i++){
        key = arr[i], j = i-1;
        while(j >= 0 && key < arr[j])
            arr[j+1] = arr[j], j--;
        arr[j+1] = key;
    }

    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl; 

    exit(0);
}
