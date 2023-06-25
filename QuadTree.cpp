#include "QuadTree.h"
 
 
QuadTree::QuadTree(float x1, float y1, float x2, float y2){
    Root = new Quad(Point(x1, y1), Point(x2, y2));
    cantQuads = 1;
    cantNodes = 0;
}

QuadTree::~QuadTree(){
    BorrarQuadTree(Root);
}

void QuadTree::BorrarQuadTree(Quad* quad) {
    if (quad != nullptr) {
        BorrarQuadTree(quad->topLeftTree);
        BorrarQuadTree(quad->topRightTree);
        BorrarQuadTree(quad->botLeftTree);
        BorrarQuadTree(quad->botRightTree);
        Node* auxnode = quad->node;
        Node* auxnext = auxnode->next;
        while (auxnode != nullptr) {
            delete auxnode;
            auxnode = auxnext;
        }
        delete quad;
    }
}

// Check if current quadtree contains the point
bool QuadTree::inBoundary(Point point, Quad* quad){
    if((point.x >= quad->topLeft.x) && (point.x <= quad->botRight.x) && (point.y >= quad->topLeft.y) && (point.y <= quad->botRight.y)){
        return true; // Punto dentro del Quad.
    }
    return false; // Punto fuera del Quad.
}

bool QuadTree::interseccionRegiones(Point point, float d, Quad* quad) {
    if((quad->botRight.x < point.x - d) || (quad->topLeft.x > point.x + d) || (quad->botRight.y < point.y - d) || (quad->topLeft.y > point.y + d)){
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

void QuadTree::insert(float x, float y, string AccentCity, int Population){
    Node* node = new Node(x, y, AccentCity, Population);
    insert(node, Root);
}

void QuadTree::insert(Node* node){
    insert(node, Root);
}

void QuadTree::insert(Node* node, Quad* quad){
    if(node == NULL){
        return;
    }   
    // Current quad cannot contain it
    if(inBoundary(node->pos, quad) == true){
        delete node;
        return;
    }
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if((abs(quad->topLeft.x - quad->botRight.x) <= 0.001) && (abs(quad->topLeft.y - quad->botRight.y) <= 0.001)) {
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
                quad->topLeftTree = new Quad(Point(quad->topLeft.x, quad->topLeft.y), Point((quad->topLeft.x + quad->botRight.x)/2, (quad->topLeft.y + quad->botRight.y)/2));
                cantQuads++;
            }
            insert(node, quad->topLeftTree);
        }
        // Indicates botLeftTree
        else {
            if(quad->botLeftTree == nullptr){
                quad->botLeftTree = new Quad(Point(quad->topLeft.x, (quad->topLeft.y + quad->botRight.y)/2), Point((quad->topLeft.x + quad->botRight.x)/2, quad->botRight.y));
                cantQuads++;
            }
            insert(node, quad->botLeftTree);
        }
    }else{
        // Indicates topRightTree
        if ((quad->topLeft.y + quad->botRight.y)/2 > node->pos.y) {
            if(quad->topRightTree == nullptr){
                quad->topRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x)/2, quad->topLeft.y), Point(quad->botRight.x, (quad->topLeft.y + quad->botRight.y)/2));
                cantQuads++;
            }
            insert(node, quad->topRightTree);
        }
        // Indicates botRightTree
        else{
            if(quad->botRightTree == nullptr){
                quad->botRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x)/2, (quad->topLeft.y + quad->botRight.y)/2), Point(quad->botRight.x, quad->botRight.y));
                cantQuads++;
            }
            insert(node, quad->botRightTree);
        }
    }
}

Node* QuadTree::search(float x, float y){
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
        Node* auxnodo = quad->node;
        while(auxnodo != nullptr){
            lista->push(auxnodo);
            auxnodo = auxnodo->next;
        }
        preOrder(quad->topLeftTree, lista);
        preOrder(quad->topRightTree, lista);
        preOrder(quad->botLeftTree, lista);
        preOrder(quad->botRightTree, lista);
    }
}

int QuadTree::countRegion(float x, float y, float d){
    return countRegion(Point(x, y), d);
}

int QuadTree::countRegion(Point point, float d){
    int countQuads = 0;
    queue<Quad*> cola;
    cola.push(Root);
    while (cola.empty() == false){
        Quad* quad = cola.front();
        cola.pop();
        if(interseccionRegiones(point, d, quad) == true){
            cout << quad->topLeft.x << " | " <<  quad->topLeft.y << " | " <<  quad->botRight.x << " | " <<  quad->botRight.y <<endl;
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
int QuadTree::countRegion(Point p, int d) {

    int count = 0;
    queue<Node *> *list = new queue<Node *>;
    Point TL = Point(p.x - d, p.y + d);
    Point BR = Point(p.x + d, p.y - d);

    nodeListRegion(TL, BR, Root,list); //Retorna una lista con los nodos de la región

    while (!list->empty()) {
        count++;
        list->pop();
    }
    return count;
}

int QuadTree::AggregateRegion(Point p, int d) {

        int count = 0;
        queue<Node *> *list = new queue<Node *>;
        Point TL = Point(p.x - d, p.y + d);
        Point BR = Point(p.x + d, p.y - d);

        nodeListRegion(TL, BR, Root,list);

        while (!list->empty()) {
            count = count + list->front()->Population;
            list->pop();
        }
        return count;
}

void QuadTree::nodeListRegion(Point TL1, Point BR1, Quad* Root, queue<Node*>*& list) {
    Point TL2 = Point(TL1.x, TL1.y); // punto auxiliar para no perder el valor de TL1
    Point BR2 = Point(BR1.x, BR1.y); // punto auxiliar para no perder el valor de BR1

    if (Root != nullptr) {
        if (Root->node != nullptr) {
            // Cuando llegue a un nodo hoja, se añaden los nodos a la lista si están dentro de la región dada
            Node* auxnode = Root->node;
            while (auxnode != nullptr) {
                if (auxnode->pos.x >= TL1.x && auxnode->pos.x <= BR1.x && auxnode->pos.y >= TL1.y && auxnode->pos.y <= BR1.y) {
                    list->push(auxnode);
                }
                auxnode = auxnode->next;
            }
        } else {
            // Cuando no es un nodo hoja, se llama recursivamente a los 4 hijos, comprobando si la región de cada hijo se intersecta con la región dada

            // topLeftTree
            if ((Root->topLeft.x + Root->botRight.x) / 2 > TL1.x && (Root->topLeft.y + Root->botRight.y) / 2 > TL1.y) {
                if (Root->topLeftTree != nullptr) {
                    if (Root->botRight.x < BR1.x) BR2.x = Root->botRight.x; // Se actualiza la región
                    if (Root->botRight.y < BR1.y) BR2.y = Root->botRight.y; // Se actualiza la región
                    nodeListRegion(TL2, BR2, Root->topLeftTree, list);
                }
            }

            // botLeftTree
            if ((Root->topLeft.x + Root->botRight.x) / 2 > TL1.x && (Root->topLeft.y + Root->botRight.y) / 2 <= BR1.y) {
                if (Root->botLeftTree != nullptr) {
                    if (Root->botRight.x < BR1.x) BR2.x = Root->botRight.x; // Se actualiza la región
                    if (Root->topLeft.y > TL1.y) TL2.y = Root->topLeft.y; // Se actualiza la región
                    nodeListRegion(TL2, BR2, Root->botLeftTree, list);
                }
            }

            // topRightTree
            if ((Root->topLeft.x + Root->botRight.x) / 2 <= BR1.x && (Root->topLeft.y + Root->botRight.y) / 2 > TL1.y) {
                if (Root->topRightTree != nullptr) {
                    if (Root->topLeft.x > TL1.x) TL2.x = Root->topLeft.x; // Se actualiza la región
                    if (Root->botRight.y < BR1.y) BR2.y = Root->botRight.y; // Se actualiza la región
                    nodeListRegion(TL2, BR2, Root->topRightTree, list);
                }
            }

            // botRightTree
            if ((Root->topLeft.x + Root->botRight.x) / 2 <= BR1.x && (Root->topLeft.y + Root->botRight.y) / 2 <= BR1.y) {
                if (Root->botRightTree != nullptr) {
                    if (Root->topLeft.x > TL1.x) TL2.x = Root->topLeft.x; // Se actualiza la región
                    if (Root->topLeft.y > TL1.y) TL2.y = Root->topLeft.y; // Se actualiza la región
                    nodeListRegion(TL2, BR2, Root->botRightTree, list);
                }
            }
        }
    }
}

//Aquí termina


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