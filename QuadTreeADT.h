#ifndef QuadTreeADT_H
#define QuadTreeADT_H

#include "Node.h"
#include <queue>

class QuadTreeADT{
    public:
        virtual int totalPoints() = 0;      /* Retorna la cantidad de Nodos almacenados en el QuadTree. */

        virtual int totalNodes() = 0;       /* Retorna la cantidad de Quads en el QuadTree. */

        virtual void insert(float x, float y, std::string AccentCity, int Population) = 0;      /* Inserta un nuevo punto en el QuadTree, asociando a */ 
                                                                                                /* dicho punto a la información aportada.             */

        virtual std::queue<Node*>* list() = 0;      /* Retorna un queue con todos los Nodos almacenados en el QuadTree. */
                                                    /* Los datos salen segun un recorrido Preorder del QuadTree.        */

        virtual int countRegion(Point point, int d) = 0;     /* Retorna la cantidad de Nodos en una región del plano, */
                                                             /* tomando como centro el punto p y una distancia d.     */
                                                             
        virtual int AggregateRegion(Point p, int d) = 0;     /* Retorna la población estimada dentro de una región del  */
                                                             /* plano, tomando como centro el punto p y una distancia d.*/
};

#endif