#include <vector>
#include <cstdlib>
#pragma once
using namespace std;

struct Arista {
    int u;
    int v;
};

struct GrafoNoPonderado {
    int a; // aristas
    int n; // nodos
    vector<vector<int>> lda;
};


struct PesoNodo{
    int v; // vecino
    int p; // peso
};

struct GrafoPonderado{
    int a;
    int n;
    vector<vector<PesoNodo>> lda;
};

GrafoNoPonderado GNP(vector<Arista>& a){
    GrafoNoPonderado g;
    g.a= a.size();
    for(int i= 0; i < a.size(); i++){
        if(a[i].u >= g.lda.size()){
            g.lda.resize(a[i].u + 1);
        }
        if(a[i].v >= g.lda.size()){
            g.lda.resize(a[i].v + 1);
        }
        g.lda[a[i].u].push_back(a[i].v);
        g.lda[a[i].v].push_back(a[i].u);
    }
    g.n= g.lda.size();
    return g;
}

GrafoPonderado GP(vector<Arista>& a){
    GrafoPonderado g;
    g.a= a.size();
    srand(42);
    for(int i= 0; i < a.size(); i++){
        if(a[i].u >= g.lda.size()){
            g.lda.resize(a[i].u + 1);
        }
        if(a[i].v >= g.lda.size()){
            g.lda.resize(a[i].v + 1);
        }
        int p= rand() % 10 + 1;
        g.lda[a[i].u].push_back({a[i].v, p});
        g.lda[a[i].v].push_back({a[i].u, p});
    }
    g.n= g.lda.size();
    return g;
}
