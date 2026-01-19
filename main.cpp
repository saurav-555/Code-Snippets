#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using u128 = __uint128_t;

#define int long long
#define order_tree tree<int, null_type, less<>, rb_tree_tag,tree_order_statistics_node_update>
#define MOD 1000000007
#define MAX 200005

int dp[MAX];

class BloomFilter {
    double acceptance_false_positive_probability;
    int capacity;
    int required_bits;
    int hash_functions_count;

    vector<bool> bits;

    size_t do_hash(const string &s, const int ith) const {
        static hash<string> hasher;
        return (hasher(s) + ith * MOD) % required_bits;
    }

public:
    BloomFilter(double acceptance_false_positive_probability, double capacity) {
        this->acceptance_false_positive_probability = acceptance_false_positive_probability;
        this->capacity = static_cast<int>(capacity);
        this->hash_functions_count = ceil(
            -log(acceptance_false_positive_probability) / log(2)
        );
        this->required_bits = ceil(capacity * (-log(acceptance_false_positive_probability) / (log(2.0f) * log(2.0f))));

        cout<<"Acceptance false positive probability: " << (this->acceptance_false_positive_probability)<<endl;
        cout<<"Capacity: " << (this->capacity)<<endl;
        cout<<"Required bits: " << (this->required_bits)<<endl;
        cout<<"Hash function count: " << (this->hash_functions_count)<<endl;

        this->bits.resize(this->required_bits, false);
    }

    void add(const string &s) {
        for (int i = 0 ; i < hash_functions_count ; i++) {
            const size_t pos = do_hash(s, i);
            bits[pos] = true;
        }
    }

    bool mightContain(string &s) {
        for (int i = 0 ; i < hash_functions_count ; i++) {
            const size_t pos = do_hash(s, i);
            if (!bits[pos]) {
                return false;
            }
        }
        return true;
    }
};


void test_case() {
    BloomFilter bloom_filter(0.01, 1000000);

    vector<string> friends = {
        "Saurav",
        "Mayank",
        "Heena",
        "Arijit",
        "Nirbhay"
    };
    for (auto &friend_: friends) {
        bloom_filter.add(friend_);
    }

    for (auto &friend_ : friends) {
        cout<<"Bloom Filter does contain: "<<friend_ <<" -> "<<(bloom_filter.mightContain(friend_) ? "Yes": "No")<<endl;
    }
    vector<string> other_friends = {
        "Rupesh",
        "Mukesh",
        "Aayush",
    };

    for (auto &friend_ : other_friends) {
        cout<<"Bloom Filter does contain: "<<friend_ <<" -> "<<(bloom_filter.mightContain(friend_) ? "Yes": "No")<<endl;
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin>>t;
    while (t--) test_case();
    return 0;
}
