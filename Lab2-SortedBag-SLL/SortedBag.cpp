#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    rel = r;
    head = nullptr;
    nrElems = 0;
}

void SortedBag::add(TComp e) {
	
    Node * current = head;
    Node * prev = nullptr;
    
    //get node current to the elem
    while (current != nullptr && rel(current->elem.first, e)) {
        prev = current;
        current = current->next;
    }
    
    //if elem exists just increment
    if (current != nullptr && current->elem.first == e) {
        current->elem.second++;
    }
    
    TPair newElem = std::make_pair(e, 1);
    Node * newNode = new Node(newElem);
    
    if (prev == nullptr) {
        newNode->next = head;
        head = newNode;
    } else {
        prev->next = newNode;
        newNode->next = current;
    }
    nrElems++;
}


bool SortedBag::remove(TComp elem) {
    //walk list with 2 *pointers
    Node* currentNode = head;
    Node* prevNode = nullptr;
    
    while (currentNode != nullptr && currentNode->elem.first != elem) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    
    // If element not found, return false
     if (currentNode == nullptr) {
         return false; // Element is not in the list
     }
    
    if (currentNode != nullptr && prevNode == nullptr) {
        head = head->next;
    }
    else if (currentNode != nullptr) {
        prevNode->next = currentNode->next;
        currentNode->next = nullptr;
        }
    delete currentNode;
    nrElems--;
    return true;
}


bool SortedBag::search(TComp elem) const {
    Node * current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            return current->elem.first;
            break;
        }
        current = current->next;
    }
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    Node * current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            return current->elem.second;
            break;
        }
        current = current->next;
    }
    return 0;
}


int SortedBag::size() const {
    int counter = 0;
    Node * current = head;
    while (current != nullptr) {
        counter += current->elem.second;
        current = current->next;
    }
	return counter;
}


bool SortedBag::isEmpty() const {
	return head == nullptr ;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}
