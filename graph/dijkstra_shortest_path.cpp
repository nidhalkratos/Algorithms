#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <list>


#define INFINITY 99999999

using namespace std;
struct edge {int vertex; int weight;};
bool operator<(const edge &a,const edge &b)
{
    return a.vertex <b.vertex;
}

class Graph
{
private:
    int nodes;
    bool directed;
    vector<set<edge> > adjacency_set;

    //Dijkstra Fields
    int dijkstra_current_source;
    vector<int> dist;
    vector<int> parent;

public:
    Graph(int nodes,bool directed);
    void add_edge(int u,int v,int weight);
    int dijkstra(int source, int target);
    list<int> get_shortest_path(int source,int target);
};

Graph::Graph(int nodes,bool directed = true)
{
    this->nodes+1;
    this->directed = directed;
    adjacency_set.resize(this->nodes);
}

void Graph::add_edge(int u,int v,int weight = 1)
{
    adjacency_set[u].insert(edge{v,weight});
    if(!this->directed)
        adjacency_set[v].insert(edge{u,weight});
}

int Graph::dijkstra(int source,int target)
{
    if(dijkstra_current_source != source)
    {
        dijkstra_current_source = source;
        dist.resize(this->nodes);
        parent.resize(this->nodes);
        for(int i = 0; i <nodes;i++)
            dist[i] = INFINITY;

        queue<edge> q;
        set<int> visited;
        q.push(edge{source,0});
        dist[source] = 0;
        while(!q.empty())
        {
            edge e = q.front();
            q.pop();
            visited.insert(e.vertex);
            for(set<edge>::iterator child=adjacency_set[e.vertex].begin();child!=adjacency_set[e.vertex].end();++child)
            {
                if( ( dist[e.vertex] + (*child).weight ) < dist[(*child).vertex])
                {
                    dist[(*child).vertex] = dist[e.vertex]+(*child).weight;
                    parent[(*child).vertex] = e.vertex;
                }
                if(visited.find((*child).vertex) == visited.end())
                {
                    q.push(*child);
                }
            }
        }
    }
    return dist[target];
}

list<int> Graph::get_shortest_path(int source,int target)
{
    list<int> path;
    dijkstra(source,target);
    for(int vertex = target;vertex != source;vertex = parent[vertex])
    {
        path.push_front(vertex);
    }
    path.push_front(source);
    return path;
}

int main()
{
    Graph graph(6,false);
    graph.add_edge(1,2,2);
    graph.add_edge(1,3,10);
    graph.add_edge(2,3,7);
    graph.add_edge(2,4,8);
    graph.add_edge(3,5,3);
    graph.add_edge(4,5,2);
    graph.add_edge(5,6,1);
    cout<<graph.dijkstra(1,6)<<endl;
    list<int> path = graph.get_shortest_path(1,6);
    for(list<int>::iterator it = path.begin();it!=path.end();++it)
        cout<<*it<<'\t';
    return 0;
}
