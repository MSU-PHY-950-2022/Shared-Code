#ifndef POINT_H
#define POINT_H

// declare point class
class Point {
public:
  Point(float x, float y, float z);
  Point();
  ~Point();
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  float getX();
  float getY();
  float getZ();
  float distance();
  float distance(Point anotherPoint);
private:
  float itsX;
  float itsY;
  float itsZ;
};
#endif
