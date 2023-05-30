#include "MagicalContainer.hpp"
/*
 * =============================================
 *              PrimeIterator
 * =============================================
 */

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {
    //if not prime and not end -> move
    if (!isPrime(container[currentIndex])) ++*this;
}


MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator
::operator=(const MagicalContainer::PrimeIterator &other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
    }
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    PrimeIterator iter(*this);
    iter.currentIndex =0;
    //if not prime and not end -> move
    if (!isPrime(*iter)) ++iter;
    return iter;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator iter(*this);
    iter.currentIndex = container.size();
    return iter;
}

int MagicalContainer::PrimeIterator::operator*() const {
    return container[currentIndex];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (currentIndex == container.size()) throw logic_error("cant increment end()");
    currentIndex++;
    while (currentIndex < container.size() && !isPrime(container[currentIndex]))
        currentIndex++;
    return *this; // return or prime or end
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    if (&container != &other.container)throw std::invalid_argument(">. different containers");
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    if (&container != &other.container)throw std::invalid_argument(">. different containers");
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
    if (&container != &other.container)throw std::invalid_argument(">. different containers");
    return currentIndex < other.currentIndex;
}

bool MagicalContainer::PrimeIterator::isPrime(int num) {
    if (num < 2)
        return false;
    for (int i = 2; i <= std::sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

