#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "algorithm"
using namespace std;

#include "graph.hpp"
vector<int> Dijkstra(GrafoPonderado& g, int origen, int destino, int& nodos, vector<int>& prev);
vector<int> reconstruirCamino(int origen, int destino, vector<int>& prev);

struct Subgrafo {
    vector<int> n; 
    vector<pair<int, int>> a;
};

Subgrafo subgrafoInd (vector<int>& c1, vector<int>& c2, GrafoNoPonderado& g){
    Subgrafo s;
    for(int i= 0; i < c1.size(); i++){
        bool existe= false;
        for(int j= 0; j < s.n.size(); j++){
            if(s.n[j] == c1[i]){
                existe= true;
                break;
            }
        }
        if(!existe){
            s.n.push_back(c1[i]);
        }
    }
    for(int k= 0; k < c2.size(); k++){
        bool existe= false;
        for(int l= 0; l < s.n.size(); l++){
            if(s.n[l] == c2[k]){
                existe= true;
                break;
            }
        }
        if(!existe){
            s.n.push_back(c2[k]);
        }
    }
    for(int i= 0; i < s.n.size(); i++){
        int u= s.n[i];
        for(int j= 0; j < g.lda[u].size(); j++){
            int v= g.lda[u][j];
            for(int k= 0; k < s.n.size(); k++){
                if(s.n[k] == v && u < v){
                    s.a.push_back({u, v});
                    break;
                }
            }
        }
    }
    return s;
}

int find(vector<int>& padre, int i){
    if(padre[i] != i){
        padre[i]= find(padre, padre[i]);
    }
    return padre[i];
}

void unite(vector<int>& padre, int x, int y){
    padre[find(padre, x)]= find(padre, y);
}

int Kruskal(int v, vector<pair<int, pair<int, int>>>& a){ // donde a son las aristas
    sort(a.begin(), a.end());
    vector<int> padre(v);
    for(int i= 0; i < v; i++){
        padre[i]= i;
    }
    int pesoT= 0;
    int cont= 0;
    for(auto& e:a){
        int w= e.first;
        int u= e.second.first;
        int z= e.second.second; //porque la arista es {peso, {u, z}}
        if(find(padre, u) != find(padre, z)){ //ambos nodos deben estar en subgrafos diferentes, sino al agregar la arista se forma un ciclo
            unite(padre, u, z);
            pesoT += w;
            if(++cont == v-1){ //porque el numero de aristas es v-1 si tiene v nodos
                break;
            }
        }
    }
    return pesoT;
}

bool DFS(Subgrafo& s, int u, vector<bool>& visitado, vector<bool>& enPila){
    visitado[u]= true;
    enPila[u]= true;
    for(int i= 0; i < s.a.size(); i++){
        if(s.a[i].first == u){
            int z= s.a[i].second;
            if(!visitado[z]){
                if(DFS(s, z, visitado, enPila)){
                    return true;
                }
            } else if(enPila[z]){
                return true;
            }
        }
    }
    enPila[u]= false;
    return false;
}

bool DAG(Subgrafo& s){
    int maxId= 0;
    for(int i= 0; i < s.n.size(); i++){
        if(s.n[i] > maxId){
            maxId= s.n[i];
        }
    }
    vector<bool> visitado(maxId + 1, false);
    vector<bool> enPila(maxId + 1, false);
    for(int i= 0; i < s.n.size(); i++){
        int u= s.n[i];
        if(!visitado[u]){
            if(DFS(s, u, visitado, enPila)){
                return false;
            }
        }
    }
    return true;
}

void exportarSubgrafo(Subgrafo& s, const string& archivo) {
    ofstream f(archivo);
    if (!f.is_open()) {
        cout << "Error al abrir " << archivo << endl;
        return;
    }

    f << "Subgrafo inducido por Q01 y Q06" << endl;
    f << "Nodos: " << s.n.size() << endl;
    f << "Aristas: " << s.a.size() << endl << endl;

    f << "Nodos:" << endl;
    for (int i = 0; i < (int)s.n.size(); i++)
        f << s.n[i] << endl;

    f << endl << "Aristas:" << endl;
    for (int i = 0; i < (int)s.a.size(); i++)
        f << s.a[i].first << " " << s.a[i].second << endl;

    f.close();
}

int buscarPeso(GrafoPonderado& g, int u, int v) {
    for (int i = 0; i < (int)g.lda[u].size(); i++) {
        if (g.lda[u][i].v == v)
            return g.lda[u][i].p;
    }
    return 1;
}

vector<pair<int, pair<int, int>>> prepararAristas(Subgrafo& s, GrafoPonderado& g) {
    vector<pair<int, pair<int, int>>> aristas;
    map<int, int> idx;

    for (int i = 0; i < (int)s.n.size(); i++)
        idx[s.n[i]] = i;

    for (int i = 0; i < (int)s.a.size(); i++) {
        int u = s.a[i].first;
        int v = s.a[i].second;
        int p = buscarPeso(g, u, v);
        aristas.push_back({p, {idx[u], idx[v]}});
    }

    return aristas;
}

void guardarAnalisis(Subgrafo& s, int pesoMST, bool esDAG, const string& archivo) {
    ofstream f(archivo);
    if (!f.is_open()) {
        cout << "Error al abrir " << archivo << endl;
        return;
    }

    f << "Analisis del subgrafo (Q01 y Q06)" << endl << endl;
    f << "Nodos: " << s.n.size() << endl;
    f << "Aristas: " << s.a.size() << endl;
    f << "Peso MST: " << pesoMST << endl;
    f << "Es DAG: " << (esDAG ? "Si" : "No") << endl;

    f.close();
}

void runModuloC(GrafoNoPonderado& graphNP, GrafoPonderado& graphP) {
    cout << "Modulo C: subgrafo, MST y DAG" << endl;

    int nodos = 0;
    vector<int> prevQ01, prevQ06;

    vector<int> distQ01 = Dijkstra(graphP, 1, 500000, nodos, prevQ01);
    vector<int> caminoQ01 = reconstruirCamino(1, 500000, prevQ01);

    nodos = 0;
    vector<int> distQ06 = Dijkstra(graphP, 1, 1087562, nodos, prevQ06);
    vector<int> caminoQ06 = reconstruirCamino(1, 1087562, prevQ06);

    if (caminoQ01.empty() || caminoQ06.empty()) {
        cout << "No se pudo reconstruir alguno de los caminos." << endl;
        return;
    }

    Subgrafo s = subgrafoInd(caminoQ01, caminoQ06, graphNP);

    vector<pair<int, pair<int, int>>> aristas = prepararAristas(s, graphP);
    int pesoMST = Kruskal(s.n.size(), aristas);
    bool esDAG = DAG(s);

    exportarSubgrafo(s, "results/subgrafo_caminos.txt");
    guardarAnalisis(s, pesoMST, esDAG, "results/analisis_subgrafo.txt");

    cout << "Modulo C finalizado." << endl;
    cout << "Archivos: results/subgrafo_caminos.txt, results/analisis_subgrafo.txt" << endl;
}
