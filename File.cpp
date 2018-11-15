//
// Created by Olya Mayorova on 15.11.2018.
//
#include <string>
using namespace std;

struct File {
    string name;
    int size;
    File(string name, int size){
        this->name=name;
        this->size=size;
    }
};
