#include<iostream>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
#define MAXV 50
struct vertex{
    char data;
    struct vertex* next;
    struct EdgeNode*edgelist;
    bool visited;

};
struct EdgeNode{
    int weight; // if included
    struct vertex* v;
    struct EdgeNode*next; 
};
vertex *graph= NULL;
bool isdirected;
// Core helpers
vertex* findvertex(char data){
    vertex* curr = graph;
    while(curr!=NULL){
        if(curr->data == data){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
void revisited(){
    vertex*curr = graph;
    while(curr!= NULL){
        curr->visited = false;
        curr= curr->next;
    }
}
void AddVertex(char val){
    vertex* curr = graph;
    curr = findvertex(val);
    if(curr){
        cout<<"\n Vertex already exist";
        return;
    }
        vertex*temp =(vertex*)malloc(sizeof(vertex));
        temp->data = val;
        temp->next = NULL;
        temp->edgelist = NULL;
        temp->visited = false;
        if(graph == NULL){
            graph = temp;
        }
        else{
        vertex*vcurr = graph;
        while(vcurr->next!= NULL){
            vcurr = vcurr->next;
        }
        vcurr->next = temp;
    }
        cout<<"\nVertex added";
    }

//Remove Vertex
void RemoveVertex(char val){
    vertex*curr = graph;
    if(findvertex(val)== NULL){
        cout<<"\nVertex not found";
        return;
    }
    // First remove all the edges that are linked with the vertex:
    while(curr!= NULL){
        if(curr->data != val){
        EdgeNode*prev = NULL;
        EdgeNode*ecurr = curr->edgelist;
        while(ecurr!=NULL){
            if(ecurr->v->data == val){
                 EdgeNode* toDelete = ecurr;
                // Remove this edge
                if(prev == NULL){
                    curr->edgelist = ecurr->next;
                }
                else{
                    prev->next = ecurr->next;
                }
                    ecurr = ecurr->next;
                free(toDelete);   
            }
            else{
            prev = ecurr;
            ecurr = ecurr->next;
        }
    }
    }
     curr = curr->next;
}
    //Remove the edges that are in the edgelist of the vertex
    vertex * target = findvertex(val);
    EdgeNode* e = target->edgelist;
    while(e!=NULL){
        EdgeNode* curr = e;
        e = e->next;
        free(curr);
    }
    //Delete the node itself
    if(graph->data == val){
        graph = graph->next;
        free(target);
        return;
    }
    vertex* prev = graph;
    while(prev->next != NULL && prev->next->data != val){
        prev = prev->next;
    }
    if(prev->next != NULL){
    prev->next = target->next;
    free(target);
        }
    cout<<"\nVertex deleted";

    }
//Insert Edge (internal helper)
void InsertEdge(char src, char dest, int weight){
    vertex* vsrc = findvertex(src);
    vertex* vdest = findvertex(dest);
    if(vsrc == NULL){
        cout<<"\n Source doesnot found";
        return;
    }
    if(vdest == NULL){
        cout<<"\nDest doesnot found";
        return;
    }
    //Check if Edge already exist
    EdgeNode* check = vsrc->edgelist;
    while(check!= NULL){
        if(check->v->data == dest){
            cout<<"\n Edge already exist";
            return;
        }
        check = check->next;
    }
    //Create New EdgeNode
    EdgeNode* temp = (EdgeNode*)malloc(sizeof(EdgeNode));
    temp->weight = weight;
    temp->v = vdest;
    temp->next =NULL;
    // Append to the end of Edgelist
    if(vsrc->edgelist == NULL){
        vsrc->edgelist = temp;
    }
    else{
    EdgeNode* ecurr = vsrc->edgelist;
    while(ecurr->next!= NULL){
        ecurr = ecurr->next;
    }
    ecurr->next = temp;
}
}
// ADD EDGE
void AddEdge(char src, char dest, int weight){
    InsertEdge(src, dest, weight);
    if(!isdirected){
        InsertEdge(dest, src, weight);
    }
    cout<<"Edge Added from source "<< src <<" to dest "<<dest<< " added (weigth=" <<weight<<")"<<endl;
}
// Helper function : Remove Edge
void RemoveOneEdge(char src, char dest){
    vertex* vsrc = findvertex(src);
    if(vsrc == NULL){
        return;
    }
    EdgeNode* prev = NULL;
    EdgeNode* ecurr = vsrc->edgelist;
    while(ecurr!= NULL){
        if(ecurr->v->data == dest){
            if(prev == NULL){
                vsrc->edgelist = ecurr->next;
            }
            else{
            prev->next = ecurr->next;
            }
            free(ecurr);
            return;
        }
        prev = ecurr;
        ecurr = ecurr->next;
    }
}
void RemoveEdge(char src, char dest){
    RemoveOneEdge(src,dest); // For directed 
    if(!isdirected){
        RemoveOneEdge(dest, src); // For undirected
             }
        cout<<"\nEdge removed from source "<<src << "to dest "<< dest;
   
}
//Display
void display(){
    vertex* vcurr= graph;
    while(vcurr!=NULL){
        cout<<vcurr->data <<"->";
        EdgeNode* ecurr = vcurr->edgelist;
        while(ecurr!=NULL){
            cout<<"[" <<ecurr->v->data <<"(weigth"<< ecurr->weight <<") ]"<<endl;
            ecurr = ecurr->next;
        }
        vcurr = vcurr->next;
    }
}
//INDegree
int inDegree(char val){
    int count =0;
    vertex* vcurr = graph;
    while(vcurr!=NULL){
        EdgeNode* ecurr = vcurr->edgelist;
        while(ecurr!= NULL){
            if(ecurr->v->data == val){
                count++;
            }
            ecurr = ecurr->next;
        }
        vcurr= vcurr->next;
    }
    return count;
}
// OUT Degree 
//How many edges leaves the vertex
int outDegree(char val){
    int count = 0;
    vertex*vcurr = findvertex(val);
    if(vcurr == NULL){
        cout<<"\n Vertex not found";
        return 0;
    }
        EdgeNode*ecurr = vcurr->edgelist;
        while(ecurr!=NULL){
            count++;
            ecurr = ecurr->next;
        }
    return count;
}
//SUM of Degrees
void SumofDegree(){
    int total = 0;
     vertex*vcurr = graph;
    while(vcurr!=NULL){
        EdgeNode*ecurr = vcurr->edgelist;
        while(ecurr!=NULL){
            total++;
            ecurr = ecurr->next;
        }
        vcurr = vcurr->next;
    }
    cout<<"Sum of degrees = "<< total <<endl;
    if(!isdirected){
        cout<<"(Undirected), each edge is counted twice, actual edges = "<< total/2;
    }
}
//BFS
void BFS(){
    if(graph == NULL){
        return;
    }
    revisited();
    queue<vertex*> q;
    graph->visited = true;
     q.push(graph);
     cout<<"BFS: ";
    while(!q.empty()){
        vertex*curr = q.front();
        q.pop();
        cout<<curr->data<< " ";
        EdgeNode * e = curr->edgelist;
        while(e!=NULL){
            if(e->v->visited == false){
                e->v->visited = true;
                q.push(e->v);
            }
            e = e->next;
        }
    }
}
//Is Adjacent
bool IsAdjacent(char src, char dest) {
    vertex* temp = findvertex(src);
     if (temp == NULL) {
        cout << "Source not found\n";
        return false;
    }
    EdgeNode* e = temp->edgelist;
    while (e != NULL) {
        if (e->v->data == dest) {
            return true;   // edge mil gayi
        }
        e = e->next;
    }
    return false;  // edge nahi mili
}
//Find Neighbours
void FindNeighbours(char value){
    vertex* vcurr = findvertex(value);
     if (vcurr == NULL) {
        cout << "Vertex not found\n";
        return;
    }
    cout << "Neighbours of " << value << ": ";
    EdgeNode* e = vcurr->edgelist;
    while (e != NULL) {
        cout << e->v->data << " ";
        e = e->next;
    }
    cout << endl;
}
// Find Path
void findPath(char src, char dest){
     vertex* vsrc = findvertex(src);
    vertex* vdest = findvertex(dest);
    if(vsrc == NULL){
        cout<<"\n Source doesnot found";
        return;
    }
    if(vdest == NULL){
        cout<<"\nDest doesnot found";
        return;
    }
    revisited();
    // Parent array, it stores where we came from
    // using parallel array
    char parentof[10];
    char labels[10];
    int cnt =0;
    //fill lables array with all  vertex labels
    vertex * curr = graph;
    while(curr!= NULL){
        labels[cnt] = curr->data;
        parentof[cnt] = '\0'; // Setting it equals to empty
        cnt++;
        curr= curr->next;
    }
    //Using helper lamda to get the index of label
    auto indexof= [&](char c)->int {
        for(int i = 0;i<cnt; i++){
            if(labels[i]== c){
                return i;
            }
    }
    return -1;
};
queue<vertex*> q;
vsrc->visited = true;
bool found = false;
q.push(vsrc);
while(!q.empty()){
    vertex*curr = q.front();
    q.pop();
    if(curr->data == dest){
        found = true;
        break;
    }
    EdgeNode* e = curr->edgelist;
    while(e!=NULL){
        if(e->v->visited == false){
            e->v->visited = true;
            parentof[indexof(e->v->data)]= curr->data;
            q.push(e->v);
        }
        e = e->next;
    }
}
if(!found){
    cout<<"\nPath not found from source "<< src << "to dest "<< dest<<endl;
    return;
}
//Back track from dest to src
//Making stack like char array
char path[10];
int pathlen =0;
char step = dest;

while(step != '\0'){
    path[pathlen++] = step;
    step = parentof[indexof(step)];
}
cout<< "Path: ";
for(int i = pathlen -1; i >=0 ; i--){
    cout<<path[i];
    if(i>0) cout<<"->";
}
}
// Is connected
// UNdirected: BFS forward traversal
// Directed: BFS forward + reverse Traversal
// Making helper function
int vertexCount(){
    int count =0;
    vertex *vcurr = graph;
    while(vcurr!= NULL){
        count++;
        vcurr= vcurr->next;
    }
    return count;
}
int visitCount(){
    int count =0;
    vertex * vcurr = graph;
    while(vcurr!=NULL){
        if(vcurr->visited == true){
            count++;
        }
         vcurr = vcurr->next;
        }
        return count;
    }
void isConnected(){
    if(graph == NULL){
        return;
    }
    int total = vertexCount();
    revisited();
    graph->visited = true;
    queue<vertex*>q;
    q.push(graph);
    while(!q.empty()){
        vertex* curr = q.front();
        q.pop();
        EdgeNode* e = curr->edgelist;
        while(e!=NULL){
            if(e->v->visited== false){
                e->v->visited = true;
                q.push(e->v);
            }
            e = e->next;
        }
    }
    int forward = visitCount();
    if(!isdirected){
        if (forward == total){
           cout<<"\n graph is completed";
        }
        else {
            cout<<"\nGraph is not connected";
            return;
        }
    }
    //For directed
    revisited();
     graph->visited == true;
    queue<vertex*> q2;
    q2.push(graph);
   
    while(!q2.empty()){
        vertex*curr= q2.front();
        q2.pop();
        vertex* vcurr = graph;
        while(vcurr!= NULL){
            if(!vcurr->visited){
        EdgeNode*ecurr = vcurr->edgelist;
        while(ecurr != NULL){
        if(ecurr->v->data == curr->data){
           vcurr-> visited = true;
           q2.push(vcurr);
           break;

        }
        ecurr = ecurr->next;

    }
}
vcurr = vcurr->next;
        }
    }
int reverseVisited = visitCount();
if(forward == total && reverseVisited == total){
    cout<<"\nGraph is strongly connected";
}
else{
cout<<"\nGraph is not strongly connected";
}
}   
// Cyclic 
// directed: DFS + recursion stack
// Undirected: DFS + parent tracking
bool dfsCyclicUndirected(vertex* v, vertex* parent){
    v->visited = true;
    EdgeNode* e = v->edgelist;
    while(e!= NULL){
        if(!e->v->visited){
            if(dfsCyclicUndirected(e->v, v)){
                return true;
            }
        }
        else if(e->v != parent){ // visited neighbor that is not our parent
            return true;
        }
        e= e->next;
    }
    return false;
}

// directed: recStack: track vertices currently in the dfs recursion path
char reclabels[10]; // parallel array
bool recStack[10];
int Reccount =0;

void buildRecLabels(){
    vertex* curr= graph;
    while(curr!= NULL){
        reclabels[Reccount] = curr->data;
        recStack[Reccount]= false;
        Reccount++;
        curr = curr->next;
    }
}
int recIndexof(char c){
    for(int i=0; i< Reccount ; i++){
        if(reclabels[i] == c){
            return i;
        }
    }
    return -1;
}
bool dfsCyclicDirected(vertex* v){
    v->visited = true;
    recStack[recIndexof(v->data)]= true;
    EdgeNode* e = v->edgelist;
    while(e!=NULL){
        if(!e->v->visited){
            if(dfsCyclicDirected(e->v)){
                return true;
            }
        }
        else if(recStack[recIndexof(e->v->data)]){
            return true;
        }
        e = e->next;
    }
    recStack[recIndexof(v->data)] = false;
    return false;
}
void isCyclic(){
    revisited();
    //Undirected:
    if(!isdirected){
    vertex* curr = graph;
    while(curr!= NULL){
        if(!curr->visited){
            if(dfsCyclicUndirected(curr, NULL)){
                cout<<"\nGraph is cyclic";
                return;
            }
        }
        curr = curr->next;
    }
    cout<<"\nGraph is not cyclic";
    return;
}
buildRecLabels();
vertex* vcurr = graph;
while(vcurr!= NULL){
    if(!vcurr->visited){
        if(dfsCyclicDirected(vcurr)){
            cout<<"\nGraph is cyclic";
            return;
        }
    }
    vcurr = vcurr->next;
}
cout<<"\nGraph is not cyclic";
}
// MST / Shortest Path helpers
int buildIndex(char labels[]){
    int n =0;
    vertex * v = graph;
    while(v!= NULL){
        labels[n++] = v->data;
        v= v->next;
    }
    return n;
}
// Return the position of char c inside labels[0..n-1]
int idxOf(char c, char labels[], int n){
    for(int i =0; i< n; i++){
        if(labels[i] ==c){
            return i;
        }
    }
    return -1;
}
// Prim's MST
// Grow one tree from vertwx 0
//key[v] = cheapest edge weight that connects v to the current tree
// parent[v] = which tree-vertex offers that cheapest connection
//inMST[v] = true once v has been locked intp the tree

// Each round will pick one vertex with the smallest key, lock it in the tree

void primMST(){
    if(graph == NULL){
        cout<<"\nGraph is empty";
        return;
    }
    char labels[MAXV];
    int n = buildIndex(labels);
    int key[MAXV]; // Cheapest connection cost to mst
    int parent[MAXV]; // index of parent in MST
    bool inMST[MAXV];

    for(int i =0; i< n; i++){
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }
    key[0] = 0; // Start from vertex 0
    for(int j =0; j < n-1; j++){
        int minkey = INT_MAX;
        int u = -1;
        for(int i =0; i <n; i++){
            if(!inMST[i] && key[i] < minkey){
                minkey = key[i];
                u =i;
            }
        }
        if(u == -1){
            break; // graph is disconnected
        }
        inMST[u] = true;
        //Relax all neighbours of u
        vertex * vu = findvertex(labels[u]);
        EdgeNode* e = vu->edgelist;
        while(e!= NULL){
            int v = idxOf(e->v->data, labels, n);
            if(!inMST[v] && e->weight < key[v]){
                key[v] = e->weight;
                parent[v] = u;
            }
            e = e->next;
        }
    }
    cout<<"\n Prim's MST"<<endl;
    cout<<"Edge Weight\n";
    int total =0;
    for(int i = 1; i < n; i++){
        if(parent[i] != -1){
            cout<< labels[parent[i]] <<" - "<<labels[i]<<"\t"<<key[i]<<endl;
            total += key[i];
        }
        else{
            cout<< labels[i] <<" : unreachable (disconnected graph)\n";
        }
    }
    cout<<"Total MST weight: "<<total <<endl;
}
// Kruskal Algorithm
// Sort all the edges by weight
// Walk the sorted list; greedily take an edge if it does not form a cycle
struct KEdge{
    int u,v,w; // u,v = vertex indices, w= weight
};
int KFind(int parent[], int i){
    if(parent[i] != i){
      parent[i] = KFind(parent, parent[i]);
    }
    return parent[i];
}
void kUnion(int parent[], int rank[], int x, int y){
    int rx = KFind(parent, x);
    int ry = KFind(parent, y);
    if(rank[rx] < rank[ry]){
        parent[rx] = ry;
    }
    else if(rank[rx] > rank[ry]){
        parent[ry] = rx;
    }
    else{
        parent[ry] = rx;
        rank[rx]++;
    }
}
    bool edgeCmp(KEdge a, KEdge b){
        return a.w <b.w;
    }
    void kruskalMST(){
        if(graph == NULL){
            cout<<"Graph is empty";
            return;
        }
        char labels[MAXV];
        int n = buildIndex(labels);
        // collect all the edges from adjacency list
        KEdge edges[MAXV * MAXV];
        int cnt = 0;
        vertex* v = graph;
        while(v!= NULL){
            int u = idxOf(v->data, labels, n);
            EdgeNode* e = v->edgelist;
            while(e!= NULL){
                int w = idxOf(e->v->data, labels, n);
                // For undirected: store each edge once (u <w avoid duplicates)
                //For directed: every edge is unique, store all
                if(isdirected || u < w){
                    edges[cnt++] = {u, w, e->weight};
                }
                    e= e->next;
            }
                v = v->next;
            }
            sort(edges, edges+cnt, edgeCmp);

            int parent[MAXV], rank[MAXV];
            for(int i = 0; i < n; i++){
                parent[i] =i;
                rank[i] =0;
            }
            cout<<"\nKruskal's MST";
            cout<<"\nEdge Weight\n";
            int total =0, taken = 0;
            for(int i =0; i < cnt && taken < n-1 ; i++){
                int rx = KFind(parent, edges[i].u);
                int ry = KFind(parent, edges[i].v);
                if(rx != ry){
                    cout<< labels[edges[i].u]<< " - "<< labels[edges[i].v]<<"\t"<<edges[i].w<<endl;
                    total += edges[i].w;
                    kUnion(parent, rank, edges[i].u, edges[i].v);
                    taken++;
                }
            }
            cout<<"Total MST weight: "<<total<<endl;
        }
    
        // Dijkstra Algorithm
        //Pick and relax structure as prim's but dist[v] is the total path cost from src, not just the edge weight to v.
        void dijkstra(char src){
            if(graph == NULL){
                cout<<"Graph is empty";
                return;
            }
            if(findvertex(src)== NULL){
                cout<<"Source vertex not found\n";
                return;
            }
            char labels[MAXV];
            int n = buildIndex(labels);
            int s = idxOf(src, labels, n);
            int dist[MAXV]; // shortest known distance from src to each vertex
            bool visited[MAXV]; // true once a vertex is distance is finalised
            int prev[MAXV];  // index of predecessor on shortest path

            for(int i=0; i< n; i++){
                dist[i] = INT_MAX;
                visited[i] = false;
                prev[i] = -1;
            }
            dist[s] =0;

            for(int i = 0; i< n-1; i++){
                int minD = INT_MAX;
                int u = -1;
            
            for(int i= 0; i < n; i++){
                if(!visited[i] && dist[i] < minD){
                    minD = dist[i];
                    u = i;
                }
            }
            if(u == -1){
                break;
            }
            visited[u] = true;
            //Relax all neighbors of u
            vertex* vu = findvertex(labels[u]);
            EdgeNode* e = vu->edgelist;
            while(e!=NULL){
                int v = idxOf(e->v->data, labels, n);
                if(!visited[v] && dist[u] != INT_MAX && dist[u] + e->weight < dist[v]){
                    dist[v] = dist[u] + e->weight;
                    prev[v] = u;
                }
                e = e->next;
            }
        }
        cout<<"\nDijkstra's Shortest Path from: "<<src <<"\n";
        cout<<"\nVertex Dist Path";
        for(int i=0; i< n; i++){
            cout<< labels[i] <<"\t";
            if(dist[i] == INT_MAX){
                cout<<"INF\n";
            }
            else{
                cout<<dist[i] <<"\t";
            }
            // Reconstruct path by walking prev[] backward into array
            char path[MAXV];
            int plen = 0;
            for(int cur =i; cur != -1; cur = prev[cur]){
                path[plen++] = labels[cur];
            }
            for(int j = plen-1; j >=0; j--){
                cout<< path[j];
                if(j>0){
                    cout<<"->";
                }
            }

        }
    }
// Main
int main(){
    // Choose graph type
    int choice;
    char val;
    char src;
    char dest;
    cout<<"\n Adjacency list Graph";
    cout<<"\nSelect Graph type: ";
    cout<<"\n1. Directed";
    cout<<"\n2. Undirected";
    cout<<"\nEnter your choice: ";
    cin>>choice;
    isdirected = (choice == 1);
    cout<<(isdirected? " Directed" : " Undirected")<< " Graph Selected";
    while (true){
        cout<< "\n1. Add Vertex\n";
        cout<< "2. Remove Vertex\n";
        cout<< "3. ADD Edge\n";
        cout<< "4. Remove Edge\n";
        cout<< "5. Display Graph\n";
        cout<< "6. BFS\n";
        cout<< "7. In Degree\n";
        cout<< "8. Out Degree\n";
        cout<< "9. Sum Of Degree\n";
        cout<< "10. Is AdjacentPath\n";
        cout<< "11. Find Neighbors\n";
        cout<< "12. Find Path\n"; 
        cout<< "13. Is Connected\n";
        cout<<"14. Is Cyclic\n";
        cout<<"15. Prim's MST\n";
        cout<<"16. Kruskal's MST\n";
        cout<<"17. Dijkstra's Shortest path\n";
        cout<<"18. Exit\n";
        cout<< "Enter your choice: ";
        cin>> choice;
        switch(choice){
             case 1:
                cout << "Enter vertex: ";
                cin >> val;
                AddVertex(val);
                break;

            case 2:
            cout<<"Enter vertex to remove:";
                cin>> val;
                RemoveVertex(val);
                break;
               // ADD Edge
            case 3:
            int weight;
            cout << "Enter src dest, weight: ";
                cin >> src >> dest>>weight;
                AddEdge(src, dest, weight);
                break;
                // Remove Edge
            case 4: 
             cout<<"enter src and dest to remove edge:";
                cin>> src >> dest;
                RemoveEdge(src, dest);
                break;
             // Display
            case 5:
                display();
                break;
             // BFS
            case 6:
                BFS();
                break;
            // INDegree
                case 7:
                cout << "Enter vertex: ";
                cin >> val;
                cout<<"In degree of "<< val<<" = "<< inDegree(val)<< endl;
                break;
            //OUTDegree
            case 8:
                cout << "Enter vertex: ";
                cin >> val;
                cout<<"Out Degree of "<<val << " = "<< outDegree(val)<<endl;
                break;
            //Sum of Degree
            case 9:
                 SumofDegree();
                 break;
                 
            case 10:
                cout << "Enter src dest : ";
                cin >> src >> dest;
                cout <<(IsAdjacent( src, dest)? "Adjacent" : "Not Adjacent") << endl;
                break;

            case 11:
                cout << "Enter vertex to find Neighbours: ";
                cin >> val;
                FindNeighbours(val);
                break;
            // FindPath
            case 12:
                cout<<"Enter src and dest to find Path: ";
                cin>> src >> dest;
                findPath(src, dest);
                break;

            case 13:
                isConnected();
                break;

            case 14:
                 isCyclic();
                 break;

                 case 15:
                 primMST();
                 break;
                 case 16:
                 kruskalMST();
                 break;
                 case 17:
                 cout<<"Enter source vertex: ";
                 cin>> src;
                 dijkstra(src);
                 break;
                 case 18:
                 cout<<"\nProgram ended";
                 exit(0);
                 break;

                 default:
                 cout<<"\nInvalid Choice";
                 break;
        }
    }
   }


