#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include  <iomanip>

#define Archivo "worldcitiespop_fixed.csv"

using namespace std;

int main() {
    ifstream archivo(Archivo);
    string linea;
    // Leemos la primer línea para descartarla, pues es el encabezado.
    getline(archivo, linea);
    // Variables que ocuparemos.
    string X, Y, aux;
    double x, y, maxX=0, maxY=0, minX=0, minY=0;
    // Leemos todas las líneas.
    while (getline(archivo, linea)) {
        stringstream stream(linea); // Convertir la cadena a un stream. 
        // Saltar valores que no ocuparemos.
        for(int i=0; i<7 ; i++) {
            getline(stream, aux, ';');
        }
        // Obtener coordenadas maximas y minimas.
        getline(stream, X, ',');
        getline(stream, Y, ',');
        x = stod(X);
        y = stod(Y);
        if(maxX < x){
           maxX = x;
        }
        if(minX > x){
           minX = x;
        }
        if(maxY < y){
           maxY = y;
        }
        if(minY > y){
           minY = y;
        }
    }
    archivo.close();
    cout << "Mayor X: " << fixed << setprecision(10) << maxX << endl;
    cout << "Menor X: " << minX << endl;
    cout << "Mayor Y: " << maxY << endl;
    cout << "Menor Y: " << minY << endl;
}
// g++ -o MaxMinCoords MaxMinCoord.cpp