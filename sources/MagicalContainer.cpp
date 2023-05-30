#include "MagicalContainer.hpp"

/*
 * =============================================
 *              MagicalContainer
 * =============================================
 */
MagicalContainer::MagicalContainer() {}

MagicalContainer::MagicalContainer(const MagicalContainer &other) : elements(other.elements) {}

MagicalContainer::~MagicalContainer() {}

MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other) {
    if (this != &other) {
        elements = other.elements;
    }
    return *this;
}

int MagicalContainer::operator[](const int index) {
    if (index >= elements.size()) throw std::out_of_range("[]. Out of bound.");
    return elements.at((size_t) index);
}

//add on O(n)
void MagicalContainer::addElement(int element) {
    //sort as insert
    auto it = std::lower_bound(elements.begin(), elements.end(), element);
    elements.insert(it, element);
}


void MagicalContainer::removeElement(int element) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        elements.erase(it);
    }else{
        throw std::invalid_argument("removeElement. not an element.");
    }
}

size_t MagicalContainer::size() const {
    return elements.size();
}

/*
 * =============================================
 *              AscendingIterator
 * =============================================
 */
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {}


MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

MagicalContainer::AscendingIterator
&MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
    }
    return *this;
}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator iter(*this);
    iter.currentIndex = container.size();
    return iter;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return container[currentIndex];
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    currentIndex++;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    return currentIndex < other.currentIndex;
}


/*
 * =============================================
 *              SideCrossIterator
 * =============================================
 */

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(container), currentIndex(0), isLeft(true) {}


MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &other)
        : container(other.container), currentIndex(other.currentIndex),isLeft(other.isLeft) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator
&MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
        isLeft = other.isLeft;
    }
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator iter(*this);
    iter.currentIndex = container.size();
    return iter;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    return container[currentIndex];
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    //if ended
    if (currentIndex >= container.size()) return *this;

    //if on the last one
    //if odd 5 -> end 2 (middle) 0,4,1,3,2
    //if even 6 -> end 3 (round up because go lower than high so go  0,5,1,4,2,3)
    int middle = container.size() / 2;
    if (currentIndex == middle) currentIndex = container.size();
        //regular

    else {
        if (isLeft) {
            currentIndex = container.size() - currentIndex - 1; //if size 5 and cur 0 -> 5-0-1 = 4
            isLeft = false;
        } else {
            currentIndex = container.size() - currentIndex; //if size 5 and cur 4 -> 5-4 =1
            isLeft = true;
        }
    }

    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    return currentIndex > other.currentIndex || (currentIndex == other.currentIndex && !isLeft && other.isLeft);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    return currentIndex < other.currentIndex || (currentIndex == other.currentIndex && isLeft && !other.isLeft);
}


/*
 * =============================================
 *              PrimeIterator
 * =============================================
 */

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {}


MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator
&MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator &other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
    }
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    PrimeIterator iter(*this);
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
    currentIndex++;
    while (currentIndex < container.size() && !isPrime(container[currentIndex]))
        currentIndex++;
    return *this; // return or prime or end
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
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

