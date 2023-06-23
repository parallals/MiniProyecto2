#ifndef Node_H
#define Node_H
#include <Point.h>
#include <string>

using namespace std;

class Node{
    protected:
        Point* pos;
        string AccentCity;
        string City;
        int Population;
        Node* next;
    public:
        Node();     
        Point* getpos();
        string getAccentCity();
        string getCity();
        int getPopulation();
        Node* getNext(); 
};
#endif
