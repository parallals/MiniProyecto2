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
    float Presicion = 1000000;
    QuadTree quadtree = QuadTree(-90*Presicion, 180*Presicion, 90*Presicion, -180*Presicion);
    // Leemos todas las líneas.
    int cont = 0;
    string AccentCity, x, y, Population, aux;
    while (getline(archivo, linea) && cont < 100) { //getline(archivo, linea)
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
    cout << quadtree.totalNodes() << "    " << quadtree.totalPoints() << endl;
    for(int i=0 ; i<10 ; i++){
        cout << "Population " << i << ": " << fixed << setprecision(7) << q->front()->pos.y/(float)Presicion << endl;
        q->pop();
    }
}
// g++ -o main main.cpp QuadTree.cpp Node.cpp Point.cpp
