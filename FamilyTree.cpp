#include <iostream>
#include "FamilyTree.hpp"
using namespace std;

//*** family tree ***

family::Tree::Tree(string name){
    this->root = new Person(name);
}

family::Tree::~Tree(){
    delete(root);

}

family::Tree& family::Tree::addFather(string name, string father){
    return *this;
}

family::Tree& family::Tree::addMother(string name, string mother){
    return *this;
}

string family::Tree::relation(string name){
    return name;
}
string family::Tree::find(string relation){
    return relation;
}
void family::Tree::display(){

}
void family::Tree::remove(string name){

}



//*** person node ***
family::Person::Person(string name){
    this->name=name;
    this->father=NULL;
    this->mother=NULL;
}

family::Person::~Person(){
    if (father) {delete(father);}
    if (mother) {delete(mother);}
}
