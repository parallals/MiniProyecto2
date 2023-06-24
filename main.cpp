#include "QuadTree.h"

#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#define Archivo "../worldcitiespop_fixed.csv"

int main() {
    ifstream archivo(Archivo);
    string linea;
    // Leemos la primer línea para descartarla, pues es el encabezado.
    getline(archivo, linea);
    // Variables que ocuparemos.
    float Presicion = 1000;
    QuadTree quadtree = QuadTree(-90*Presicion, 180*Presicion, 90*Presicion, -180*Presicion);
    // Leemos todas las líneas.
    int cont = 0;
    string AccentCity, x, y, Population, aux;
    while (getline(archivo, linea) && cont < 100000) { //getline(archivo, linea)
        stringstream stream(linea); // Convertir la cadena a un stream. 
        // Saltar valores que no ocuparemos.
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, AccentCity, ';');
        getline(stream, aux, ';');
        getline(stream, Population, ';');
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, x, ',');
        getline(stream, y, '\n');
        quadtree.insert(stod(x)*Presicion, stod(y)*Presicion, AccentCity, stoi(Population)); 
        cont++;
    }
    archivo.close();
    queue<Node*>* q = quadtree.list();
    cout << "Cantidad de Nodos: " << quadtree.totalNodes() << "   |   Cantidad de Puntos: " << quadtree.totalPoints() << endl;
    cout << "Nodos dentro de x=[-30,30] e y=[-30,30]: " << quadtree.countRegion(0*Presicion, 0*Presicion, 170*Presicion) << endl;
    
}
// g++ -o main main.cpp QuadTree.cpp Node.cpp Point.cpp
