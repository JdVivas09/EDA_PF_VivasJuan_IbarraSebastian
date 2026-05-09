#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;

#include "graph.hpp"

vector<int> BFS_B(GrafoNoPonderado& g, int origen, int destino, int& nE, vector<int>& prev);

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
        if (d > dist[u]){
            continue;
        }
        nE++;
        if(u == destino){
            break;
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

vector<int> reconstruirCamino(int origen, int destino, vector<int>& prev){
    vector<int> c;
    for(int actual= destino; actual != -1; actual= prev[actual]){
        c.push_back(actual);
    }
    reverse(c.begin(), c.end());
    if(c.empty() || c[0] != origen){
        c.clear();
    }
    return c;
}

void runModuloB(GrafoNoPonderado& graphNP, GrafoPonderado& graphP){
    ofstream archivo("results/consultas_p2p.csv");
    archivo << "consulta,origen,destino,dist_dijkstra,saltos_bfs,nodos_dijkstra,nodos_bfs,t_dijkstra_ms,t_bfs_ms\n";

    vector<pair<int, int>> consultas = {
        {1, 500000},
        {100, 1000000},
        {50000, 750000},
        {200000, 800000},
        {300000, 100000},
        {1, 1087562},
        {500000, 1},
        {250000, 600000},
        {10000, 900000},
        {400000, 150000}
    };

    vector<int> caminoQ01;
    vector<int> caminoQ06;

    for (int i = 0; i < consultas.size(); i++) {
        int origen = consultas[i].first;
        int destino = consultas[i].second;

        int nE_Dijkstra;
        vector<int> prevDijkstra;
        auto startDijkstra = chrono::high_resolution_clock::now();
        vector<int> distDijkstra = Dijkstra(graphP, origen, destino, nE_Dijkstra, prevDijkstra);
        auto endDijkstra = chrono::high_resolution_clock::now();
        auto tDijkstra = chrono::duration_cast<chrono::milliseconds>(endDijkstra - startDijkstra).count();

        int nE_BFS;
        vector<int> prevBFS;
        auto startBFS = chrono::high_resolution_clock::now();
        vector<int> distBFS = BFS_B(graphNP, origen, destino, nE_BFS, prevBFS);
        auto endBFS = chrono::high_resolution_clock::now();
        auto tBFS = chrono::duration_cast<chrono::milliseconds>(endBFS - startBFS).count();

        vector<int> caminoDijkstra = reconstruirCamino(origen, destino, prevDijkstra);
        vector<int> caminoBFS = reconstruirCamino(origen, destino, prevBFS);

        int distFinDijkstra = (caminoDijkstra.empty()) ? -1 : distDijkstra[destino];
        int saltosBFS = (caminoBFS.empty()) ? -1 : caminoBFS.size() -1;
        archivo << i+1 << "," << origen << "," << destino << "," << distFinDijkstra << "," << saltosBFS << "," << nE_Dijkstra << "," << nE_BFS << "," << tDijkstra << "," << tBFS << "\n";

        if (i == 0) {
            caminoQ01 = caminoDijkstra;
        }
        if (i == 5) {
            caminoQ06 = caminoDijkstra;
        }

    }
    archivo.close();

}
