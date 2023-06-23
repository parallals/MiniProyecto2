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
    QuadTree quadtree = QuadTree(-90, 180, 90, -180);
    // Leemos todas las líneas.
    int cont = 0;
    string AccentCity, x, y, Population, aux;
    while (getline(archivo, linea) && cont < 10) { //getline(archivo, linea)
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
        quadtree.insert(stod(x), stod(y), AccentCity, stoi(Population)); 
        cont++;
    }
    archivo.close();
    queue<Node*>* q = quadtree.list();
    cout << quadtree.totalNodes() << "    " << quadtree.totalPoints() << endl;
    for(int i=0 ; i<10 ; i++){
        cout << "Population " << i << ": " << q->front() << endl;
        q->pop();
    }
}
// g++ -o MaxMinCoords MaxMinCoord.cpp
