#include "QuadTree.h"

#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#define Archivo "../worldcitiespop_fixed.csv"

using namespace std;
using namespace std::chrono;

int TestInsert(int elementos){
    ifstream archivo(Archivo);
    string linea;
    // Leemos la primer línea para descartarla, pues es el encabezado.
    getline(archivo, linea);
    // Variables que ocuparemos.    
    QuadTree* quadtree = new QuadTree(-90, 180, 90, -180);
    int cont = 0, duracion = 0;
    string AccentCity, x, y, Population, aux;
    while(getline(archivo, linea) && (cont < elementos)){ 
        stringstream stream(linea); // Convertir la cadena a un stream. 
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, AccentCity, ';');
        getline(stream, aux, ';');
        getline(stream, Population, ';');
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, x, ',');
        getline(stream, y, '\n');
        float xf = stof(x);
        float yf = stof(y);
        int Populationi = stoi(Population);
	    auto start = high_resolution_clock::now();
        quadtree->insert(xf, yf, AccentCity, Populationi);
	    auto end = high_resolution_clock::now();
	    auto duration = duration_cast<milliseconds>(end - start);
        duracion = duracion + duration.count();
        cont++;
    }
    archivo.close();
	delete quadtree;
 	return duracion;	
} 

QuadTree* QuadTreeCompleto(){
    ifstream archivo(Archivo);
    string linea;
    getline(archivo, linea);
    QuadTree* quadtree = new QuadTree(-90, 180, 90, -180);
    int  duracion = 0;
    string AccentCity, x, y, Population, aux;
    while(getline(archivo, linea)){ 
        stringstream stream(linea);
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, AccentCity, ';');
        getline(stream, aux, ';');
        getline(stream, Population, ';');
        getline(stream, aux, ';');
        getline(stream, aux, ';');
        getline(stream, x, ',');
        getline(stream, y, '\n');
        float xf = stof(x);
        float yf = stof(y);
        int Populationi = stoi(Population);
        quadtree->insert(xf, yf, AccentCity, Populationi);
    }
    archivo.close();
 	return quadtree;	
} 

int TestAggregate(QuadTree* quadtree, int distancia){
	auto start = high_resolution_clock::now();
    long aux = quadtree->AggregateRegion(0, 0, distancia);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
 	return duration.count();    
}

int TestCount(QuadTree* quadtree, int distancia){
	auto start = high_resolution_clock::now();
    int aux = quadtree->countRegion(0, 0, distancia);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
 	return duration.count();    
}

int main(){

	cout<< "----------------------------------------------------------------------------------" <<endl;
	cout<< "Todas los siguientes valores son el promedio de veinte veces el mismo experimento:" <<endl;
	cout<< "----------------------------------------------------------------------------------" <<endl;

	cout << endl;
	cout<< "QuadTree, insert():" <<endl;
	cout << endl;
    int dur100k = 0 ; int dur200k = 0 ; int dur300k = 0 ; int dur400k = 0 ; int dur500k = 0; int durTodos = 0;
    for(int i = 0; i < 20 ; ++i){     
    	dur100k = dur100k + TestInsert(100000);
    	dur200k = dur200k + TestInsert(200000);
    	dur300k = dur300k + TestInsert(300000);
    	dur400k = dur400k + TestInsert(400000);
        dur500k = dur500k + TestInsert(500000);
        durTodos = durTodos + TestInsert(10000000);
	}	    
    cout << "Insercion de 100000 elementos en ms: " << dur100k/20 << endl;
	cout << "Insercion de 200000 elementos en ms: " << dur200k/20 << endl;
	cout << "Insercion de 300000 elementos en ms: " << dur300k/20 << endl;
	cout << "Insercion de 400000 elementos en ms: " << dur400k/20 << endl;
	cout << "Insercion de 500000 elementos en ms: " << dur500k/20 << endl;    
	cout << "Insercion de todos los elementos en ms: " << durTodos/20 << endl;     
	cout << endl;	

    cout<< "----------------------------------------------------------------------------------" <<endl;

    cout << endl;
    cout<<"QuadTree, AggregateRegion():"<<endl;
    cout << endl;
    int d1 = 1 ; int d2 = 2 ; int d3 = 8 ; int d4 = 15 ; int d5 = 90;
    int dur1 = 0 ; int dur2 = 0 ; int dur3 = 0 ; int dur4 = 0 ; int dur5 = 0;
    QuadTree* quadtree = QuadTreeCompleto();
    for(int i = 0; i<20 ; ++i){
        dur1 = dur1 + TestAggregate(quadtree, d1);
        dur2 = dur2 + TestAggregate(quadtree, d2);
        dur3 = dur3 + TestAggregate(quadtree, d3);
        dur4 = dur4 + TestAggregate(quadtree, d4);
        dur5 = dur5 + TestAggregate(quadtree, d5);
    }
    cout << "Aggregate de 2x2 en ms: " << dur1/20 << endl;
	cout << "Aggregate de 5x5 en ms:" << dur2/20 << endl;
	cout << "Aggregate de 17x17 en ms:" << dur3/20 << endl;
	cout << "Aggregate de 31x31 en ms:" << dur4/20 << endl;
	cout << "Aggregate de 181x181 en ms:: " << dur5/20 << endl;    
    cout << endl;

    cout<< "----------------------------------------------------------------------------------" <<endl;
    
    cout << endl;
    cout<<"QuadTree, countRegion():"<<endl;
    cout << endl;
    dur1 = 0 ; dur2 = 0 ; dur3 = 0 ; dur4 = 0 ; dur5 = 0;
    for(int i = 0; i<20 ; ++i){
        dur1 = dur1 + TestCount(quadtree, d1);
        dur2 = dur2 + TestCount(quadtree, d2);
        dur3 = dur3 + TestCount(quadtree, d3);
        dur4 = dur4 + TestCount(quadtree, d4);
        dur5 = dur5 + TestCount(quadtree, d5);
    }
    cout << "Aggregate de 2x2 en ms: " << dur1/20 << endl;
	cout << "Aggregate de 5x5 en ms:" << dur2/20 << endl;
	cout << "Aggregate de 17x17 en ms:" << dur3/20 << endl;
	cout << "Aggregate de 31x31 en ms:" << dur4/20 << endl;
	cout << "Aggregate de 181x181 en ms:: " << dur5/20 << endl;    
    cout << endl;
}

