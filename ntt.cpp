#include "bits/stdc++.h"
using namespace std;

using u128 = __uint128_t;
#define int long long
#define endl '\n'

int mod, g, g_1;

int exp(int n, int e) {
    int res = 1;
    while (e) {
        if (e & 1) {
            res = (u128)res * n % mod;
        }
        n = (u128)n * n % mod;
        e >>= 1;
    }
    return res;
}

void init(){
    // mod : prime =  k * (2 ^ c) + 1;
    // g : primitive root of prime (mod);
    // g_1 : inverse of primitive root
    mod = 13, g = 2, g_1 = exp(g, mod - 2);
}

void ntt(vector<int> &p, bool inverse){
    int n = (int)p.size();
    if(n == 1) return;

    int w = inverse ? exp(g_1 , (mod - 1) / n) : exp(g , (mod - 1) / n);
    vector<int> pe , po;
    for(int i = 0 ; i < n ; i += 2){
        pe.push_back(p[i]);
        po.push_back(p[i+1]);
    }
    ntt(pe, inverse);
    ntt(po, inverse);
    for(int i = 0 ; i < n / 2 ; i++){
        p[i] = pe[i] + exp(w, i) * po[i];
        p[i + n/2] = pe[i] - exp(w, i) * po[i];
        p[i] %= mod;
        if(p[i] < 0) p[i] += mod;
        p[i + n/2] %= mod;
        if(p[i + n/2] < 0) p[i + n/2] += mod;
    }
}

vector<int> multiply(vector<int> &a, vector<int> &b){
    int n = 1;
    while(n < a.size() + b.size())
        n <<= 1;
    a.resize(n), b.resize(n);
    ntt(a, false);
    ntt(b, false);
    vector<int> res(n, 0);
    for(int i = 0 ; i < n ; i++){
        res[i] = a[i] * b[i] % mod;
    }
    ntt(res, true);
    int inv_n = exp(n , mod - 2);
    for(auto &i : res){
        i = i * inv_n % mod;
    }
    return res;
}

void solve(){
    init();
    vector<int> a = {2, 2} , b = {3, 5};
    vector<int> res = multiply(a , b);
    for(auto i : res){
        cout<<i<<" ";
    }
    cout<<endl;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
//    cin>>t;
    while(t--)
        solve();
    return 0;
}
