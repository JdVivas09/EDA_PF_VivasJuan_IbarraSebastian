#include <vector>
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
