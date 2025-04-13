/*
Create a C++ generic abstract class named List, with the following:
Attributes:
Type *arr;
int maxSize;
int currentSize;
Functions:
a. virtual void addElementAtFirstIndex(Type) = 0;
// Should add the element at the first position of the List
b. virtual void addElementAtLastIndex(Type) = 0;
// Should add the element at the last position of the List
c. virtual Type removeElementFromEnd() = 0;
// Should remove the element from the last position of the
List
d. virtual void removeElementFromStart() = 0;
//Should remove the element from the first position of the
List
• Write a parameterized constructor with default arguments for the above class.
• Write a copy constructor for the above class.
• Write destructor for the above class.
*/
#include <iostream>
using namespace std;

template <typename Type>
class List {
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    List(int size = 100) {
        maxSize = size;
        currentSize = 0;
        arr = new Type[maxSize];
    }

    List(const List& other) {
        maxSize = other.maxSize;
        currentSize = other.currentSize;
        arr = new Type[maxSize];
        for (int i = 0; i < currentSize; i++) {
            arr[i] = other.arr[i];
        }
    }

    virtual ~List() {
        delete[] arr;
    }

    virtual void addElementAtFirstIndex(Type) = 0;
    virtual void addElementAtLastIndex(Type) = 0;
    virtual Type removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;
};
