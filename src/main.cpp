#include <iostream>
#include <vector>
#include "graph.hpp"

using namespace std;

vector<Arista> ParsearArchivo(const string& archivo);

void runStructuralAnalysis(GrafoNoPonderado& graph);
    
int main() {

    cout << "Cargando grafo" << endl;

    vector<Arista> aristas = ParsearArchivo("data/roadNet-PA.txt");
    
    cout << "Archivo cargado correctamente." << endl;  

    GrafoNoPonderado graph = GNP(aristas);

    cout << "Grafo cargado correctamente." << endl;

    cout << "Ejecutando modulo A" << endl;

    runStructuralAnalysis(graph);

    cout << "Analisis completado." << endl;
    
    return 0;
}
