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
    Person *p=NULL;
    try{
        p = family::Tree::search(this->root,name);
    }catch(exception e){cerr<<"two person with the same name"<<endl;}
    if (p){
        if (!p->getFather()){
            family::Person *f = new family::Person(father);
            p->setFather(f);
        }else throw runtime_error("ERROR: a father already exist");
    }else throw runtime_error("ERROR 404: person was not found.");
    return *this;
}

family::Tree& family::Tree::addMother(string name, string mother){
    Person *p=NULL;
    try{
        p = family::Tree::search(this->root,name);
    }catch(exception e){cerr<<"two person with the same name"<<endl;}
    if (p){
        if (!p->getMother()){
            family::Person *m = new family::Person(mother);
            p->setMother(m);
        }else throw runtime_error("ERROR: a mother already exist");
    }else throw runtime_error("ERROR 404: person was not found.");
    return *this;
}

string family::Tree::relation(string name){
    if (name==this->root->getName()) return "me";
    string relation;
    try{relation=family::Tree::gen(name,this->root,0);}catch(exception e){relation="unrelated";}
    return relation;
}

string family::Tree::find(string relation){
    if (!validRelation(relation)) {
        string err = "The tree cannot handle the '"+relation+"' relation";
        throw runtime_error(err);
    }
    return family::Person::find(this->root,relation);
}


void family::Tree::display(){

}
void family::Tree::remove(string name){
    if (name==this->root->getName()) throw runtime_error("cannot remove root");
    family::Person *child = family::Tree::findChild(this->root,name);
    if (!child) throw runtime_error("ERROR: this person does not exist in the tree");
    family::Person *parent;
    if (child->getMother() && child->getMother()->getName()==name) {
        parent = child->getMother();
        child->setMother(nullptr);
        delete(parent);
    }else if (child->getFather() && child->getFather()->getName()==name) {
        parent = child->getFather();
        child->setFather(nullptr);
        delete(parent);
    }else throw runtime_error("ERROR: didn't remove parent (unknown)");
}

string family::Tree::gen(string name, family::Person *p, int level){
    string ans;
    if (p->getMother()) if (p->getMother()->getName()==name) ans="mother";
    if (p->getFather()) if (p->getFather()->getName()==name) ans="father";
    if (ans.empty()){
        if (p->getMother()) try{ans=family::Tree::gen(name,p->getMother(),level+1);}catch(exception e){}
        if (p->getFather()) try{ans=family::Tree::gen(name,p->getFather(),level+1);}catch(exception e){}
        if (!ans.empty()) return ans;
        throw runtime_error("ERROR: wasn't found");
    }
    if (level>0) {ans="grand"+ans;level--;}
    while (level>0){
        ans = "great-"+ans;
        level--;
    }
    return ans; 
}

family::Person* family::Tree::search(family::Person *p, string name){
    if (name==p->getName()) return p;
    family::Person *rf=NULL,*rm=NULL,*f=NULL,*m=NULL;
    if (p->getMother()) m=p->getMother();
    if (p->getFather()) f=p->getFather();

    if (m) rm=search(m,name);
    if (f) rf=search(f,name);
    if(rm && rf) throw runtime_error("ERROR: tree can't have 2 persons with the same name.");
    if (rm) return rm;
    if (rf) return rf;
    return NULL;
}

family::Person* family::Tree::findChild(family::Person *p, string name){
    if (p->getMother()) if (p->getMother()->getName()==name) return p;
    if (p->getFather()) if (p->getFather()->getName()==name) return p;
    family::Person *temp;
    if (p->getMother()) {
        temp=family::Tree::findChild(p->getMother(),name);
        if (temp) return temp;
    }
    if (p->getFather()) {
        temp=family::Tree::findChild(p->getFather(),name);
        if (temp) return temp;
    }
    return NULL;
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
    if (family::isEqualIgnoreCase(relation,"mother")) if (p->getMother()) return p->getMother()->getName();
    if (family::isEqualIgnoreCase(relation,"father")) if (p->getFather()) return p->getFather()->getName();
    if (relation.length()==11) {
        relation=relation.substr(5);
    }else relation=relation.substr(6);
    string name;
    if (p->getMother()) try{name=family::Person::find(p->getMother(),relation);}catch(exception e){}
    if (p->getFather()) try{name=family::Person::find(p->getFather(),relation);}catch(exception e){}
    if (!name.empty()) return name;
    throw runtime_error("the related person was not found");
}


// *** namespace functions ***
bool family::isEqualIgnoreCase(string a, string b){
    size_t aLen = a.length();
    size_t bLen = b.length();
    if (aLen!=bLen) return false;
    for (size_t i=0;i<aLen;i++){
        char ac = a.at(i);
        char bc = b.at(i);
        if (ac>64 && ac<91) ac=tolower(ac);
        if (bc>64 && bc<91) bc=tolower(bc);
        if (ac!=bc) return false;
    }
    return true;
}

bool family::validRelation(string relation){
    if (family::isEqualIgnoreCase(relation,"me")) return true;
    string m="mother",f="father",g="grand",b="great-";
    string checkM=m,checkF=f; 
    int i = 0;
    while(checkF.length()<=relation.length() && checkM.length()<=relation.length()){
        if (family::isEqualIgnoreCase(relation,checkM)) return true;
        if (family::isEqualIgnoreCase(relation,checkF)) return true;
        if (i==0) {checkM=g+m;checkF=g+f;i++;}
        else{checkM=b+checkM;checkF=b+checkF;i++;}
    }
    return false;
}