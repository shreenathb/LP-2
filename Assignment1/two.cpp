#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;


class Graph{
    int V;
    vector<vector<int>>adj;

public:
    Graph(int V){
        this -> V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void bfs_iterative(int start){
        vector<bool>visited(V, false);
        queue<int>q;

        q.push(start);
        visited[start] = true;

        while(!q.empty()){
            int u = q.front();
            cout << u << " ";
            q.pop();

            for(int v : adj[u]){
                if(!visited[v]){
                    q.push(v);
                    visited[v] = true;
                }    
            }
        }

        cout << endl;
    }

    void dfs_iterative(int start){
        stack<int>stk;
        vector<bool>visited(V, false);

        stk.push(start);
        visited[start] = true;

        while(!stk.empty()){
            int u = stk.top();
            stk.pop();
            cout << u << " ";

            for(int v : adj[u]){
                if(!visited[v]){
                    stk.push(v);
                    visited[v] = true;
                }
               
            }
        }

        cout << endl;

    }

    void dfs_rec(int start, vector<bool>&visited){
        cout << start << " ";
        visited[start] = true;
        
        for(int v : adj[start]){
            if(!visited[v]){
                dfs_rec(v, visited);
            }
        }

    }

    void bfs_rec(int start){
        vector<bool>visited(V, false);
        queue<int>q;

        q.push(start);
        visited[start] = true;

        bfs_util(q, visited);
    }

    void bfs_util(queue<int> &q, vector<bool>&visited){
        if(q.empty())return;
        int u = q.front();
        cout << u << " ";
        q.pop();
        
        

        for(int v : adj[u]){
            if(!visited[v]){
                q.push(v);
                visited[v] = true;
            }
        }
        bfs_util(q, visited);
    }
};

int main(){
    int V, E;
    cout << "Enter no. of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    for(int i=0;i<E;i++){
        int u, v;
        cin >> u >> v;
        g.addEdge(u,v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    g.bfs_iterative(start);
    g.dfs_iterative(start);

    vector<bool>visited(V, false);
    g.dfs_rec(start, visited);
    cout << endl;

    g.bfs_rec(start);
    
}