#include <vector>
#include <algorithm>
using namespace std;

#include "graph.hpp"

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
