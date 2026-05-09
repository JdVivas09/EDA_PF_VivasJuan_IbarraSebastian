#pragma once
#include <vector>
#include <cstdlib>
using namespace std;

struct Arista {
    int u;
    int v;
};

struct GrafoNoPonderado {
    int a;
    int n;
    vector<vector<int>> lda;
};

struct PesoNodo {
    int v;
    int p;
};

struct GrafoPonderado {
    int a;
    int n;
    vector<vector<PesoNodo>> lda;
};

GrafoNoPonderado GNP(vector<Arista>& a);
GrafoPonderado GP(vector<Arista>& a);