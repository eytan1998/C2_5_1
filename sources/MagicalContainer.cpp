#include "MagicalContainer.hpp"

/*
 * =============================================
 *              MagicalContainer
 * =============================================
 */

MagicalContainer::MagicalContainer(const MagicalContainer &other) : elements(other.elements) {}

MagicalContainer::~MagicalContainer() {}

MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other) {
    if (this != &other) {
        elements = other.elements;
    }
    return *this;
}

int MagicalContainer::operator[](const int index) {
    if (index >= elements.size() || index <0 ) throw std::out_of_range("[]. Out of bound.");
    return elements.at((size_t) index);
}

//add on O(n)
void MagicalContainer::addElement(int element) {
    // Element already exists, do not add
    if (std::find(elements.begin(), elements.end(), element) != elements.end()) {
        return;
    }
    //sort as insert
    auto it = std::lower_bound(elements.begin(), elements.end(), element);
    elements.insert(it, element);
}


void MagicalContainer::removeElement(int element) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        elements.erase(it);
    } else {
        throw std::invalid_argument("removeElement. not an element.");
    }
}

size_t MagicalContainer::size() const {
    return elements.size();
}

