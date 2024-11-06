#include <vector>
using namespace std;

class DisjointSetUnion {
public:
    DisjointSetUnion(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Each node is initially its own parent
        }
    }

    int find(int x) {
        // Path compression
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Recursively make parent the root
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

// Example usage
int main() {
    DisjointSetUnion dsu(10);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);
    dsu.unionSets(2, 3);

    // Checking if 1 and 4 are in the same set
    if (dsu.find(1) == dsu.find(4)) {
        // Output True
    }
    if (dsu.find(1) != dsu.find(5)) {
        // Output False
    }
    return 0;
}
