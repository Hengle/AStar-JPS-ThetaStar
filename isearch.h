#ifndef ISEARCH_H
#define ISEARCH_H
#include "list.h"
#include "map.h"
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <chrono>
#include "open.h"
class ISearch
{
    public:
        ISearch();
        virtual ~ISearch(void);

        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);
        Node findMin(int size);
        double MoveCost(int start_i, int start_j, int fin_i, int fin_j, const EnvironmentOptions &options);

    protected:
        virtual void addOpen(Node newNode) = 0; //каждый поиск по своему добавляет вершины в список OPEN
        virtual double computeHFromCellToCell(int start_i, int start_j, int fin_i, int fin_j, const EnvironmentOptions &options) = 0; //для Дейкстры и BFS этот метод всегда возвращает ноль
        virtual std::list<Node> findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options);//метод, который ищет соседей текущей вершины, удовлетворяющие параметрам поиска
        virtual void makePrimaryPath(Node curNode);//строит путь по ссылкам на родителя
        virtual void makeSecondaryPath(const Map &map, Node curNode);//разбивает найденный путь на секции, содержащие только прямые участки
        virtual Node resetParent(Node current, Node parent, const Map &map, const EnvironmentOptions &options) { return current;}//меняет родителя, нужен для алгоритма Theta*
        virtual bool stopCriterion();
        SearchResult    sresult; //результат поиска
        NodeList         lppath, hppath; //списки OPEN, CLOSE и путь
        Node lastnode;
        std::unordered_map<int,Node> close;
        NodeList *open;
        int     openSize;
        int     sizelimit; //ограничение на размер OPEN
        float   hweight; //вес эвристики
        int     breakingties; //критерий выбора очередной вершины из OPEN, когда F-значений равны

};
#endif
