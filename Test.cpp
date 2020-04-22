#include <iostream>
#include "doctest.h"
#include "FamilyTree.hpp"
using namespace std;

family::Tree* treeFactory(){
    family::Tree *t =new family::Tree("Ido");
    t->addFather("Ido", "Dror");
    t->addMother("Ido", "Aviva");
    t->addFather("Dror", "Yosef");
    t->addMother("Dror", "Hanna");
    t->addFather("Aviva", "Moshe");
    t->addMother("Aviva", "Malka");
    return t;
}

TEST_CASE("add mother/father"){
    family::Tree t("Ido");
    CHECK_THROWS(t.addFather("ido","Dror")); //person case sensitive.
    CHECK_THROWS(t.addMother("ido", "aviva"));//person case sensitive.
    CHECK_NOTHROW(t.addFather("Ido", "Dror")); 
    CHECK_NOTHROW(t.addMother("Ido", "Aviva"));
    CHECK_THROWS(t.addFather("Ido","Dror")); //already added a father.
    CHECK_THROWS(t.addMother("Ido", "Aviva"));// already added a mother.
    CHECK_NOTHROW(t.addFather("Dror", "Yosef"));
    CHECK_NOTHROW(t.addMother("Dror", "Hanna"));
    CHECK_NOTHROW(t.addFather("Aviva", "Moshe"));
    CHECK_NOTHROW(t.addMother("Aviva", "Malka"));
    CHECK_NOTHROW(t.display());
}

TEST_CASE("basic find"){
    family::Tree *t = treeFactory();
    CHECK(t->find("father")=="Dror");
    CHECK(t->find("mother")=="Aviva");
    CHECK(t->find("me")=="Ido");
    CHECK_NOTHROW(t->find("grandfather"));
    CHECK_NOTHROW(t->find("grandmother"));
    CHECK_THROWS(t->find("great-grandmother"));
    CHECK_THROWS(t->find("great-grandfather"));
    CHECK_THROWS(t->find("uncle"));
    CHECK_NOTHROW(t->display());
    delete(t);
}

TEST_CASE("basic relation"){
    family::Tree *t = treeFactory();
    CHECK(t->relation("Ido")=="me");
    CHECK(t->relation("Dror")=="father");
    CHECK(t->relation("Aviva")=="mother");
    CHECK(t->relation("Yosef")=="grandfather");
    CHECK(t->relation("Hanna")=="grandmother");
    CHECK(t->relation("Moshe")=="grandfather");
    CHECK(t->relation("Malka")=="grandmother");
    CHECK(t->relation("Eran")=="unrelated");
    CHECK_NOTHROW(t->display());
    delete(t);
}

TEST_CASE("basic remove"){
    family::Tree *t = treeFactory();
    CHECK_THROWS(t->remove("dror")); //lower case in the begining of the name
    CHECK_NOTHROW(t->remove("Dror"));
    CHECK(t->relation("Dror")=="unrelated");
    CHECK(t->relation("Hanna")=="unrelated");
    CHECK(t->relation("Yosef")=="unrelated");
    CHECK(t->find("grandmother")=="Malka");
    CHECK(t->find("grandfather")=="Moshe");
    CHECK_NOTHROW(t->display());
}

TEST_CASE("numbers"){
    family::Tree t("1");
    CHECK_NOTHROW(t.addFather("1","2"));
    CHECK_NOTHROW(t.addMother("1","3"));
    CHECK_THROWS(t.addFather("1","5")); // 1 already have a father
    CHECK(t.relation("2")=="father");
    CHECK_NOTHROW(t.addFather("2","4"));
    CHECK(t.find("grandfather")=="4");
    CHECK_NOTHROW(t.remove("2"));
    CHECK(t.relation("4")=="unrelated");
    CHECK_THROWS(t.remove("1")); // should not be able to delete root
    CHECK(t.relation("9")=="unrelated");
    CHECK_THROWS(t.remove("9"));
    CHECK_NOTHROW(t.addFather("1","6"));
    CHECK(t.find("father")=="6");
    CHECK(t.relation("3")=="mother");
    CHECK_NOTHROW(t.remove("3"));
    CHECK_NOTHROW(t.remove("6"));
}


TEST_CASE("letters"){
    family::Tree t("a");
    CHECK_THROWS(t.find("f"));
    CHECK_THROWS(t.find("A")); // case sensetive
    CHECK_NOTHROW(t.addMother("a","m"));
    CHECK_NOTHROW(t.addFather("a","d"));
    CHECK_NOTHROW(t.addMother("m","mgm"));
    CHECK_NOTHROW(t.addMother("d","dgm"));
    CHECK_NOTHROW(t.find("grandmother"));
    CHECK_NOTHROW(t.addFather("d","dgf"));
    CHECK(t.find("grandfather")=="dgf");
    CHECK_NOTHROW(t.addFather("dgf","dggf"));
    CHECK(t.find("great-grandfather")=="dggf");
    CHECK_THROWS(t.remove("mgf")); //mgf does not exist in the tree
    CHECK_NOTHROW(t.remove("m"));
    CHECK(t.relation("mgm")=="unrelated");
    CHECK(t.relation("m")=="unrelated");
    CHECK_THROWS(t.addMother("m","r")); //m doesn't exist in the tree (was deleted)
    
}

TEST_CASE("more"){
    family::Tree t("me");
    CHECK_THROWS(t.addMother("mother","grandmother"));
    CHECK_NOTHROW(t.addMother("me","mother"));
    CHECK_NOTHROW(t.addFather("me","father"));
    CHECK(t.find("father")=="father");
    CHECK(t.relation("father")=="father");
    CHECK_NOTHROW(t.addFather("father","grandfather"));
    CHECK(t.find("grandfather")=="grandfather");
    CHECK(t.relation("grandfather")=="grandfather");
    CHECK_NOTHROW(t.remove("father"));
    CHECK_THROWS(t.find("father"));
    CHECK(t.relation("father")=="unrelated");
    CHECK_NOTHROW(t.remove("mother"));
    CHECK_THROWS(t.remove("me)")); // can't remove root
}

TEST_CASE("more more"){
    family::Tree t("one");
    CHECK(t.find("me")=="one");
    CHECK(t.relation("one")=="me");
    CHECK_NOTHROW(t.addFather("one","two"));
    CHECK_THROWS(t.addFather("three","four"));
    CHECK(t.find("father")=="two");
    CHECK_THROWS(t.find("mother"));
    CHECK_THROWS(t.find("blabla"));//not a real type of relation
    CHECK(t.relation("someone")=="unrelated");
    CHECK_NOTHROW(t.addMother("one","three"));
    CHECK(t.relation("three")=="mother");
    CHECK(t.find("mother")=="three");
    CHECK_NOTHROW(t.remove("two"));
    CHECK_THROWS(t.remove("four"));
    CHECK_NOTHROW(t.remove("three"));
}

TEST_CASE("a bit more"){
    family::Tree t("_+");
    CHECK_THROWS(t.addMother("me","mother"));
    CHECK_NOTHROW(t.addFather("_+","=_"));
    CHECK_THROWS(t.remove("father"));
    CHECK_NOTHROW(t.remove("=_"));
    CHECK(t.find("me")=="_+");
    CHECK(t.relation("_+")=="me");


}

TEST_CASE("namespace test"){
    CHECK(family::isEqualIgnoreCase("I d 0 : sd", "i D 0 : Sd")==true);
    CHECK(family::validRelation("uncle")==false);
    CHECK(family::validRelation("great-great-great-grandMother")==true);
}