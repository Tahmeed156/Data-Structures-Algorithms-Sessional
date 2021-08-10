#include <bits/stdc++.h>
#define INF 99999
#define NIL -1
#define WHITE -1
#define GREY 1
#define BLACK 0

using namespace std;

typedef pair <int, int> nodePair;

class Queue {

    int * data;
    int maxSize; // capacity
    int length; // elements present
    int front; // point of insertion
    int rear; // starting point

public:

    Queue();

    Queue(int n);

    ~Queue();

    void enqueue(int item); //insert item in the queue

    int dequeue(); //returns the item according to FIFO

    bool empty(); //return true if Queue is empty
};

class Graph {

    bool directed;
    int nVertices, nEdges;

    vector <int> * ArrayList;
    vector <int> * Capacity;
    int ** Residual;

	int * color, * distance, * parent;

    ifstream fin;
    ofstream fout;
    ostream * out;
    bool fileInput;

public:
    int source, sink;

    /// Constructor / Destructor

    Graph() {}

    ~Graph() {
        nVertices = 0;
        nEdges = 0;
        delete [] parent;
        delete [] distance;
        delete [] ArrayList;
        delete [] Capacity;
    }

    /// Utility functions

    int searchEdge (int u, int v) {
        int * data = ArrayList[u].data();
        for (int i=0; i<ArrayList[u].size(); i++)
            if (data[i] == v)
                return i;

        return NIL;
    }

    void addEdge(int u, int v, int w) {
        int position = searchEdge(u, v);
        if (position == NIL) {
            ArrayList[u].push_back(v);
            Capacity[u].push_back(w);
        }
        else {
            Capacity[u][position] += w;
        }
    }

    int getCapacity (int u, int v) {
        int position = searchEdge(u, v);
        if (position == NIL)
            return INF;
        else
            return Capacity[u][position];
    }

    /// I-O functions

    void inputFlow (string file) {

        directed = true;

        int u, v, w;
        fin.open(file, ios::in);
        cout << "Input:" << endl;

        // Vertices & Edges
        fin >> nVertices >> nEdges;
        cout << setw(2) << nVertices << " " << setw(2) << nEdges << endl;

        // Variables for Edges, BFS, Residual Graph
        parent = new int [nVertices];
        distance = new int [nVertices];
        color = new int [nVertices];

        ArrayList = new vector <int> [nVertices];
        Capacity = new vector <int> [nVertices];

        Residual = new int * [nVertices];


        // Taking Edges as Input
        for (int i=0; i < nEdges; i++) {
            fin >> u >> v >> w;
            addEdge(u, v, w);
            addEdge(v, u, 0);
            cout << setw(2) << u << " " << setw(2) << v << " " << setw(2) << w << endl;
        }

        // Source & Sink
        fin >> source >> sink;
        cout << setw(2) << source << " " << setw(2) << sink << endl;

        fin.close();
    }

    void inputMatching (string file) {

        directed = false;

        int u, v, w=1;
        fin.open(file, ios::in);
        cout << "Input:" << endl;

        // Vertices & Edges
        fin >> nVertices >> nEdges;
        cout << setw(2) << nVertices << " " << setw(2) << nEdges << endl;

        // Adding Source, Sink
        source = nVertices;
        sink = nVertices + 1;
        nVertices += 2;

        // Variables for Edges, BFS, Residual Graph
        ArrayList = new vector <int> [nVertices];
        Capacity = new vector <int> [nVertices];

        parent = new int [nVertices];
        distance = new int [nVertices];
        color = new int [nVertices];

        Residual = new int * [nVertices];

        // Taking Edges as Input
        for (int i=0; i < nEdges; i++) {
            fin >> u >> v;
            addEdge(u, v, 0);
            addEdge(v, u, 0);
            cout << setw(2) << u << " " << setw(2) << v << endl;
        }

        // Check Bipartite & Separate Vertices
        bfsColoring();

        // Add Edges from Source, Sink to all Vertices
        for (int i=0; i < nVertices-2; i++) {
            if (color[i] == 1) {
                for (int x=0; x < Capacity[i].size(); x++)
                    Capacity[i][x] = 1;
                addEdge(source, i, 1);
                addEdge(i, source, 0);
            }
            else {
                addEdge(i, sink, w);
                addEdge(sink, i, 0);
            }
        }

        fin.close();
    }

    void maxflow(string file="") {

        int u, v;
        int flow = fordFulkerson();

        // Selecting Output Stream
        if (file == "") {
            fileInput = false;
        }
        else {
            fout.open(file, ios::out);
            fileInput = true;
            cout << "Output to file '" << file << "'!" << endl;
        }
        (fileInput) ? out = &fout: out = &cout;

        // Generating Output
        (*out) << endl << "Output (Flow): \n" << setw(2) << flow << endl;
        for (u=0; u<nVertices; u++) {
            for (int i=0; i < ArrayList[u].size(); i++) {
                v = ArrayList[u][i];

                if (getCapacity(u, v) == 0) {
                    continue;
                }

                flow = getCapacity(u, v) - Residual[u][v];
                if (flow < 0) {
                    Residual[u][v] += flow;
                    flow = 0;
                }

                (*out) << setw(2) << u << " " << setw(2) << v << " ";
                (*out) << setw(2) << flow << "/" << setw(2) << getCapacity(u, v) << endl;
            }
        }


        if (fileInput)
            fout.close();
    }

    void matching(string file="") {

        int u, v;
        int flow = fordFulkerson();

        // Selecting Output Stream
        if (file == "") {
            fileInput = false;
        }
        else {
            fout.open(file, ios::out);
            fileInput = true;
            cout << "Output to file '" << file << "'!" << endl;
        }
        (fileInput) ? out = &fout: out = &cout;

        // Generating Output
        (*out) << endl << "Output (Matching): \n" << setw(2) << flow << endl;
        for (u=0; u<nVertices; u++) {
            for (int i=0; i < ArrayList[u].size(); i++) {
                v = ArrayList[u][i];
                if (u == source || v == source || u == sink || v == sink)
                    continue;

                flow = getCapacity(u, v) - Residual[u][v];
                if (flow > 0)
                    (*out) << setw(2) << u << " " << setw(2) << v << endl;
            }
        }

        if (fileInput)
            fout.close();
    }

    /// Algorithms

    bool bfs();

    void bfsColoring();

    int fordFulkerson();

};


/// ALGORITHMS


bool Graph::bfs() {

    // Initialize All Vertices
    for (int i = 0; i < nVertices; i++) {
        color[i] = WHITE;
        parent[i] = NIL;
        distance[i] = INF;
    }

    // Initialize Source Vertex
    color[source] = GREY;
    parent[source] = NIL;
    distance[source] = 0;
    Queue q(source);


    while (!q.empty()) {
        int foo = q.dequeue();

        for (int i=0; i < ArrayList[foo].size(); i++) {
            int bar = ArrayList[foo][i];

            if (color[bar] == WHITE && Residual[foo][bar] > 0) {
                // Vertex not visited, Path can be Augmented
                color[bar] = GREY;
                parent[bar] = foo;
                distance[bar] = distance[foo] + 1;
                q.enqueue(bar);
            }
        }

        color[foo] = BLACK;
    }

    // Whether Augmenting Path was Found
    return color[sink] == BLACK;
}

void Graph::bfsColoring() {

    // Initialize all Vertices
    for (int i = 0; i < nVertices; i++) {
        color[i] = -1;
    }

    // Run From All Vertices, for Disconnected Graphs
    for (int k=0; k<nVertices-2; k++) {

        // Check & Initialize Source
        if (color[k] == -1)
            color[k] = 1;
        else
            continue;
        Queue q(k);


        while (!q.empty()) {
            int foo = q.dequeue();

            for (int i=0; i < ArrayList[foo].size(); i++) {
                int bar = ArrayList[foo][i];

                if (color[bar] == -1) {
                    // New vertex has not been visited
                    color[bar] = 1 - color[foo];
                    q.enqueue(bar);
                }

                if (color[bar] == color[foo]) {
                    // New vertex already colored by same color
                    cout << "\nOutput:\nThe graph is not bipartite" << endl;
                    exit(0);
                }
            }

        }
    }

}

int Graph::fordFulkerson () {

    int flow = 0;
    int u, v;

    // Create Residual Graph
    for (u=0; u < nVertices; u++) {
        Residual[u] = new int [nVertices];

        for (int i=0; i < ArrayList[u].size(); i++) {
            int v = ArrayList[u][i];
            Residual[u][v] = getCapacity(u, v);
        }
    }


    while (bfs()) { // Find Augmenting Paths

        int bottleneck = INF;

        // Find the Bottleneck value in that path
        for (v=sink; v!=source || v==NIL; v=parent[v]) {
            u = parent[v];
            bottleneck = min(bottleneck, Residual[u][v]);
        }

        // Change Flow in residual graph
        for (v=sink; v!=source; v=parent[v]) {
            u = parent[v];
            Residual[u][v] -= bottleneck;
            Residual[v][u] += bottleneck;
        }

        // Update Max-Flow
        flow += bottleneck;
    }

    return flow;
}

// ==================================================

int main () {

    // FLOW = 1 , MATCHING = 2
    int a = 2;
    string fileName = "../test-cases/moodle/in.txt";


    Graph G;

    if (a == 1) {
        G.inputFlow(fileName);
        G.maxflow();
    }
    else {
        G.inputMatching(fileName);
        G.matching();
    }

}




































// ************ </Queue> ****************

Queue::Queue()
{
    maxSize = 2;
    data = new int[maxSize] ;
    length = 0;
    front = 0;
    rear = 0;
}

Queue::Queue(int n){
    // Constructor with an initial value
    maxSize = 2;
    data = new int[maxSize]; // CHANGE - call prev cons
    length = 0 ;
    front = 0;
    rear = 0;
    enqueue(n);
}


void Queue::enqueue(int item) {

	if (length == maxSize) {
        // o v e r f l o w

		// allocate new memory (twice every time)
		int * tempData ;
		maxSize = 2 * maxSize;
		tempData = new int[maxSize];

		int i, j;
		j = 0;

		for( i = rear; i < length ; i++ ) { // CHANGE (maxSize?)
			// copy items from rear
			tempData[j++] = data[i];
		}
		for( i = 0; i < rear ; i++ ) { // CHANGE (front?)
            // copy items before rear
			tempData[j++] = data[i] ;
		}

		rear = 0 ;
		front = length ;
		// free previous memory, point to new memory
		delete [] data ;
		data = tempData ;
	}

	data[front] = item ;
	front = (front + 1) % maxSize ; // cyclic queue
	length++ ;
}


bool Queue::empty()
{
	return length == 0;
}


int Queue::dequeue()
{
	if(length == 0)
        // u n d e r f l o w
        return NIL ;

	int item = data[rear] ;
	rear = (rear + 1) % maxSize ; // cyclic queue
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if (data)
        // if data present, release memory
        delete [] data;
    data = 0; // set to NULL
}

// ************ </Queue> ****************
