#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 1000000007

class CountMinSketch {
    double err_rate; // defines error in answer
    double err_probability; // defines probability in answer;
    int width; // defines required width of data structure
    int depth; // defines hash function count and depth of data structure
    int total_element_cnt; // total entries (to estimate threshold)

    vector<vector<int>> sketch;

    size_t do_hash(const string &s, const int ith) const {
        static hash<string> hasher;
        return (hasher(s) + ith * MOD) % width;
    }

public:
    CountMinSketch(double err_rate, double err_probability) {
        this->err_rate = err_rate;
        this->err_probability = err_probability;
        this->depth = ceil(-log(err_probability));
        this->width = ceil(numbers::e / err_rate);

        cout<<"Error probability (possibility of an error): " << (this->err_probability)<<endl;
        cout<<"Error rate (how large is the error): " << (this->err_rate)<<endl;
        cout<<"Sketch width: " << (this->width)<<endl;
        cout<<"Sketch depth (Hash function count): " << (this->depth)<<endl;

        sketch.assign(depth, vector<int>(width, 0));
        total_element_cnt = 0;
    }

    void add(const string &s) {
        for (int i = 0 ; i < depth ; i++) {
            const size_t pos = do_hash(s, i);
            sketch[i][pos]++;
        }
        total_element_cnt++;
    }

    int upperBound(const string &s) {
        int mini = INT_MAX;
        for (int i = 0 ; i < depth ; i++) {
            const size_t pos = do_hash(s, i);
            mini = min(mini, sketch[i][pos]);
        }
        int threshold = ceil(err_rate * static_cast<double>(total_element_cnt));
        cout<<"Threshold (Any freq <= this should be ignore): "<<threshold<<endl;
        return mini;
    }
};


void test_case() {
    CountMinSketch cnt_min_sketch(0.01, 0.01);
    map<string, int> freq;
    freq["Saurav"] = 20;
    freq["Heena"] = 6;
    freq["Mayank"] = 30;
    freq["Nirbhay"] = 8;
    freq["Arijit"] = 15;

    for (auto &ii: freq) {
        for (int i = 0 ; i < ii.second ; i++) {
            cnt_min_sketch.add(ii.first);
            int ttl = cnt_min_sketch.upperBound(ii.first);
            cout<<"Total (" + ii.first + "): "<<ttl<<endl;
        }
    }

    cout<<endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin>>t;
    while (t--) test_case();
    return 0;
}
