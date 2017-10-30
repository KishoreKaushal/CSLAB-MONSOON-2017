#include<bits/stdc++.h>
using namespace std;
#define EDGE_LENGTH (6)


class GRAPH {
public:
    vector< vector <int> > adjMat;
    // vector <int> levelInfo;
    int nodes , edges ;
    GRAPH(vector< vector <int> > x, int n=0, int m=0){
        adjMat = x;
        nodes = n;
        edges = m;
        // for (size_t i=0; i < nodes; i++){
        //     levelInfo.push_back(0);
        // }
    }
};

int DFSconnectedInfo(GRAPH &g, int rootNode , vector <bool> &visited){
    int curr;
    stack<int> s;
    visited.clear();
    for(size_t i=0; i <g.nodes ; i++) visited.push_back(false);
    // vector<bool>  visited(g.nodes , false);
    vector<int> prev(g.nodes , -1);
    visited.at(rootNode) = true;
    s.push(rootNode);

    // cout<<"DFS: "<<endl;
    while(!s.empty()){

        curr = s.top();
        // cout<<curr+1<<endl;
        s.pop();
        // if(curr == endNodeNumber ){
        //     while(!q.empty()) q.pop();
        //     break;
        // }
        for(int i=0; i<g.nodes ; i++ ){
            if(g.adjMat.at(curr).at(i) && !visited.at(i)){
                prev[i] = curr;
                visited.at(i) = true;
                s.push(i);
            }
        }
    }
    return 0;
}



int main(){
    int n, m , q, s, A, B;
    cin>>n;         // nodes
    cin>>m;         // edges
    // m = n-1;    // tree : fully connected graph

    vector< pair<int, int> > edges;
    pair <int , int > e;

    for(int i=0; i<m; i++){
        cin >> e.first ;
        cin >> e.second ;
        e.first--;      // when input numbering of vertex starts from 1
        e.second--;     // when input numbering of vertex starts from 1
        edges.push_back(e);
        e = make_pair(e.second , e.first);
        edges.push_back(e);
    }
    vector< vector <int> > adjMat;
    std::vector<int> row(n);
    for (int i = 0; i <n; i++) {
        for(int j = 0; j<n; j++){
            auto p = std::make_pair(i, j);
            if(std::find(edges.begin(), edges.end(), p) != edges.end())
            row.at(j) = 1;
            else
            row.at(j) = 0;
        }
        adjMat.push_back(row);
    }
    GRAPH g(adjMat , n , m);
    int count =0, rootNode=0;     cin>>rootNode;
    rootNode--;     // when input numbering of vertex starts from 1
    vector <bool> connected;
    DFSconnectedInfo(g , rootNode , connected);
    for(size_t i=0; i<connected.size(); i++){
        if(connected[i] == false) count++;
    }
    cout<<count;
    return 0;
}
