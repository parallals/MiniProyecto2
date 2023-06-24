#include "QuadTree.h"
 
 
QuadTree::QuadTree(int x1, int y1, int x2, int y2){
    Root = new Quad(Point(x1, y1), Point(x2, y2));
    cantQuads = 1;
    cantNodes = 0;
}

QuadTree::~QuadTree(){

}

// Check if current quadtree contains the point
bool QuadTree::inBoundary(Point point, Quad* quad){
    if((point.x >= quad->topLeft.x) && (point.x <= quad->botRight.x) && (point.y >= quad->topLeft.y) && (point.y <= quad->botRight.y)){
        return true; // Punto dentro del Quad.
    }
    return false; // Punto fuera del Quad.
}

bool QuadTree::interseccionRegiones(Point point, int d, Quad* quad){
    if((quad->botRight.x < point.x-d) || (quad->topLeft.x > point.x+d) || (quad->botRight.y < point.y-d) || (quad->topLeft.y > point.y+d)){
        return false; // Quad fuera de la Región.
    }
    return true; // Quad dentro o intersectando la Región.
}

int QuadTree::totalPoints(){
    return cantNodes;
}

int QuadTree::totalNodes(){
    return cantQuads;
}

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
                cantQuads++;
            }
            insert(node, quad->topLeftTree);
        }
        // Indicates botLeftTree
        else {
            if(quad->botLeftTree == nullptr){
                quad->botLeftTree = new Quad(Point(quad->topLeft.x, (quad->topLeft.y + quad->botRight.y) / 2), Point((quad->topLeft.x + quad->botRight.x) / 2, quad->botRight.y));
                cantQuads++;
            }
            insert(node, quad->botLeftTree);
        }
    }else{
        // Indicates topRightTree
        if ((quad->topLeft.y + quad->botRight.y)/2 > node->pos.y) {
            if(quad->topRightTree == nullptr){
                quad->topRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x) / 2, quad->topLeft.y), Point(quad->botRight.x, (quad->topLeft.y + quad->botRight.y) / 2));
                cantQuads++;
            }
            insert(node, quad->topRightTree);
        }
        // Indicates botRightTree
        else{
            if(quad->botRightTree == nullptr){
                quad->botRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x) / 2, (quad->topLeft.y + quad->botRight.y) / 2), Point(quad->botRight.x, quad->botRight.y));
                cantQuads++;
            }
            insert(node, quad->botRightTree);
        }
    }
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
}

queue<Node*>* QuadTree::list(){
    queue<Node*>* lista = new queue<Node*>();
    preOrder(Root, lista);
    return lista;
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

int QuadTree::countRegion(int x, int y, int d){
    return countRegion(Point(x, y), d);
}

int QuadTree::countRegion(Point point, int d){
    int countQuads = 0;
    queue<Quad*> cola;
    cola.push(Root);
    while (cola.empty() == false){
        Quad* quad = cola.front();
        cola.pop();
        if(interseccionRegiones(point, d, quad) == true){
            Node* auxnodo = quad->node;
            while (auxnodo != nullptr){
                countQuads++;
                auxnodo = auxnodo->next;
            }
        }
        if(quad->topLeftTree != nullptr){
            cola.push(quad->topLeftTree);
        }
        if(quad->topRightTree != nullptr){
            cola.push(quad->topRightTree);
        }
        if(quad->botLeftTree != nullptr){
            cola.push(quad->botLeftTree);
        }
        if(quad->botRightTree != nullptr){
            cola.push(quad->botRightTree);
        }
    }
    return countQuads;
}







/*
int QuadTree::countRegion(Point p, int d){
    int counter = 0;
    int xTL = p.x - d; int yTL = p.y - d;
    if(p.x - d < 0){
        p.x = 0;
    }
    if(p.y - d > 0){
        p.y = 0;
    }
    int xBR = p.x + d; int yBR = p.y + d;
    if(p.x + d > 360){
        p.x = 360;
    }
    if(p.y + d > 360){
        p.y = 360;
    }
    
    for(int i = xTL; i < xBR - xTL; ++i){
        for(int j = yTL; j < yBR - yTL; ++j){
            Node* aux = search(Root, Point(i,j));
            if(aux != nullptr){
                while(aux->next != nullptr){
                    counter = counter + aux->Population;
                    aux = aux->next;
                }
            };
        }
    }
    return counter;
}

int QuadTree::AggregateRegion(Point p, int d){
    int counter = 0;
    int xTL = p.x - d; int yTL = p.y - d;
    if(p.x - d < 0){
        p.x = 0;
    }
    if(p.y - d > 0){
        p.y = 0;
    }
    int xBR = p.x + d; int yBR = p.y + d;
    if(p.x + d > 360){
        p.x = 360;
    }
    if(p.y + d > 360){
        p.y = 360;
    }
    
    for(int i = xTL; i < xBR - xTL; ++i){
        for(int j = yTL; j < yBR - yTL; ++j){
            Node* aux = search(Root, Point(i,j));
            if(aux != nullptr){
                while(aux->next != nullptr){
                    counter = counter + aux->Population;
                    aux = aux->next;
                }
            };
        }
    }
    return counter;
}
*/