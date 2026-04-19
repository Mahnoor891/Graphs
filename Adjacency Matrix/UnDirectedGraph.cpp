#include<iostream>
#include<stack>
using namespace std;
const int max = 10;
int matrix[10][10];
int V;

void initMatrix(){
    for(int i =0; i < V; i++){
        for (int j =0; j< V; j++){
            matrix[i][j] = 0;
        }
    }
}
void addEdge(int src, int dest){
    matrix[src][dest] = 1;
    matrix[dest][src] = 1;
    if(src>= 0 && src < V && dest >=0 && dest <V){
        cout<< "Edge added from: "<< src << " to " << dest<< endl;
    }
    else {
        cout<<"\n Invalid . The vertices are from 0 to "<< V-1<< endl;
    }
}
void PrintMatrix(){
    cout<<"\n";
    for(int i =1; i < V; i++){
        cout<< i << " ";
    }
    cout<<"\n";
    for(int i = 0; i < V; i++){
        cout<< i << " ";
    for(int j =0; j < V; j++){
        cout<< matrix[i][j] << " ";
        cout<< "\n";
    }
}
}
// Operation 1 : Degree of Vertex
//count how many 1 are there in vertex's row
//v = vertex, j = row
int degree(int v){
    int c = 0; // count
    for(int j=0; j< V; j++){
        if(matrix[v][j] ==1){
            c++;
        }
    }
    
    return c;
}
//Operation 2 : Sum of Degree
int SumDegree() {
    int total =0;
    for(int i =0; i < V; i++){
        total += degree(i);
    }
    return total;
}
// Operation 3 : Find the path 
// We did it using stack and flags
void findPath(int src, int dest){
    bool visited[10] = {false}; // flagged the whole array to false as we haven't visited any index yet
    int parent[10];
    bool found = false;
    for(int i =0; i < 10; i++){
        parent[i] = -1; // Nobody has a parent yet
    }
    stack<int> s; // intialize stack
    // Start from the source
    s.push(src);  
    visited[src] = true;
    //Keep on popping until the stack is empty
    while(!s.empty()){
        // Remove the top vertex from the stack by storing in curr
        int curr = s.top(); 
        s.pop(); // remove current from the stack

        if(curr == dest){
            found = true;
            break;
        }
        // Check the surrounding neighbors as well
        for(int j =0; j<V; j++){
            if(matrix[curr][j] ==1) {  // check if the specified cell exist
                if(visited[j] == false){ // if it does and is not visited
                    visited[j] = true;   // then mark it true once visited it
                    parent[j] = curr;    // the parent of the cell value is the current row from where it is accessed
                    s.push(j);           // push that cell value in stack
                }
            }
        }  
        }
        if(found == false){
        cout<< "\nNo path exist";
        return;
    }
    //Now to print in forward direction from source to destination
    cout<<"path found: ";
    stack<int> path;
    int node = dest;
    while(node!= -1){
    path.push(node);  // push dest first, the work backward
    node = parent[node];
    }
    // Now pop , this will print source to destination 
    while(!path.empty()){
        cout<<path.top();
        path.pop();
        if(!path.empty()){
            cout<< "-> ";
        }
    }
}
// Operation 5: Is graph connected?
bool isConnected(){
    bool visited [10] = {false};
    stack<int> s;
    s.push(0);
    visited[0] = true;
    int count = 1;
    while(!s.empty()){
        int curr = s.top();
        s.pop();
        for(int j =0; j<V; j++){
            if(matrix[curr][j] ==1 && visited[j]==false){
                visited[j] = true;
                s.push(j);
                count++;
            }
        }

    }
         return (count==V);
}
//Operation 7: Is graph cyclic?
bool isCyclic(int v, bool visited[], int parent){
    visited[v] = true;
    for(int j =0; j<V; j++){
        if(matrix[v][j]==1){
            if(visited[j] ==false){
                if(isCyclic(j, visited, v)){
                    return true;
                }
            }
            else if (j!= parent){
                // the visited edge is not parent
                return true;
            }
        }
    }
    return false;
}
bool iscyclic(){
    bool visited[10]= {false};
    for(int i =0; i<V; i++){
        if(visited[i] ==false){
            if(isCyclic(i, visited,-1)){
                return true;
            }
        }
    }
    return false;
}
int main(){
    cout<<"Enter the number of vertices: ";
    cin>> V;
    if(V <= 0 || V > 10){
        cout<<"Invalid! Vertices must be between 0 to 10";
    }
    else {
        cout<<"Vertices are 0 to " << V-1 << "\n";
    }
    while(V >=0 || V < 10){
    initMatrix();
    int choice;
     cout<< " Graph Layout: \n";
    while(true){
    cout<<"\n1. Add edge";
    cout<<"\n2. Print Adjacency Matrix";
    cout<<"\n3. Degree of vertex";
    cout<<"\n4. Sum of all degrees";
    cout<<"\n5. Find path";
    cout<<"\n6.Check is connected?";
    cout<<"\n7.Check is Cyclic?";
    cout<<"\n8. exit\n";
    cout<<"\nEnter your choice: ";
    cin >> choice;

    switch(choice){
        case 1:
        int src;
        int dest;
        cout<<"\nEnter the source and destination: ";
        cin>> src;
        cin>> dest;
        addEdge(src, dest);
        break;

        case 2:
        cout<<"\nDisplaying Adjacency Matrix: ";
        PrintMatrix();
        break;

        case 3: 
        int v;
        cout<<"\n Enter vertex: ";
        cin>>v;
        if(v>=0 && v< V){
            cout<< "\n Degree of vertex is:"<< v << " is: "<< degree(v) <<endl;
        }
        else {
            cout<<"\ninvalid vertex";
        }
        break;

        case 4:
        cout<<"\n Sum of Degree: " << SumDegree()<< endl;
        break;

        case 5: 
        cout<<"\n Enter source and destination: ";
        cin>> src;
        cin>> dest;
        break;

        case 6:
        if(isConnected()){
            cout<<"\nThe graph is connected";
        }
        else{
            cout<< "\n The graph is not connected";
        }
        break;

        case 7:
        if(iscyclic()){
            cout<<"\nThe graph is cyclic ";
        }
        else {
            cout<<"\n The graph is not cyclic";
        }
        break;

        case 8:
        exit(0);

        default: {
            cout<<"\nInvalid choice";
            break;
        }
    }
}
    }
return 0;
}

