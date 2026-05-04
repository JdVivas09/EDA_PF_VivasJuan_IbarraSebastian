#include <vector>
using namespace std;

#include "graph.hpp"

struct Cola{
    vector<int> datos;
    int f= 0; // frente de la cola
    void encolar(int v){
        datos.push_back(v);
    }
    int vaciar(){
        return datos[f++];
    }
    bool vacia(){
        return f == datos.size();
    }
};

vector<int> BFS (GrafoNoPonderado& g, int origen){
    vector<int> distancias(g.n, -1);
    vector<bool> visitados(g.n, false);
    Cola c;
    c.encolar(origen);
    visitados[origen]= true;
    distancias[origen]= 0;

    while(!c.vacia()){
        int w= c.vaciar();
        for(int i= 0; i < g.lda[w].size(); i++){
            int z= g.lda[w][i];
            if(!visitados[z]){
                visitados[z]= true;
                distancias[z]= distancias[w] + 1;
                c.encolar(z);
            }
        }
    }
    return distancias;
}
