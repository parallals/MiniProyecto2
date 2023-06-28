#ifndef QuadTree_H
#define QuadTree_H

#include "QuadTreeADT.h"

#include <cmath>

using namespace std;

class QuadTree: public QuadTreeADT{

    private:
        struct Quad {
            Node* nodo;
            Point topLeft;
            Point botRight;
            Quad* topLeftTree;
            Quad* topRightTree;
            Quad* botLeftTree;
            Quad* botRightTree;
            Quad(Point topLeft, Point botRight){
                this->topLeft = topLeft;
                this->botRight = botRight;
                nodo = nullptr;
                topLeftTree = nullptr;
                topRightTree = nullptr;
                botLeftTree = nullptr;
                botRightTree = nullptr;
            }
            ~Quad(){
                nodo = nullptr;
                topLeftTree = nullptr;
                topRightTree = nullptr;
                botLeftTree = nullptr;
                botRightTree = nullptr;
            }
        };
        Quad* Root;
        int cantQuads;
        int cantNodes;
        void BorrarQuadTree(Quad* quad);
        bool inBoundary(Point point, Point p1, Point p2);
        bool interseccionRegiones(Point point, int d, Quad* quad);
        void insert(Node* nodo, Quad* &quad);
        Node* search(Quad* quad, Point p);
        void preOrder(Quad* quad, queue<Node*>* &lista);

    public:
        int totalPoints();    /* Retorna la cantidad de Nodos almacenados en el QuadTree. */

        int totalNodes();     /* Retorna la cantidad de Quads en el QuadTree. */

        void insert(float x, float y, string AccentCity, int Population);   /* Inserta un nuevo punto en el QuadTree, asociando a */ 
        void insert(Node* nodo);                                            /* dicho punto a la información aportada.             */
        
        queue<Node*>* list();   /* Retorna un queue con todos los Nodos almacenados en el QuadTree. */
                                /* Los datos salen segun un recorrido Preorder del QuadTree.        */

        int countRegion(Point point, int d);     /* Retorna la cantidad de Nodos en una región del plano, */
        int countRegion(int x, int y, int d);    /* tomando como centro el punto p y una distancia d.     */

        long AggregateRegion(Point p, int d);        /* Retorna la población estimada dentro de una región del  */
        long AggregateRegion(int x, int y, int d);   /* plano, tomando como centro el punto p y una distancia d.*/

        Node* search(int x, int y);    /* Realiza la busqueda y retorno de un Nodo en el QuadTree. */
        Node* search(Point point);

        Node* searchInNodeList(float x, float y , Node* nodo);  /* Dado una coordenada en valores flotantes, retorna una copia del Nodo mas cercano en la */
                                                                /* lista ligada de Nodos dada. Es recomendable usarla con el nodo retornado por search(). */

        Node* searchSpecificNode(float x, float y);  /* Funcion que realiza la busqueda especifica de un nodo y entrega una copia. */

        QuadTree(int x1, int y1, int x2, int y2);   // Contructor de QuadTree.

        ~QuadTree();                                // Destructor de QuadTree.     
};

#endif