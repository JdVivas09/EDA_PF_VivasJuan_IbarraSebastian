#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Arista {
    int u;
    int v;
};

vector<Arista> ParsearArchivo (const string& ruta){
    ifstream archivo(ruta);
    vector<Arista> a;
    string l;
    
    while (getline(archivo, l)){
        if (l.empty() || l[0]=='#'){
            continue;
        }
        stringstream ss(l);
        int u;
        int v;
        if (ss >> u >> v){
            a.push_back({u, v});
        }
    }
    archivo.close();
    return a;
}
