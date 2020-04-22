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

        static string find(Person *p, string relation);
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

      private:
        //recursive search for a person with a specific name
        Person* search(Person *p, string name);
        Person* findChild(Person *p,string name);
        static string gen(string name, Person *p, int level);
    };

    bool isEqualIgnoreCase(string a, string b);
    bool validRelation(string relation);
};