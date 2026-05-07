#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

#include "graph.hpp"

vector<int> Dijkstra(GrafoPonderado& g, int origen, int destino, int& nE, vector<int>& prev) {
    int v= g.n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //min heap
    vector<int> dist(v, 1000000000);
    prev.assign(v, -1);
    nE= 0;
    if (origen < 0 || origen >= g.n || destino < 0 || destino >= g.n ) {
        return dist;
    }
    dist[origen] = 0;
    pq.emplace(0, origen);

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int d = top.first;  
        int u = top.second;
        if(d > dist[u]){
            continue;
        }
        nE++;
        if (u == destino){
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

vector<int> BFS_B(GrafoNoPonderado& g, int origen, int destino, int& nE, vector<int>& prev);

void guardarCamino(const string& nombreArchivo, vector<int>& camino){
    ofstream archivo(nombreArchivo);
    if(!archivo.is_open()){
        cout << "Error al crear el archivo" << endl;
        return;
    }
    if (camino.empty()){
        archivo << "no hay camino"<< endl;
    } else {
        for (int i=0; i < camino.size(); i++){
            archivo << camino[i];
            if (i < camino.size() - 1){
                archivo << " ";
            }
        }
        archivo << endl;
    }
    archivo.close();
}
