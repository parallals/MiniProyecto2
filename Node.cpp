#include "Node.h"

Node::Node(float x, float y, std::string AccentCity, int Population){
    pos = Point(x, y);
    this->AccentCity = AccentCity;
    this->Population = Population;
    next = nullptr;
}

Node::Node(Point point, std::string AccentCity, int Population){
    pos = point;
    this->AccentCity = AccentCity;
    this->Population = Population;
    next = nullptr;
}

Node::~Node(){
    next = nullptr;
}