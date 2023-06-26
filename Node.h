#ifndef Node_H
#define Node_H

#include "Point.h"

#include <string>

class Node{
    public:
        Point pos;
        float x;
        float y;
        std::string AccentCity;
        int Population;
        Node* next;
        Node(float x, float y, std::string AccentCity, int Population);
        ~Node();
};

#endif
