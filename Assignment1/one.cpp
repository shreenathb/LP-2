#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
        string name;
        Node* down;
        Node* next;
    
        Node(string name){
            this -> name = name;
            down = NULL;
            next = NULL;
        }
};

class Graph{
    private:
        Node* head= NULL;
    public:
        void add(string node_1, string node_2){
            if(head == NULL){
                // graph hasn't been created yet
                Node* node1 = new Node(node_1);
                Node* node2 = new Node(node_2);

                head = node1;
                node1 -> next = node2;
            }else{
                // check if node_1 exists in the graph yet

                Node* currentArrayNode = head;
                bool found = false;
                Node* prevNode = NULL;

                while(currentArrayNode != NULL){
                    if(currentArrayNode->name==node_1){
                        found = true;
                        Node* currentListNode = currentArrayNode;

                        while(currentListNode->next != NULL){
                            currentListNode = currentListNode->next;
                        }
                        Node* newNode = new Node(node_2);
                        currentListNode->next = newNode;

                        break;
                    }
                    prevNode = currentArrayNode;
                    currentArrayNode = currentArrayNode->down;
                }

                if(!found){
                    Node* node1 = new Node(node_1);
                    Node* node2 = new Node(node_2);

                    prevNode->down = node1;
                    node1->next = node2;
                }
            }
        }


        void addNode(string a, string b){
            add(a,b);
            add(b,a);
        }

        void print(){
            Node* currentArrayNode = head;

            while(currentArrayNode != NULL){
                cout << currentArrayNode -> name << " : ";

                Node* currentListNode = currentArrayNode->next;

                while(currentListNode!=NULL){
                    cout << currentListNode->name << " -> ";
                    currentListNode = currentListNode->next;
                }
                currentArrayNode = currentArrayNode->down;

            }
            cout << endl;
        }

        void countOutDegree(){
            Node* currentArrayNode = head;

            while (currentArrayNode!=NULL){
                int count = 0;
                cout << currentArrayNode->name  << " : ";
                Node* currentListNode = currentArrayNode->next;
                while(currentListNode!=NULL){
                    count++;
                    currentListNode= currentListNode->next;
                }
                cout << count << endl;
                currentArrayNode = currentArrayNode->down;
            }
            
        }

        void countInDegree(){
            Node* currentArrayNode = head;
            while(currentArrayNode != NULL){
                cout << currentArrayNode->name << " : ";
                int count = 0;
                Node* currentArrayNode2 = head;
                while(currentArrayNode2 != NULL){
                    Node* currentListNode = currentArrayNode2->next; 
                    while(currentListNode != NULL){
                        if(currentListNode->name == currentArrayNode->name){
                            count++;
                        }
                        currentListNode = currentListNode->next;
                    }
                    currentArrayNode2 = currentArrayNode2->down;
                }
                cout << count<< endl;
                currentArrayNode= currentArrayNode->down;
            }
        }

        void BFS(string node){
            Node* currentNode = head;
            queue<string>q;
            vector<string>visited;

            q.push(node);
            visited.push_back(node);

            while(true){
                if(!q.empty()){
                    node = q.front();
                    q.pop();
                    cout << node << " ";
                }else{
                    break;
                }

                Node* currentNode = head;
                bool found = false;

                while(currentNode!=NULL){
                    if(currentNode->name == node){
                        found = true;
                        Node* currentListNode = currentNode->next;
                        while( currentListNode != nullptr ){
                            if( find( visited.begin(), visited.end(), currentListNode->name ) == visited.end() ) {
                            visited.push_back( currentListNode->name );
                            q.push( currentListNode->name );
                        }
                        currentListNode = currentListNode->next;
                        }
                        break;
                    }
                    currentNode = currentNode->down;
                }

                if(!found){
                    cout << "Not in graph"; 
                    return;
                }

            }

        }

        void dfs(){
            
        }

};

int main() {
    Graph g ; 
    g.addNode( "Katraj" , "PICT" ) ;
    g.addNode( "Bharti" , "Katraj" ) ; 
    g.addNode( "Bharti" , "PICT" ) ;
    g.addNode( "Katraj" , "SKNCOE" ) ; 
    g.addNode( "PICT" , "SKNCOE" ) ;
    g.addNode( "SKNCOE" , "Temple" ) ; 
    g.addNode( "Temple" , "Katraj" ) ; 
    g.addNode( "Temple" , "Kondhwa" ) ; 
    g.print() ; 
    g.countInDegree();
    g.countOutDegree();
    g.BFS( "Katraj" ) ; 
   // g.DFS( "Katraj" ) ;
    return 0;
}