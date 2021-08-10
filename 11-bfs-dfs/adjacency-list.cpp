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


void Queue::enqueue(int item)
{
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
        return NULL_VALUE ;

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

// ************ <ArrayList> **************

class ArrayList
{
	int * list;
	int length ;
	int maxSize ;

public:
	ArrayList() ;
	~ArrayList() ;

	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	maxSize = 2 ;
	list = new int[maxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{

	if (length == maxSize) {
        // o v e r f l o w

        // allocate new memory (twice every time)
		maxSize = 2 * maxSize ;
		int * tempList ;
		tempList = new int[maxSize] ;

		for(int i = 0; i < length ; i++ ) {
            tempList[i] = list[i];
        }

        delete [] list ;
        list = tempList ;
	};

	list[length] = newitem ;
	length++ ;
}

int ArrayList::searchItem(int item) {

	for (int i = 0; i < length; i++)
	{
		if ( list[i] == item )
            return i;
	}
	// item not found
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length )
        // index out of bounds
        return ;

	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item);

	if ( position == NULL_VALUE )
        // item not present
        return ;

    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if (position < 0 || position >= length)
        // index out of bounds
        return NULL_VALUE ;
	return
        list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    return length == 0 ;
}

void ArrayList::printList()
{
    for(int i = 0; i < length; i++)
        printf("%d ", list[i]);

    printf("Current size: %d, current length: %d\n", maxSize, length);
}

ArrayList::~ArrayList()
{
    if (list)
        delete [] list;
    list = 0 ;
}

// ********* </ArrayList> ******************


// ********* <Graph> ******************

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
    int dfsTime;
	ArrayList * adjList ;

	// BFS, DFS parameters
	int * color, * distance, * parent;

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
    void prettyPrintGraph();

	void bfs(int source);
	void dfs(int source);
	void dfsVisit(int foo);

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n) {

    if (adjList != 0)
        // delete previous adjList
        delete[] adjList ;

    // Creating a new empty adjList of vertices
	nVertices = n ;
	adjList = new ArrayList[nVertices];
    color = new int [nVertices];
    parent = new int [nVertices];
    distance = new int [nVertices];
}

bool Graph::addEdge(int u, int v)
{
    // Edge not added
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        return false;
    }
    if (adjList[u].searchItem(v) != NULL_VALUE) {
        return false;
    }

    // New edge added
    nEdges += 1;

	adjList[u].insertItem(v) ;

	if(!directed) {
        adjList[v].insertItem(u) ;
	}

	return true;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u >= nVertices || v >= nVertices) {
        printf("Vertex out of range!\n");
        return;
    }

    nEdges--;
    adjList[u].removeItem(v); // no error if edge already absent
    printf("Removed edge %d-%d\n", u, v);

    if (!directed) {
        adjList[v].removeItem(u);
        printf("Removed edge %d-%d\n", u, v);
    }
}

bool Graph::isEdge(int u, int v)
{
    if (adjList[u].searchItem(v) != NULL_VALUE)
        return true;
    else if (adjList[v].searchItem(u) != NULL_VALUE)
        return true;
    else
        return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getOutDegree(int u)
{
    // returns the degree of vertex u
    if (u < 0 && u >= nVertices) {
        printf("The vertex %d is not present :(\n", u);
        return -1;
    }

    return adjList[u].getLength();
}

int Graph::getInDegree(int u)
{
    // returns the degree of vertex u
    if (u < 0 && u >= nVertices) {
        printf("The vertex %d is not present :(\n", u);
        return -1;
    }

    if (!directed) {
        return adjList[u].getLength();
    }
    else {
        int cnt=0;
        for (int i=0; i<nVertices; i++) {
            if (adjList[i].searchItem(u) != NULL_VALUE)
                cnt++;
        }
        return cnt;
    }
}

void Graph::printAdjVertices(int u) {

    // prints all adjacent vertices of a vertex u
    printf("The vertices of %d: ", u);

    for (int i=0; i<adjList[u].getLength(); i++) {
        printf("%d ", adjList[u].getItem(i));
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    // returns true if vertices u and v have common adjacent vertices
    for (int i = 0 ; i < adjList[u].getLength() ; i++) {

        int foo = adjList[u].getItem(i);
        if (adjList[v].searchItem(foo) != NULL_VALUE)
            return true;
    }
    return false;
}

void Graph::bfs(int source) {

    if (source < 0 && source >= nVertices) {
        printf("The source %d is not present :(\n", source);
        return ;
    }

    for (int i = 0; i < nVertices; i++) {
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

        for (int i=0; i < adjList[foo].getLength(); i++)
        {
            int bar = adjList[foo].getItem(i);
            if (color[bar] == WHITE)
            {
                color[bar] = GREY;
                parent[bar] = foo;
                distance[bar] = distance[foo] + 1;
                printf("%d ", bar);
                q.enqueue(bar);
            }
        }

        color[foo] = BLACK;
    }

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

    for (int i=0; i < adjList[foo].getLength(); i++) {

        int bar = adjList[foo].getItem(i);
        if (color[bar] == WHITE) {
            parent[bar] = foo;
            printf("%d ", bar);
            dfsVisit(bar);
        }
    }
    dfsTime = dfsTime + 1;
    finish[foo] = dfsTime;
    color[foo] = BLACK;
}

int Graph::getDist(int u, int v)
{
    // returns the shortest path distance from u to v
    // must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex is out of bounds \n");
        return INFINITY;
    }
    else {
        bfs(u);
    }

    if (distance[v] != INFINITY) {
        return distance[v];
    }
    else {
        printf("%d and %d are not connected :(\n", u, v);
        return -1;
    }
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
    printf("\n");

}

void Graph::prettyPrintGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            if (directed)
                printf(" %d>%d", i, adjList[i].getItem(j));
            else
                printf(" %d-%d", i, adjList[i].getItem(j));

        }
        printf("\n");
    }
}

Graph::~Graph()
{
    delete [] adjList;
    delete [] color;
    delete [] parent;
    delete [] distance;
}

// ***************** </Graph> *********************
//
//
////******main function to test your code*************************
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


//******main function to test your code*************************
//int main(void)
//{
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
