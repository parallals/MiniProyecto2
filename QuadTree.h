#include <cmath>
#include <queue>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

class QuadTree {

    private:
        struct Point {
            int x;
            int y;
            Point(int x, int y) {
                this->x = x;
                this->y = y;
            }
            ~Point();
        };
        struct Node {
            Point* pos;
            string AccentCity;
            string City;
            int Population;
            Node* next;
            Node(int x, int y, string AccentCity, string City, int Population){
                this->pos = new Point(x, y);
                this->AccentCity;
                this->City;
                this->Population;
                next = nullptr;
            }
            ~Node();
        };
        struct Quad {
            bool State; // false=blanco  true=negro 
            Node* node;
            Point* topLeft;
            Point* botRight;
            Quad* topLeftTree;
            Quad* topRightTree;
            Quad* botLeftTree;
            Quad* botRightTree;
            Quad(Point* topLeft, Point* botRight){
                this->topLeft = topLeft;
                this->botRight = botRight;
                State = false;
                node = nullptr;
                topLeft = nullptr;
                botRight = nullptr;
                topLeftTree = nullptr;
                topRightTree = nullptr;
                botLeftTree = nullptr;
                botRightTree = nullptr;
            }
            ~Quad();
        };
        Quad* Root;
        int cantQuads, cantNodes;
        bool inBoundary(Point* point, Quad* quad);
        void insert(Node* node, Quad* &quad);
        void inOrder(Quad* quad, std::queue<int> lista);

    public:
        int totalPoints();                      // Retorna la cantidad de puntos almacenados en el QuadTree.
        int totalNodes();                       // Retorna la cantidad de nodos, tanto blancos como negros, en el QuadTree.
        void insert(int x, int y, string AccentCity, string City, int Population);         // Inserta un nuevo punto p en el QuadTree, asociando a dicho punto la 
                                                                                           // información disponible en data (ej. la población de una ciudad con coordenadas p).
        std::queue<int> list();                 // Retorna un contenedor con todos los puntos almacenados en el QuadTree. Por cada punto retorna sus coordenadas y su valor 
                                                // asociado (ej. la población). Para esta función, queda a criterio de los estudiantes elegir un recorrido entre preorder, 
                                                // postorder o una variante de inorder. El tipo de retorno dependerá del tipo de contenedor que se utilice.
        int countRegion(Point p, int d);        // Retorna la cantidad de puntos en una región del plano, tomando como centro el punto p y una distancia d.
        int AggregateRegion(Point p, int d);    // Retorna la población estimada dentro de una región del plano, tomando como centro el punto p y una distancia d.
        QuadTree(int x1, int y1, int x2, int y2);                             // Contructor de QuadTree.
        ~QuadTree();                            // Destructor de QuadTree.         
};