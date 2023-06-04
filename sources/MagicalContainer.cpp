#include "MagicalContainer.hpp"

/*
 * =============================================
 *              MagicalContainer
 * =============================================
 */
MagicalContainer::MagicalContainer() = default;

MagicalContainer::MagicalContainer(const MagicalContainer &other) : elements(other.elements) {}

MagicalContainer::~MagicalContainer()= default;

MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other) {
    return *this;
}

int MagicalContainer::operator[](const int index) {
    return 0;
}

//add on O(n)
void MagicalContainer::addElement(int element) {
}


void MagicalContainer::removeElement(int element) {
}

size_t MagicalContainer::size() const {
    return 0;
}

