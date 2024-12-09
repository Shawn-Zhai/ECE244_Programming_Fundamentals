//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "ShapeList.h"

ShapeList::ShapeList(){
    head = nullptr;
}

ShapeList::~ShapeList(){
    while(head != nullptr){
        ShapeNode* temp = head;
        head = head->getNext();
        delete temp;
    }
}

ShapeNode* ShapeList::getHead() const{
    return head;
}

void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
}

ShapeNode* ShapeList::find(string name) const{
    ShapeNode* temp = head;
    while(temp != nullptr){
        if(temp -> getShape() -> getName() == name) break;
        temp = temp -> getNext();
    }
    return temp;
}

void ShapeList::insert(ShapeNode* s){
    if(head == nullptr){
        head = s;
        s -> setNext(nullptr);
    }
    else{
        ShapeNode* temp = head;
        while(temp -> getNext() != nullptr) temp = temp -> getNext();
        temp -> setNext(s);
        s -> setNext(nullptr);
    }
}

ShapeNode* ShapeList::remove(string name){
    if(head == nullptr) return nullptr;
    ShapeNode* temp = head;
    ShapeNode* prev = nullptr;
    while(temp != nullptr){
        if(temp -> getShape() -> getName() == name) break;
        prev = temp;
        temp = temp -> getNext();
    }
    if(temp == nullptr) return nullptr;
    if(temp == head){
        head = head -> getNext();
        return temp;
    }
    prev -> setNext(temp -> getNext());
    return temp;
}

void ShapeList::print() const{
    ShapeNode* temp = head;
    while(temp != nullptr){
        temp -> print();
        temp = temp -> getNext();
    }
}