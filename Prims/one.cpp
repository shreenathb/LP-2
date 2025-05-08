#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int prims(vector<vector<pair<int,int>>>& adj, int V){
    vector<bool>mstSet(V, false);
    vector<int>key(V, INT_MAX);
    vector<int>parent(V, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>pq;

    pq.push({0,0});
    key[0]=0;
    int totalCost = 0; 

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        if(mstSet[u])continue;

        mstSet[u] = true;
        totalCost += key[u];

        for(auto p : adj[u]){
            if(!mstSet[p.first] && key[p.first] > p.second){
                pq.push({p.second, p.first});
                key[p.first] = p.second;
                parent[p.first] = u;
            }
        }
    }

    for(int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " (" << key[i] << ") " << endl;
    }

    return totalCost;
}

int main(){
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pair<int,int>>>adj(V);

    for(int i=0;i<E;i++){
        cout << "Enter u, v and weight";
        int u,v, weight;

        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    cout << prims(adj, V);
}