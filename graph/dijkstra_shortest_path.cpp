#include <bits/stdc++.h>

#define INFINITY 99999999
#define DIRECTED 1
#define UNDIRECTED 0

using namespace std;
struct edge {int vertex; double weight;};
bool operator<(const edge &a,const edge &b)
{
    return a.vertex <b.vertex;
}

class Graph
{
private:
    size_t nb_nodes;
    bool directed;
    vector<set<edge> > adjacency_set;

    //Dijkstra Fields
    int dijkstra_current_source;
    vector<double> dist;
    vector<int> parent;

public:
    Graph(int nodes,bool directed = DIRECTED);
    void add_edge(int u,int v,int weight = 1);
    int dijkstra(int source, int target);
    list<int> get_shortest_path(int source,int target);
};

Graph::Graph(int nodes,bool directed )
{
    this->nb_nodes = nodes+1;
    this->directed = directed;
    adjacency_set.resize(this->nb_nodes);
}

void Graph::add_edge(int u,int v,int weight)
{
    adjacency_set[u].insert(edge{v,weight});
    if(!this->directed)
        adjacency_set[v].insert(edge{u,weight});
}

int Graph::dijkstra(int source,int target)
{
    if(dijkstra_current_source != source)               //Prevent recalculations when they are not needed
    {
        dijkstra_current_source = source;
        dist.resize(this->nb_nodes);
        parent.resize(this->nb_nodes);
        fill(dist.begin(),dist.end(),INFINITY);

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
                if( ( dist[e.vertex] + child->weight ) < dist[child->vertex])
                {
                    dist[child->vertex] = dist[e.vertex]+child->weight;
                    parent[child->vertex] = e.vertex;
                }
                if(visited.find(child->vertex) == visited.end())
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
    Graph graph(6,UNDIRECTED);
    graph.add_edge(1,2,2);
    graph.add_edge(1,3,10);
    graph.add_edge(2,3,7);
    graph.add_edge(2,4,8);
    graph.add_edge(3,5,3);
    graph.add_edge(4,5,2);
    graph.add_edge(5,6,1);
    list<int> path = graph.get_shortest_path(1,6);
    cout << "The shortest path is " << path.size() << " nodes long!\n";
    for(list<int>::iterator it = path.begin();it!=path.end();++it)
        cout<<*it<<'\t';
    return 0;
}
