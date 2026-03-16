#include<bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

int exp(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void test_case() {
    int message = 11001898;
    cout<<"Message: "<<message<<endl;

    int keyA = 82928; // random key
    int encrypted_message = (message * keyA) % mod;
    cout<<"Encrypted message by client: "<<encrypted_message<<endl;

    int keyB = 92849; // random key
    int double_encrypted_message = (encrypted_message * keyB) % mod;
    cout<<"Encrypted message by server passed by client: "<<double_encrypted_message<<endl;

    int double_decrypted_message = (double_encrypted_message * exp(keyA, mod-2, mod)) % mod;
    cout<<"Decrypted message by client passed by server: "<<double_decrypted_message<<endl;

    int original_message = (double_decrypted_message * exp(keyB, mod-2, mod)) % mod;
    cout<<"Original message read by server sent by client: "<<original_message<<endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) test_case();
    return 0;
}
