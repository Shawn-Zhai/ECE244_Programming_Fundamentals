//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool checkTooManyArg(stringstream & x){
    string temp;
    bool y = false;

    if(char(x.peek()) != ' ' && char(x.peek()) != EOF){
        cout << "Error: invalid argument" << endl;
        y = true;
        return y;
    }

    x >> temp;

    if(!(x.fail() && x.eof())){
        cout << "Error: too many arguments" << endl;
        y = true;
        return y;
    }
    return y;
}

int trackDeleteArray[1000];

int main() {

    string line;
    string command;
    
    for(int i = 0; i < 1000; i++){
        trackDeleteArray[i] = -1;
    }

    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        if(lineStream.eof()){
            cout << "Error: invalid command" << endl;
            cout << "> ";
            getline(cin, line);
            continue;
        }
        
        command = "";
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        // If invalid command
        if(command != "maxShapes" && command != "create" && command != "move" && command != "rotate" && command != "draw" && command != "delete"){
            cout << "Error: invalid command" << endl;
            cout << "> ";
            getline(cin, line);
            continue;
        }

        // Valid command
        else{

            // Command is maxShapes
            if(command == "maxShapes"){
                
                int sizeOfDatabase;

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> sizeOfDatabase;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(checkTooManyArg(lineStream)){
                    cout << "> ";
                    getline(cin, line);
                    continue;  
                }

                // Delete previously allocated database
                for(int i = 0; i < max_shapes; i++){
                    if(trackDeleteArray[i] != -1){
                        delete shapesArray[i];
                        shapesArray[i] = NULL;
                        trackDeleteArray[i] = -1;
                    }
                }
                max_shapes = 0;
                shapeCount = 0;
                delete [] shapesArray;
                shapesArray = NULL;

                max_shapes = sizeOfDatabase;

                cout << "New database: max shapes is " << max_shapes << endl;
                shapesArray = new Shape*[max_shapes];
                for(int i = 0; i < max_shapes; i++){
                    shapesArray[i] = NULL;
                }
            }

            // Command is create
            else if(command == "create"){

                string n, t;
                int xloc, yloc, xsize, ysize;
                bool checkDuplicateName;

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> n;

                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(n == "all" || n == "maxShapes" || n == "create" || n == "move" || n == "rotate" || n == "draw" || n == "delete" ||
                   n == "circle" || n == "ellipse" || n == "rectangle" || n == "triangle"){
                    cout << "Error: invalid shape name" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue; 
                }

                checkDuplicateName = false;
                for(int i = 0; i < max_shapes; i++){
                    if(trackDeleteArray[i] != -1){
                        if(n == (*shapesArray[i]).getName()){
                            checkDuplicateName = true;
                            cout << "Error: shape " << (*shapesArray[i]).getName() << " exists" << endl;
                            cout << "> ";
                            getline(cin, line);
                            break; 
                        }
                    }
                }

                if(checkDuplicateName){
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> t;
                
                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }
                
                if(t != "circle" && t != "ellipse" && t != "rectangle" && t != "triangle"){
                    cout << "Error: invalid shape type" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> xloc;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(xloc < 0){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> yloc;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(yloc < 0){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> xsize;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(xsize < 0){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> ysize;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(ysize < 0){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(t == "circle" && xsize != ysize){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(checkTooManyArg(lineStream)){
                    cout << "> ";
                    getline(cin, line);
                    continue;  
                }

                shapeCount++;

                if(shapeCount > max_shapes){
                    cout << "Error: shape array is full" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                trackDeleteArray[shapeCount - 1] = shapeCount - 1;
                shapesArray[shapeCount - 1] = new Shape(n, t, xloc, xsize, yloc, ysize);

                cout << "Created " << (*shapesArray[shapeCount - 1]).getName() << ": " << (*shapesArray[shapeCount - 1]).getType() << " "
                     << (*shapesArray[shapeCount - 1]).getXlocation() << " " << (*shapesArray[shapeCount - 1]).getYlocation() << " "
                     << (*shapesArray[shapeCount - 1]).getXsize() << " " << (*shapesArray[shapeCount - 1]).getYsize() << endl;
            }

            // Command is move
            else if(command == "move"){

                string n;
                int xloc, yloc;
                bool checkNameFound;

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> n;

                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(n == "all" || n == "maxShapes" || n == "create" || n == "move" || n == "rotate" || n == "draw" || n == "delete" ||
                   n == "circle" || n == "ellipse" || n == "rectangle" || n == "triangle"){
                    cout << "Error: invalid shape name" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue; 
                }

                checkNameFound = false;
                int index;
                for(int i = 0; i < max_shapes; i++){
                    if(trackDeleteArray[i] != -1){
                        if(n == (*shapesArray[i]).getName()){
                            checkNameFound = true;
                            index = i;
                            break; 
                        }
                    }
                }

                if(!checkNameFound){
                    cout << "Error: shape " << n << " not found" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> xloc;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(xloc < 0){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> yloc;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(yloc < 0){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(checkTooManyArg(lineStream)){
                    cout << "> ";
                    getline(cin, line);
                    continue;  
                }

                (*shapesArray[index]).setXlocation(xloc);
                (*shapesArray[index]).setYlocation(yloc);

                cout << "Moved " << (*shapesArray[index]).getName() << " to "
                     << (*shapesArray[index]).getXlocation() << " " << (*shapesArray[index]).getYlocation() << endl;
            }

            // Command is rotate
            else if(command == "rotate"){
                string n;
                int angle;
                bool checkNameFound;

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> n;

                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(n == "all" || n == "maxShapes" || n == "create" || n == "move" || n == "rotate" || n == "draw" || n == "delete" ||
                   n == "circle" || n == "ellipse" || n == "rectangle" || n == "triangle"){
                    cout << "Error: invalid shape name" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue; 
                }

                checkNameFound = false;
                int index;
                for(int i = 0; i < max_shapes; i++){
                    if(trackDeleteArray[i] != -1){
                        if(n == (*shapesArray[i]).getName()){
                            checkNameFound = true;
                            index = i;
                            break; 
                        }
                    }
                }

                if(!checkNameFound){
                    cout << "Error: shape " << n << " not found" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> angle;

                if(lineStream.fail() || char(lineStream.peek()) == '.'){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(angle < 0 || angle > 360){
                    cout << "Error: invalid value" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue; 
                }

                if(checkTooManyArg(lineStream)){
                    cout << "> ";
                    getline(cin, line);
                    continue;  
                }

                (*shapesArray[index]).setRotate(angle);

                cout << "Rotated " << (*shapesArray[index]).getName() << " by " << angle << " degrees" << endl;
            }

            // Command is draw
            else if(command == "draw"){

                string argument;

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> argument;

                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(argument != "all"){
                    if(argument == "maxShapes" || argument == "create" || argument == "move" || argument == "rotate" || argument == "draw" || argument == "delete" ||
                       argument == "circle" || argument == "ellipse" || argument == "rectangle" || argument == "triangle"){
                        cout << "Error: invalid shape name" << endl;
                        cout << "> ";
                        getline(cin, line);
                        continue; 
                    }


                    bool checkNameFound = false;
                    int index;
                    for(int i = 0; i < max_shapes; i++){
                        if(trackDeleteArray[i] != -1){
                            if(argument == (*shapesArray[i]).getName()){
                                checkNameFound = true;
                                index = i;
                                break; 
                            }
                        }
                    }

                    if(!checkNameFound){
                        cout << "Error: shape " << argument << " not found" << endl;
                        cout << "> ";
                        getline(cin, line);
                        continue;
                    }

                    if(checkTooManyArg(lineStream)){
                        cout << "> ";
                        getline(cin, line);
                        continue;  
                    }

                    cout << "Drew " << (*shapesArray[index]).getName() << ": " << (*shapesArray[index]).getType() << " "
                         << (*shapesArray[index]).getXlocation() << " " << (*shapesArray[index]).getYlocation() << " "
                         << (*shapesArray[index]).getXsize() << " " << (*shapesArray[index]).getYsize() << endl;
                }

                else{

                    if(checkTooManyArg(lineStream)){
                        cout << "> ";
                        getline(cin, line);
                        continue;  
                    }

                    cout << "Drew all shapes" << endl;

                    for(int i = 0; i < max_shapes; i++){
                        if(trackDeleteArray[i] != -1){
                            cout << (*shapesArray[i]).getName() << ": " << (*shapesArray[i]).getType() << " "
                                 << (*shapesArray[i]).getXlocation() << " " << (*shapesArray[i]).getYlocation() << " "
                                 << (*shapesArray[i]).getXsize() << " " << (*shapesArray[i]).getYsize() << endl;
                        }
                    }
                }
            }

            // Command is delete
            else if(command == "delete"){

                string argument;

                if(lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    cout << "> ";
                    getline(cin, line);
                    continue;                    
                }

                lineStream >> argument;

                if(lineStream.fail()){
                    if(lineStream.eof()){
                        cout << "Error: too few arguments" << endl;
                    }
                    else{
                        cout << "Error: invalid argument" << endl;
                    }
                    cout << "> ";
                    getline(cin, line);
                    continue;
                }

                if(argument != "all"){
                    if(argument == "maxShapes" || argument == "create" || argument == "move" || argument == "rotate" || argument == "draw" || argument == "delete" ||
                       argument == "circle" || argument == "ellipse" || argument == "rectangle" || argument == "triangle"){
                        cout << "Error: invalid shape name" << endl;
                        cout << "> ";
                        getline(cin, line);
                        continue; 
                    }
                    
                    bool checkNameFound = false;
                    int index;
                    for(int i = 0; i < max_shapes; i++){
                        if(trackDeleteArray[i] != -1){
                            if(argument == (*shapesArray[i]).getName()){
                                checkNameFound = true;
                                index = i;
                                break; 
                            }
                        }
                    }

                    if(!checkNameFound){
                        cout << "Error: shape " << argument << " not found" << endl;
                        cout << "> ";
                        getline(cin, line);
                        continue;
                    }

                    if(checkTooManyArg(lineStream)){
                        cout << "> ";
                        getline(cin, line);
                        continue;  
                    }

                    cout << "Deleted shape " << (*shapesArray[index]).getName() << endl;
                    delete shapesArray[index];
                    shapesArray[index] = NULL;
                    trackDeleteArray[index] = -1;
                }

                else{

                    if(checkTooManyArg(lineStream)){
                        cout << "> ";
                        getline(cin, line);
                        continue;  
                    }

                    cout << "Deleted: all shapes" << endl;

                    for(int i = 0; i < max_shapes; i++){
                        if(trackDeleteArray[i] != -1){
                            delete shapesArray[i];
                            shapesArray[i] = NULL;
                            trackDeleteArray[i] = -1;
                        }
                    }

                    shapeCount = 0;
                }
            }

        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.

    for(int i = 0; i < max_shapes; i++){
        if(trackDeleteArray[i] != -1){
            delete shapesArray[i];
            shapesArray[i] = NULL;
            trackDeleteArray[i] = -1;
        }
    }

    delete [] shapesArray;
    shapesArray = NULL;
    
    return 0;
}