#ifndef MAGICALCONTAINER_H
#define MAGICALCONTAINER_H
#include <stdexcept>
#include "iostream"
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
namespace ariel{}

class MagicalContainer {
private:
    std::vector<int> elements;

public:
    MagicalContainer();

    MagicalContainer(const MagicalContainer& other);

    ~MagicalContainer();

    MagicalContainer& operator=(const MagicalContainer& other);

    int operator[](int index);

    void addElement(int element);

    void removeElement(int element);

    size_t size() const;

/*
 * =============================================
 *              AscendingIterator
 * =============================================
 */
    class AscendingIterator {
    private:
        MagicalContainer &container;
        size_t currentIndex;

    public:
        explicit AscendingIterator();

        explicit AscendingIterator(MagicalContainer& container);

        AscendingIterator(const AscendingIterator& other);

        ~AscendingIterator();

        AscendingIterator& operator=(const AscendingIterator& other);

        bool operator==(const AscendingIterator& other) const;

        bool operator!=(const AscendingIterator& other) const;

        bool operator<(const AscendingIterator& other) const;

        bool operator>(const AscendingIterator& other) const;

        int operator*() const;

        AscendingIterator& operator++();

        AscendingIterator begin();

        AscendingIterator end();
    };


/*
 * =============================================
 *              SideCrossIterator
 * =============================================
 */

    class SideCrossIterator {
    private:
        MagicalContainer &container;
        bool isLeft;
        size_t currentIndex;

    public:
        explicit SideCrossIterator();

        explicit SideCrossIterator(MagicalContainer& container);

        SideCrossIterator(const SideCrossIterator& other);

        ~SideCrossIterator();

        SideCrossIterator& operator=(const SideCrossIterator& other);

        int operator*() const;

        bool operator==(const SideCrossIterator& other) const;

        bool operator!=(const SideCrossIterator& other) const;

        bool operator<(const SideCrossIterator& other) const;

        bool operator>(const SideCrossIterator& other) const;

        SideCrossIterator& operator++();

        SideCrossIterator begin();

        SideCrossIterator end();
    };


/*
 * =============================================
 *              PrimeIterator
 * =============================================
 */
    class PrimeIterator {
    private:
        MagicalContainer &container;
        size_t currentIndex;

        bool isPrime(int num);

    public:
        explicit PrimeIterator();
        explicit PrimeIterator(MagicalContainer& container);

        PrimeIterator(const PrimeIterator& other);

        ~PrimeIterator();

        PrimeIterator& operator=(const PrimeIterator& other);

        bool operator==(const PrimeIterator& other) const;

        bool operator!=(const PrimeIterator& other) const;

        bool operator<(const PrimeIterator& other) const;

        bool operator>(const PrimeIterator& other) const;

        int operator*() const;

        PrimeIterator& operator++();

        PrimeIterator begin();

        PrimeIterator end();
    };


};

#endif  // MAGICALCONTAINER_H
