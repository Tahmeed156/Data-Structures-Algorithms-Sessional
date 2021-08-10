#include <bits/stdc++.h>
#define INF 99999
#define NIL -1

using namespace std;

typedef pair <int, int> nodePair;

class Edge {

public:

    int u;
    int v;
    int w;

    Edge (int u_, int v_, int w_) {
        u = u_;
        v = v_;
        w = w_;
    }

    ~ Edge () {
        u = 0;
        v = 0;
        w = 0;
    }

    bool operator < (const Edge & edge) {
        return w < edge.w;
    }

};

class DisjointSet {

    int * parent;
    int * rank;

public:

    DisjointSet (int n) {
        parent = new int [n];
        rank = new int [n];
    }

    ~DisjointSet () {
        delete [] parent;
        delete [] rank;
    }

    void makeSet (int a) {
        parent[a] = a;
        rank[a] = 0;
    }

    int findSet (int a) {
        if (a != parent[a])
            parent[a] = findSet(parent[a]);
        return parent[a];
    }

    void unionByRank (int a, int b) {
        if (rank[a] > rank[b]) {
            parent[b] = a;
        }
        else {
            parent[a] = b;
            if (rank[a] == rank[b])
                rank[b] = rank[b] + 1;
        }
    }

};

class Graph {

    int nVertices, nEdges;
    vector <int> * ArrayList;
    vector <int> * Weights;
    vector <Edge> * Edges;
    int * parent, * distance;

    ifstream fin;
    ofstream fout;
    ostream * out;
    bool fileInput;

public:

    int source, dest;

    /// G R A P H functions

    Graph(int ver, int edg) {
        nVertices = ver;
        nEdges = edg;
        parent = new int [ver];
        distance = new int [ver];
        ArrayList = new vector <int> [ver];
        Weights = new vector <int> [ver];
    }

    ~Graph() {
        nVertices = 0;
        nEdges = 0;
        delete [] parent;
        delete [] distance;
        delete [] ArrayList;
        delete [] Weights;
    }


    Graph(string file) {

        int u, v, w;
        fin.open(file, ios::in);

        fin >> nVertices >> nEdges; // Vertices, Edges
        cout << nVertices << " " << nEdges << endl;

        parent = new int [nVertices];
        distance = new int [nVertices];
        ArrayList = new vector <int> [nVertices];
        Weights = new vector <int> [nVertices];
        Edges = new vector <Edge> [nEdges]; // for Kruskal

        for (int i=0; i < nEdges; i++) {
            fin >> u >> v >> w;
            addEdge(u, v, w);
            addEdge(v, u, w);
            Edges->push_back(Edge(u, v, w));
            cout << u << " " << v << " " << w << endl;
        }

        fin.close();

    }

    int searchEdge (int u, int v) {
        int * data = ArrayList[u].data();
        for (int i=0; i<ArrayList[u].size(); i++)
            if (data[i] == v)
                return i;
        return NIL;
    }

    void addEdge(int u, int v, int w) {
            ArrayList[u].push_back(v);
            Weights[u].push_back(w);
    }

    int getWeight (int u, int v) {
        int position = searchEdge(u, v);
        if (position == NIL)
            return INF;
        else
            return Weights[u][position];
    }

    /// M S T functions

    void prims (int source_) {

        // Initializations
        source = source_;
        bool visited [nVertices];
        for (int i=0; i<nVertices; i++) {
            distance[i] = INF;
            visited[i] = false;
        }

        priority_queue <nodePair, vector <nodePair>, greater<nodePair> > Q;
        distance[source] = 0;
        parent[source] = NIL;
        Q.push(make_pair(0, source));

        // One by one extract items from min heap
        while (!Q.empty()) {

            int u = Q.top().second;
            int dist = Q.top().first;
            visited[u] = true;
            Q.pop();

            // Looping over adjacent nodes
            for (int i=0; i < ArrayList[u].size(); i++) {
                int v = ArrayList[u][i];

                int w = getWeight(u, v);

                if (!visited[v] && distance[v] > w) {
                    distance[v] = w;
                    parent[v] = u;
                    Q.push(make_pair(distance[v], v));
                }
            }
        }

    }

    void kruskal () {

        DisjointSet D(nVertices);
        int total = 0;

        for (int i=0; i<nVertices; i++) { // O(V)
            D.makeSet(i);
        }

        sort(Edges->begin(), Edges->end()); // O(E.lgE)

        for(vector <Edge>::iterator e = Edges->begin(); e != Edges->end(); ++e) {

            int u = (*e).u;
            int v = (*e).v;
            int w = (*e).w;

            if (D.findSet(u) != D.findSet(v)) {
                total = total + w;
                (*out) << u << " " << v << endl;
                D.unionByRank(D.findSet(u), D.findSet(v));
            }
        }
        cout << total << endl;
    }


    /// I / O functions

    void offlineOutput(int source_, string file="") {

        if (file == "") {
            fileInput = false;
        }
        else {
            fout.open(file, ios::out);
            fileInput = true;
            cout << "Output to file '" << file << "'!" << endl;
        }


        (fileInput) ? out = &fout: out = &cout;

        prims(source_);
        (*out) << "Prim’s Algorithm:" << endl;
        (*out) << "Root node = " << source << endl;
        printMst();
        printMstWeight();

        (*out) << "Kruskal’s algorithm:" << endl;
        kruskal();
//        printMstWeight();

        if (fileInput)
            fout.close();
    }

    void printMst () {
        // OPTIONAL FILE / CONSOLE output
        for (int i=0; i<nVertices; i++) {
            if (i == source)
                continue;
            (*out) << i << " " << parent[i] << endl;
        }
    }

    void printMstWeight () {
        int cnt = 0;
        for (int i=0; i<nVertices; i++) {
            cnt += distance[i];
        }
        (*out) << cnt << endl;
    }

};

int main () {

    int source = 0;

    Graph G("in.txt");
    G.offlineOutput(source);
}
