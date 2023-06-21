#include "QuadTree.h"

#include <cmath>
#include <queue>
#include <iostream>

using namespace std;
 
void QuadTree::insert(int x, int y, string AccentCity, string City, int Population){
    Node* node = new Node(x, y, AccentCity, City, Population);
    insert(node, Root);
    cantNodes++;
}

void QuadTree::insert(Node* &node, Quad* &quad){
    // Current quad cannot contain it
    if(!inBoundary(node->pos, quad)){
        return;
    }
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if((abs(quad->topLeft->x - quad->botRight->x) <= 1) && (abs(quad->topLeft->y - quad->botRight->y) <= 1)) {
        if(quad->node == NULL) {
            quad->node = node;
            ++cantNodes;
        }
        return;
    }
    if((quad->topLeft->x + quad->botRight->x) / 2 > node->pos->x) {
        // Indicates topLeftTree
        if ((quad->topLeft->y + quad->botRight->y)/2 > node->pos->y) {
            if(quad->topLeftTree == NULL){
                quad->topLeftTree = new Quad(new Point(quad->topLeft->x, quad->topLeft->y), new Point((quad->topLeft->x + quad->botRight->x) / 2, (quad->topLeft->y + quad->botRight->y) / 2));
                ++cantQuads;
            }
            insert(node, quad->topLeftTree);
        }
        // Indicates botLeftTree
        else {
            if(quad->botLeftTree == NULL){
                quad->botLeftTree = new Quad(new Point(quad->topLeft->x, (quad->topLeft->y + quad->botRight->y) / 2), new Point((quad->topLeft->x + quad->botRight->x) / 2, quad->botRight->y));
                ++cantQuads;
            }
            insert(node, quad->botLeftTree);
        }
    }else{
        // Indicates topRightTree
        if ((quad->topLeft->y + quad->botRight->y) / 2 > node->pos->y) {
            if(quad->topRightTree == NULL){
                quad->topRightTree = new Quad(new Point((quad->topLeft->x + quad->botRight->x) / 2, quad->topLeft->y), new Point(quad->botRight->x, (quad->topLeft->y + quad->botRight->y) / 2));
                ++cantQuads;
            }
            insert(node, quad->topRightTree);
        }
        // Indicates botRightTree
        else{
            if(quad->botRightTree == NULL){
                quad->botRightTree = new Quad(new Point((quad->topLeft->x + quad->botRight->x) / 2, (quad->topLeft->y + quad->botRight->y) / 2), new Point(quad->botRight->x, quad->botRight->y));
                ++cantQuads;
            }
            insert(node, quad->botRightTree);
        }
    }
    cantQuads++;
}

// Check if current quadtree contains the point
bool QuadTree::inBoundary(Point* point, Quad* quad){
    if(point->x >= quad->topLeft->x && point->x <= quad->botRight->x && point->y >= quad->topLeft->y && point->y <= quad->botRight->y){
        return true;
    }else{
        return false;
    }
}

int QuadTree::totalPoints(){
    return cantNodes;
}

int QuadTree::totalNodes(){
    return cantQuads;
}

void QuadTree::inorder(Quad* r, std::queue<int> lista){
    if(r!=nullptr){
        inorder(r->topLeftTree,lista);
        lista.push(r->node->Population);
        inorder(r->topRightTree,lista);
        lista.push(r->node->Population);
        inorder(r->botLeftTree,lista);
        lista.push(r->node->Population);
        inorder(r->botRightTree,lista);
        lista.push(r->node->Population);
    }
}

std::queue<int> QuadTree::list(){
    std::queue<int> listaPoblacion;
    inorder(Root,listaPoblacion);
    return listaPoblacion;
}

QuadTree::QuadTree(int x1, int y1, int x2, int y2){
    Root = new Quad(new Point(x1, y1), new Point(x2, y2));
    cantQuads = 0;
    cantNodes = 0;
}

QuadTree::~QuadTree(){


}