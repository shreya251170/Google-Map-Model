#include<bits/stdc++.h>
using namespace std;
#define max 5
float vertArr[25][25]; //the adjacency matrix initially 0
int dist = 0;
int V=25;    // No. of vertices

// This class represents a directed graph using adjacency list representation
class Graph
{
    list<int> *adj;
     void DFSUtil(int v, vector<bool> &visited);
public:
    Graph(int V);  // Constructor
    void createAndAddEdge(int v, int w, float weight); // adds an edge

    int findShortestPath(int s, int d);

    int printShortestPath(int parent[], int s, int d);

    int add_edge(int u,int v,float w);

    void displayMatrix(int v);

    int findMother();

};

Graph::Graph(int V)
{
    adj = new list<int>[2*V];
}

void Graph::createAndAddEdge(int v, int w, float weight)
{
        adj[v].push_back(w);
}

// To print the shortest path stored in parent[]
int Graph::printShortestPath(int parent[], int s, int d)
{
    static int level = 0;
    // If we reached root of shortest path tree
    if (parent[s] == -1)
    {
        cout << "Shortest Path between " << s << " and "
             << d << " is "  << s << " ";

        return level;
    }

    printShortestPath(parent, parent[s], d);

    level++;
    if (s < V)
        cout << s << " ";

    return level;
}

// This function mainly does BFS and prints the  shortest path
int Graph::findShortestPath(int src, int dest)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[2*V];
    int *parent = new int[2*V];

       for (int i = 0; i < 2*V; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }

    // Create a queue for BFS
    list<int> queue;

    visited[src] = true;
    queue.push_back(src);

    list<int>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        int s = queue.front();

        if (s == dest)
            return printShortestPath(parent, s, dest);

        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
                parent[*i] = s;
            }
        }
    }
}

void Graph::displayMatrix(int v) {
   int i, j;
   for(i = 0; i < v; i++) {
      for(j = 0; j < v; j++) {
         cout << vertArr[i][j]<<"\t";
      }
      cout << endl;
   }
}
int Graph::add_edge(int u, int v, float w) {       //function to add edge into the matrix
   vertArr[u][v] = w;
   vertArr[v][u] = w;
}

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void Graph::DFSUtil(int v, vector<bool> &visited)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// Returns a mother vertex if exists. Otherwise returns -1
int Graph::findMother()
{
    vector <bool> visited(V, false);

    int v = 0;

    // Do a DFS traversal and find the last finished vertex
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false)
        {
            DFSUtil(i, visited);
            v = i;
        }
    }

    //Checking the rechability

    fill(visited.begin(), visited.end(), false);
    DFSUtil(v, visited);
    for (int i=0; i<V; i++)
        if (visited[i] == false)
            return -1;

    return v;
}


void printSolution(int dist[],int s)
{
    cout<<"Vertex"<<"\t\t"<<"Distance from "<<s<<"\n";
    for (int i = 0; i < V; i++)
        cout<<i<<"\t\t"<<dist[i]<<"\n";
}

void dijkstra(float vertArr[25][25], int src)
{
    int dist[V]; // The output array.

    bool sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
        dist[src] = 0;

        for (int count = 0; count < V - 1; count++)
        {

        int u = minDistance(dist, sptSet);

        sptSet[u] = true;


        for (int v = 0; v < V; v++)

            if (!sptSet[v] && vertArr[u][v] && dist[u] != INT_MAX
                && dist[u] + vertArr[u][v] < dist[v])
                dist[v] = dist[u] + vertArr[u][v];
        }

    // print the constructed distance array
    printSolution(dist,src);
}

int findnear(float vertArr[25][25],int s,int c)
{
    int i,j=0;
    if(c==0)
        cout<<"Nearest City to source City"<<"\t\t"<<"Distance\n";
    else
        cout<<"Nearest City to destination City"<<"\t\t"<<"Distance\n";
    for(i=0;i<V;i++)
    {
            if(s>vertArr[s][i] && vertArr[s][j]!=0)
            {
                if(s-vertArr[s][i] < 50){
                    cout<<i<<"\t\t\t\t\t";
                    cout<<vertArr[s][i]<<"\n";

                }
            }
            else{
                if(vertArr[s][i]<50 && vertArr[s][i]!=0){
                    cout<<i<<"\t\t\t\t\t";
                    cout<<vertArr[s][i]<<"\n";
                }
            }

    }
}

// Driver code
int main()
{
    int V=25;
    Graph g(V);
    int s,d,choice,c;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tMAPS USING GRAPH DATA STRUCTURE \n\n\t\t\t\t\t\tBY GANESHI SHREYA(19PD12)\n\t\t\t\t\t\t   KRITHIKA V(19PD19)";
    getchar();
    system("cls");
    cout<<"\t\t\t\t\t\tCities avialable in our map:\n";
    cout<<"\n0-Coimbatore\n";
    cout<<"1-Dharapuram\n";
    cout<<"2-Oddanchatran\n";
    cout<<"3-Dindigun\n";
    cout<<"4-Madurai\n";
    cout<<"5-Pollachi\n";
    cout<<"6-Palani\n";
    cout<<"7-Chennai\n";
    cout<<"8-Neyveli\n";
    cout<<"9-Salem\n";
    cout<<"10-Pondicherry\n";
    cout<<"11-Karur\n";
    cout<<"12-Ooty\n";
    cout<<"13-Mettupalayam\n";
    cout<<"14-Kochi\n";
    cout<<"15-Alathur\n";
    cout<<"16-Kanyakumari\n";
    cout<<"17-Tirunelveli\n";
    cout<<"18-Erode\n";
    cout<<"19-Tiruppur\n";
    cout<<"20-Vellore\n";
    cout<<"21-Avinashi\n";
    cout<<"22-Krishnagiri\n";
    cout<<"23-Dharmapuri\n";
    cout<<"24-Palladan\n";
    cout<<"Enter the source(i.e;The number which represents your source city)";
    cin>>s;
    while(s <0 || s >24)
    {
        cout<<"Enter valid input";
        cin>>s;
    }
    cout<<"Enter the destination city(i.e;The number which represents your destination city)\n";
    cin>>d;
    while(d <0 || d >24)
    {
        cout<<"Enter valid input";
        cin>>d;
    }
    if(s==d)
    {
        cout<<"Source and destination city can't be the same so enter enter different city";
        cin>>d;
    }
    g.add_edge(1, 2, 41.4);
    g.add_edge(2, 3, 28.6);
    g.add_edge(3, 4, 63.2);
    g.add_edge(0,5,44.1);
    g.add_edge(1,5,58.9);
    g.add_edge(5,6,66.5);
    g.add_edge(6,3,59);
    g.add_edge(24,1,46);
    g.add_edge(24,5,50.1);
    g.add_edge(0,21,46);
    g.add_edge(9,8,156);
    g.add_edge(8,10,65.3);
    g.add_edge(10,7,166);
    g.add_edge(11,8,195);
    g.add_edge(9,23,70.5);
    g.add_edge(23,22,50.5);
    g.add_edge(22,20,120);
    g.add_edge(21,9,127);
    g.add_edge(0,24,41.6);
    g.add_edge(24,11,91.2);
    g.add_edge(0,13,34.3);
    g.add_edge(13,12,50.9);
    g.add_edge(0,15,71.3);
    g.add_edge(15,14,119);
    g.add_edge(4,17,162.8);
    g.add_edge(17,16,85.2);
    g.add_edge(19,24,16.9);
    g.add_edge(24,18,79.1);
    g.add_edge(18,21,64.8);
    g.createAndAddEdge(1, 2, 41.4);
    g.createAndAddEdge(2, 3, 28.6);
    g.createAndAddEdge(3, 4, 63.2);
    g.createAndAddEdge(0,5,44.1);
    g.createAndAddEdge(1,5,58.9);
    g.createAndAddEdge(5,6,66.5);
    g.createAndAddEdge(6,3,59);
    g.createAndAddEdge(24,1,46);
    g.createAndAddEdge(24,5,50.1);
    g.createAndAddEdge(0,21,46);
    g.createAndAddEdge(9,8,156);
    g.createAndAddEdge(8,10,65.3);
    g.createAndAddEdge(10,7,166);
    g.createAndAddEdge(11,8,195);
    g.createAndAddEdge(9,23,70.5);
    g.createAndAddEdge(23,22,50.5);
    g.createAndAddEdge(22,20,120);
    g.createAndAddEdge(21,9,127);
    g.createAndAddEdge(0,24,41.6);
    g.createAndAddEdge(24,11,91.2);
    g.createAndAddEdge(0,13,34.3);
    g.createAndAddEdge(13,12,50.9);
    g.createAndAddEdge(0,15,71.3);
    g.createAndAddEdge(15,14,119);
    g.createAndAddEdge(4,17,162.8);
    g.createAndAddEdge(17,16,85.2);
    g.createAndAddEdge(19,24,16.9);
    g.createAndAddEdge(24,18,79.1);
    g.createAndAddEdge(18,21,64.8);
    system("cls");
    cout<<"What do you want to find?\n1.The nearest cities situated around your source city\n2.The nearest cities situated around your destination city\n3.The nearest distance between source city to all the cities in the graph\n4.Finding the mother vertrex\n5.The matrix representation of a graph\n6.The shortest pathe from souce to destination\n7.Exit : ";
    cin>>choice;
    while(choice>0 && choice<7)
    {
        cout<<"\n0-Coimbatore\n";
        cout<<"1-Dharapuram\n";
        cout<<"2-Oddanchatran\n";
        cout<<"3-Dindigun\n";
        cout<<"4-Madurai\n";
        cout<<"5-Pollachi\n";
        cout<<"6-Palani\n";
        cout<<"7-Chennai\n";
        cout<<"8-Neyveli\n";
        cout<<"9-Salem\n";
        cout<<"10-Pondicherry\n";
        cout<<"11-Karur\n";
        cout<<"12-Ooty\n";
        cout<<"13-Mettupalayam\n";
        cout<<"14-Kochi\n";
        cout<<"15-Alathur\n";
        cout<<"16-Kanyakumari\n";
        cout<<"17-Tirunelveli\n";
        cout<<"18-Erode\n";
        cout<<"19-Tiruppur\n";
        cout<<"20-Vellore\n";
        cout<<"21-Avinashi\n";
        cout<<"22-Krishnagiri\n";
        cout<<"23-Dharmapuri\n";
        cout<<"24-Palladan\n";
        while(choice <0 || choice >6)
        {
            cout<<"Enter valid input";
            cin>>choice;
        }
        if(choice==1)
        {
            c=0;
            findnear(vertArr,s,c);
        }
        if(choice==2)
        {
            c=1;
            findnear(vertArr,d,c);
        }
        if(choice==4)
        {
            cout << "A mother vertex is " << g.findMother();
        }
        if(choice==3){
            dijkstra(vertArr, s);
        }
        if(choice==5)
        {
            g.displayMatrix(V);
        }
        else if(choice==6){
             g.findShortestPath(s, d);
        }
        cout<<"\nWhat do you want to find?\n1.The nearest cities situated around your source city\n2.The nearest cities situated around your destination city\n3.The nearest distance between source city to all the cities in the graph\n4.Finding the mother vertrex\n5.The matrix representation of a graph\n6.The shortest pathe from souce to destination\n7.Exit : ";
        cin>>choice;
        system("cls");
    }
    cout<<"Thank you!";

}
