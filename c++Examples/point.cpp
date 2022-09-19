#include <iostream>
#include <cmath>
#include "point_v6.h"

using namespace std;

// constructor
Point::Point(float x, float y, float z) {
  itsX = x;
  itsY = y;
  itsZ = z;
}

// constructor
Point::Point() {
  itsX = 0;
  itsY = 0;
  itsZ = 0;
}

// destructor
Point::~Point() {
}

// set x coordinate
void Point::setX(float x) {
  itsX = x;
  return;
}

// set y coordinate
void Point::setY(float y) {
  itsY = y;
  return;
}

// set z coordinate
void Point::setZ(float z) {
  itsZ = z;
  return;
}

// get x coordinate
float Point::getX() {
  return itsX;
}

// get y coordinate
float Point::getY() {
  return itsY;
}

// get z coordinate
float Point::getZ() {
  return itsZ;
}

// calculate distance from origin
float Point::distance() {
  float distance = sqrt( pow(itsX,2) + pow(itsY,2) + pow(itsZ,2) );
  return distance;
}

// calculate distance from another point
float Point::distance(Point anotherPoint) {
  float difX = itsX - anotherPoint.itsX;
  float difY = itsY - anotherPoint.itsY;
  float difZ = itsZ - anotherPoint.itsZ;
  float distance = sqrt( pow(difX,2) + pow(difY,2) + pow(difZ,2) );
  return distance;
}

