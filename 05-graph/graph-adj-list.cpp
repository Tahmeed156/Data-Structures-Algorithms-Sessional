#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
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
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		// doubling memory when array is full
		listMaxSize = 2 * listMaxSize ;
		// allocate new memory space for tempList
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if (position < 0 || position >= length)
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
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int * color, * distance, * parent;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u, bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void prettyPrintGraph();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
    // delete previous adjList
	if(adjList!=0)
        delete[] adjList ;

    // Creating a new empty adjList of vertices
	adjList = new ArrayList[nVertices];
    color = new int [nVertices];
    parent = new int [nVertices];
    distance = new int [nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return;
    }
    this->nEdges++ ;

	adjList[u].insertItem(v) ;
    printf("New connection %d-%d\n", u, v);

	if(!directed) {
        adjList[v].insertItem(u) ;
        printf("New connection %d-%d\n", u, v);
	}
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return;
    }
    this->nEdges--;

    adjList[u].removeItem(v);
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

int Graph::getDegree(int u, bool out=true)
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
        if (out) {
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
}

void Graph::printAdjVertices(int u)
{
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
    for (int i=0; i<adjList[u].getLength(); i++) {
        int foo = adjList[u].getItem(i);
        if (adjList[v].searchItem(foo) != NULL_VALUE)
            return true;
    }
    return false;
}

void Graph::bfs(int source)
{

    for (int i=0; i<nVertices; i++) {
        color[i] = WHITE;
        parent[i] = NULL_VALUE;
        distance[i] = INFINITY;
    }

    color[source] = GREY;
    parent[source] = NULL_VALUE;
    distance[source] = 0;

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
                q.enqueue(bar);
            }
        }

        color[foo] = BLACK;
    }

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


//**********************Graph class ends here******************************


//******main function to test your code*************************
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
        printf("4. Get degree\n");
        printf("5. Print adjacent vertices \n");
        printf("6. Has common adjacent vertices\n");
        printf("7. Shortest distance\n");
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
        else if (ch ==4)
        {
            printf("Enter u & then direction (1=out, 0=in): \n");
            scanf("%d %d", &u, &v);
            u = g.getDegree(u, v);
            printf("Degree: %d\n", u);
        }
        else if(ch==5)
        {
            scanf("%d", &u);
            g.printAdjVertices(u);
        }
        else if (ch == 6) {
            scanf("%d %d", &n, &v);
            if (g.hasCommonAdjacent(u, v))
                printf("Nothing common :(\n");
            else
                printf("Has common adjacent vertices!\n");
        }
        else if (ch == 7)
        {
            scanf("%d %d", &u, &v);
            printf("Shortest distance: %d edges\n", g.getDist(u, v));
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


// Adding the same edge twice
// adding an edge between the same vertices
