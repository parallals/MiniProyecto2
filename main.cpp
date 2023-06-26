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
        quadtree.insert(stod(x), stod(y), AccentCity, stoi(Population)); 
        cont++;
    }
    archivo.close();
    queue<Node*>* q = quadtree.list();
    cout << " size ;" << " x ;" << " y " << endl;
    for(int i=0 ; i<100 ; i++){
        cout << q->size() << " ; " <<  q->front()->pos.x << " ; " << q->front()->pos.y << endl;
        q->pop();
    }
    cout << "Cantidad de Nodos: " << quadtree.totalNodes() << "   |   Cantidad de Puntos: " << quadtree.totalPoints() << endl;
    cout << "Nodos dentro de x=[-30,30] e y=[-30,30]: " << quadtree.countRegion(0, 0, 30) << endl;
    
}
// g++ -o main main.cpp QuadTree.cpp Node.cpp Point.cpp
