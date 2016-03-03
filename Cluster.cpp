//
// Created by Peter on 2/19/2016.
//
//Cluster implementation
#include <sstream>
#include <iostream>
#include <fstream>
#include "Cluster.h"

using std::cout;
using std::endl;
namespace Clustering {
    typedef struct LNode *LNodePtr;

    LNode::LNode(const Point &p, LNodePtr n) : point(1) {
        point = p;

        next = n;
    }

    Cluster::Cluster() {
        __size = 0;
        __points = NULL;
    }

    void Cluster::__del() {

        while (__size > 0) {
            LNodePtr cursor = __points;
            for (int i = 0; i < __size; ++i) {
                cursor = cursor->next;
            }
            __size--;
            delete cursor;
        }
        __points = NULL;
    }

    void insertAtFront(LNodePtr &headPtr, const Point &p) {

        LNodePtr insertPtr = NULL;
        insertPtr = new LNode(p, headPtr);

        headPtr = insertPtr;
    }


    void insertAfterNode(LNodePtr previous_ptr, const Point &p) {
        LNodePtr insertPtr = NULL;
        LNodePtr nextPtr = NULL;
        nextPtr = previous_ptr->next;

        insertPtr = new LNode(p, nextPtr);

        previous_ptr->next = insertPtr;
    }

    void Cluster::__cpy(LNodePtr pts) {
        __del();
        LNodePtr cursor = pts;
        while (cursor != NULL) {
            add(cursor->point);
            cursor = cursor->next;
        }


    }

    bool Cluster::__in(const Point &p) const {
        LNodePtr cursor = __points;
        for (int i = 0; i < __size; i++) {
            if (cursor->point == p) {
                return true;
            }
            cursor = cursor->next;
        }
        return false;
    }

    Cluster::Cluster(const Cluster &c) {
        __size = 0;
        __points = NULL;
        __cpy(c.__points);

    }

    Cluster &Cluster::operator=(const Cluster &c) {

        __cpy(c.__points);
        __size = c.__size;
        return *this;
    }

    Cluster::~Cluster() {

        __del();
    }


    int Cluster::getSize() const {
        return __size;
    }


    void Cluster::add(const Point &p) {


        if (!__size || p < __points->point) {

            insertAtFront(__points, p);
        }
        else {
            LNodePtr cursor = __points;
            while (p <= cursor->point) {
                if (cursor->next == NULL) {
                    break;
                }
                cursor = cursor->next;
            }

            insertAfterNode(cursor, p);
        }
        __size++;


    }

    const Point &Cluster::remove(const Point &p) {
        if (__in(p)) {
            LNodePtr previous = __points;
            if (previous->point == p) {
                LNodePtr newHead = __points->next;
                LNodePtr oldHead = __points;
                __points = newHead;
                delete oldHead;

            }
            else {
                while (previous->next != NULL && previous->next->point != p) {
                    previous = previous->next;
                }

                LNodePtr pointToBeDeleted = NULL;
                LNodePtr pointToBeAssigned = NULL;

                pointToBeDeleted = previous->next;
                pointToBeAssigned = pointToBeDeleted->next;
                previous->next = pointToBeAssigned;

                delete pointToBeDeleted;
            }
            __size--;
            return p;


        }
    }

    bool Cluster::contains(const Point &p) {
        return __in(p);
    }

    const Point &Cluster::operator[](unsigned int index) const {
        LNodePtr cursor = __points;
        for (int i = 0; i < index; ++i) {
            cursor = cursor->next;
        }

        return cursor->point;
    }


    Cluster &Cluster::operator+=(const Point &p) {
        if (!__in(p)) {
            add(p);
        }

    }

    Cluster &Cluster::operator-=(const Point &p) {
        if (__in(p)) {
            remove(p);
        }

    }

    Cluster &Cluster::operator+=(const Cluster &c) {
        for (int i = 0; i < c.__size; i++) {
            Point curPoint(c[i]);
            if (!__in(curPoint)) {
                add(curPoint);
            }
        }
    }

    Cluster &Cluster::operator-=(const Cluster &c) {
        for (int i = 0; i < c.__size; i++) {
            Point curPoint(c[i]);
            if (__in(curPoint)) {
                remove(curPoint);
            }
        }
    }

    std::ostream &operator<<(std::ostream &outStream, const Cluster &c) {
        LNodePtr cursor;
        cursor = c.__points;
        while (cursor != NULL) {
            Point curPoint = cursor->point;
            outStream << curPoint << std::endl;

            cursor = cursor->next;


        }
        return outStream;
    }

    std::istream &operator>>(std::istream &inStream, Cluster &c) {
        Cluster newCluster;
        std::string line;
        while (getline(inStream, line)) {
            std::istringstream iss(line);

            Point curLine(1);
            iss >> curLine;
            newCluster += curLine;
            c = newCluster;

        }
    }


    bool operator==(const Cluster &rhs, const Cluster &lhs) {
        if (rhs.getSize() != lhs.getSize()) {
            return 0;
        }

        LNodePtr cursorR = rhs.__points;
        LNodePtr cursorL = lhs.__points;
        for (int i = 0; i < rhs.getSize(); ++i) {
            if ((cursorR->point) != (cursorL->point)) {
                return false;

            }
            cursorR = cursorR->next;
            cursorL = cursorL->next;
        }
        return true;

    }

    bool operator!=(const Cluster &rhs, const Cluster &lhs) {
        return !(rhs == lhs);
    }


    const Cluster operator+(const Cluster &c, const Point &p) {
        Cluster sum(c);
        sum += p;
        return sum;
    }

    const Cluster operator-(const Cluster &c, const Point &p) {
        Cluster difference(c);
        difference -= p;
        return difference;
    }

    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &rhs, const Cluster &lhs) {
        Cluster sum;
        sum += rhs;
        sum += lhs;
        return sum;
    }

    const Cluster operator-(const Cluster &rhs, const Cluster &lhs) {
        Cluster difference(rhs);

        difference -= lhs;
        return difference;

    }


}