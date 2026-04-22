#include<iostream>
#include<stack>
using namespace std;
int matrix[10][10];
int V;
void initMatrix(){
    for(int i =0; i< V; i++){
        for(int j =0; j< V; j++){
            matrix[i][j] =0;
        }
    }
}
// In directed graph, edge only goes one way
void addEdge(int src, int dest){
    matrix[src][dest] = 1;
    if(src >= 0 && src < V && dest >=0 && dest < V){
        cout<<"Edge Added from "<< src << " to " << dest << endl;
    }
    else{
        cout<<"Invalid. The vertices are between 0 to "<< V -1 << endl;
    }
}
// Print matrix
void printMatrix(){
    cout<<"\n";
    for(int i =0; i < V; i++){
        cout<<i << " ";
    }
    cout<<"\n";
    for(int i =0; i <V; i++){
        cout<< i << " ";
        for(int j=0; j< V; j++){
            cout<< matrix[i][j] << " ";
        }
        cout<<"\n";
    }
}
//Operation 1: Out degree
int OutDegree(int v){
    int count = 0;
    for(int j =0; j < V; j++){
        if(matrix[v][j] ==1){// check the row, as it tells what goes out of vertex
        count++;
        }
    }
    return count;
}
//Operation 2: In degree
int InDegree(int v){
    int count =0;
    for(int i =0; i<V; i++){
        if(matrix[i][v] ==1){ // check the column, as it tells what comes in the vertex
            count++;
        }
    }
    return count;
}
// Operation 3 : Sum of degrees
int SumDegree(){
    int total = 0;
    for(int i =0; i<V; i++){
        total += OutDegree(i);
    }
    return total;
}
// Operation 4: Find path
void findPath(int src, int dest){
    bool visited[10] = { false};
    bool found = false;
    stack<int> s;
    int parent[10];
    for(int i =0; i < 10 ; i++){
        parent[i] = -1;
    }
    s.push(src);
    visited[src]=true;
    while(!s.empty()){
        int curr = s.top();
        s.pop();

        if(curr == dest){
            found = true;
            break;
        }
        for(int j = 0; j < V; j++){
            if(matrix[curr][j]==1){
                if(visited[j]==false){
                    visited[j] = true;
                    parent[j] = curr;
                    s.push(j);
                }
            }
        }
    }
    if(found == false){
        cout<<"\n Path not found";
        return;
    }
    stack<int> path;
    int node = dest;

    while(node != 1){
        path.push(node);
        node = parent[node];
    }
    cout<<"Path found: ";
    while(path.empty()== false){
        cout<<path.top();
        path.pop();
        if((path.empty() == false)){
            cout<<" -> ";
        }
    }
    cout<<"\n";
}
// Operation 5: Is Graph Strongly connected?
int Count(int start, int matrix[10][10]){
    bool visited[10] = { false};
    stack<int> s;
    s.push(start);
    visited[start]=true;
    int count =1;   // counting from the starting index

    while(!s.empty()){
        int curr = s.top();
        s.pop();

        for(int j =0; j<V; j++){
            if(matrix[curr][j]==1 && visited[j]== false){
                visited[j] = true;
                s.push(j);
                count++;
            }
        }
    }
    return count;
}
// Pass 1 :Traverse all the way forward and check if we can reach the vertices 
// If count < V -> then the graph will not be strongly connected
// Pass 2 : Flip the arrow direction to reverse all the edges to check if every pair of vertex can reach each other 
// If count == V -> then the graph is strongly connected
//For example: (pass 1: if vertex 0 can reach every vertex) -> (Then every vertex should reach vertex 0 as well (pass 2))
    bool isStronglyConnected(){
        int pass1 = Count(0, matrix);
        if(pass1 != V){
            return false;
        }
        //Pass 2 build the reverse graph
        int reversed[10][10];
        for(int i =0; i< V; i++){
            for(int j =0; j<V; j++){
                reversed[i][j]=0;
            }
        }
        for(int i =0; i<V ;i++){
            for(int j=0; j< V; j++){
                reversed[j][i] = matrix[i][j]; // Storing matrix's value in reverse
                // Flipping the arrow direction
            }
        }
        int pass2 = Count(0, matrix);
        if(pass2 == V){
            return true;
        }
        else{
            return false;
        }
    }
    //Operation 6: Is graph cyclic?
    bool isCyclic(int v, bool visited[], bool inStack[]){
        visited[v] = {true}; // mark as visited
        inStack[v] = {true}; // mark as a current active path

    // Now check the neighbors of vertex v
    for(int j =0; j<V; j++){
        if(matrix[v][j] ==1){
        if(visited[j] == false){ //if not visited the go deeper
            if(isCyclic(j, visited,inStack) == true){
                return true;
            }
        }
        else if(inStack[j] == true){
            //visited and is the current active path
            //then this cycle
            return true;
        }
    }
    }
    //after exploring all neighbors of v, remove it from the current active vertex
    inStack[v] = false;
    return false;
    }
    bool cyclic(){
        bool visited[10] = {false};
        bool inStack[10] = {false};

        for(int i =0; i<V;i++){
            if(visited[i]==false){ // Not visited yet
                if(isCyclic(i, visited, inStack)==true){
                    return true;
                }

            }
        }
        return false; // Cycle not found
    }
    int main(){
        int choice;
        cout<<"Directed Graph using Adjacency Matrix: \n";
        cout<<"Enter the number of vertices: ";
        cin>> V;
        if(V<=0 || V > 10){
            cout<<"Invalid! The vertices should exist between 0 to " << V << endl;
        }
        else{
            cout<<"\n The vertices are between 0 to "<< V - 1 << endl;
        }
        while(V>=0 || V<10){
            initMatrix();
            cout<<"\n1.Add Edge";
            cout<<"\n2.Display Adjacency matrix";
            cout<<"\n3.OutDegree of vertex";
            cout<<"\n4.InDegree of vertex";
            cout<<"\n5.Sum of Degrees";
            cout<<"\n6.Find path";
            cout<<"\n7.Check Strongly Connected";
            cout<<"\n8.Check Cyclic";
            cout<<"\n9.exit(0)";
            cout<<"\nEnter your choice: ";
            cin>> choice;

            switch(choice){
                case 1:
                // For 1.AddEdge
                int src;
                int dest;
                cout<<"Enter source and destination: ";
                cin>> src;
                cin>> dest;
                addEdge(src, dest);
                break;

                case 2:
                // For 2. Print Matrix
                cout<<"Displaying Adjacency Matrix: \n";
                printMatrix();
                break;

                case 3 :
                // For 3. Out degree
                int v;
                cout<<"\nEnter the vertex: ";
                cin>>v;
                if(v>=0 && v < V){
                    cout<<"Out Degree of vertex "<< v << " is "<< OutDegree(v) << endl;
                }
                else {
                    cout<<"\nInvalid vertex";
                }
                break;

                case 4:
                //For 4. in degree
                cout<<"\nEnter the vertex: ";
                cin>> v;
                if(v>=0 && v< V){
                    cout<<"\n The In Degree of vertex "<< v << " is "<< InDegree(v)<< endl;
                }
                else {
                    cout<<"\n Invalid vertex";
                }
                break;

                case 5:
                // For 5. Sum of Degree
                cout<<"\n Sum of Degrees: "<< SumDegree() << endl;
                break;

                case 6:
                //For 6. Find Path
                cout<<"\nEnter source and destination: ";
                cin>> src;
                cin>> dest;
                findPath(src, dest);
                break;

                case 7:
                //For 7. Strongly Connected
                if(isStronglyConnected()){
                    cout<<"\n The Graph is strongly connected\n";
                }
                else {
                    cout<<"\n The graph is not strongly connected";
                }
                break;

                case 8:
                //For 8. Cyclic or Acyclic
                if(cyclic()){
                    cout<<"\n The graph is Cyclic. \n";
                }
                else {
                    cout<<"\n The graph is not cyclic";
                }
                break;

                case 9:
                //To exit
                exit(0);
                break;

                default: {
                    cout<<"\nInvalid choice";
                    break;
                }
            }

        }
        return 0;
    }
