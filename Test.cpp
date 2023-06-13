#include "doctest.h"

#include <stdexcept>
#include "sources/MagicalContainer.hpp"

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


        //dont add dup
        int size = container.size();
        CHECK_EQ(container.size(), size);
        for (int i = 0; i < 20; ++i) {
            container.addElement(2);
        }
        CHECK_EQ(container.size(), size);
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
            container.addElement(i);
        }

        CHECK_EQ(container.size(), size);
        for (int i = 0; i < 5; ++i) {
            container.removeElement(i);
        }
        CHECK_EQ(container.size(), size - 5);
        container.addElement(20);
        CHECK_EQ(container.size(), size - 4);

        //add same element dont insincere
        for (int i = 0; i < size; ++i) {
            container.addElement(20);
        }
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
        MagicalContainer::AscendingIterator Iter(container);
        CHECK_EQ(*Iter.begin(), 2);
    }
    SUBCASE("Copy constructor") {
        MagicalContainer::AscendingIterator Iter(container);
        ++Iter;
        CHECK_EQ(*Iter, 3);
        MagicalContainer::AscendingIterator Iter2(Iter);
        CHECK_EQ(*Iter2, 3);

    }
    SUBCASE("Assignment operator") {
        MagicalContainer::AscendingIterator Iter(container);
        MagicalContainer::AscendingIterator Iter2(container2);
        CHECK_EQ(*Iter, 2);
        CHECK_EQ(*Iter2, 1);
        Iter2 = Iter;
        CHECK_EQ(*Iter2, 2);
    }
    SUBCASE("operator==/!=") {
        MagicalContainer::AscendingIterator Iter(container);
        MagicalContainer::AscendingIterator Iter2(container2);
        MagicalContainer::AscendingIterator Iter3(container);
        //different containers

        CHECK_THROWS(boolean = Iter == Iter2);
        CHECK_NOTHROW(boolean = Iter == Iter3);

        //check equals
        ++Iter;
        CHECK_NE(Iter, Iter3);
        ++Iter3;
        CHECK_EQ(Iter, Iter3);

        ++Iter3;
        ++Iter;
        CHECK_EQ(Iter, Iter3);


    }
    SUBCASE("operator >") {
        MagicalContainer::AscendingIterator Iter(container);
        MagicalContainer::AscendingIterator Iter2(container2);
        MagicalContainer::AscendingIterator Iter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = Iter > Iter2);
        CHECK_NOTHROW(a = Iter > Iter3);

        //2,3,9,17,25 size =5
        ++Iter;
        ++Iter;
        CHECK_GT(Iter, Iter3); //2>0
        ++Iter3;
        ++Iter3;
        ++Iter3;
        CHECK_GT(Iter3, Iter); //3>2
        ++Iter;
        ++Iter;
        ++Iter;
        CHECK_GT(Iter, Iter3); //5>3

    }
    SUBCASE("operator<") {
        MagicalContainer::AscendingIterator Iter(container);
        MagicalContainer::AscendingIterator Iter2(container2);
        MagicalContainer::AscendingIterator Iter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = Iter < Iter2);
        CHECK_NOTHROW(a = Iter < Iter3);

        //2,3,9,17,25 size =5
        ++Iter;
        ++Iter;
        CHECK_LT(Iter3, Iter); //2>0
        ++Iter3;
        ++Iter3;
        ++Iter3;
        CHECK_LT(Iter, Iter3); //3>2
        ++Iter;
        ++Iter;
        ++Iter;
        CHECK_LT(Iter3, Iter); //5>3

    }
    SUBCASE("operator*") {
        MagicalContainer::AscendingIterator Iter(container2);
        CHECK_EQ(*Iter, 1);
        ++Iter;
        CHECK_EQ(*Iter, 2);
        ++Iter;
        ++Iter;
        CHECK_EQ(*Iter, 4);
    }
    SUBCASE("operator++") {
        MagicalContainer::AscendingIterator Iter(container2);
        CHECK_EQ(*Iter, 1);
        ++Iter;
        CHECK_EQ(*Iter, 2);
        ++Iter;
        ++Iter;
        CHECK_EQ(*Iter, 4);
        ++Iter;
        CHECK_EQ(*Iter, 5);

        //cant ++ after end
        ++Iter;
        CHECK_THROWS(++Iter);
        CHECK_THROWS(boolean = *Iter == 5);

    }
    SUBCASE("begin") {
        MagicalContainer::AscendingIterator Iter(container2);
        ++Iter;
        CHECK_EQ(*Iter, 2);
        CHECK_EQ(*Iter.begin(), 1);
    }
    SUBCASE("end") {
        MagicalContainer::AscendingIterator Iter(container2);
        ++Iter;
        CHECK_EQ(*Iter, 2);
        CHECK_THROWS(boolean = *Iter.end() == 5);

        //can iterate
        int i = 1;
        for (auto it = Iter.begin(); it != Iter.end(); ++i, ++it) {
            CHECK_EQ(i, *it);
        }
    }
    SUBCASE("insert") {
        MagicalContainer::AscendingIterator Iter(container);
        CHECK_EQ(*Iter, 2);
        //add before not good (its moves)
        container.addElement(0);
        CHECK_EQ(*Iter, 0);

        //add after is okay
        container.addElement(100);
        CHECK_EQ(*Iter, 0);

    }
    SUBCASE("AscendingIterator add remove") {
        MagicalContainer container;
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);
        //  .
        //2,3,9,17
        //1,2,3,9,17
        MagicalContainer::AscendingIterator it(container);
        CHECK_EQ(*it,2);
        container.addElement(200);
        CHECK_EQ(*it,2);
        CHECK_EQ(*++it,3);
        container.addElement(1);
        CHECK_EQ(*it,3);
        container.removeElement(200);
        CHECK_EQ(*it,3);
        container.removeElement(2);
        CHECK_EQ(*it,3);


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
        MagicalContainer::SideCrossIterator Iter(container);
        CHECK_EQ(*Iter.begin(), 2);
    }
    SUBCASE("Copy constructor") {
        MagicalContainer::SideCrossIterator Iter(container);
        ++Iter;
        CHECK_EQ(*Iter, 25);
        MagicalContainer::SideCrossIterator Iter2(Iter);
        CHECK_EQ(*Iter2, 25);

    }
    SUBCASE("Assignment operator") {
        MagicalContainer::SideCrossIterator Iter(container);
        MagicalContainer::SideCrossIterator Iter2(container2);
        CHECK_EQ(*Iter, 2);
        CHECK_EQ(*Iter2, 1);
        Iter2 = Iter;
        CHECK_EQ(*Iter2, 2);
    }
    SUBCASE("operator==/!=") {
        MagicalContainer::SideCrossIterator Iter(container);
        MagicalContainer::SideCrossIterator Iter2(container2);
        MagicalContainer::SideCrossIterator Iter3(container);
        //different containers

        CHECK_THROWS(boolean = Iter == Iter2);
        CHECK_NOTHROW(boolean = Iter == Iter3);

        //check equals
        ++Iter;
        CHECK_NE(Iter, Iter3);
        ++Iter3;
        CHECK_EQ(Iter, Iter3);


        ++Iter;
        ++Iter3;
        CHECK_EQ(Iter, Iter3);


    }
    SUBCASE("operator >") {
        MagicalContainer::SideCrossIterator Iter(container);
        MagicalContainer::SideCrossIterator Iter2(container2);
        MagicalContainer::SideCrossIterator Iter3(container);
        //different containers
        CHECK_THROWS(boolean = Iter > Iter2);
        CHECK_NOTHROW(boolean = Iter > Iter3);

        //2,3,9,17,25 size = 5
        //0,4,1 ,3 ,2
        //0,1,2 ,3 ,4
        ++Iter;
        ++Iter;
        CHECK_GT(Iter, Iter3);
        ++Iter3;
        ++Iter3;
        ++Iter3;
        CHECK_GT(Iter3, Iter);
        ++Iter;
        ++Iter;
        ++Iter;
        CHECK_GT(Iter, Iter3);

    }
    SUBCASE("operator<") {
        MagicalContainer::SideCrossIterator Iter(container);
        MagicalContainer::SideCrossIterator Iter2(container2);
        MagicalContainer::SideCrossIterator Iter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = Iter < Iter2);
        CHECK_NOTHROW(a = Iter < Iter3);

        ++Iter;
        ++Iter;
        CHECK_LT(Iter3, Iter);
        ++Iter3;
        ++Iter3;
        ++Iter3;
        CHECK_LT(Iter, Iter3);
        ++Iter;
        ++Iter;
        ++Iter;
        CHECK_LT(Iter3, Iter);

    }
    SUBCASE("operator*") {
        //1,5,2,4,3
        MagicalContainer::SideCrossIterator Iter(container2);
        CHECK_EQ(*Iter, 1);
        ++Iter;
        CHECK_EQ(*Iter, 5);
        ++Iter;
        ++Iter;
        CHECK_EQ(*Iter, 4);
    }
    SUBCASE("operator++") {
        //1,5,2,4,3

        MagicalContainer::SideCrossIterator Iter(container2);
        CHECK_EQ(*Iter, 1);
        ++Iter;
        CHECK_EQ(*Iter, 5);
        ++Iter;
        ++Iter;
        CHECK_EQ(*Iter, 4);
        ++Iter;
        CHECK_EQ(*Iter, 3);
        //cant ++ after end
        ++Iter;

        CHECK_THROWS(++Iter);
        CHECK_THROWS(boolean = *Iter == 3);

    }
    SUBCASE("begin") {
        //1,5,2,4,3

        MagicalContainer::SideCrossIterator Iter(container2);
        ++Iter;
        CHECK_EQ(*Iter, 5);
        CHECK_EQ(*Iter.begin(), 1);
    }
    SUBCASE("end") {
        //1,5,2,4,3

        MagicalContainer::SideCrossIterator Iter(container2);
        ++Iter;
        CHECK_EQ(*Iter, 5);
        CHECK_THROWS(boolean = *Iter.end() == 3);

        //can iterate
        int i = 1;
        bool toggle = true;
        int size = container.size();
        for (auto it = Iter.begin(); it != Iter.end(); ++it) {
            CHECK_EQ(i, *it);
            if (toggle) {
                i = size - 1 - i;
            } else {
                i = size - i;
            }
            toggle = !toggle;
        }
    }

    SUBCASE("SideCrossIterator add remove") {
        MagicalContainer container;
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);
        container.addElement(4);
        container.addElement(5);


        MagicalContainer::SideCrossIterator it(container);
        CHECK_EQ(*it,1);
        container.addElement(200);
        CHECK_EQ(*it,1);
        CHECK_EQ(*++it,200);

        container.addElement(0);
        CHECK_EQ(*it,200);



        container.removeElement(0);
        CHECK_EQ(*++it,2);
        container.removeElement(200);
        CHECK_EQ(*it,2);


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
        MagicalContainer::PrimeIterator Iter(container);
        CHECK_EQ(*Iter.begin(), 2);
    }
    SUBCASE("Copy constructor") {
        MagicalContainer::PrimeIterator Iter(container);
        ++Iter;
        CHECK_EQ(*Iter, 3);
        MagicalContainer::PrimeIterator Iter2(Iter);
        CHECK_EQ(*Iter2, 3);

    }
    SUBCASE("Assignment operator") {
        MagicalContainer::PrimeIterator Iter(container);
        MagicalContainer::PrimeIterator Iter2(container2);
        CHECK_EQ(*Iter, 2);
        ++Iter2;
        CHECK_EQ(*Iter2, 3);
        Iter2 = Iter;
        CHECK_EQ(*Iter2, 2);
    }
    SUBCASE("operator==/!=") {
        MagicalContainer::PrimeIterator Iter(container);
        MagicalContainer::PrimeIterator Iter2(container2);
        MagicalContainer::PrimeIterator Iter3(container);
        //different containers

        CHECK_THROWS(boolean = Iter == Iter2);
        CHECK_NOTHROW(boolean = Iter == Iter3);

        //check equals
        ++Iter;
        CHECK_NE(Iter, Iter3);
        ++Iter3;
        CHECK_EQ(Iter, Iter3);

        ++Iter;
        ++Iter3;
        CHECK_EQ(Iter, Iter3);


    }
    SUBCASE("operator >") {
        MagicalContainer::PrimeIterator Iter(container);
        MagicalContainer::PrimeIterator Iter2(container2);
        MagicalContainer::PrimeIterator Iter3(container);
        //different containers

        CHECK_THROWS(boolean = Iter > Iter2);
        CHECK_NOTHROW(boolean = Iter > Iter3);

        //1,_2,_3,4,_5
        ++Iter;
        CHECK_GT(Iter, Iter3); //3>2
        ++Iter3;
        ++Iter3;
        CHECK_GT(Iter3, Iter); //5>3
        ++Iter3;
        ++Iter;
        ++Iter;
        CHECK_EQ(Iter, Iter3);
    }
    SUBCASE("operator<") {
        MagicalContainer::PrimeIterator Iter(container);
        MagicalContainer::PrimeIterator Iter2(container2);
        MagicalContainer::PrimeIterator Iter3(container);
        //different containers
        bool a;
        CHECK_THROWS(a = Iter < Iter2);
        CHECK_NOTHROW(a = Iter < Iter3);

        //1,_2,_3,4,_5
        ++Iter;
        CHECK_GT(Iter, Iter3); //3>2
        ++Iter3;
        ++Iter3;
        CHECK_GT(Iter3, Iter); //5>3
        ++Iter3;
        ++Iter;
        ++Iter;
        CHECK_EQ(Iter3, Iter);//6>5 but size is 5 so 5=5
    }
    SUBCASE("operator*") {
        MagicalContainer::PrimeIterator Iter(container2);
        CHECK_EQ(*Iter, 2);
        ++Iter;
        ++Iter;
        CHECK_EQ(*Iter, 5);
    }
    SUBCASE("operator++") {
        MagicalContainer::PrimeIterator Iter(container2);
        CHECK_EQ(*Iter, 2);
        ++Iter;
        ++Iter;
        CHECK_EQ(*Iter, 5);
        //cant ++ after end
        ++Iter;


        CHECK_THROWS(++Iter);
        CHECK_THROWS(boolean = *Iter == 5);

    }
    SUBCASE("begin") {
        MagicalContainer::PrimeIterator Iter(container2);
        ++Iter;
        CHECK_EQ(*Iter, 3);
        CHECK_EQ(*Iter.begin(), 2);
    }
    SUBCASE("end") {
        MagicalContainer::PrimeIterator Iter(container2);
        ++Iter;
        CHECK_EQ(*Iter, 3);
        CHECK_THROWS(boolean = *Iter.end() == 5);

        //can iterate
        int i = 0;
        int arr[3] = {2, 3, 5};
        for (auto it = Iter.begin(); it != Iter.end(); ++i, ++it) {
            CHECK_EQ(arr[i], *it);
        }
    }
    SUBCASE("PrimeIterator add remove") {
        MagicalContainer container;
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);
        //  .
        //2,3,17
        //3,17
        MagicalContainer::PrimeIterator it(container);
        CHECK_EQ(*it,2);
        container.addElement(51);
        CHECK_EQ(*it,2);
        CHECK_EQ(*++it,3);
        CHECK_EQ(*++it,17);
        container.addElement(7);
        CHECK_EQ(*it,17);

        container.removeElement(51);
        CHECK_EQ(*it,17);
        container.removeElement(2);
        CHECK_EQ(*it,17);



    }

}

