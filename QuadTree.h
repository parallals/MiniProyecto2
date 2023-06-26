#ifndef QuadTree_H
#define QuadTree_H

#include "Node.h"

#include <cmath>
#include <queue>
#include <iostream>
#include <queue>

using namespace std;

class QuadTree{

    private:
        struct Quad {
            bool State; // false=blanco  true=negro 
            Node* node;
            Point topLeft;
            Point botRight;
            Quad* topLeftTree;
            Quad* topRightTree;
            Quad* botLeftTree;
            Quad* botRightTree;
            Quad(Point topLeft, Point botRight){
                this->topLeft = topLeft;
                this->botRight = botRight;
                State = false;
                node = nullptr;
                topLeftTree = nullptr;
                topRightTree = nullptr;
                botLeftTree = nullptr;
                botRightTree = nullptr;
            }
        };
        Quad* Root;
        int cantQuads;
        int cantNodes;
        bool inBoundary(Point point, Quad* quad);
        bool interseccionRegiones(Point point, int d, Quad* quad);
        void preOrder(Quad* quad, queue<Node*>* &lista);
        void insert(Node* node, Quad* &quad);
        Node* search(Quad* quad, Point p);
        void BorrarQuadTree(Quad* quad);
        void nodeListRegion(Point TL, Point BR, Quad *Root, queue<Node *> *&lista);

    public:
        int totalPoints();    /* Retorna la cantidad de puntos almacenados en el QuadTree. */
        int totalNodes();    /* Retorna la cantidad de nodos, tanto blancos como negros, en el QuadTree. */
        void insert(float x, float y, string AccentCity, int Population);    /* Inserta un nuevo punto p en el QuadTree, asociando a dicho punto la                */
        void insert(Node* node);                                         /* información disponible en data (ej. la población de una ciudad con coordenadas p). */
        Node* search(int x, int y);
        Node* search(Point point);
        Node* searchInNodeList(float x, float y , Node* node);
        queue<Node*>* list();  // Retorna un contenedor con todos los puntos almacenados en el QuadTree. Por cada punto retorna sus coordenadas y su valor 
                                                // asociado (ej. la población). Para esta función, queda a criterio de los estudiantes elegir un recorrido entre preorder, 
                                                // postorder o una variante de inorder. El tipo de retorno dependerá del tipo de contenedor que se utilice.
        int countRegion(Point point, int d);        // Retorna la cantidad de puntos en una región del plano, tomando como centro el punto p y una distancia d.
        int countRegion(int x, int y, int d);
        int AggregateRegion(Point p, int d);    // Retorna la población estimada dentro de una región del plano, tomando como centro el punto p y una distancia d.
        int AggregateRegion(int x, int y, int d);
        QuadTree(int x1, int y1, int x2, int y2);                             // Contructor de QuadTree.
        ~QuadTree();                            // Destructor de QuadTree.     
};

#endif