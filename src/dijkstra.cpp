#include <vector>
#include <queue>
using namespace std;

#include "graph.hpp"

vector<int> Dijkstra(GrafoPonderado& g, int origen, int destino, int& nE, vector<int>& prev) {
    int v= g.n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //min heap
    vector<int> dist(v, 1000000000);
    prev.assign(v, -1);
    nE= 0;
    dist[origen] = 0;
    pq.emplace(0, origen);

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int d = top.first;  
        int u = top.second;
        nE++;
        if(u == destino){
            break;
        }
        if (d > dist[u]){
            continue;
        }
        for(int i= 0; i < g.lda[u].size(); i++){
            int z= g.lda[u][i].v;
            int w= g.lda[u][i].p;
            if(dist[u] + w < dist[z]){
                dist[z]= dist[u] + w;
                prev[z]= u;
                pq.emplace(dist[z], z);
            }
        }
    }
    return dist;
}
