#include "set.hpp"

/*
 * std::size_t is defined in the C++ standard library
 * std::size_t is an unsigned integer type that can store the maximum size of any possible object
 * sizes are non-negative integers -- i.e. unsigned integer type
 */

/* *********** class Node ************ */

// This class is private to class Set
// but all class Node members are public to class Set
class Set::Node {
public:
    // Constructor
    Node(int nodeVal = 0, Node* nextPtr = nullptr) : value{nodeVal}, next{nextPtr} {
        ++count_nodes;
    }

    // Destructor
    ~Node() {
        --count_nodes;
        assert(count_nodes >= 0);  // number of existing nodes can never be negative
    }
    int value;
    Node* next;

    // Total number of existing nodes -- used only to help to detect bugs in the code
    // Cannot be used in the implementation of any member functions
    static std::size_t count_nodes;

    friend std::ostream& operator<<(std::ostream& os, const Set& rhs);
};

/* ************************************ */

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* *********** class Set member functions ************ */

// Default constructor
Set::Set() : head{new Node{}}, counter{0} {  // create the dummy node
}

// Constructor for creating a singleton {x}
Set::Set(int x) : Set() {
    head->next = new Node{ x }; //insert node with value x
    counter = 1;
}

// Constructor: create a set with elements
// elements is not sorted and values in it may not be unique
Set::Set(const std::vector<int>& elements) : Set() { //dummy node
    for (int i : elements) { //goes through the every element in the vector
        // is the current value of the element in the vector
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr && curr->value < i) {//to keep adding the values that are less then i
            prev = curr;
            curr = curr->next;
        }
        if (curr != nullptr && curr->value == i) continue; //skipps if already the value isin the list

        prev->next = new Node(i, curr);
        ++counter; //dont forget the counter if aleady one is programed
    }
}

// copy constructor
Set::Set(const Set& rhs) : Set() {
    Node* curr = rhs.head->next; //skipps the dummy node to the first real node
    Node* tail = head; //pointer that starts at the dummy node
    while (curr != nullptr) { // go throuhg the list and copy every node while curr exists
        tail->next = new Node{ curr->value };
        curr = curr->next; //bättre att ha två pointer istället för att ha en och bli förvirrad
    }//måste finnas två pointers för curr gäller för rhs och tail gäller för den nya listan som copieras av rhs
    counter = rhs.counter; //glöm ej counter om det finns med i classen
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) {
    std::swap(head, rhs.head); //swap pointers to swap the lists
    std::swap(counter, rhs.counter); //since counter is in the class it needs to be swapepd
    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* curr = head; //start at dummy node
    while (curr != nullptr) {
        Node* temp = curr; //sent temp to curr
        curr = curr->next; //move it before deleting temp 
        delete temp; //delete temp and in the process curr
    }
}

// Return number of elements in the set
std::size_t Set::cardinality() const {
    return counter;  // delete, if needed
}

// Test if set is empty
bool Set::empty() const {
    if (counter == 0) {
        return true;
    }
    return false;
      // delete, if needed
}

// Test if x is an element of the set
bool Set::member(int x) const {
    Node* ptr = head->next; //skip the dummy node and start at the first real node
    while (ptr != nullptr && ptr->value != x) { //go thorugh list
        if (ptr->value > x) { return false; } //can do this since the list is sorted
        ptr = ptr->next;
    }
    if (ptr == nullptr) { return false; } //end of the list
    return true;
}

// Return true, if *this is a subset of Set b
// Otherwise, false is returned
bool Set::is_subset(const Set& b) const {
    Node* ptr = this->head->next; //pointer to go thorugh the current set
    Node* bptr = b.head->next; //pointer to go thorugh set b

    while (ptr != nullptr && bptr != nullptr) {
        if (ptr->value == bptr->value) {
            ptr = ptr->next;
            bptr = bptr->next;
        }
        else if (ptr->value < bptr->value) {//ptr samller this not in b hence this not a subset of b
            ptr = ptr->next;
            return false;
        }
        else {
            bptr = bptr->next;
        }
    }
    return true;
    
}

// Return a new Set representing the union of Sets *this and b
// Repeated values are not allowed
// Implement an algorithm similar to the one in exercise 3/Set 1, but don't use vectors
Set Set::set_union(const Set& b) const {
    Set newset; //an empty new set
    Node* ptr = this->head->next; //pointer to current set this
    Node* bptr = b.head->next; //pointer to b
    Node* curr = newset.head; //pointer to new set

    //go thorugh both sets at the same time
    while (ptr != nullptr && bptr != nullptr) {

        //if both have the same value only add one to the union not two of the sam value
        if (ptr->value == bptr->value) {
            curr->next = new Node(ptr->value);
            curr = curr->next;
            newset.counter++;
            ptr = ptr->next;
            bptr = bptr->next;
        }

        //this set smaller add to union 
        else if (ptr->value < bptr->value) {
            curr->next = new Node(ptr->value);
            curr = curr->next;
            ptr = ptr->next;
            newset.counter++;
        }

        //b set smaller add to union
        else {
            curr->next = new Node(bptr->value);
            curr = curr->next;
            bptr = bptr->next;
            newset.counter++;
        }
    }

    //if the sets are not the same length

    //Go thorugh the remaning nodes in this if b is fully done
    while (ptr != nullptr) {
        curr->next = new Node(ptr->value);
        curr = curr->next;
        ptr = ptr->next;
        newset.counter++;
    }

    //Go thorugh the remaning nodes in b if this is fully done
    while (bptr != nullptr) {
        curr->next = new Node(bptr->value);
        curr = curr->next;
        bptr = bptr->next;
        newset.counter++;
    }
    return newset;  // delete, if needed
}

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
    Set newset; //empty new set
    Node* ptr = this->head->next; //pointer to current list this
    Node* bptr = b.head->next; //pointer to list b
    Node* curr = newset.head; //pointer to newSet

    //Go thorugh both lists
    while (ptr != nullptr && bptr != nullptr) {
        //ptr smaller so it cannot be an intersection
        if (ptr->value < bptr->value) {
            ptr = ptr->next;
        }
        //bptr is smaller and cannot be in the intersection
        else if (bptr->value < ptr->value) {
            bptr = bptr->next;
        }

        //values match so it is added to the intercation
        else {
            curr->next = new Node(ptr->value);
            newset.counter++;
            curr = curr->next;

            ptr = ptr->next;
            bptr = bptr->next;
        }
    }

    return newset;  // delete, if needed
}

// Return a new Set representing the difference between Set *this and Set b
Set Set::set_difference(const Set& b) const {
    Set newset; //empty new set
    Node* ptr = this->head->next; //pointer to current set this
    Node* bptr = b.head->next;//pointer to the set b
    Node* curr = newset.head; //pointer to the newSet

    //Go thorugh all the elements in this
    while (ptr != nullptr) {

        //case 1: ptr->value is not in b add it to new set
        if (bptr == nullptr || ptr->value < bptr->value) {
            curr->next = new Node(ptr->value);
            curr = curr->next;
            ptr = ptr->next;
            newset.counter++;
        }

        //case 2: ptr->value is in b so it is skipped
        else if (ptr->value == bptr->value) {
            bptr = bptr->next;
            ptr = ptr->next;
        }


        //case 3: bptr->value is smaller so move bptrto ctach up
        else {
            bptr = bptr->next;
        }
    }



    return newset;  // delete, if needed
}

std::ostream& operator<<(std::ostream& os, const Set& rhs) {
    if (rhs.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* ptr = rhs.head->next;
        os << "{ ";

        while (ptr != nullptr) {
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/
