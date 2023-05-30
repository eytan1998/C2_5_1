#include "MagicalContainer.hpp"

/*
 * =============================================
 *              SideCrossIterator
 * =============================================
 */

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(container), currentIndex(0), isLeft(true) {}


MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &other)
        : container(other.container), currentIndex(other.currentIndex), isLeft(other.isLeft) {}

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
    SideCrossIterator iter(*this);
    iter.currentIndex = 0;
    return iter;
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
    if (currentIndex == container.size()) throw logic_error("cant increment end()");

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
    if (&container != &other.container)throw std::invalid_argument(">. different containers");
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    if (&container != &other.container)throw std::invalid_argument(">. different containers");

    //calculate with one is finish
    if(currentIndex >= container.size() && other.currentIndex < container.size()) return true;
    if(currentIndex >= container.size() && other.currentIndex >= container.size()) return false;
    if(currentIndex < container.size() && other.currentIndex >= container.size()) return false;

    float middle = ((container.size()-1) / 2.0);


    //closest to middle is the smaller
    int mDis = abs(currentIndex - middle) ;
    int oDis = abs(other.currentIndex - middle);

    if(mDis < oDis) return true;
    //same distance but I am left so came first
    if(mDis==oDis && (!isLeft && other.isLeft)) return true;
    //return false if greater distance, or same but he on left or we both on same side
    return false;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    //if not > so its <=, but if also != so <
    return (!(*this > other)&& (*this != other));
}

