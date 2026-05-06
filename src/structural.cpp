#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "graph.hpp"
#include "bfs.cpp"

void Estadisticas(GrafoNoPonderado& g, int& numN, int& numA, int& compConP, double& prom, int& mayorGrado, int& diametroAprox, int& numCompCon){
    numN= g.n;
    numA= g.a;
    compConP= 0;
    prom= (2 * numA)/numN; // porque las suma de los grados es el doble de aristas
    mayorGrado= 0;
    int grado= 0; //grado del nodo de mayor grado
    diametroAprox= 0;
    numCompCon= 0;

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

   vector<bool> visitado(g.n, false);
    for(int k= 0; k < g.lda.size(); k++){
        if(!visitado[k]){
            vector<int> d= BFS(g, k);
            int t= 0; // tamaño de la componente conexa
            for(int l= 0; l < d.size(); l++){
                if(d[l] != -1){
                    visitado[l]= true;
                    t++;
                }
            }
            numCompCon++;
            if(t > compConP){
                compConP= t;
            }
        }
    } 
    
}

void runStructuralAnalysis(GrafoNoPonderado& graph){
    int numN, numA, compConP, mayorGrado, diametroAprox, numeroCompcon;
    double prom;

    Estadisticas(graph, numN, numA, compConP, prom, mayorGrado, diametroAprox, numeroCompcon);

    ofstream archivo("results/analisis_estructural.txt");
    
    archivo << "Anailisis estructural del grafo" << endl;
    archivo << "Numero de nodos: " << numN << endl;
    archivo << "Numero de aristas: " << numA << endl;
    archivo << "Promedio de grado: " << prom << endl;
    archivo << "Grado mayor: " << mayorGrado << endl;
    archivo << "Diametro aproximado: " << diametroAprox << endl;
    archivo << "Numero de componentes conexas: " << numeroCompcon << endl;
    archivo << "Numero de nodos en la componente conexa principal: " << compConP << endl;
    archivo.close();

    cout << "Resultados del analisis estructural:" << endl;

}
