//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.

#endif /* Triangle_h */


#include "Shape.h"

class Triangle : Shape {
private:
    float x1;                  // The radius of the circle
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;

public:
    // Constructor
    Triangle (string n, float x1, float y1, float x2, float y2, float x3, float y3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getx1() const;       // Returns the radius of the circle
    float gety1() const;
    float getx2() const;
    float gety2() const;
    float getx3() const;
    float gety3() const;

    // Mutator
    void setx1(float x11);       // Sets the radius of the circle
    void sety1(float y11);
    void setx2(float x22);
    void sety2(float y22);
    void setx3(float x33);
    void sety3(float y33);

    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
    virtual float computeArea() const;   // Computes the area of the circle
    
    virtual Shape* clone() const;  // Clones the object
};