#include "MagicalContainer.hpp"


/*
 * =============================================
 *              AscendingIterator
 * =============================================
 */
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {}


MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &other)
        = default;



MagicalContainer::AscendingIterator::~AscendingIterator() =default;

MagicalContainer::AscendingIterator
&MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &other) {
    return *this;
}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return 0;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    return true;
}
bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return false;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    return true;

}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    return true;
}
