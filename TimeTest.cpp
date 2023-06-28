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
	    auto duration = duration_cast<microseconds>(end - start);
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
	auto duration = duration_cast<microseconds>(end - start);
 	return duration.count();    
}

int TestCount(QuadTree* quadtree, int distancia){
	auto start = high_resolution_clock::now();
    int aux = quadtree->countRegion(0, 0, distancia);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
 	return duration.count();    
}

int main(){

	cout<< "----------------------------------------------------------------------------------" <<endl;
	cout<< "Todas los siguientes valores son el promedio de veinte veces el mismo experimento:" <<endl;
	cout<< "----------------------------------------------------------------------------------" <<endl;

	cout << endl;
	cout<< "QuadTree, insert():" <<endl;
	cout << endl;
    long dur100k = 0 ; long dur200k = 0 ; long dur300k = 0 ; long dur400k = 0 ; long dur500k = 0 ; long dur600k = 0 ;
    long dur700k = 0 ; long dur800k = 0 ; long dur900k = 0 ; long dur1000k = 0 ; long durTodos = 0 ; 
    long dur1400k = 0 ; long dur1800k = 0 ; long dur2200k = 0 ; long dur2600k = 0 ; long dur3000k = 0 ; 
    for(int i = 0; i < 20 ; ++i){     
    	dur100k = dur100k + TestInsert(100000);
    	dur200k = dur200k + TestInsert(200000);
    	dur300k = dur300k + TestInsert(300000);
    	dur400k = dur400k + TestInsert(400000);
        dur500k = dur500k + TestInsert(500000);
        dur600k = dur600k + TestInsert(600000);
        dur700k = dur700k + TestInsert(700000);
        dur800k = dur800k + TestInsert(800000);
        dur900k = dur900k + TestInsert(900000);
        dur1000k = dur1000k + TestInsert(1000000);
        dur1400k = dur1400k + TestInsert(1400000);
        dur1800k = dur1800k + TestInsert(1800000);
        dur2200k = dur2200k + TestInsert(2200000);
        dur2600k = dur2600k + TestInsert(2600000);
        dur3000k = dur3000k + TestInsert(3000000);
        durTodos = durTodos + TestInsert(10000000);
	}	    
    cout << "Insercion de 100000 elementos en microsegundos: " << dur100k/20 << endl;
	cout << "Insercion de 200000 elementos en microsegundos: " << dur200k/20 << endl;
	cout << "Insercion de 300000 elementos en microsegundos: " << dur300k/20 << endl;
	cout << "Insercion de 400000 elementos en microsegundos: " << dur400k/20 << endl;
	cout << "Insercion de 500000 elementos en microsegundos: " << dur500k/20 << endl; 
	cout << "Insercion de 600000 elementos en microsegundos: " << dur600k/20 << endl;    
	cout << "Insercion de 700000 elementos en microsegundos: " << dur700k/20 << endl;    
	cout << "Insercion de 800000 elementos en microsegundos: " << dur800k/20 << endl;    
	cout << "Insercion de 900000 elementos en microsegundos: " << dur900k/20 << endl;   
	cout << "Insercion de 1000000 elementos en microsegundos: " << dur1000k/20 << endl;        
	cout << "Insercion de 1400000 elementos en microsegundos: " << dur1400k/20 << endl;     
	cout << "Insercion de 1800000 elementos en microsegundos: " << dur1800k/20 << endl;     
	cout << "Insercion de 2200000 elementos en microsegundos: " << dur2200k/20 << endl;        
	cout << "Insercion de 2600000 elementos en microsegundos: " << dur2600k/20 << endl;     
	cout << "Insercion de 3000000 elementos en microsegundos: " << dur3000k/20 << endl;      
	cout << "Insercion de todos los elementos en microsegundos: " << durTodos/20 << endl;     
	cout << endl;	

    cout<< "----------------------------------------------------------------------------------" <<endl;

    cout << endl;
    cout<<"QuadTree, AggregateRegion():"<<endl;
    cout << endl;
    long d1 = 1 ; long d2 = 2 ; long d3 = 8 ; long d4 = 15 ; long d5 = 90;
    long dur1 = 0 ; long dur2 = 0 ; long dur3 = 0 ; long dur4 = 0 ; long dur5 = 0;
    QuadTree* quadtree = QuadTreeCompleto();
    for(int i = 0; i<20 ; ++i){
        dur1 = dur1 + TestAggregate(quadtree, d1);
        dur2 = dur2 + TestAggregate(quadtree, d2);
        dur3 = dur3 + TestAggregate(quadtree, d3);
        dur4 = dur4 + TestAggregate(quadtree, d4);
        dur5 = dur5 + TestAggregate(quadtree, d5);
    }
    cout << "Aggregate de 2x2 en microsegundos: " << dur1/20 << endl;
	cout << "Aggregate de 5x5 en microsegundos:" << dur2/20 << endl;
	cout << "Aggregate de 17x17 en microsegundos:" << dur3/20 << endl;
	cout << "Aggregate de 31x31 en microsegundos:" << dur4/20 << endl;
	cout << "Aggregate de 181x181 en microsegundos:: " << dur5/20 << endl;    
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
    cout << "Aggregate de 2x2 en microsegundos: " << dur1/20 << endl;
	cout << "Aggregate de 5x5 en microsegundos:" << dur2/20 << endl;
	cout << "Aggregate de 17x17 en microsegundos:" << dur3/20 << endl;
	cout << "Aggregate de 31x31 en microsegundos:" << dur4/20 << endl;
	cout << "Aggregate de 181x181 en microsegundos:: " << dur5/20 << endl;    
    cout << endl;
}

