#include "MagicalContainer.hpp"

/*
 * =============================================
 *              SideCrossIterator
 * =============================================
 */

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(container), currentIndex(0), isLeft(true) {}


MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &other)
      = default;

MagicalContainer::SideCrossIterator::~SideCrossIterator() = default;

MagicalContainer::SideCrossIterator
&MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &other) {
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return *this;

}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    return *this;

}

int MagicalContainer::SideCrossIterator::operator*() const {
    return 0;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    return true;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return false;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    return true;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    return true;
}

