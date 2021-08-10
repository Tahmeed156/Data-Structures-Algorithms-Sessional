#include <bits/stdc++.h>
#define INF 99999
#define NIL -1

using namespace std;

typedef pair <int, int> nodePair;

class Graph {

    int nVertices, nEdges;
    vector <int> * ArrayList;
    vector <int> * Weights;
    int * parent, * distance;

    ifstream fin;
    ofstream fout;

public:

    int source, dest;

    Graph(int ver, int edg) {
        nVertices = ver;
        nEdges = edg;
        parent = new int [ver];
        distance = new int [ver];
        ArrayList = new vector <int> [ver];
        Weights = new vector <int> [ver];
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

        for (int i=0; i < nEdges; i++) {
            fin >> u >> v >> w;
            addEdge(u, v, w);
             cout << u << " " << v << " " << w << endl;
        }

        fin >> source >> dest;
        cout << source << " " << dest << endl;
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

    void dijkstra () {

        // Initializations
        for (int i=0; i<nVertices; i++) {
            distance[i] = INF;
            parent[i] = NIL;
        }
        priority_queue <nodePair, vector <nodePair>, greater<nodePair> > Q;

        distance[source] = 0;
        Q.push(make_pair(0, source));

        // One by one extract items from min heap
        while (!Q.empty()) {

            int u = Q.top().second;
            int dist = Q.top().first;
            Q.pop();

            for (int i=0; i < ArrayList[u].size(); i++) {

                int v = ArrayList[u][i];
                int position = searchEdge(u, v);
                int weightUV = abs(Weights[u][position]); // CHANGE - take abs

                if (distance[v] > distance[u] + weightUV) {
                    distance[v] = distance[u] + weightUV;
                    parent[v] = u;
                    Q.push(make_pair(distance[v], v));
                }
            }
        }

    }

    bool bellmanFord () {

        // Initializations
        for (int i=0; i<nVertices; i++) {
            distance[i] = INF;
            parent[i] = NIL;
        }
        distance[source] = 0;

        // Loop over vertices
        for (int i=0; i<nVertices; i++) {

            // Loop over edges
            for (int u=0; u<nVertices; u++) {
                int * data = ArrayList[u].data();
                for (int k=0; k<ArrayList[u].size(); k++) {

                    int v = ArrayList[u][k];
                    int position = searchEdge(u, v);
                    int weightUV = Weights[u][position];

                    if (distance[v] > distance[u] + weightUV) {
                        distance[v] = distance[u] + weightUV;
                        parent[v] = u;
                    }

                }
            }
        }

        // Loop over edges
        for (int u=0; u<nVertices; u++) {
            int * data = ArrayList[u].data();

            for (int k=0; k<ArrayList[u].size(); k++) {

                int v = ArrayList[u][k];
                int position = searchEdge(u, v);
                int weightUV = Weights[u][position];

                if (distance[v] > distance[u] + weightUV) {
                    return false;
                }

            }
        }

        return true;

    }

    void offlineOutput(string file) {

        fout.open(file, ios::out);

        fout << "Bellman Ford Algorithm: " << endl;
        bool success = bellmanFord();
        if (success) {
            fout << distance[dest] << endl;
            pathToSource(source, dest);
            fout << endl;
        }
        else {
            fout << "Negative Weight Cycles present :(" << endl;
        }

        fout << "\nDijkstra Algorithm: " << endl;
        dijkstra();
        fout << distance[dest] << endl;
        pathToSource(source, dest);

        fout.close();
    }

    void pathToSource (int source, int dest) {

        if (source == dest) {
            fout << source;
            return;
        }
        pathToSource(source, parent[dest]);
        fout << " -> " << dest;
    }

};

int main () {

    Graph G("test/in.txt");
    G.offlineOutput("out.txt");
}
