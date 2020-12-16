#include "stdc++.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Creating shortcut for an integer pair
typedef pair<int, int> iPair;

// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;

    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }

    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        /* Make tree with smaller height
        a subtree of the other tree */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result

    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(V);

    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << u << " - " << v << endl;

            // Update MST weight
            mst_wt += it->first;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

vector<vector<int>> read_csv(string filePath, int n) {
    vector<vector<int>> data;
    ifstream csvFile(filePath);
    if (!csvFile.is_open()) throw runtime_error("Could not open file");
    string row, col;
    int cost = 0;

    for(auto i = 0; i < n; i++) {
        vector<int> tmp;
        getline(csvFile, row);
        stringstream ss(row);

        for(auto j = 0; j < n; j++) {
            getline(ss, col, ',');
            stringstream col_str(col);
            col_str >> cost;
            //cout<<cost<<" ";
            tmp.push_back(cost);
        }
        data.push_back(tmp);
    }
    return data;
}

int main()
{
    for (auto i = 10; i <= 50; i += 10) {
        Graph g(i, i * i - i);
        /*
         * file path: /Users/twlin/NCTU/Courses/Advanced_Algorithms/hw5/src/test.csv
         * */
        vector<vector<int>> data = read_csv("/Users/twlin/NCTU/Courses/Advanced_Algorithms/hw5/src/test.csv", i);
        int index = 1, j = 1, k = 2;
        while (index++ < i) {
            g.addEdge(j, k, data[j - 1][k - 1]);
            g.addEdge(k, j, data[k - 1][j - 1]);
            j++;
            k++;
        }
        cout << "when # of nodes are " << i << ", Edges of MST are \n";
        int mst_wt = g.kruskalMST();
        cout << "Weight of MST is " << mst_wt << endl;
        cout << "\n===========================\n" << endl;
    }

    return 0;
}
