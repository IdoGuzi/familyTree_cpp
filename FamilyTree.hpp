#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace family{
    class Person{
      private:
        string name;
        Person *father, *mother;
      public:
        Person(string name);
        ~Person();

        string getName(){return this->name;}

        Person* getFather(){return this->father;}
        void setFather(Person *father){this->father=father;}

        Person* getMother(){return this->mother;}
        void setMother(Person *mother){this->mother=mother;}
    };

    class Tree{
      private:
        Person *root;
      public:
        Tree(string name);
        ~Tree();


        Tree& addFather(string name, string father);
        Tree& addMother(string name, string mother);
        string relation(string name);
        string find(string relation);
        void display();
        void remove(string name);
    };
};