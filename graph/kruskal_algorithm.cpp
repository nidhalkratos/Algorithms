/*
Hi, This source code has been written by Nidhal Abidi from IknowBrain
please visit us at:
www.iknowbrain.work
www.youtube.com/iknowbrain

This is an implementation for kruskal's algorithm , it takes a graph and output the minimum spannint tree MST.

Run the application after compiling it with g++ , 
input the numer of nodes nb_nodes, and the number of edges nb_edges and then for nb_edges lines input the vertex
u and vertex v and the weight w. 
*/

#include <iostream>
#include <list>

using namespace std;

struct edge
{
    int u;
    int v;
    int w;
};

bool operator < (edge &a,edge &b)
{
    return a.w < b.w;
}


void init_union_find(int arr[],int size)
{
    for(int i = 0;i<= size;i++)
    {
        arr[i] = i;
    }
}
/*The find function just below this comment is the regular and simple implementation, while the second one makes sure 
that the tree stays balanced
*/
/*int find(int arr[], int vertex)
{
    if(vertex == arr[vertex])
        return vertex;
    else
        return find(arr,arr[vertex]);
}*/

int find(int arr[], int vertex)
{
    if(vertex == arr[vertex])
        return vertex;
    else
    {
         int root = find(arr,arr[vertex]);
         return arr[vertex] = root;
    }
}


void _union(int arr[],int vertex1,int vertex2)
{
    int root1 = find(arr,vertex1);
    int root2 = find(arr,vertex2);
    arr[root2] = root1;
}

list<edge> edges;
list<edge> mst_list;
int arr[1001];


int main()
{
    int nb_nodes,nb_edges;
    cin>>nb_nodes>>nb_edges;
    for(int i = 0 ;i<nb_edges;i++)
    {
        edge e;
        cin>>e.u>>e.v>>e.w;
        edges.push_back(e);
    }
    edges.sort();
    init_union_find(arr,nb_nodes);
    int counter = 0;
    for(list<edge>::iterator e = edges.begin();e!=edges.end();++e)
    {
        int u = (*e).u;
        int v = (*e).v;
        if(find(arr,u) != find(arr,v))
        {
            _union(arr,u,v);
            mst_list.push_back(*e);
            counter++;
        }
        if(counter >= nb_nodes-1)
            break;
    }
    cout<<endl;
    for(list<edge>::iterator e = mst_list.begin();e!=mst_list.end();++e)
    {
        cout<<(*e).u<<' '<<(*e).v<<' '<<(*e).w<<endl;
    }

    return 0;
}
/*Example imput is below*/
/*
6 8
1 4 4
2 3 1
2 6 2
6 5 2
3 4 3
1 2 1
3 5 1
4 5 5
*/
