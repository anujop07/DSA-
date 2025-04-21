#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Namespaces for convenience
using namespace std;
using namespace __gnu_pbds;

// Fast I/O
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr);

// Type aliases and constants
typedef long long ll;
const ll MOD = 1000000007;

// Ordered Set (Policy based data structure for order statistics)
template<typename T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ----------------------------------------------------------------
// Disjoint Set Union (DSU) for graph connectivity
struct DSU {
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int find(int a) {
        return parent[a] = (parent[a] == a ? a : find(parent[a]));
    }
    
    bool unionSets(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b)
            return false;
        if(rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if(rank[a] == rank[b])
            rank[a]++;
        return true;
    }
};

// ----------------------------------------------------------------
// Bit Manipulation: Iterate over all submasks of a bitmask
void iterateSubsets(int mask) {
    // Iterate over all non-empty submasks of 'mask'
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        // Process each submask (sub)
        // For example, count bits or test properties.
    }
    // Optionally handle the empty submask
}

// ----------------------------------------------------------------
// Prime checking function (Simple trial division)
bool isPrime(ll n) {
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// ----------------------------------------------------------------
// Modular arithmetic for nCr and nPr using precomputed factorials
const int MAX = 1000005;  // Adjust as necessary
vector<ll> fact(MAX), invFact(MAX);

// Fast exponentiation under modulo
ll modExp(ll base, ll exp, ll m = MOD) {
    ll result = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % m;
        base = (base * base) % m;
        exp /= 2;
    }
    return result;
}

// Precompute factorials and modular inverses
void precomputeFactorials() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
    
    invFact[MAX - 1] = modExp(fact[MAX - 1], MOD - 2);
    for (int i = MAX - 2; i >= 0; i--)
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
}

// nCr computation under modulo
ll nCr(int n, int r) {
    if (r < 0 || r > n)
        return 0;
    return ((fact[n] * invFact[r]) % MOD * invFact[n - r]) % MOD;
}

// nPr computation under modulo
ll nPr(int n, int r) {
    if (r < 0 || r > n)
        return 0;
    return (fact[n] * invFact[n - r]) % MOD;
}

// ----------------------------------------------------------------
// Graph Diameter for a general (undirected, unweighted) graph
// This function computes the diameter as the longest shortest path in the graph,
// along with one corresponding path. Note that for disconnected graphs, only
// vertices reachable from the starting vertex in the BFS will be considered.
pair<int, vector<int>> graphDiameter(const vector<vector<int>> &adj) {
    int n = adj.size();
    int maxDiameter = -1;
    vector<int> bestPath;
    
    // For every vertex, run a BFS to compute the farthest distance.
    for (int start = 0; start < n; start++) {
        vector<int> dist(n, -1), parent(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {  // unvisited
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        
        // Update maxDiameter if a longer distance is found.
        for (int i = 0; i < n; i++) {
            if (dist[i] > maxDiameter) {
                maxDiameter = dist[i];
                // Reconstruct the path from start to i
                vector<int> path;
                int cur = i;
                while (cur != -1) {
                    path.push_back(cur);
                    cur = parent[cur];
                }
                reverse(path.begin(), path.end());
                bestPath = path;
            }
        }
    }
    return {maxDiameter, bestPath};
}

// ----------------------------------------------------------------
// Main function demonstrating usage of the above utilities.
int main() {
    fastio;
    
    // Precompute factorials for nCr and nPr functions.
    precomputeFactorials();
    
    return 0;
}
