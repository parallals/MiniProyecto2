#include "Node.h"

Node::Node(float x, float y, std::string AccentCity, int Population){
    pos = Point(x, y);
    this->x = x;
    this->y = y ;
    this->AccentCity = AccentCity;
    this->Population = Population;
    next = nullptr;
}

Node::~Node(){
    next = nullptr;
}