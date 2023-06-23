#include <Node.h>
#include <string>
#include <Point.h>
using namespace std;

 Node::Node(int x, int y, string AccentCity, string City, int Population){
       this->pos = new Point(x, y);
       this->AccentCity = AccentCity;
       this->City = City;
       this->Population = Population;
       next = nullptr;
}

Point* Node::getpos(){
    return pos;
}

string Node::getAccentCity(){
    return AccentCity;
}

string Node::getCity(){
    return City;
}

int Node::getPopulation(){
    return Population;
}

Node* Node::getNext(){
    return next;
}


