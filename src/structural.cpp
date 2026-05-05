#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "graph.hpp"
#include "bfs.cpp"

void Estadisticas(GrafoNoPonderado& g){
    int numN= g.n;
    int numA= g.a;
    int CompConP;
    double prom= (2 * numA)/numN; // porque las suma de los grados es el doble de aristas
    int mayorGrado= 0;
    int grado= 0;
    int diametroAprox= 0;
    int numCompCon;

    for(int i= 0; i < g.lda.size(); i++){
        if(g.lda[i].size() > grado){
            mayorGrado= i;
            grado= g.lda[i].size();
        }
    }

    vector<int> d= BFS(g, mayorGrado);
    for(int j= 0; j < d.size(); j++){
        if(d[j] > diametroAprox){
            diametroAprox= d[j];
        }
    }
}
