//
// Created by Peter on 2/19/2016.
//
#include <iostream>

#include <cmath>
#include <sstream>
#include <stdlib.h>

#include "Point.h"

namespace Clustering {

    unsigned int Point::__idGen = 0;

    Point::Point(int dim) {
        __id = __idGen;
        __idGen++;
        __values = NULL;
        __values = new double[dim];
        __dim = dim;
        for (int i = 0; i < dim; i++) {
            __values[i] = 0;
        }
    }

    Point::Point(int dim, double *values) {
        __id = __idGen;
        __idGen++;
        __values = new double[dim];
        __dim = dim;
        for (int i = 0; i < dim; i++) {
            __values[i] = values[i];
        }
    }

    Point::Point(const Point &inPoint) {
        __id = inPoint.getId();
        __dim = inPoint.getDims();
        __values = new double[inPoint.getDims()];
        for (int i = 0; i < __dim; i++) {
            __values[i] = inPoint.getValue(i);
        }

    }

    Point &Point::operator=(const Point &inPoint) {
        __id = inPoint.getId();
        __dim = inPoint.getDims();
        __values = new double[inPoint.getDims()];
        for (int i = 0; i < __dim; i++) {
            __values[i] = inPoint.__values[i];
        }

        return *this;
    }

    Point::~Point() {
        delete[] __values;
    }

    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int index, double inValue) {
        __values[index] = inValue;
    }

    double Point::getValue(int index) const {
        return __values[index];
    }

    double Point::distanceTo(const Point &point2) const {
        double *distanceArray;
        double sum = 0;
        distanceArray = new double[__dim];

        for (int i = 0; i < __dim; i++) {
            double manhatanDistance = (point2.getValue(i) - __values[i]);
            distanceArray[i] = manhatanDistance * manhatanDistance;
        }
        for (int i = 0; i < __dim; i++) {
            sum += distanceArray[i];
        }

        return sqrt(sum);

    }

    Point &Point::operator*=(double multiplier) {
        for (int i = 0; i < __dim; i++) {
            __values[i] *= multiplier;
        }
        return *this;
    }

    Point &Point::operator/=(double divider) {
        for (int i = 0; i < __dim; i++) {
            __values[i] /= divider;
        }
        return *this;
    }

    const Point  Point::operator*(double multiplier) const {
        return Point(*this) *= multiplier;
    }

    const Point  Point::operator/(double divider) const {


        return Point(*this) /= divider;
    }

    double &Point::operator[](int index) {
        return __values[index];
    }

    Point &operator+=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs) {
            return lhs *= 2;
        } else if (lhs.__dim == rhs.__dim) {
            for (int i = 0; i < lhs.__dim; i++)
                lhs.__values[i] += rhs.__values[i];
        }
        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs) {
            return lhs *= 2;
        } else if (lhs.__dim == rhs.__dim) {
            for (int i = 0; i < lhs.__dim; i++)
                lhs.__values[i] -= rhs.__values[i];
        }
        return lhs;

    }

    const Point operator+(const Point &point1, const Point &point2) {
        Point sum(point1);

        return sum += point2;
    }

    const Point  operator-(const Point &point1, const Point &point2) {
        Point difference(point1);

        return difference -= point2;
    }

    bool operator==(const Point &lhs, const Point &rhs) {

        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {
                return false;
            }
        }


        return lhs.getId() == rhs.getId();

    }

    bool operator!=(const Point &lhs, const Point &rhs) {


        return !(lhs == rhs);

    }

    bool operator<(const Point &lhs, const Point &rhs) {

        for (int i = 0; i < rhs.__dim; i++) {
            if (lhs.__values[i] < rhs.__values[i]) {

                return true;
            }
            if (lhs.__values[i] > rhs.__values[i]) {

                return false;
            }

        }
        return false;


    }

    bool operator>(const Point &lhs, const Point &rhs) {

        bool areEqual = true;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {

                areEqual = false;
            }

        }

        return !(lhs < rhs) & !areEqual;


    }


    bool operator<=(const Point &lhs, const Point &rhs) {
        bool areEqual = true;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {

                areEqual = false;
            }

        }
        return lhs < rhs | areEqual;
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        bool areEqual = true;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {
                areEqual = false;
            }

        }
        return lhs > rhs | areEqual;
    }

    std::ostream &operator<<(std::ostream &outStream, const Point &inPoint) {
        double value = 0;
        for (int i = 0; i < inPoint.__dim; i++) {
            outStream << inPoint.getValue(i);
            if (i < inPoint.__dim - 1) {
                outStream << ',';
            }


        }
        return outStream;
    }

    std::istream &operator>>(std::istream &inStream, Point &outPoint) {
        std::string line;
        std::getline(inStream, line);//we read the current stream and get a string out of it.
        double value = 0;

        int count = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                line[i] = ' ';//We replace all comas with whitespaces so that the
                // stringstream >> operator down the line can easily read it. I know its a strange method but it works.
                count++;//The total number of dimensions is the total number of comas +1 so we count all the comas.
            }
        }
        count++;//then we add one.
        outPoint = Point(count);
        std::istringstream iss(line);
        for (int i = 0; i < count; i++) {
            iss >> value;
            outPoint.__values[i] = value;
        }
    }


}