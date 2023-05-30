#include "doctest.h"

#include <iostream>
#include <stdexcept>
#include "sources/MagicalContainer.hpp"

#define LOOPS_AMOUNT 20
using namespace std;

bool boolean;

TEST_CASE("container") {
    SUBCASE("add") {
        MagicalContainer container;
        container.addElement(1);
        CHECK_EQ(container[0], 1);

        //sort as inserting
        container.addElement(2);
        CHECK_EQ(container[0], 1);
        container.addElement(0);
        CHECK_EQ(container[0], 0);

    }
    SUBCASE("remove") {
        MagicalContainer container;
        container.addElement(1);
        CHECK_EQ(container[0], 1);

        //remove and accesses it get an exception
        container.removeElement(1);
        CHECK_THROWS_AS(container[0], std::out_of_range);

    }
    SUBCASE("size") {
        MagicalContainer container;
        int size = 11;
        for (int i = 0; i < size; ++i) {
            container.addElement(1);
        }

        CHECK_EQ(container.size(), size);
        for (int i = 0; i < 5; ++i) {
            container.removeElement(1);
        }
        CHECK_EQ(container.size(), size - 5);
        container.addElement(1);
        CHECK_EQ(container.size(), size - 4);

    }
}

TEST_CASE("AscendingIterator") {
    MagicalContainer container;

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    MagicalContainer container2;

    container2.addElement(1);
    container2.addElement(2);
    container2.addElement(3);
    container2.addElement(4);
    container2.addElement(5);

    SUBCASE("constructor") {
        MagicalContainer::AscendingIterator ascIter(container);
        CHECK_EQ(*ascIter.begin(), 2);
    }
    SUBCASE("Copy constructor") {
        MagicalContainer::AscendingIterator ascIter(container);
        ++ascIter;
        CHECK_EQ(*ascIter, 3);
        MagicalContainer::AscendingIterator ascIter2(ascIter);
        CHECK_EQ(*ascIter2, 3);

    }
    SUBCASE("Assignment operator") {
        MagicalContainer::AscendingIterator ascIter(container);
        MagicalContainer::AscendingIterator ascIter2(container2);
        CHECK_EQ(*ascIter, 2);
        CHECK_EQ(*ascIter2, 1);
        ascIter2 = ascIter;
        CHECK_EQ(*ascIter2, 2);
    }
    SUBCASE("operator==/!=") {
        MagicalContainer::AscendingIterator ascIter(container);
        MagicalContainer::AscendingIterator ascIter2(container2);
        MagicalContainer::AscendingIterator ascIter3(container);
        //different containers

        CHECK_THROWS(boolean = ascIter == ascIter2);
        CHECK_NOTHROW(boolean = ascIter == ascIter3);

        //check equals
        ++ascIter;
        CHECK_NE(ascIter, ascIter3);
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);

        //till the end it dosent matter
        for (int i = 0; i < 10; ++i) {
            ++ascIter;
            ++ascIter3;
        }
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);


    }
    SUBCASE("operator >") {
        MagicalContainer::AscendingIterator ascIter(container);
        MagicalContainer::AscendingIterator ascIter2(container2);
        MagicalContainer::AscendingIterator ascIter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = ascIter > ascIter2);
        CHECK_NOTHROW(a = ascIter > ascIter3);

        //2,3,9,17,25 size =5
        ++ascIter;
        ++ascIter;
        CHECK_GT(ascIter, ascIter3); //2>0
        ++ascIter3;
        ++ascIter3;
        ++ascIter3;
        CHECK_GT(ascIter3, ascIter); //3>2
        ++ascIter;
        ++ascIter;
        ++ascIter;
        CHECK_GT(ascIter, ascIter3); //5>3
        ++ascIter;
        ++ascIter3;
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);//6>5 but size is 5 so 5=5
    }
    SUBCASE("operator<") {
        MagicalContainer::AscendingIterator ascIter(container);
        MagicalContainer::AscendingIterator ascIter2(container2);
        MagicalContainer::AscendingIterator ascIter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = ascIter < ascIter2);
        CHECK_NOTHROW(a = ascIter < ascIter3);

        //2,3,9,17,25 size =5
        ++ascIter;
        ++ascIter;
        CHECK_LT(ascIter3, ascIter); //2>0
        ++ascIter3;
        ++ascIter3;
        ++ascIter3;
        CHECK_LT(ascIter, ascIter3); //3>2
        ++ascIter;
        ++ascIter;
        ++ascIter;
        CHECK_LT(ascIter3, ascIter); //5>3
        ++ascIter;
        ++ascIter3;
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);//6>5 but size is 5 so 5=5
    }
    SUBCASE("operator*") {
        MagicalContainer::AscendingIterator ascIter(container2);
        CHECK_EQ(*ascIter, 1);
        ++ascIter;
        CHECK_EQ(*ascIter, 2);
        ++ascIter;
        ++ascIter;
        CHECK_EQ(*ascIter, 4);
    }
    SUBCASE("operator++") {
        MagicalContainer::AscendingIterator ascIter(container2);
        CHECK_EQ(*ascIter, 1);
        ++ascIter;
        CHECK_EQ(*ascIter, 2);
        ++ascIter;
        ++ascIter;
        CHECK_EQ(*ascIter, 4);
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
        //can ++ after end just dont increment, but cant * the element
        for (int i = 0; i < 100; ++i) {
            ++ascIter;
        }
        CHECK_THROWS(boolean = *ascIter == 5);

    }
    SUBCASE("begin") {
        MagicalContainer::AscendingIterator ascIter(container2);
        ++ascIter;
        CHECK_EQ(*ascIter, 2);
        CHECK_EQ(*ascIter.begin(), 1);
    }
    SUBCASE("end") {
        MagicalContainer::AscendingIterator ascIter(container2);
        ++ascIter;
        CHECK_EQ(*ascIter, 2);
        CHECK_THROWS(boolean = *ascIter.end() == 5);

        //can iterate
        int i = 1;
        for (auto it = ascIter.begin(); it != ascIter.end(); ++i, ++it) {
            CHECK_EQ(i, *it);
        }
    }
}

TEST_CASE("SideCrossIterator") {
    MagicalContainer container;

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    MagicalContainer container2;

    container2.addElement(1);
    container2.addElement(2);
    container2.addElement(3);
    container2.addElement(4);
    container2.addElement(5);

    SUBCASE("constructor") {
        MagicalContainer::SideCrossIterator ascIter(container);
        CHECK_EQ(*ascIter.begin(), 2);
    }
    SUBCASE("Copy constructor") {
        MagicalContainer::SideCrossIterator ascIter(container);
        ++ascIter;
        CHECK_EQ(*ascIter, 25);
        MagicalContainer::SideCrossIterator ascIter2(ascIter);
        CHECK_EQ(*ascIter2, 25);

    }
    SUBCASE("Assignment operator") {
        MagicalContainer::SideCrossIterator ascIter(container);
        MagicalContainer::SideCrossIterator ascIter2(container2);
        CHECK_EQ(*ascIter, 2);
        CHECK_EQ(*ascIter2, 1);
        ascIter2 = ascIter;
        CHECK_EQ(*ascIter2, 2);
    }
    SUBCASE("operator==/!=") {
        MagicalContainer::SideCrossIterator ascIter(container);
        MagicalContainer::SideCrossIterator ascIter2(container2);
        MagicalContainer::SideCrossIterator ascIter3(container);
        //different containers

        CHECK_THROWS(boolean = ascIter == ascIter2);
        CHECK_NOTHROW(boolean = ascIter == ascIter3);

        //check equals
        ++ascIter;
        CHECK_NE(ascIter, ascIter3);
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);

        //till the end it dosent matter
        for (int i = 0; i < 10; ++i) {
            ++ascIter;
            ++ascIter3;
        }
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);


    }
    SUBCASE("operator >") {
        MagicalContainer::SideCrossIterator ascIter(container);
        MagicalContainer::SideCrossIterator ascIter2(container2);
        MagicalContainer::SideCrossIterator ascIter3(container);
        //different containers
        CHECK_THROWS(boolean = ascIter > ascIter2);
        CHECK_NOTHROW(boolean = ascIter > ascIter3);

        //2,3,9,17,25 size = 5
        //0,4,1 ,3 ,2
        //0,1,2 ,3 ,4
        ++ascIter;
        ++ascIter;
        CHECK_GT(ascIter, ascIter3);
        ++ascIter3;
        ++ascIter3;
        ++ascIter3;
        CHECK_GT(ascIter3, ascIter);
        ++ascIter;
        ++ascIter;
        ++ascIter;
        CHECK_GT(ascIter, ascIter3);
        ++ascIter;
        ++ascIter3;
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);
    }
    SUBCASE("operator<") {
        MagicalContainer::SideCrossIterator ascIter(container);
        MagicalContainer::SideCrossIterator ascIter2(container2);
        MagicalContainer::SideCrossIterator ascIter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = ascIter < ascIter2);
        CHECK_NOTHROW(a = ascIter < ascIter3);

        ++ascIter;
        ++ascIter;
        CHECK_LT(ascIter3,ascIter);
        ++ascIter3;
        ++ascIter3;
        ++ascIter3;
        CHECK_LT(ascIter,ascIter3 );
        ++ascIter;
        ++ascIter;
        ++ascIter;
        CHECK_LT( ascIter3,ascIter);
        ++ascIter;
        ++ascIter3;
        ++ascIter3;
        CHECK_EQ(ascIter3,ascIter );
    }
    SUBCASE("operator*") {
        //1,5,2,4,3
        MagicalContainer::SideCrossIterator ascIter(container2);
        CHECK_EQ(*ascIter, 1);
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
        ++ascIter;
        ++ascIter;
        CHECK_EQ(*ascIter, 4);
    }
    SUBCASE("operator++") {
        //1,5,2,4,3

        MagicalContainer::SideCrossIterator ascIter(container2);
        CHECK_EQ(*ascIter, 1);
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
        ++ascIter;
        ++ascIter;
        CHECK_EQ(*ascIter, 4);
        ++ascIter;
        CHECK_EQ(*ascIter, 3);
        //can ++ after end just dont increment, but cant * the element
        for (int i = 0; i < 100; ++i) {
            ++ascIter;
        }
        CHECK_THROWS(boolean = *ascIter == 3);

    }
    SUBCASE("begin") {
        //1,5,2,4,3

        MagicalContainer::SideCrossIterator ascIter(container2);
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
        CHECK_EQ(*ascIter.begin(), 1);
    }
    SUBCASE("end") {
        //1,5,2,4,3

        MagicalContainer::SideCrossIterator ascIter(container2);
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
        CHECK_THROWS(boolean = *ascIter.end() == 3);

        //can iterate
        int i = 1;
        bool toggle = true;
        int size = container.size();
        for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
            CHECK_EQ(i, *it);
            if (toggle) {
                i = size - 1 - i;
            } else {
                i = size - i;
            }
            toggle = !toggle;
        }
    }
}

TEST_CASE("PrimeIterator") {
    MagicalContainer container;

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    MagicalContainer container2;

    container2.addElement(1);
    container2.addElement(2);
    container2.addElement(3);
    container2.addElement(4);
    container2.addElement(5);

    SUBCASE("constructor") {
        MagicalContainer::PrimeIterator ascIter(container);
        CHECK_EQ(*ascIter.begin(), 2);
    }
    SUBCASE("Copy constructor") {
        MagicalContainer::PrimeIterator ascIter(container);
        ++ascIter;
        CHECK_EQ(*ascIter, 3);
        MagicalContainer::PrimeIterator ascIter2(ascIter);
        CHECK_EQ(*ascIter2, 3);

    }
    SUBCASE("Assignment operator") {
        MagicalContainer::PrimeIterator ascIter(container);
        MagicalContainer::PrimeIterator ascIter2(container2);
        CHECK_EQ(*ascIter, 2);
        ++ascIter2;
        CHECK_EQ(*ascIter2, 3);
        ascIter2 = ascIter;
        CHECK_EQ(*ascIter2, 2);
    }
    SUBCASE("operator==/!=") {
        MagicalContainer::PrimeIterator ascIter(container);
        MagicalContainer::PrimeIterator ascIter2(container2);
        MagicalContainer::PrimeIterator ascIter3(container);
        //different containers

        CHECK_THROWS(boolean = ascIter == ascIter2);
        CHECK_NOTHROW(boolean = ascIter == ascIter3);

        //check equals
        ++ascIter;
        CHECK_NE(ascIter, ascIter3);
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);

        //till the end it dosent matter
        for (int i = 0; i < 10; ++i) {
            ++ascIter;
            ++ascIter3;
        }
        ++ascIter3;
        CHECK_EQ(ascIter, ascIter3);


    }
    SUBCASE("operator >") {
        MagicalContainer::PrimeIterator ascIter(container);
        MagicalContainer::PrimeIterator ascIter2(container2);
        MagicalContainer::PrimeIterator ascIter3(container);
        //different containers

        CHECK_THROWS(boolean = ascIter > ascIter2);
        CHECK_NOTHROW(boolean = ascIter > ascIter3);

        //1,_2,_3,4,_5
        ++ascIter;
        CHECK_GT(ascIter, ascIter3); //3>2
        ++ascIter3;
        ++ascIter3;
        CHECK_GT(ascIter3, ascIter); //5>3
        ++ascIter3;
        ++ascIter;
        ++ascIter;
        ++ascIter;
        CHECK_EQ(ascIter, ascIter3);//6>5 but size is 5 so 5=5
    }
    SUBCASE("operator<") {
        MagicalContainer::PrimeIterator ascIter(container);
        MagicalContainer::PrimeIterator ascIter2(container2);
        MagicalContainer::PrimeIterator ascIter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = ascIter < ascIter2);
        CHECK_NOTHROW(a = ascIter < ascIter3);

        //1,_2,_3,4,_5
        ++ascIter;
        CHECK_GT(ascIter, ascIter3); //3>2
        ++ascIter3;
        ++ascIter3;
        CHECK_GT(ascIter3, ascIter); //5>3
        ++ascIter3;
        ++ascIter;
        ++ascIter;
        ++ascIter;
        CHECK_EQ(ascIter3, ascIter);//6>5 but size is 5 so 5=5
    }
    SUBCASE("operator*") {
        MagicalContainer::PrimeIterator ascIter(container2);
        CHECK_EQ(*ascIter, 2);
        ++ascIter;
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
    }
    SUBCASE("operator++") {
        MagicalContainer::PrimeIterator ascIter(container2);
        CHECK_EQ(*ascIter, 2);
        ++ascIter;
        ++ascIter;
        CHECK_EQ(*ascIter, 5);
        //can ++ after end just dont increment, but cant * the element
        for (int i = 0; i < 100; ++i) {
            ++ascIter;
        }
        CHECK_THROWS(boolean = *ascIter == 5);

    }
    SUBCASE("begin") {
        MagicalContainer::PrimeIterator ascIter(container2);
        ++ascIter;
        CHECK_EQ(*ascIter, 3);
        CHECK_EQ(*ascIter.begin(), 2);
    }
    SUBCASE("end") {
        MagicalContainer::PrimeIterator ascIter(container2);
        ++ascIter;
        CHECK_EQ(*ascIter, 3);
        CHECK_THROWS(boolean = *ascIter.end() == 5);

        //can iterate
        int i = 0;
        int arr[3] = {2, 3, 5};
        for (auto it = ascIter.begin(); it != ascIter.end(); ++i, ++it) {
            CHECK_EQ(arr[i], *it);
        }
    }
}

