#include "Node.h"

Node::Node(int x, int y, std::string AccentCity, int Population){
    pos = Point(x, y);
    this->AccentCity = AccentCity;
    this->Population = Population;
    next = nullptr;
}

Node::~Node(){
    delete next;
    next = nullptr;
}


