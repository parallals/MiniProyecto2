#include "QuadTree.h"
 
/* Contructor de la clase QuadTree. */
QuadTree::QuadTree(int x1, int y1, int x2, int y2){
    Root = new Quad(Point(x1, y1), Point(x2, y2));
    cantQuads = 1;
    cantNodes = 0;
}

/* Destructor de la clase QuadTree. */
QuadTree::~QuadTree(){
    BorrarQuadTree(Root);
}

/* Funcion recursiva, realiza un recorrido DFS y libera la memoria del Quadtree. */
void QuadTree::BorrarQuadTree(Quad* quad){
    if(quad != nullptr){
        BorrarQuadTree(quad->topLeftTree);
        BorrarQuadTree(quad->topRightTree);
        BorrarQuadTree(quad->botLeftTree);
        BorrarQuadTree(quad->botRightTree);
        if(quad->nodo != nullptr){
            Node *auxnode = quad->nodo;
            while(auxnode != nullptr){
                Node *auxnext = auxnode->next;
                delete auxnode;
                auxnode = auxnext;
            }
            delete quad;
        }
    }
}

/* Funcion encargada de comprbar si un punto se encuentra fuera o dentro de una region. */
bool QuadTree::inBoundary(Point point, Point p1, Point p2){
    if((point.x >= p1.x) && (point.x <= p2.x) && (point.y <= p1.y) && (point.y >= p2.y)){ // Punto dentro del Quad.
        return true; 
    }
    return false; // Punto fuera del Quad.
}

/* Funcion encargada de comprobar si un Quad esta fuera, dentro o intersectando una region. */
bool QuadTree::interseccionRegiones(Point point, int d, Quad* quad){
    if((quad->botRight.x < point.x-d) || (quad->topLeft.x > point.x+d) || (quad->topLeft.y < point.y-d) || (quad->botRight.y > point.y+d)){
        return false; // Quad fuera de la region.
    }
    return true; // Quad dentro o intersectando la r11egion.
}

/* Funcion encargada de retornar la cantidad de Nodos totales en el QuadTree. */
int QuadTree::totalPoints(){
    return cantNodes;
}

/* Funcion encargada de retornar la cantidad de Quads totales en el QuadTree. */
int QuadTree::totalNodes(){
    return cantQuads;
}

/* Funciones overloading encargadas de llamar al insert() recursivo. */
void QuadTree::insert(float x, float y, string AccentCity, int Population){
    Node* nodo = new Node(x, y, AccentCity, Population);
    insert(nodo, Root);
}
void QuadTree::insert(Node* nodo){
    if(nodo == nullptr){
        return;
    }
    insert(nodo, Root);
}

/* Funcion recursiva encargada de realizar las inserciones en el QuadTree. */
void QuadTree::insert(Node* nodo, Quad* &quad){
    // El Nodo no corresponde al Quad actual.
    if(inBoundary(nodo->pos, quad->topLeft, quad->botRight) == false){
        return;
    }
    // El Quad es de tamaño unitario, no se subdividira mas y se realizara la insercion.
    if((abs(quad->topLeft.x - quad->botRight.x <= 1)) && (abs(quad->topLeft.y - quad->botRight.y <= 1))){
        if(quad->nodo == nullptr){ // En caso de que no haya un nodo en el Quad, insertar.
            quad->nodo = nodo;
        }else{ // En caso contrario, añadir al tope de la lista ligada.
            nodo->next = quad->nodo;
            quad->nodo = nodo;
        }
        ++cantNodes;
        return;
    }
    // El Quad sigue siendo lo suficientemente grande, seguiremos adentrandonos en sus cuadrantes.
    if((quad->topLeft.x + quad->botRight.x)/2 > nodo->pos.x){
        // Entraremos al cuarto cuadrante.
        if((quad->topLeft.y + quad->botRight.y)/2 > nodo->pos.y){
            if(quad->botLeftTree == nullptr){
                quad->botLeftTree = new Quad(Point(quad->topLeft.x, (quad->topLeft.y + quad->botRight.y)/2), Point((quad->topLeft.x + quad->botRight.x)/2, quad->botRight.y));
                cantQuads++;
            }
            insert(nodo, quad->botLeftTree);
        // Entraremos al primer cuadrante.
        }else{
            if(quad->topLeftTree == nullptr){
                quad->topLeftTree = new Quad(Point(quad->topLeft.x, quad->topLeft.y), Point((quad->topLeft.x + quad->botRight.x)/2, (quad->topLeft.y + quad->botRight.y)/2));
                cantQuads++;
            }
            insert(nodo, quad->topLeftTree);
        }
    }else{
        // Entraremos al tercer cuadrante.
        if((quad->topLeft.y + quad->botRight.y)/2 > nodo->pos.y){
            if(quad->botRightTree == nullptr){
                quad->botRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x)/2, (quad->topLeft.y + quad->botRight.y)/2), Point(quad->botRight.x, quad->botRight.y));
                cantQuads++;
            }
            insert(nodo, quad->botRightTree);
        // Entraremos al segundo cuadrante.
        }else{
            if(quad->topRightTree == nullptr){
                quad->topRightTree = new Quad(Point((quad->topLeft.x + quad->botRight.x)/2, quad->topLeft.y), Point(quad->botRight.x, (quad->topLeft.y + quad->botRight.y)/2));
                cantQuads++;
            }
            insert(nodo, quad->topRightTree);
        }
    }
}

/* Funcion encargada de retornar una lista con todos los elementos del Quadtree. */
/* Hace una llamada la funcion recursiva "preOrder" para hacer una queue.        */
queue<Node*>* QuadTree::list(){
    queue<Node*>* lista = new queue<Node*>();
    preOrder(Root, lista);
    return lista;
}

/* Funcion recursiva encargada de ingresar los elementos al queue. Realiza un recorrido preOrder. */
void QuadTree::preOrder(Quad* quad, queue<Node*>* &lista){
    if(quad != nullptr){
        Node* auxnode = quad->nodo;
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

/* Funcion overloading que llama a countRegion(Point point, int d). */
int QuadTree::countRegion(int x, int y, int d){
    return countRegion(Point(x, y), d);
}

/* Funcion iterativa que realiza un recorrido BFS y cuenta la cantidad de Nodos en una region. */
int QuadTree::countRegion(Point point, int d){
    d++;
    int countQuads = 0;
    queue<Quad*> cola;
    cola.push(Root);
    while (cola.empty() == false){
        Quad* quad = cola.front();
        cola.pop();
        if(interseccionRegiones(point, d, quad) == true){
            Node* auxnodo = quad->nodo;
            while (auxnodo != nullptr){
                if(inBoundary(auxnodo->pos, Point(point.x-d+1, point.y+d-1), Point(point.x+d-1, point.y-d+1)) == true){
                    countQuads++;
                }
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

/* Funcion overloading que llama a AggregateRegion(Point point, int d). */
long QuadTree::AggregateRegion(int x, int y, int d){
    return AggregateRegion(Point(x, y), d);
}

/* Funcion iterativa que realiza un recorrido BFS y suma la poblacion total de una region. */
long QuadTree::AggregateRegion(Point point, int d){
    d++;
    long countPopulation = 0;

    queue<Quad *> cola;
    cola.push(Root);
    while (cola.empty() == false){
        Quad *quad = cola.front();
        cola.pop();
        if(interseccionRegiones(point, d, quad) == true){
            Node *auxnodo = quad->nodo;
            while (auxnodo != nullptr){
                if(inBoundary(auxnodo->pos, Point(point.x - d + 1, point.y + d - 1), Point(point.x + d - 1, point.y - d + 1)) == true){
                    countPopulation == countPopulation + auxnodo->Population;
                }
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
    return countPopulation;
}

/* Funciones overloading encargadas de llamar al search() recursivo. */
Node* QuadTree::search(int x, int y){
    return search(Root, Point(x, y));
}
Node* QuadTree::search(Point point){
    return search(Root, point);
}

/* Funcion recursiva encargada de realizar la busqueda y retorno de un Nodo en el QuadTree. */
Node* QuadTree::search(Quad* quad, Point point){
	// El Nodo no corresponde al Quad actual.
	if(inBoundary(point, quad->topLeft, quad->botRight) == false){
		return nullptr;
    }
	// El Quad es de tamaño unitario, no se subdividira mas y retornara el nodo con su lista ligada.
	if(quad->nodo != nullptr){
		return quad->nodo;
    }
	if((quad->topLeft.x + quad->botRight.x) / 2 > point.x){
		// Entraremos al primer cuadrante.
		if((quad->topLeft.y + quad->botRight.y) / 2 > point.y){
			if(quad->topLeftTree == nullptr){
				return nullptr;
            }
			return search(quad->topLeftTree, point);
		// Entraremos al cuarto cuadrante.
		}else{
			if(quad->botLeftTree == nullptr){
				return nullptr;
            }
			return search(quad->botLeftTree, point);
		}
	}else{
		// Entraremos al segundo cuadrante.
		if((quad->topLeft.y + quad->botRight.y) / 2 > point.y){
			if(quad->topRightTree == nullptr){
				return nullptr;
            }
			return search(quad->topRightTree, point);
		// Entraremos al tercer cuadrante.
		}else{
			if(quad->botRightTree == nullptr){
				return nullptr;
            }
			return search(quad->botRightTree, point);
		}
	}
}

/* Funcion iterativa que dado una coordenada en valores flotantes, retorna una copia del Nodo mas cercano */
/* en la lista ligada de Nodos dada. Es recomendable usarla con el nodo retornado por search().           */
Node* QuadTree::searchInNodeList(float x, float y , Node* nodo){
    Node* minDistance = nodo;
    float dis1 = sqrt(pow(x - minDistance->x, 2) + pow(y - minDistance->y, 2));
    while (nodo->next != nullptr){
        float dis2 = sqrt(pow(x - nodo->next->x, 2) + pow(y - nodo->next->y, 2));
        if(dis2 < dis1){
            dis1 = dis2;
            minDistance = nodo->next;
        }
        nodo = nodo->next;
    }
    Node* copy = new Node(minDistance->x, minDistance->y, minDistance->AccentCity, minDistance->Population);
    return copy;
}

/* Funcion que llama a search() y a searchInNodeList()  para realizar la busqueda especifica de un nodo y retorna una copia. */
Node* QuadTree::searchSpecificNode(float x, float y){
    Node* nodo = search((int)x, (int)y);
    return searchInNodeList(x, y, nodo);
}