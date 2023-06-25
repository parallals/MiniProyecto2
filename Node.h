#ifndef Node_H
#define Node_H

#include "Point.h"

#include <string>

class Node{
    public:
        Point pos;
        std::string AccentCity;
        int Population;
        Node* next;
        Node(float x, float y, std::string AccentCity, int Population);
        Node(Point point, std::string AccentCity, int Population);
        ~Node();
};

#endif
