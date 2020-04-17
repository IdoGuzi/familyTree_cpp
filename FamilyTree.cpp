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
    if (name==this->root->getName()) return "me";
    return family::Tree::gen(name,this->root,0);
}

string family::Tree::find(string relation){
    if (!validRelation(relation)) throw runtime_error("check your input");
    return family::Person::find(this->root,relation);
}


void family::Tree::display(){

}
void family::Tree::remove(string name){

}

string family::Tree::gen(string name, family::Person *p, int level){
    //string m="mother",f="father",g="grand",b="great-";
    string result;
    if (p->getMother()){
        if (p->getMother()->getName()==name) result="mother";
    }
    if (p->getFather()){
        if (p->getFather()->getName()==name) result="father";
    }
    if (!result.empty()){
        if (level>0) {result="grand"+result;level--;}
        while (level) {result="great-"+result;level--;}
        return result;
    }
    if (p->getMother()) return family::Tree::gen(name,p->getMother(),level+1);
    if (p->getFather()) return family::Tree::gen(name,p->getFather(),level+1);
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

string family::Person::find(family::Person *p, string relation){
    if (family::isEqualIgnoreCase(relation,"me")) return p->getName();
    if (family::isEqualIgnoreCase(relation,"mother")) return p->getMother()->getName();
    if (family::isEqualIgnoreCase(relation,"father")) return p->getFather()->getName();
    if (relation.length()==11){
        relation=relation.substr(5);
    }else relation=relation.substr(6);
    string a=nullptr,b=nullptr;
    if (p->getMother()){try{a=family::Person::find(p->getMother(),relation);}catch(exception e){}}
    if (p->getFather()){try{b=family::Person::find(p->getFather(),relation);}catch(exception e){}}
    
    if (!a.empty()) return a;
    if (!b.empty()) return b;
    throw runtime_error("Error: "+relation+" wasn't found in the family tree");
    return nullptr;
}


// *** namespace functions ***
bool family::isEqualIgnoreCase(string a, string b){
    size_t aLen = a.length();
    size_t bLen = b.length();
    if (aLen!=bLen) return false;
    for (size_t i=0;i<aLen;i++){
        char ac = a.at(i);
        char bc = b.at(i);
        if (ac>64 && ac<91) tolower(ac);
        if (bc>64 && bc<91) tolower(bc);
        if (ac!=bc) return false;
    }
    return true;
}

bool family::validRelation(string relation){
    if (family::isEqualIgnoreCase(relation,"me")) return true;
    string m="mother",f="father",g="grand",b="great-";
    string checkM=m,checkF=f; 
    while(checkF.length()<=relation.length() && checkM.length()<=relation.length){
        int i = 0;
        if (family::isEqualIgnoreCase(relation,checkM)) return true;
        if (family::isEqualIgnoreCase(relation,checkF)) return true;
        if (i==0) {checkM=g+m;checkF=g+f;i++;}
        else{checkM=b+checkM;checkF=b+checkF;i++;}
    }
    return false;
}