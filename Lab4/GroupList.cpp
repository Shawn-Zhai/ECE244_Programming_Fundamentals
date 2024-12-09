//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "GroupList.h"

GroupList::GroupList(){
    head = nullptr;
}

GroupList::~GroupList(){
    while(head != nullptr){
        GroupNode* temp = head;
        head = head -> getNext();
        delete temp;
    }
}

GroupNode* GroupList::getHead() const{
    return head;
}

void GroupList::setHead(GroupNode* ptr){
    head = ptr;
}

void GroupList::insert(GroupNode* s){
    if(head == nullptr){
        head = s;
        s -> setNext(nullptr);
    }
    else{
        GroupNode* temp = head;
        while(temp -> getNext() != nullptr) temp = temp -> getNext();
        temp -> setNext(s);
        s -> setNext(nullptr);
    }
}

GroupNode* GroupList::remove(string name){
    if(head == nullptr) return nullptr;
    GroupNode* temp = head;
    GroupNode* prev = nullptr;
    while(temp != nullptr){
        if(temp -> getName() == name) break;
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

void GroupList::print() const{
    GroupNode* temp = head;
    while(temp != nullptr){
        temp -> print();
        temp = temp -> getNext();
    }
}
