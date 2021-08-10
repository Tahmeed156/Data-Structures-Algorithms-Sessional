#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std::chrono;
using namespace std;


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    Queue(int n);
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


Queue::Queue(int n)
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
    enqueue(n);
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
    int dfsTime;
	bool directed ;
	int ** matrix ;

	// BFS, DFS
	int *color, *parent, *distance;
	int *start, *finish;

public:

	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();

	void bfs(int source);
	void dfs(int source);
	void dfsVisit(int foo);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	// allocate an array of integer pointers
    matrix = new int * [nVertices];
    for(int i=0;i<nVertices;i++)
    {
        // allocate an integer array for every integer pointer
        matrix[i] = new int[nVertices];

        for(int j=0;j<nVertices;j++)
            //initialize the matrix cells to 0
            matrix[i][j] = 0;
    }
    color = new int [nVertices];
    parent = new int [nVertices];
    distance = new int [nVertices];
    start = new int [nVertices];
    finish = new int [nVertices];
}

bool Graph::addEdge(int u, int v) {

    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;
    if (matrix[u][v])
        return false;

    this->nEdges++;
    matrix[u][v] = 1;
    if(!directed)
        matrix[v][u] = 1;

    return true;
}


void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return;
    }

    this->nEdges--;
    if (matrix[u][v]) {
        matrix[u][v] = 0;
        printf("Removed edge %d-%d\n", u, v);
        if (!directed) {
            printf("Removed edge %d-%d\n", u, v);
            matrix[u][v] = 0;
        }
    }
    else {
        printf("The edge does not exist :(\n");
    }
}


bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return false;
    }
    else {
        return matrix[u][v] || matrix[v][u]; // CHANGE dir
    }
}


int Graph::getOutDegree(int u)
{
    if(u<0 || u>=nVertices) {
        printf("Vertex out of range!\n");
        return -1;
    }

    int cnt=0;

    for (int i=0; i<nVertices; i++) {
        if (matrix[u][i])
            cnt++;
    }
    return cnt;
}


int Graph::getInDegree(int u)
{
    if(u<0 || u>=nVertices) {
        printf("Vertex out of range!\n");
        return -1;
    }

    int cnt = 0;
    for (int i=0; i<nVertices; i++) {
        if (matrix[i][u])
            cnt++;
    }
    return cnt;

}

void Graph::printAdjVertices(int u)
{

    if(u<0 || u>=nVertices ) {
        printf("Vertex out of range!\n");
        return;
    }
    // prints all adjacent vertices of a vertex u
    printf("The vertices of %d:", u);
    for (int i=0; i<nVertices; i++) {
        if (matrix[u][i])
            printf(" %d", i);
    }
    printf("\n");
}


bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return false;
    }
    for (int i=0; i<nVertices; i++) {
        // printf("%d: %d %d\n", i, matrix[u][i], matrix[v][i]);
        if (matrix[u][i] && matrix[v][i])
            return true;
    }
    return false;
}

void Graph::bfs(int source)
{

    if( source<0 || source>=nVertices ) {
        printf("Vertex out of range!\n");
        return;
    }

    for (int i=0; i<nVertices; i++) {
        color[i] = WHITE;
        parent[i] = NULL_VALUE;
        distance[i] = INFINITY;
    }

    color[source] = GREY;
    parent[source] = NULL_VALUE;
    distance[source] = 0;
    printf("BFS Source - %d\nOrder of Discovery - ", source);

    Queue q(source);
    while (!q.empty()) {

        int foo = q.dequeue();

        for (int i=0; i < nVertices; i++)
        {
            if ( matrix[foo][i] && color[i] == WHITE )
            {
                color[i] = GREY;
                parent[i] = foo;
                distance[i] = distance[foo] + 1;
                printf("%d ", i);
                q.enqueue(i);
            }
        }

        color[foo] = BLACK;
    }
    printf("\n");

}


void Graph::dfs(int source) {

    if (source < 0 && source >= nVertices) {
        printf("The source %d is not present :(\n", source);
        return ;
    }

    for (int i = 0; i < nVertices; i++) {
        color[i] = WHITE;
        parent[i] = NULL_VALUE;
    }

    dfsTime = 0;
    printf("DFS Source - %d\nOrder of Discovery - ", source);
    dfsVisit(source);

    printf("\nStart times - ");
    for (int i = 0; i < nVertices; i++) {
        printf("%d ", start[i]);
    }
    printf("\nFinish times - ");
    for (int i = 0; i < nVertices; i++) {
        printf("%d ", finish[i]);
    }
    printf("\n");
}

void Graph::dfsVisit(int foo) {
    dfsTime = dfsTime + 1;
    start[foo] = dfsTime;
    color[foo] = GREY;

    for (int i=0; i < nVertices; i++) {

        if ( matrix[foo][i] && color[i] == WHITE ) {
            parent[i] = foo;
            printf("%d ", i);
            dfsVisit(i);
        }
    }
    dfsTime = dfsTime + 1;
    finish[foo] = dfsTime;
    color[foo] = BLACK;
}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return INFINITY;
    }
    bfs(u);
    return distance[v];
}


void Graph::printGraph()
{
    printf("Number of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    for (int i=0; i < nVertices; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    delete [] color;
    delete [] parent;
    delete [] distance;
    delete [] start;
    delete [] finish;
}


//**********************Graph class ends here******************************


int main(void)
{
    int n, choice;
    int u, v; // vertices
    bool dir;

    // Choosing between directed and undirected graphs
    printf("Enter your choice:\n");
    printf("1. directed graph \n2. undirected graph\n");
    scanf("%d",&choice);

    if(choice == 1)
        dir = true;
    else if(choice == 2)
        dir = false;
    Graph g(dir);

    // Setting the number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge \n");
        printf("2. Remove edge \n");
        printf("3. Is edge \n");
        printf("4. Get out degree\n");
        printf("5. Get in degree\n");
        printf("6. Print adjacent vertices \n");
        printf("7. Has common adjacent vertices\n");
        printf("8. Shortest distance\n");
        printf("9. Run DFS\n");
        printf("~. Print Graph\n");
        printf("0. Exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            scanf("%d %d", &u, &v);
            g.addEdge(u, v);
            g.printGraph();
        }
        else if(ch==2)
        {
            scanf("%d %d", &u, &v);
            g.removeEdge(u, v);
            g.printGraph();
        }
        else if(ch==3)
        {
            scanf("%d %d", &u, &v);
            if (g.isEdge(u, v))
                printf("%d and %d does not make an edge :(\n", u, v);
            else
                printf("%d and %d makes an edge!\n", u, v);
        }
        else if (ch == 4)
        {
            printf("Enter u : \n");
            scanf("%d", &u);
            u = g.getOutDegree(u);
            printf("Out degree: %d\n", u);
        }
        else if (ch == 5)
        {
            printf("Enter u : \n");
            scanf("%d", &u);
            u = g.getInDegree(u);
            printf("In degree: %d\n", u);
        }
        else if(ch==6)
        {
            scanf("%d", &u);
            g.printAdjVertices(u);
        }
        else if (ch == 7) {
            scanf("%d %d", &u, &v);
            if (g.hasCommonAdjacent(u, v))
                printf("Has common adjacent vertices!\n");
            else
                printf("Nothing common :(\n");
        }
        else if (ch == 8)
        {
            scanf("%d %d", &u, &v);
            printf("Shortest distance: %d edges\n", g.getDist(u, v));
        }
        else if (ch == 9)
        {
            printf("Source ");
            scanf("%d", &u);
            g.dfs(u);
        }
        else if (ch == 0)
        {
            break;
        }
        else
        {
            g.printGraph();
        }
    }

}

//
//int main(void) {
//
//    int n, choice;
//    int u, v;
//    bool dir;
//
//    // ==========================
//
//    printf("Creating the Graph! ...\n");
//    srand(time(NULL));
//
//    dir = true;
//
//    for (int i = 1; i <= 16; i *= 2) { // Looping over #vertices
//
//        Graph g(dir);
//        int ver = 1000 * i;
//        g.setnVertices(ver);
//
//        for (int nEdges = ver; nEdges <= (ver*ver - ver)/8; nEdges *= 2) { // Looping over #edges
//
//            int cnt = 0;
//            while (cnt < nEdges) {
//                // Select random vertices to form edge
//                u = rand() % ver;
//                v = rand() % ver;
//                // Try to form edge
//                bool success = g.addEdge(u, v);
//                if (success)
//                    cnt += 1;
//            }
//
//            // Recording time ...
//
//            auto start = high_resolution_clock::now();
//            for (int k=0; k < 10; k++) { // Taking average values
//                int source = rand() % ver;
//                g.bfs(source);
//            }
//            auto stop = high_resolution_clock::now();
//
//            auto timeDiff = duration_cast <nanoseconds> (stop-start).count()/10;
//
//            // printf("v=%d, e=%d, time=%dns\n", ver, nEdges, timeDiff);
//            printf("%dns\n", timeDiff);
//        }
//
//    }
//
//    return 0;
//
//}
