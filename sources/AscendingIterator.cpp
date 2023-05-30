#include "MagicalContainer.hpp"


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
    AscendingIterator iter(*this);
    iter.currentIndex = 0;
    return iter;
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
    if (currentIndex == container.size()) throw logic_error("cant increment end()");
    if (currentIndex < container.size()) currentIndex++;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    if (&container != &other.container) throw std::invalid_argument("==. different containers");
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    if (&container != &other.container)throw std::invalid_argument(">. different containers");
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    if (&container != &other.container)throw std::invalid_argument("<. different containers");
    return currentIndex < other.currentIndex;
}
