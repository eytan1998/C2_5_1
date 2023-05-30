#include "doctest.h"

#include <iostream>
#include <stdexcept>
#include "sources/MagicalContainer.hpp"

#define LOOPS_AMOUNT 20
using namespace std;


TEST_CASE("container") {
    SUBCASE("add") {
        MagicalContainer container;
        container.addElement(1);
        CHECK_EQ(container[0] , 1);
        //TODO
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);
        CHECK_EQ(container[0] , 1);

        //sort as inserting
        container.addElement(2);
        CHECK_EQ(container[0] , 1);
        container.addElement(0);
        CHECK_EQ(container[0] , 0);

    }
    SUBCASE("remove") {
        MagicalContainer container;
        container.addElement(1);
        CHECK_EQ(container[0] , 1);

        //remove and accesses it get an exception
        container.removeAt(0);
        CHECK_THROWS_AS(container[0],std::out_of_range);

    }
    SUBCASE("size") {
        MagicalContainer container;
        int size = 11;
        for (int i = 0; i < size; ++i) {
            container.addElement(1);
        }

        CHECK_EQ(container.size()  , size);
        for (int i = 0; i < 5; ++i) {
            container.removeAt(0);
        }
        CHECK_EQ(container.size()  , size-5);
        container.addElement(1);
        CHECK_EQ(container.size()  , size-4);

    }
}

TEST_CASE("AscendingIterator") {
    MagicalContainer container;

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    SUBCASE("constructor") {
        MagicalContainer::AscendingIterator ascIter(container);
        CHECK_EQ(*ascIter.begin(),2);
    }
    SUBCASE("Copy constructor") {
    }
    SUBCASE("Destructor") {
    }
    SUBCASE("Assignment operator") {
    }
    SUBCASE("operator==") {
    }
    SUBCASE("operator!=") {
    }
    SUBCASE("operator>") {
    }
    SUBCASE("operator<") {
    }
    SUBCASE("operator*") {
    }
    SUBCASE("operator++") {
    }
    SUBCASE("begin") {
    }
    SUBCASE("end") {
    }
}
TEST_CASE("SideCrossIterator") {
    SUBCASE("constructor") {
    }
    SUBCASE("Copy constructor") {
    }
    SUBCASE("Destructor") {
    }
    SUBCASE("Assignment operator") {
    }
    SUBCASE("operator==") {
    }
    SUBCASE("operator!=") {
    }
    SUBCASE("operator>") {
    }
    SUBCASE("operator<") {
    }
    SUBCASE("operator*") {
    }
    SUBCASE("operator++") {
    }
    SUBCASE("begin") {
    }
    SUBCASE("end") {
    }
}
TEST_CASE("PrimeIterator") {
    SUBCASE("constructor") {
    }
    SUBCASE("Copy constructor") {
    }
    SUBCASE("Destructor") {
    }
    SUBCASE("Assignment operator") {
    }
    SUBCASE("operator==") {
    }
    SUBCASE("operator!=") {
    }
    SUBCASE("operator>") {
    }
    SUBCASE("operator<") {
    }
    SUBCASE("operator*") {
    }
    SUBCASE("operator++") {
    }
    SUBCASE("begin") {
    }
    SUBCASE("end") {
    }
}
