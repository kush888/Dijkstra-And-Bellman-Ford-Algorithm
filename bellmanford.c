/* sample Input 
5 8 
1 2 -0.1
1 3 0.4
2 3 0.3
2 4 0.2
2 5 0.2
4 3 0.5
4 2 0.1
5 4 -0.3
1 1.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int** create (int);																			

float** createf (int);

int relax(int, float*, int**, float*, float**);


int main()
{
	int vertices,edges,**graph,i,j,k,pos;                                         
	float **weight , ans ;
	scanf("%d %d",&vertices,&edges);
	graph=create(vertices);											// function call to create a 2D array to store the adjacency list
	weight=createf(vertices);										// function call to create a 2D array to store the weights of the edges 
	int size[vertices+1] ;
	for(i=0;i<vertices+1;i++)
	{
		size[i]=0;
	}									// array to store no. of adjacent vertices of each vertex   
	float dist[vertices+1],temp[vertices+1];						
	
	for(i=1;i<=vertices;i++)										// initialising the arrays 
	{
		for(j=1;j<=vertices;j++)
		{
			graph[i][j]=-1;											
			weight[i][j]=0;
		}
	}

	for(i=0;i<edges;i++)											// taking input from user 
	{
		int s , d ;													
		float wgt ;
		scanf("%d %d %f",&d,&s,&wgt);								// scan the vertices and the associated weights 
		weight[s][d]=wgt;											
		size[s]++;
		graph[s][size[s]]=d;
		
	}
	int source ;
	float currentweight ;
	scanf("%d %f",&source , &currentweight);
	
	for(i=1;i<=vertices;i++)										// initialise the distance array with zero and infinity 
	{
		if(i==source)													
			dist[i]=0;
		else
			dist[i]=INT_MAX;
	}

	for(i=1;i<vertices;i++)										   //loop to calculate shortest distance using i edges						
	{
		for(j=1;j<=vertices;j++)
		{
			temp[j]=dist[j];
		}
		for(j=1;j<=vertices;j++)									// loop will update distance for each vertex
		{
			relax(j,temp,graph,dist,weight);						// function call to relax the edge 
		}

		for(j=1;j<=vertices;j++)									// print dist array after every loop 
		{
			printf("%f ",dist[j]);
		}
		printf("\n");
	}

	ans=dist[1];
	pos=1;

	for(i=2;i<=vertices;i++)										// calculate minimum of shortest distances 
	{
		if(dist[i]<ans)
		{
			ans=dist[i];
			pos=i;
		}
	}

	ans = pow(10,ans);
	printf("%d %f ",pos,ans);										// print the answer
}

int** create (int vertices)											//function to create 2d array of integers									
{
	int **x,i;
	x= (int**)malloc(vertices+1*sizeof(int*));												
	for (i=0; i<vertices+1; i++)
         x[i] = (int *) malloc(vertices+1 * sizeof(int));
    return(x);
}

float** createf (int vertices)										//function to create 2d array of integers												
{
	float **x;
	int i ;
	x= (float**)malloc(vertices+1*sizeof(float*));												
	for (i=0; i<vertices+1; i++)
         x[i] = (float *) malloc(vertices+1 * sizeof(float));
    return(x);
}

int relax(int j , float *temp , int**graph , float*dist , float **weight)    //function to relax an edge 
{
	float min = temp[j];
			int k=1;
			while(graph[j][k]!=-1)
			{
				if(temp[graph[j][k]]+weight[j][graph[j][k]]<min)
				{
					min=temp[graph[j][k]]+weight[j][graph[j][k]];
				}
				k++;
			}
			dist[j]=min;
}