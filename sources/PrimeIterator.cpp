#include "MagicalContainer.hpp"
/*
 * =============================================
 *              PrimeIterator
 * =============================================
 */

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {
}


MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &other)
        = default;

MagicalContainer::PrimeIterator::~PrimeIterator() = default;

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator
::operator=(const MagicalContainer::PrimeIterator &other) {
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return *this;

}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return *this;

}

int MagicalContainer::PrimeIterator::operator*() const {
    return 0;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    return true;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return false;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    return true;

}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
    return true;

}

