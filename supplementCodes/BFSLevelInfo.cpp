// #include<iostream>
// #include<vector>
// #include<utility>
#include<bits/stdc++.h>

// node numbering starts from 0

#define EDGE_LENGTH (1)

using namespace std;

class GRAPH {
public:
    vector< vector <int> > adjMat;
    vector <int> levelInfo;
    int nodes , edges ;
    GRAPH(vector< vector <int> > x, int n=0, int m=0){
        adjMat = x;
        nodes = n;
        edges = m;
        for (size_t i=0; i < nodes; i++){
            levelInfo.push_back(0);
        }
    }
};

int BFSUpdatelevelInfo(GRAPH &g, int rootNode, int rootLevel) {
    g.levelInfo.clear();
    int curr;
    queue<int>  q;
    vector<bool>  visited(g.nodes , false);
    vector<int> prev(g.nodes , -1);
    vector<int> distanceOfNodes(g.nodes, rootLevel);
    visited.at(rootNode) = true;
    q.push(rootNode);

    while(!q.empty()){
        curr = q.front();
        q.pop();
        // if(curr == endNodeNumber ){
        //     while(!q.empty()) q.pop();
        //     break;
        // }
        for(int i=0; i<g.nodes ; i++ ){
            if(g.adjMat.at(curr).at(i) && !visited.at(i)){
                prev[i] = curr;
                visited.at(i) = true;
                distanceOfNodes[i] = distanceOfNodes[curr] + EDGE_LENGTH;
                q.push(i);
            }
        }
    }
    //cout<<"LEVEL_INFO: "<<endl;
    // int temp;
    for (size_t i=0; i<g.nodes ; i++ ){
        g.levelInfo[i] = distanceOfNodes[i];
    //    cout<<"VERTEX "<< i << " : " << g.levelInfo[i] << endl;
        //cout<<"Node ";
    }
    return 0;
}

int main(){
    int n, m , q, s, A, B;
    cin>>n;         // nodes
    // cin>>m;         // edges
    m = n-1;    // tree : fully connected graph

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
    int rootNode = 0 , x, count =0, rootLevel=1;
    // cin>>rootNode; rootNode--;  // when input numbering of vertex starts from 1
    BFSUpdatelevelInfo(g, rootNode, rootLevel);

    // cout<<"LEVEL_INFO: "<<endl;
    // // int temp;
    // for (size_t i=0; i<g.nodes ; i++ ){
    //     cout<<"VERTEX "<< i << " : " << g.levelInfo[i] << endl;
    //     //cout<<"Node ";
    // }

    cin>>x;
    for (size_t i=0; i<g.nodes ; i++){
        if(g.levelInfo[i] == x)
            count++;
    }
    cout<<count;
    return 0;
}
