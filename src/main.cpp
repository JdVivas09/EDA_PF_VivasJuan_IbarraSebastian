#include <iostream>
#include <vector>
#include <string>
#include "graph.hpp"
#include "chrono"
using namespace std;

vector<Arista> ParsearArchivo(const string& archivo);

void runStructuralAnalysis(GrafoNoPonderado& graph);

void runModuloB(GrafoNoPonderado& graphNP, GrafoPonderado& graphP);
void runModuloC(GrafoNoPonderado& graphNP, GrafoPonderado& graphP);

int main(int argc, char* argv[]) {

    string modulo ="A";

    if (argc >= 2) {
        modulo = argv[1];
    }

    cout << "Cargando grafo" << endl;

    vector<Arista> aristas = ParsearArchivo("data/roadNet-PA.txt");

    cout << "Archivo cargado." << endl;

    if (modulo == "A" || modulo == "a") {

        cout << "Ejecutando modulo A: Analisis estructural" << endl;

        GrafoNoPonderado graphNP = GNP(aristas);

        runStructuralAnalysis(graphNP);

    } else if (modulo == "B" || modulo == "b") {

        cout << "Ejecutando modulo B: Comparacion de algoritmos de caminos minimos" << endl;

        GrafoNoPonderado graphNP = GNP(aristas);

        GrafoPonderado graphP = GP(aristas);

        runModuloB(graphNP, graphP);

    } else if (modulo == "C" || modulo == "c") {

        cout << "Ejecutando modulo C: Subgrafo, MST y DAG" << endl;

        GrafoNoPonderado graphNP = GNP(aristas);

        GrafoPonderado graphP = GP(aristas);

        runModuloC(graphNP, graphP);

    } else {

        cout << "Modulo no reconocido. Por favor ingrese 'A', 'B' o 'C'." << endl;
    }

    return 0;

}
