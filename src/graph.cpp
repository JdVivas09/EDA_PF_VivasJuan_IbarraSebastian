#include "graph.hpp"
using namespace std;

GrafoNoPonderado GNP(vector<Arista>& a) {
    GrafoNoPonderado g;
    g.a = a.size();
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i].u >= (int)g.lda.size()) g.lda.resize(a[i].u + 1);
        if (a[i].v >= (int)g.lda.size()) g.lda.resize(a[i].v + 1);
        g.lda[a[i].u].push_back(a[i].v);
        g.lda[a[i].v].push_back(a[i].u);
    }
    g.n = g.lda.size();
    return g;
}

GrafoPonderado GP(vector<Arista>& a) {
    GrafoPonderado g;
    g.a = a.size();
    srand(42);
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i].u >= (int)g.lda.size()) g.lda.resize(a[i].u + 1);
        if (a[i].v >= (int)g.lda.size()) g.lda.resize(a[i].v + 1);
        int p = rand() % 10 + 1;
        g.lda[a[i].u].push_back({a[i].v, p});
        g.lda[a[i].v].push_back({a[i].u, p});
    }
    g.n = g.lda.size();
    return g;
}