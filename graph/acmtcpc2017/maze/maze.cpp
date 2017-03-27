#include <bits/stdc++.h>
#define FOR(i,beg,end) for(int i =beg;i<end;i++)
#define INFINITY 1000000000
//#define PRINT_PATH        //Activate this line to see the path  , note that the path is reversed

using namespace std;
typedef pair<int , int > ii;
typedef vector< ii > vii;
typedef vector< vii > vvii;

bool exist(ii point,int rows, int cols)
{
    return point.first <rows && point.first >=0 && point.second < cols && point.second >=0;
}
bool same_line(ii point1,ii point2)
{
    return point1.first == point2.first || point1.second == point2.second;
}
bool its_up(ii point1,ii point2)
{
    return point1.second == point2.second && point1.first > point2.first;
}
bool its_bottom(ii point1,ii point2)
{
    return point1.second == point2.second && point1.first < point2.first;
}
bool its_left(ii point1,ii point2)
{
    return point1.second > point2.second && point1.first == point2.first;
}
bool its_right(ii point1,ii point2)
{
    return point1.second < point2.second && point1.first == point2.first;
}
int dist(ii point1, ii point2)
{
    return sqrt((point1.first - point2.first) * (point1.first - point2.first) + (point1.second - point2.second) * (point1.second - point2.second));
}

vii get_neighbors(vii all_rocks, ii current_point,int rows, int cols)
{
    vii neighbors;
    ii right_neighbor;
    ii left_neigbor;
    ii top_neighbor;
    ii bottom_neighbor;
    int dist_right, dist_left, dist_up ,dist_bottom;
    dist_bottom = dist_left = dist_right = dist_up = INFINITY;
    right_neighbor = left_neigbor = top_neighbor = bottom_neighbor = make_pair(-1,-1);
    FOR(i,0,all_rocks.size())
    {
        ii point = all_rocks[i];
        if(same_line(current_point,point))
        {
            if(its_up(current_point,point))
            {
                if(dist(current_point,point) < dist_up)
                {
                    dist_up = dist(current_point,point);
                    top_neighbor = point;
                    top_neighbor.first++;
                    dist_up--;
                }
            }
            if(its_bottom(current_point,point))
            {
                if(dist(current_point,point) < dist_bottom)
                {
                    dist_bottom = dist(current_point,point);
                    bottom_neighbor = point;
                    bottom_neighbor.first--;
                    dist_bottom--;
                }
            }
            if(its_left(current_point,point))
            {
                if(dist(current_point,point) < dist_left)
                {
                    dist_left = dist(current_point,point);
                    left_neigbor = point;
                    left_neigbor.second++;
                    dist_left--;
                }
            }
            if(its_right(current_point,point))
            {
                if(dist(current_point,point) < dist_right)
                {
                    dist_right = dist(current_point,point);
                    right_neighbor = point;
                    right_neighbor.second--;
                    dist_right--;
                }
            }
        }
    }
    if(dist_up < INFINITY && dist_up > 0)
        neighbors.push_back(top_neighbor);
    else if(dist_up == INFINITY)
        neighbors.push_back(make_pair(0,current_point.second));
    if(dist_bottom < INFINITY && dist_bottom > 0)
        neighbors.push_back(bottom_neighbor);
    else if(dist_bottom == INFINITY)
        neighbors.push_back(make_pair(rows-1,current_point.second));
    if(dist_left < INFINITY && dist_left > 0)
        neighbors.push_back(left_neigbor);
    else if(dist_left == INFINITY)
        neighbors.push_back(make_pair(current_point.first,0));
    if(dist_right < INFINITY && dist_right > 0)
        neighbors.push_back(right_neighbor);
    else if(dist_right == INFINITY)
        neighbors.push_back(make_pair(current_point.first,cols-1));

    return neighbors;
}
int bfs(vii all_rocks , ii starting_point,ii target_point,int rows, int cols)
{
    queue<ii> to_be_visited;
    set<ii> is_visited;
    map<ii,int> dists;
    map<ii,ii> parents;
    if(starting_point == target_point)
        return 0;
    dists[starting_point] = 0;
    parents[starting_point] = starting_point;
    to_be_visited.push(starting_point);
    is_visited.insert(starting_point);
    int min_nb_steps = 0;
    vii target_point_neighbors = get_neighbors(all_rocks,target_point,rows,cols);
    set<ii> reachable_to_target_point;
    FOR(i,0,target_point_neighbors.size())
    {
        if(its_right(target_point,target_point_neighbors[i]))
        {
            for(ii p = make_pair(target_point.first,target_point.second+1);p.second <= target_point_neighbors[i].second;p.second++)
            {
                reachable_to_target_point.insert(p);
            }
        }
        if(its_left(target_point,target_point_neighbors[i]))
        {
            for(ii p = make_pair(target_point.first,target_point.second-1);p.second >= target_point_neighbors[i].second;p.second--)
            {
                reachable_to_target_point.insert(p);
            }
        }
        if(its_up(target_point,target_point_neighbors[i]))
        {
            for(ii p = make_pair(target_point.first-1,target_point.second);p.first >= target_point_neighbors[i].first;p.first--)
            {
                reachable_to_target_point.insert(p);
            }
        }
        if(its_bottom(target_point,target_point_neighbors[i]))
        {
            for(ii p = make_pair(target_point.first+1,target_point.second);p.first <= target_point_neighbors[i].first;p.first++)
            {
                reachable_to_target_point.insert(p);
            }
        }
    }

    while(!to_be_visited.empty())
    {
        ii point = to_be_visited.front();
        to_be_visited.pop();
        vii neighbors = get_neighbors(all_rocks,point,rows,cols);
        if(same_line(point, target_point))
        {
            if(reachable_to_target_point.find(point) != reachable_to_target_point.end())
            {
                int distance = dists[point] + 1;
                cout << distance << endl;
                #ifdef PRINT_PATH
                    do
                    {
                        cout << point.first << ' ' << point.second << endl;
                        point = parents[point];
                    }while(parents[point] != point);
                #endif
                return distance;
            }
        }
        FOR(i,0,neighbors.size())
        {
            ii neighbor = neighbors[i];
            if(is_visited.find(neighbor) == is_visited.end())
            {
                to_be_visited.push(neighbor);
                is_visited.insert(neighbor);
                dists[neighbor] = dists[point] + 1;
                parents[neighbor] = point;
            }
        }
    }
    cout << -1;
    return -1;
}

int main()
{
    freopen("maze.in","r",stdin);
    cin.sync_with_stdio(false);
    cin.tie(0);
    int nb_cases; cin >> nb_cases;
    while(nb_cases--)
    {
        int rows, cols, rocks;
        cin >> rows >> cols >> rocks;
        ii start_point , end_point;
        cin >> start_point.first >> start_point.second >> end_point.first >> end_point.second;
        vii all_rocks;
        FOR(i,0,rocks)
        {
            ii arock;
            cin >> arock.first >> arock.second;
            all_rocks.push_back(arock);
        }
        sort(all_rocks.begin(),all_rocks.end());
        bfs(all_rocks,start_point,end_point,rows,cols);
    }
    return 0;
}
