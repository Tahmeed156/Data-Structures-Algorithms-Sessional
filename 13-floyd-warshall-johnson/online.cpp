#include <bits/stdc++.h>
#define INF 9999999
#define NIL -1

using namespace std;

typedef pair <double, int> nodePair;

class Graph {

    int nVertices, nEdges;
    vector <int> * ArrayList;
    vector <double> * Weights;

    int * parent;
    double * distance;
    int ** parentMatrix;
    double ** distanceMatrix;

    ofstream fout;

public:

    int source, dest;

    Graph() {}

    Graph (Graph & puraton) {

        // cout << "New Graph Created" << endl;
        // Adding regular vertices, +1 s vertex
        nVertices = puraton.nVertices + 1;
        setnVertices(nVertices);

        // Copy weights of regular vertices
        for (int u=0; u < puraton.nVertices; u++) {
            int * data = puraton.ArrayList[u].data();
            for (int i=0; i<puraton.ArrayList[u].size(); i++) {
                // cout << u << " " << data[i] << " " << puraton.getWeight(u, data[i]) << endl;
                addEdge(u, data[i], puraton.getWeight(u, data[i]));
            }
        }

        // Edge from s to all vertices, weight 0
        for (int u=0; u<nVertices-1; u++) {
            // cout << nVertices-1 << " " << u << " " << 0 << endl;
            addEdge(nVertices-1, u, 0);
        }

    }

    ~ Graph () {
        for (int i=0; i<nVertices; i++) {
            delete [] distanceMatrix[i];
            delete [] parentMatrix[i];
        }
        delete [] parent, distance, distanceMatrix, parentMatrix;
    }

    /// G R A P H functions

    void setnVertices (int n) {

        nVertices = n;
        ArrayList = new vector <int> [n];
        Weights = new vector <double> [n];

        distance = new double [n];
        parent = new int [n];
        distanceMatrix = new double * [n];
        parentMatrix = new int * [n];

        for (int i=0; i<n; i++) {
            distanceMatrix[i] = new double [n];
            parentMatrix[i] = new int [n];
        }
    }

    int searchEdge (int u, int v) {
        int * data = ArrayList[u].data();
        for (int i=0; i<ArrayList[u].size(); i++)
            if (data[i] == v)
                return i;
        return NIL;
    }

    bool isEdge (int u, int v) {
        return searchEdge(u, v) != NIL;
    }

    void addEdge(int u, int v, double w) {
        ArrayList[u].push_back(v);
        Weights[u].push_back(w);
    }

    void reweightEdge (int u, int v, double w) {
        int position = searchEdge(u, v);
        if (position == NIL)
            cout << "Edge " << u << " " << v << " not present" << endl;
        Weights[u][position] = w;
    }

    double getWeight (int u, int v) {
        int position = searchEdge(u, v);
        if (position == NIL)
            return INF;
        else
            return Weights[u][position];
    }

    double getDistance (int v) {
        return distance[v];
    }

    double getParent (int v) {
        return parent[v];
    }

    double getShortestPathWeight (int u, int v) {
        return distanceMatrix[u][v];
    }

    /// A L G O R I T H M S

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
            double dist = Q.top().first;
            Q.pop();

            for (int i=0; i < ArrayList[u].size(); i++) {

                int v = ArrayList[u][i];
                double w = getWeight(u, v);
                // w = abs(w);

                if (distance[v] > distance[u] + w) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                    Q.push(make_pair(distance[v], v));
                }
            }
        }

    }

    void floydWarshall () {

        cout << "Floyd-Warshall algorithm implemented" << endl;

        // Set initial distances to edge weights
        for (int i=0; i<nVertices; i++) {
            for (int j=0; j<nVertices; j++) {
                distanceMatrix[i][j] = getWeight(i, j);
                if (distanceMatrix[i][j] == INF)
                    parentMatrix[i][j] = NIL;
                else
                    parentMatrix[i][j] = i;
            }
        }

        // Set diagonals to 0
        for (int i=0; i<nVertices; i++) {
            distanceMatrix[i][i] = 0;
        }

        for (int k=0; k<nVertices; k++) {
            for (int i=0; i<nVertices; i++) {
                for (int j=0; j<nVertices; j++) {
                    if (distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j]) {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j];
                    }
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
                    double w = getWeight(u, v);

                    if (distance[v] > distance[u] + w) {
                        distance[v] = distance[u] + w;
                        parent[v] = u;
                    }
//                    cout << distance[v] << " " << distance[u] << " " << w << endl;

                }
            }
        }

        // Loop over edges
        for (int u=0; u<nVertices; u++) {

            int * data = ArrayList[u].data();

            for (int k=0; k<ArrayList[u].size(); k++) {

                int v = ArrayList[u][k];
                double w = getWeight(u, v);

                if (distance[v] > distance[u] + w) {
                    return false;
                }

            }
        }

        return true;

    }

    void johnsonsAlgo () {

        cout << "Johnson’s algorithm implemented" << endl;
        // Create new graph G', with new source
        // Add 0 weights edges from source
        Graph G = * this;

        G.source = G.nVertices - 1; // new vertex (s) as source
        if (!G.bellmanFord()) {
            cout << "There is a negative-weight cycle :(" << endl;
            return;
        }

        // Saving weights from bellman ford
        for (int v=0; v < nVertices; v++) {
            distance[v] = G.getDistance(v);
        }

        // Looping over edges
        for (int u=0; u<nVertices; u++) {
            int * data = ArrayList[u].data();
            for (int k=0; k<ArrayList[u].size(); k++) {
                int v = ArrayList[u][k];

                // Re-weighting edges
                double w = getWeight(u, v) + distance[u] - distance[v];
                G.reweightEdge(u, v, w);

            }
        }

        // Looping over vertices
        for (int u=0; u<nVertices; u++) {
            G.source = u;
            G.dijkstra();
            // Updating distance, parent given from dijkstra
            for (int v=0; v<nVertices; v++) {
                distanceMatrix[u][v] = G.getDistance(v) + distance[v] - distance[u];
                parentMatrix[u][v] = G.getParent(v);
            }
        }


    }

    /// I / O functions

    void offlineOutput (string file) {

        fout.open(file, ios::out);
        // ...
        fout.close();
    }

    void printShortestPath (int source, int dest, bool re=false) {

        if (source == dest) {
            if (!re) {
                cout << "Path: " << source + 1;
                return;
            }
            else {
                cout << "";
                return;
            }
        }
        printShortestPath(source, parentMatrix[source][dest], re);
        cout << " --> " << dest + 1 << "(" << getWeight(parentMatrix[source][dest], dest) << ")" ;

    }

    void printDistanceMatrix () {
        cout << "\nDistance Matrix:" << endl;
        double dist=0;
        for (int i=0; i<nVertices; i++) {
            for (int j=0; j<nVertices; j++) {
                dist = distanceMatrix[i][j];
                if (dist == INF)
                    cout << "INF ";
                else
                    cout << setw(3) << dist << " ";
            }
            cout << endl;
        }
    }

    void printPredecessorMatrix () {
        cout << "\nPredecessor Matrix:" << endl;
        int par=0;
        for (int i=0; i<nVertices; i++) {
            for (int j=0; j<nVertices; j++) {
                par = parentMatrix[i][j];
                if (par == NIL)
                    cout << "NIL ";
                else
                    cout << setw(3) << par+1 << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void cleanSPInfo () {
        for (int i=0; i<nVertices; i++) {
            for (int j=0; j<nVertices; j++) {
                distanceMatrix[i][j] = INF;
                parentMatrix[i][j] = NIL;
            }
        }
        cout << "APSP matrices cleared" << endl;
    }

    void printGraph() {
        cout << "Graph: " << endl;

        for (int i=0; i < nVertices; i++) {
            cout << i+1 << " : ";
            int * data = ArrayList[i].data();
            for (int k=0; k<ArrayList[i].size(); k++) {
                cout << ArrayList[i][k]+1 << "(" << setw(2) << Weights[i][k] << ")  ";
            }
            cout << endl;
        }
        cout << endl;
    }

};

int main () {

    Graph G;
    string inFile = "in.txt";
    ifstream fin;

    int u, v;
    double w;
    int nVertices, nEdges;
    fin.open(inFile, ios::in);

    // Vertices and Edges input
    fin >> nVertices >> nEdges;
    cout << nVertices << " " << nEdges << endl;
    G.setnVertices(nVertices);
    for (int i=0; i < nEdges; i++) {
        fin >> u >> v >> w;
        G.addEdge(u-1, v-1, w);
        cout << u << " " << v << " " << w << endl;
    }


    int mamarBari;
    fin >> mamarBari;
    cout << "mamar bari = " << mamarBari << endl;

    cout << "Graph Created." << endl;

    cout << "\nRunning Floyd Warshall ...." << endl;
    G.floydWarshall();
    cout << endl;


    while (true) {
        fin >> u >> v;
        if (u == -1 && v == -1)
            break;

        int weight = G.getShortestPathWeight(u-1, mamarBari-1) + G.getShortestPathWeight(mamarBari-1, v-1);
        if (weight > INF) {
            cout << "No Path from " << u << " to " << v << " through " << mamarBari << endl;
            continue;
        }

        cout << "Shorted Path Weight: " << weight  << endl;

        G.printShortestPath(u-1, mamarBari-1);
        G.printShortestPath(mamarBari-1, v-1, true);

        cout << endl;
    }

    return 0;


}
