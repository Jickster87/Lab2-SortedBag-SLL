#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    currentElem = bag.head;
    freqCount = 1;
}

TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw exception();
    }
    return currentElem->elem.first;
}

bool SortedBagIterator::valid() {
    return currentElem != nullptr;
}

void SortedBagIterator::next() {
    if (!valid()) {
        throw exception();
    }
    freqCount++;
    
    if (freqCount > currentElem->elem.second) {
        currentElem = currentElem->next;
        freqCount = 1;
    }
}

void SortedBagIterator::first() {
    currentElem = bag.head;
    freqCount = 1;
}

