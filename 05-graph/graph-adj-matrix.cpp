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
	bool directed ;
	int ** matrix ;
	int *color, *parent, *distance;

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
	void bfs(int source);
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
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        printf("Vertex out of range!\n");
        return;
    }

    if (!matrix[u][v]) {
        this->nEdges++;
        matrix[u][v] = 1;
        printf("New connection %d-%d\n", u, v);
        if(!directed)
            matrix[v][u] = 1;
    }
    else {
        printf("The edge already exists!");
    }
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
        return matrix[u][v] || matrix[v][u];
    }
}


int Graph::getDegree(int u, bool out=true)
{
    if(u<0 || u>=nVertices) {
        printf("Vertex out of range!\n");
        return -1;
    }

    int cnt=0;
    if (!directed || out) {
        for (int i=0; i<nVertices; i++) {
            if (matrix[u][i])
                cnt++;
        }
        return cnt;
    }
    else { // directed, in-vertices
        for (int i=0; i<nVertices; i++) {
            if (matrix[i][u])
                cnt++;
        }
        return cnt;
    }
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
                q.enqueue(i);
            }
        }

        color[foo] = BLACK;
    }
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
    for(int i=0;i<nVertices;i++)
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
                printf("%d and %d makes an edge!\n", u, v);
            else
                printf("%d and %d does not make an edge :(\n", u, v);
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
                printf("Has common adjacent vertices!\n");
            else
                printf("Nothing common :(\n");
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
