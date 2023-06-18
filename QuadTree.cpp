#include "QuadTree.h"

#include <cmath>
#include <iostream>

using namespace std;
 
void QuadTree::insert(int x, int y, string AccentCity, string City, int Population){
    Node* node = new Node(x, y, AccentCity, City, Population);
    insert(node, Root);
    return;
}

void QuadTree::insert(Node* node, Quad* quad){
    if(node == NULL){
        return;
    }
    // Current quad cannot contain it
    if(!inBoundary(node->pos, quad)){
        return;
    }
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if((abs(quad->topLeft->x - quad->botRight->x) <= 1) && (abs(quad->topLeft->y - quad->botRight->y) <= 1)) {
        if(node == NULL) {
            quad->n = node;
        }
        return;
    }
    if((quad->topLeft->x + quad->botRight->x) / 2 >= node->pos->x) {
        // Indicates topLeftTree
        if ((quad->topLeft->y + quad->botRight->y)/2 >= node->pos->y) {
            if(quad->topLeftTree == NULL){
                quad->topLeftTree = new Quad(new Point(quad->topLeft->x, quad->topLeft->y), new Point((quad->topLeft->x + quad->botRight->x) / 2, (quad->topLeft->y + quad->botRight->y) / 2));
            }
            insert(node, quad->topLeftTree);
        }
        // Indicates botLeftTree
        else {
            if(quad->botLeftTree == NULL){
                quad->botLeftTree = new Quad(new Point(quad->topLeft->x, (quad->topLeft->y + quad->botRight->y) / 2), new Point((quad->topLeft->x + quad->botRight->x) / 2, quad->botRight->y));
            }
            insert(node, quad->botLeftTree);
        }
    }else{
        // Indicates topRightTree
        if ((quad->topLeft->y + quad->botRight->y) / 2 >= node->pos->y) {
            if(quad->topRightTree == NULL){
                quad->topRightTree = new Quad(new Point((quad->topLeft->x + quad->botRight->x) / 2, quad->topLeft->y), new Point(quad->botRight->x, (quad->topLeft->y + quad->botRight->y) / 2));
            }
            insert(node, quad->topRightTree);
        }
        // Indicates botRightTree
        else{
            if(quad->botRightTree == NULL){
                quad->botRightTree = new Quad(new Point((quad->topLeft->x + quad->botRight->x) / 2, (quad->topLeft->y + quad->botRight->y) / 2), new Point(quad->botRight->x, quad->botRight->y));
            }
            insert(node, quad->botRightTree);
        }
    }
}

// Check if current quadtree contains the point
bool QuadTree::inBoundary(Point* p, Quad* quad){
    if(p->x >= quad->topLeft->x && p->x <= quad->botRight->x && p->y >= quad->topLeft->y && p->y <= quad->botRight->y){
        return true;
    }else{
        return false;
    }
}