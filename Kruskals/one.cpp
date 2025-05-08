#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    int u;
    int v;
    int wt;
};

bool comp(Edge &a, Edge &b){
    return a.wt < b.wt;
}

int findUParent(vector<int>& parent, int i){
    if(i == parent[i]){
        return i;
    }else{
        return findUParent(parent, parent[i]);
    }
}

void UnionByRank(vector<int>& parent, vector<int> & rank, int u , int v){
    u = findUParent(parent, u);
    v = findUParent(parent, v);
    if(rank[u] < rank[v]){
        parent[u] = v;
    }else if(rank[u] > rank[v]){
        parent[v] = u;
    }else{
        parent[v] = u;
        rank[u]++;
    }
}

vector<Edge> kruskal(vector<Edge> edges, int V){
    vector<int>parent(V);

    sort(edges.begin(), edges.end(), comp);
    for(int i=0;i<V;i++){
        parent[i] = i;
    }

    vector<int> rank(V, 0);
    vector<Edge>res;

    for(auto edge : edges){
        int u = edge.u;
        int v = edge.v;
        int wt = edge.wt;

        if(findUParent(parent,u) != findUParent(parent,v)){
            res.push_back(edge);
            UnionByRank(parent, rank, u, v);
        }
    }

    return res;
}

int main(){
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter edges (u v weight):\n";
    vector<Edge> edges(E);
    for(int i=0;i<E;i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].wt;
    }

    vector<Edge> mst = kruskal(edges, V);
    for (auto e : mst){
        cout << e.u << " - " << e.v << " : " << e.wt << endl;
    }
     
}