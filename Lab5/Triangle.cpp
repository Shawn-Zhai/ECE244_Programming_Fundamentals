//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build a Circle object
Triangle::Triangle(string n, float x11, float y11, float x22, float y22, float x33, float y33):Shape(n, (x1+x2+x3)/3, (y1+y2+y3)/3){
    x1 = x11;
    y1 = y11;
    x2 = x22;
    y2 = y22;
    x3 = x33;
    y3 = y33;
}

Triangle::~Triangle() {
    // Nothing to do
}

// Accessor
float Triangle::getx1() const {
    return x1;
}

float Triangle::gety1() const {
    return y1;
}

float Triangle::getx2() const {
    return x2;
}

float Triangle::gety2() const {
    return y2;
}

float Triangle::getx3() const {
    return x3;
}

float Triangle::gety3() const {
    return y3;
}

// Mutator
void Triangle::setx1(float x11) {
    x1 = x11;
}

void Triangle::sety1(float y11) {
    y1 = y11;
}

void Triangle::setx2(float x22) {
    x2 = x22;
}

void Triangle::sety2(float y22) {
    y2 = y22;
}

void Triangle::setx3(float x33) {
    x3 = x33;
}

void Triangle::sety3(float y33) {
    y3 = y33;
}

void Triangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "Triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << computeArea()
         << endl;
}

float Triangle::computeArea() const {
    float area;
    area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
    if(area < 0) area = -area;
    return area;
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}