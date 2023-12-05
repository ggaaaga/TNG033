#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set() : head(new Node{ 0, nullptr }), counter{ 0 } {

}

// Constructor for creating a set from an int
Set::Set(int v) : Set{} {
    Node* newNode = new Node(v, nullptr);
    head->next = newNode;
    counter++;
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) : Set{} {

    //Make list
    for (size_t i = 0; i < V.size(); i++)
    {
        Node* newNode = head;
        while (newNode->next != nullptr && newNode->next->value < V[i]) {

            newNode = newNode->next;
        }

        if (newNode->next == nullptr || newNode->next->value != V[i])
        {
            insert(newNode, V[i]);
        }
    }
}

// copy constructor (deep copy)
Set::Set(const Set& source) : Set{} {

    Node* ptr1 = source.head->next;
    Node* ptr2 = head;

    while (ptr1 != nullptr) {
        insert(ptr2, ptr1->value);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    //counter = source.counter;
}

// Assignment operator: copy-and-swap idiom
Set& Set::operator=(Set s) {

    std::swap(head, s.head);
    std::swap(counter, s.counter);

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {

    Node* ptr = head; //Hoppa över dummy

    while (ptr != nullptr) {
        head = ptr->next;
        remove(ptr); //funktion för delete mst ha
        ptr = head;
    }
}

// Return number of elements in the set
std::size_t Set::cardinality() const {

    return counter;
}

// Test if set is empty
bool Set::empty() const {

    if (counter != 0)
    {
        return false;
    }

    else
    {
        return true;
    }
}


// Test if x is an element of the set
bool Set::member(int x) const { //Behövs set?

    Node* ptr = head->next; // pekar på nästa node efter dummyn?

    while ((ptr != nullptr) && (ptr->value != x)) {
        ptr = ptr->next;
    }

    if (ptr == nullptr)
    {
        return false;
    }

    else
    {
        return true;
    }
}

bool Set::operator<=(const Set& S) const {

    Node* R = head->next;

    while (R != nullptr && S.member(R->value)) {
        R = R->next;
    }

    if (R == nullptr) {
        return true;
    }

    return false;
}

bool Set::operator==(const Set& S) const {

    if (operator<=(S)) {
        
        if (S.operator<=(*this)) {

            return true;
        }
    }

    return false;
}

bool Set::operator!=(const Set& S) const {

    if (operator==(S)) {
        return false;
    }

    return true;
}

bool Set::operator<(const Set& S) const {

    if (operator<=(S)) {

        if (S.counter > counter) {
            return true;
        }

        else {
            return false;
        }
    }
    return false;
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& S) const {
    std::vector<int> V;
    Node* ptr1 = S.head->next;
    Node* ptr2 = head->next;

    while (ptr1 != nullptr) {
        V.push_back(ptr1->value);
        ptr1 = ptr1->next;
    }

    while (ptr2 != nullptr) {
        V.push_back(ptr2->value);
        ptr2 = ptr2->next;
    }

    return Set{ V };
}

// Set intersection
Set Set::operator*(const Set& S) const {
    std::vector<int> V;
    Node* ptr = head->next;

    while (ptr != nullptr) {
        if (S.member(ptr->value)) {
            V.push_back(ptr->value);
        }
        ptr = ptr->next;
    }

    return Set{ V };
}

// Set difference
Set Set::operator-(const Set& S) const {
    std::vector<int> V;
    Node* ptr = head->next;

    while (ptr != nullptr) {
        if (!S.member(ptr->value)) {
            V.push_back(ptr->value);
        }
        ptr = ptr->next;
    }

    return Set{ V };
}

// set difference with set {x}
Set Set::operator-(int x) const {
    return Set::operator-(Set{ x });
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    }
    else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

void Set::insert(Node* p, int value) {

    Node* newNode = new Node(value, p->next);
    p->next = newNode;
    counter++;
}

void Set::remove(Node* ptr) {
    delete(ptr);
    counter--;
}