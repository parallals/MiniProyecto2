#include "QuadTree.h"
 
void QuadTree::insert(int x, int y, string AccentCity, int Population){
    Node* node = new Node(x, y, AccentCity, Population);
    insert(node, Root);
}

void QuadTree::insert(Node* node){
    insert(node, Root);
}

void QuadTree::insert(Node* node, Quad* &quad){
    // Current quad cannot contain it
    if(inBoundary(node->pos, quad) == true){
        delete node;
        return;
    }
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if((abs(quad->topLeft.x - quad->botRight.x) <= 1) && (abs(quad->topLeft.y - quad->botRight.y) <= 1)) {
        if(quad->node == nullptr) {
            quad->node = node;
        } else {
            Node* auxnode = quad->node;
            while(auxnode->next != nullptr){
                auxnode = auxnode->next;
            }
            auxnode->next = node;
        }
        ++cantNodes;
        return;
    }
    if((quad->topLeft.x + quad->botRight.x)/2 > node->pos.x) {
        // Indicates topLeftTree
        if ((quad->topLeft.y + quad->botRight.y)/2 > node->pos.y) {
            if(quad->topLeftTree == nullptr){
                quad->topLeftTree = new Quad(Point(quad->topLeft.x, quad->topLeft.y), Point((quad->topLeft.x + quad->botRight.x) / 2, (quad->topLeft.y + quad->botRight.y) / 2));
            }
            insert(node, quad->topLeftTree);
        }
        // Indicates botLeftTree
        else {
            if(quad->botLeftTree == nullptr){
                quad->botLeftTree = new Quad(Point(quad->topLeft.x, (quad->topLeft.y + quad->botRight.y) / 2), Point((quad->topLeft.x + quad->botRight.x) / 2, quad->botRight.y));
            }
            insert(node, quad->botLeftTree);
        }
    }else{
        // Indicates topRightTree
        if ((quad->topLeft.y + quad->botRight.y)/2 > node->pos.y) {
            if(quad->topRightTree == nullptr){
                quad->topRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x) / 2, quad->topLeft.y), Point(quad->botRight.x, (quad->topLeft.y + quad->botRight.y) / 2));
            }
            insert(node, quad->topRightTree);
        }
        // Indicates botRightTree
        else{
            if(quad->botRightTree == nullptr){
                quad->botRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x) / 2, (quad->topLeft.y + quad->botRight.y) / 2), Point(quad->botRight.x, quad->botRight.y));
            }
            insert(node, quad->botRightTree);
        }
    }
    cantQuads++;
}

// Check if current quadtree contains the point
bool QuadTree::inBoundary(Point point, Quad* quad){
    if(point.x >= quad->topLeft.x && point.x <= quad->botRight.x && point.y >= quad->topLeft.y && point.y <= quad->botRight.y){
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

void QuadTree::preOrder(Quad* quad, queue<Node*>* &lista){
    if(quad != nullptr){
        Node* auxnode = quad->node;
        while(auxnode != nullptr){
            lista->push(auxnode);
            auxnode = auxnode->next;
        }
        preOrder(quad->topLeftTree, lista);
        preOrder(quad->topRightTree, lista);
        preOrder(quad->botLeftTree, lista);
        preOrder(quad->botRightTree, lista);
    }
}

queue<Node*>* QuadTree::list(){
    queue<Node*>* listaPoblacion = new queue<Node*>();
    preOrder(Root, listaPoblacion);
    return listaPoblacion;
}

QuadTree::QuadTree(int x1, int y1, int x2, int y2){
    Root = new Quad(Point(x1, y1), Point(x2, y2));
    cantQuads = 1;
    cantNodes = 0;
}

QuadTree::~QuadTree(){


}






Node* QuadTree::search(int x, int y){
    return search(Root, Point(x, y));
}

Node* QuadTree::search(Point point){
    return search(Root, point);
}

Node* QuadTree::search(Quad* quad, Point point){
	// Current quad cannot contain it
	if (inBoundary(point, quad) == true){
		return nullptr;
    }
	// We are at a quad of unit length
	// We cannot subdivide this quad further
	if (quad->node != nullptr){
		return quad->node;
    }
	if ((quad->topLeft.x + quad->botRight.x) / 2 > point.x) {
		// Indicates topLeftTree
		if ((quad->topLeft.y + quad->botRight.y) / 2 > point.y) {
			if (quad->topLeftTree == nullptr){
				return nullptr;
            }
			return search(quad->topLeftTree, point);
		}
		// Indicates botLeftTree
		else {
			if (quad->botLeftTree == nullptr){
				return nullptr;
            }
			return search(quad->botLeftTree, point);
		}
	}else{
		// Indicates topRightTree
		if ((quad->topLeft.y + quad->botRight.y) / 2 > point.y) {
			if (quad->topRightTree == nullptr){
				return nullptr;
            }
			return search(quad->topRightTree, point);
		}
		// Indicates botRightTree
		else {
			if (quad->botRightTree == nullptr){
				return nullptr;
            }
			return search(quad->botRightTree, point);
		}
	}
};  