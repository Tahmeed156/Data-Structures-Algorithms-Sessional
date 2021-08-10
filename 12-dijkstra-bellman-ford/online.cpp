#include <bits/stdc++.h>
#define INF 99999
#define NIL -1

using namespace std;

typedef pair <int, int> nodePair;

class Graph {

    int nVertices, nEdges;
    vector <int> * ArrayList;
    vector <int> * Weights;
    string * city;
    int * parent, * time, * quarantine;

    ifstream fin;
    ofstream fout;

public:

    int source, dest;

    int cityIndex(string st) {
        for (int i=0; i < nVertices; i++) {
            if (st == city[i]) {
                return i;
            }
        }
        cout << "City not found :(" << endl;
        return -1;
    }

    Graph(string file) {

        int u, v, w;
        string uCity, vCity;
        fin.open(file, ios::in);

        fin >> nVertices >> nEdges; // Vertices, Edges
         cout << nVertices << " " << nEdges << endl;

        parent = new int [nVertices];
        time = new int [nVertices];
        quarantine = new int [nVertices];
        city = new string [nVertices];

        ArrayList = new vector <int> [nVertices];
        Weights = new vector <int> [nVertices];

        for (int i=0; i < nVertices; i++) {
            fin >> uCity >> w;
            quarantine[i] = w;
            city[i] = uCity;
            cout << uCity << " " << w << endl;
        }

        for (int i=0; i < nEdges; i++) {
            fin >> uCity >> vCity >> w;
            u = cityIndex(uCity);
            v = cityIndex(vCity);
            addEdge(u, v, w);
            addEdge(v, u, w);
            cout << uCity << " " << vCity << " " << w << endl;
        }

        fin >> uCity >> vCity;
        source = cityIndex(uCity);
        dest = cityIndex(vCity);
        cout << uCity << " " << vCity << endl;
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
            time[i] = INF;
            parent[i] = NIL;
        }
        priority_queue <nodePair, vector <nodePair>, greater<nodePair> > Q;

        time[source] = 0;
        Q.push(make_pair(0, source));

        // One by one extract items from min heap
        while (!Q.empty()) {

            int u = Q.top().second;
            int dist = Q.top().first;
            Q.pop();

            for (int i=0; i < ArrayList[u].size(); i++) {

                int v = ArrayList[u][i];
                int position = searchEdge(u, v);
                int weightUV = Weights[u][position]; // CHANGE - take abs
                int quar = quarantine[v];

                if (time[v] > time[u] + weightUV + quar) {
                    time[v] = time[u] + weightUV + quar;
                    parent[v] = u;
                    Q.push(make_pair(time[v], v));
                }
            }
        }

    }

    void online(string file) {

        fout.open(file, ios::out);

        cout << "\nTime required " << endl;
        dijkstra();
        fout << time[dest] << endl;
        cout << time[dest] << endl;
        pathToSource(source, dest);
        cout << endl;

        fout.close();
    }

    void pathToSource (int source, int dest) {

        if (source == dest) {
            fout << city[source];
            cout << city[source];
            return;
        }
        pathToSource(source, parent[dest]);
        fout << " -> " << city[dest];
        cout << " -> " << city[dest];
    }

};

int main () {

    Graph G("test/io6/input6.txt");
    G.online("out.txt");
}
