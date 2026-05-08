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

vector<int> BFS_B (GrafoNoPonderado& g, int origen, int destino, int& nE, vector<int>& prev){
    vector<int> d(g.n, -1);
    vector<bool> v(g.n, false);
    prev.assign(g.n, -1);
    Cola c;
    nE= 0; // contador de nodos explorados

    if (origen < 0 || origen >= g.n || destino < 0 || destino >= g.n) {
        return d; //en caso de no recibir ningún nodo
    }
    c.encolar(origen);
    v[origen]= true;
    d[origen]= 0;

    while(!c.vacia()){
        int w= c.vaciar();
        nE++;
        if(w == destino){
            break;
        }
        for(int i= 0; i < g.lda[w].size(); i++){
            int z= g.lda[w][i];
            if(!v[z]){
                v[z]= true;
                d[z]= d[w] + 1;
                prev[z]= w; //asigna al vector prev el anterior nodo
                c.encolar(z);
            }
        }
    }
    return d; //numero de saltos
}
