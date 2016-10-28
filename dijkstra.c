/* sample Input 
5 8       
1 2 4
1 3 9
2 3 8
2 4 7
2 5 7
4 3 10
4 2 6
5 4 2 
1 2 
3 
5

*/
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#define  maxVertices 100
#define  infinity 1000000000

typedef struct Node                                                             // structure for heap (priority queue)
{
    int vertex,distance;
}Node;

typedef struct adj                                                              // structure for adjacency list         
{
    int index;
    struct adj *next;
}adj;

Node heap[1000000];                                                             // declaring size of heap 
int visited[maxVertices];
int heapSize;

int** array(int);                                                                     
void Init();
void create(adj**,int ,int);
void Insert(Node element);
Node DeleteMin();
void dijkstra(adj ** , int *, int ** , int  , int );

int main()
{
    adj **list=NULL;                                                            // pointer to graph 
    int Vertex,Edges,**weight,i,j,k;                                            
    scanf("%d",&Vertex);
    scanf("%d",&Edges);
    list=(adj **)malloc(sizeof(adj *)*(Vertex+1));
    int dist[Vertex+1] ;                                                        // array to store min distance 
    weight=array(Vertex);
    
    for(i=1;i<=Vertex;i++)                                                      // initialize weight of each edge equal to zero     
    {
        for(j=1;j<=Vertex;j++)
        {
            weight[i][j]=0;
        }
    }

    for(i=0;i<Edges;i++)                                                        // taking input from user   
    {
        int s , d ,wgt ;
        scanf("%d %d %d",&s,&d,&wgt);
        if(wgt<0)
        {
            printf("weight should be positive \n");
            return 0 ;
        }
        create(list,s,d);                                                       // add edge between s and d 
        weight[s][d]=wgt;   
    }
    
    int src , no ;
    scanf("%d %d",&src , &no);
    int host[no+1];
    for(i=1;i<=no;i++)
    {
        scanf("%d",&host[i]);
    }
    Init();
    dijkstra(list,dist,weight,Vertex,src);                                       // function call to dijkstra's
    for(i=1;i<=no;i++)
    {
        printf("%d %d\n",host[i],dist[host[i]]);                                 // print the answer 
    }
     return 0;

}

int** array(int vertices)                                                       //function to create 2d array of integers                                       
{
    int **x,i;
    x= (int**)malloc(vertices+1*sizeof(int*));                                              
    for (i=0; i<vertices+1; i++)
         x[i] = (int *) malloc(vertices+1 * sizeof(int));
    return(x);
}


void Init()                                                                     // initialize our priority queue
{
        heapSize = 0;
        heap[0].distance = -INT_MAX;
        heap[0].vertex  = -1;
}

void create(adj **list ,int x ,int y)                                           // function to add edge between two vertices
{
  adj *tmp=(adj *)malloc(sizeof(adj));
  tmp->index=y;
  if(list[x]==NULL)
  {
    list[x]=tmp;
    tmp->next=NULL;
  }
  else
  {
    tmp->next=list[x];
    list[x]=tmp;
  }
}
void dijkstra(adj **list , int *dist , int **weight,int Vertex , int src)         // function to calculate shortest distance 
{
    int i ;
    Node temp;
    for(i=1;i<=Vertex;i++)                                                          // initialize distance array 
    {
        if(i==src)
        {
                temp.distance = 0;
                dist[i]=0;
        }
        else
        {
                temp.distance = infinity;
                dist[i]= infinity;
        }
        temp.vertex = i;
        Insert(temp);                                                               // insert vertices in queue
    }

    while(heapSize)
    {
            Node del = DeleteMin();                                                 // extract vertice with minimum distance from queue
            int u = del.vertex;
            if(visited[u])
            {
                continue;
            }
            visited[u] = 1;                                                          // set vertex as visited 
            adj* head ;
            head = list[u];
            while(head)                                                              // check each adjacent vertex of u 
            {
                    int v = head->index;
                    if(dist[v] > dist[u] +weight[u][v])                              // relax the edge between u and v 
                    {
                            dist[v] = dist[u] + weight[u][v];
                            temp.vertex = v;
                            temp.distance = dist[v];    
                            Insert(temp);                                            // insert updated dist in priority queue
                    }
                    head=head->next;
            }
    }

}

void Insert(Node element)                                                             //function to insert element in priority queue
{
        heapSize++;
        heap[heapSize] = element;
        int i = heapSize;
        while(heap[i/2].distance > element.distance) 
        {
                heap[i] = heap[i/2];
                i /= 2;
        }
        heap[i] = element;
}

Node DeleteMin()                                                                        // function to extract element from priority queue
{
        Node minElement,lastElement;
        int child,i;
        minElement = heap[1];
        lastElement = heap[heapSize--];
        for(i = 1; i*2 <= heapSize ;i = child)
        {
            child = i*2;
            if(child != heapSize && heap[child+1].distance < heap[child].distance) 
            {
                child++;
            }
            if(lastElement.distance > heap[child].distance)
            {
                heap[i] = heap[child];
            }
            else 
            {
                break;
            }
        }
        heap[i] = lastElement;
        return minElement;
}
