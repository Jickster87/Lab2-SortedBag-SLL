#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    rel = r;
    head = nullptr;
    nrElems = 0;
}

void SortedBag::add(TComp e) {
    Node* current = head;
    Node* prev = nullptr;

    // Traverse the list to find the right position based on the relation
    while (current != nullptr && rel(current->elem.first, e)) {
        prev = current;
        current = current->next;
    }

    // Check if the element exists at the current position
    if (current != nullptr && current->elem.first == e) {
        current->elem.second++;  // Element already exists, increment its frequency
        return;  // Exit after incrementing
    }

    // Element does not exist, so create a new node for it
    TPair newElem = std::make_pair(e, 1);
    Node* newNode = new Node(newElem);

    // Insert the new node at the correct position in the list
    if (prev == nullptr) {
        // Insert at the head if we're at the start of the list
        newNode->next = head;
        head = newNode;
    } else {
        // Insert after the prev node
        prev->next = newNode;
        newNode->next = current;
    }

    // Increase the total number of elements
    nrElems++;
}

bool SortedBag::remove(TComp elem) {
    Node* currentNode = head;
    Node* prevNode = nullptr;

    // Traverse to find the element
    while (currentNode != nullptr && currentNode->elem.first != elem) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    // If element not found, return false
    if (currentNode == nullptr) {
        return false;
    }

    // Handle the removal of the node
    if (currentNode == head) {
        head = head->next;  // Remove head
    } else {
        prevNode->next = currentNode->next;  // Bypass the node to remove it
    }

    delete currentNode;  // Free the memory
    nrElems--;  // Decrease element count
    return true;
}

bool SortedBag::search(TComp elem) const {
    Node * current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            return current->elem.first;
        }
        current = current->next;
    }
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            return current->elem.second;  // Return the frequency
        }
        current = current->next;
    }
    return 0;  // Element not found
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
