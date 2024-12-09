//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool existName(GroupList* x, string name){
    bool y = false;
    GroupNode* temp1 = x -> getHead();
    ShapeNode* temp2;
    while(temp1 != nullptr){

        if(temp1 -> getName() == name){
            y = true;
            break;
        }

        temp2 = temp1 -> getShapeList() -> getHead();

        while(temp2 != nullptr){
                    
            if(temp2 -> getShape() -> getName() == name){
                y = true;
                break;
            }

            temp2 = temp2 -> getNext();
        }

        if(y) break;
        temp1 = temp1 -> getNext();
    }

    return y;
}

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        command = "";
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        // command is shape
        if(command == "shape"){
            string name, type;
            int xloc, yloc, xsize, ysize;
            int check = 0;

            lineStream >> name;
            lineStream >> type;
            lineStream >> xloc;
            lineStream >> yloc;
            lineStream >> xsize;
            lineStream >> ysize;

            // invalid name error
            if(name == "shape" || name == "group" || name == "move" || name == "delete" || name == "draw" ||
               name == "pool" || name == "ellipse" || name == "rectangle" || name == "triangle"){
                cout << "error: invalid name" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // name exist error
            else if(existName(gList, name)){
                cout << "error: name " << name << " exists" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // no error
            else{
                ShapeNode* x = new ShapeNode;
                Shape* y = new Shape(name, type, xloc, yloc, xsize, ysize);
                x -> setShape(y);
                poolGroup -> getShapeList() -> insert(x);
                cout << name << ": " << type << " " << xloc << " " << yloc << " " << xsize << " " << ysize << endl;
            }
        }

        // command is group
        else if(command == "group"){
            string name;
            lineStream >> name;

            // invalid name error
            if(name == "shape" || name == "group" || name == "move" || name == "delete" || name == "draw" ||
               name == "pool" || name == "ellipse" || name == "rectangle" || name == "triangle"){
                cout << "error: invalid name" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // name exist error
            else if(existName(gList, name)){
                cout << "error: name " << name << " exists" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // no error
            else{
                GroupNode* x = new GroupNode(name);
                gList -> insert(x);
                cout << name << ": " << "group" << endl;
            }
        }

        // command is draw
        else if(command == "draw"){
            cout << "drawing:" << endl;
            gList -> print();
        }

        // command is move
        else if(command == "move"){
            string name1, name2;
            lineStream >> name1;
            lineStream >> name2;

            GroupNode* groupToBeMovedTo = nullptr;
            ShapeNode* shapeToBeMovedOut = nullptr;
            ShapeList* shapeListToBeMovedOut = nullptr;

            GroupNode* temp1 = gList -> getHead();
            ShapeNode* temp2;

            // invalid name error
            if(name1 == "shape" || name1 == "group" || name1 == "move" || name1 == "delete" || name1 == "draw" ||
               name1 == "pool" || name1 == "ellipse" || name1 == "rectangle" || name1 == "triangle"){
                cout << "error: invalid name" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // invalid name error
            if(name2 == "shape" || name2 == "group" || name2 == "move" || name2 == "delete" || name2 == "draw" ||
               name2 == "pool" || name2 == "ellipse" || name2 == "rectangle" || name2 == "triangle"){
                cout << "error: invalid name" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            while(temp1 != nullptr){

                    temp2 = temp1 -> getShapeList() -> getHead();

                    while(temp2 != nullptr){
                                
                        if(temp2 -> getShape() -> getName() == name1){
                            shapeToBeMovedOut = temp2;
                            shapeListToBeMovedOut = temp1 -> getShapeList();
                            break;
                        }

                        temp2 = temp2 -> getNext();
                    }

                    if(shapeToBeMovedOut != nullptr) break;
                    temp1 = temp1 -> getNext();
            }

            temp1 = gList -> getHead();

            while(temp1 != nullptr){

                if(temp1 -> getName() == name2){
                    groupToBeMovedTo = temp1;
                    break;
                }

                temp1 = temp1 -> getNext();
            }

            // shape name not found error
            if(shapeToBeMovedOut == nullptr){
                cout << "error: shape " << name1 << " not found" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // group name not found error
            else if(groupToBeMovedTo == nullptr){
                cout << "error: group " << name2 << " not found" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            // no error
            else{
                ShapeNode* x = shapeListToBeMovedOut -> remove(name1);
                groupToBeMovedTo -> getShapeList() -> insert(x);
                cout << "moved " << name1 << " to " << name2 << endl;
            }
        }

        // command is delete
        else if(command == "delete"){
            string name;
            lineStream >> name;

            GroupNode* temp1 = gList -> getHead();
            ShapeNode* temp2;
            ShapeNode* shapeToBeDeleted = nullptr;
            ShapeList* shapeListOfShapeToBeDeleted = nullptr;
            GroupNode* groupToBeDeleted = nullptr;

            // invalid name error
            if(name == "shape" || name == "group" || name == "move" || name == "delete" || name == "draw" ||
               name == "pool" || name == "ellipse" || name == "rectangle" || name == "triangle"){
                cout << "error: invalid name" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            while(temp1 != nullptr){

                    temp2 = temp1 -> getShapeList() -> getHead();

                    while(temp2 != nullptr){
                                
                        if(temp2 -> getShape() -> getName() == name){
                            shapeToBeDeleted = temp2;
                            shapeListOfShapeToBeDeleted = temp1 -> getShapeList();
                            break;
                        }

                        temp2 = temp2 -> getNext();
                    }

                    if(shapeToBeDeleted != nullptr) break;
                    temp1 = temp1 -> getNext();
            }

            temp1 = gList -> getHead();

            while(temp1 != nullptr){

                if(temp1 -> getName() == name){
                    groupToBeDeleted = temp1;
                    break;
                }

                temp1 = temp1 -> getNext();
            }

            // name not found error
            if(shapeToBeDeleted == nullptr && groupToBeDeleted == nullptr){
                cout << "error: shape " << name << " not found" << endl;
                cout << "> ";
                getline(cin, line);
                continue;
            }

            else if(shapeToBeDeleted != nullptr){
                ShapeNode* temp = shapeListOfShapeToBeDeleted -> getHead();

                if(shapeToBeDeleted == temp){
                    shapeListOfShapeToBeDeleted -> setHead(temp -> getNext());
                    delete temp;
                }

                else{
                    while(temp -> getNext() != shapeToBeDeleted) temp = temp -> getNext();
                    temp -> setNext(shapeToBeDeleted -> getNext());
                    delete shapeToBeDeleted;
                }

                cout << name << ": deleted" << endl;
            }

            else if(groupToBeDeleted != nullptr){
                ShapeNode* temp = poolGroup -> getShapeList() -> getHead();

                if(temp == nullptr) poolGroup -> getShapeList() -> setHead(groupToBeDeleted -> getShapeList() -> getHead());

                else{
                    while(temp -> getNext() != nullptr) temp = temp -> getNext();
                    temp -> setNext(groupToBeDeleted -> getShapeList() -> getHead());
                }


                GroupNode* temp2 = gList -> getHead();

                while(temp2 -> getNext() != groupToBeDeleted) temp2 = temp2 -> getNext();
                temp2 -> setNext(groupToBeDeleted -> getNext());
                groupToBeDeleted -> getShapeList() -> setHead(nullptr);
                delete groupToBeDeleted;

                cout << name << ": deleted" << endl;
            }
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.

    delete gList;
    gList = nullptr;
    
    return 0;
}