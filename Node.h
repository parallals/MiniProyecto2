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
        Node(int x, int y, std::string AccentCity, int Population);
        ~Node();
};

#endif
