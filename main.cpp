#include "QuadTree.h"

#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#define Archivo "worldcitiespop_fixed.csv"

int main() {
    ifstream archivo(Archivo);
    string linea;
    // Leemos la primer línea para descartarla, pues es el encabezado.
    getline(archivo, linea);
    // Variables que ocuparemos.
    QuadTree quadtree = QuadTree(-180, 90, 180, -90);
    // Leemos todas las líneas.
    int cont = 0;
    string AccentCity, City, x, y, Population, aux;
    while (getline(archivo, linea) && cont < 10) { //getline(archivo, linea)
        stringstream stream(linea); // Convertir la cadena a un stream. 
        // Saltar valores que no ocuparemos.
        getline(stream, aux, ';');
        getline(stream, City, ';');
        getline(stream, AccentCity, ';');
        getline(stream, aux, ';');
        getline(stream, Population, ';');
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, x, ',');
        getline(stream, y, '\n');
        quadtree.insert((int)stod(x), (int)stod(y), AccentCity, City, stoi(Population)); 
        cont++;
    }
    archivo.close();
    queue<int>* q = quadtree.list();
    for(int i=0 ; i<10 ; i++){
        cout << "Population " << i << ": " << q->front() << endl;
        q->pop();
    }
}
// g++ -o MaxMinCoords MaxMinCoord.cpp
