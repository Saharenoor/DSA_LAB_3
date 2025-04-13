/*
Create a menu-based program for the following functions, using the class made in task 2, make a class
named as CustomList, having the following additional functionalities:
• Type sum_ofPrime(): It finds prime numbers in the list and calculates and returns the sum
of all prime numbers present in list.
• Type secondMaxEven(): It finds and returns the second maximum even number present in
list.
• Type secondMinOdd(): It finds and returns the second minimum odd number present in
list.
• void printDuplicates(): It finds and displays all the numbers which occur more than
once.
• void rotateClockwaise( int r): It divides the list into two parts (halves the list), and
rotate both parts “r” times in clockwise direction
• void rotateanitclockwaise( int rt) : It divides the list into two parts (halves the
list), and rotate both parts “rt” times in the anti-clockwise direction
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


template <typename Type>
class MyList : public List<Type> {
public:
    MyList(int size = 100) : List<Type>(size) {}

    MyList(const MyList& other) : List<Type>(other) {}

    ~MyList() {}

    void addElementAtFirstIndex(Type val) override {
        if (this->currentSize >= this->maxSize) return;
        for (int i = this->currentSize; i > 0; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[0] = val;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type val) override {
        if (this->currentSize >= this->maxSize) return;
        this->arr[this->currentSize++] = val;
    }

    Type removeElementFromEnd() override {
        if (this->currentSize == 0) throw runtime_error("List empty");
        return this->arr[--this->currentSize];
    }

    void removeElementFromStart() override {
        if (this->currentSize == 0) return;
        for (int i = 0; i < this->currentSize - 1; i++)
            this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }

    bool empty() { return this->currentSize == 0; }
    bool full() { return this->currentSize == this->maxSize; }
    int size() { return this->currentSize; }

    bool insertAt(int index, Type value) {
        if (index < 0 || index > this->currentSize || this->currentSize >= this->maxSize)
            return false;
        for (int i = this->currentSize; i > index; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    Type last() {
        if (this->currentSize == 0) throw runtime_error("List empty");
        return this->arr[this->currentSize - 1];
    }

    bool search(Type val) {
        for (int i = 0; i < this->currentSize; i++)
            if (this->arr[i] == val) return true;
        return false;
    }

    void print() {
        for (int i = 0; i < this->currentSize; i++)
            cout << this->arr[i] << " ";
        cout << endl;
    }
};

template <typename Type>
class CustomList : public MyList<Type> {
public:
    CustomList(int size = 100) : MyList<Type>(size) {}

    CustomList(const CustomList& other) : MyList<Type>(other) {}

    ~CustomList() {}

    bool isPrime(Type num) {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++)
            if (num % i == 0) return false;
        return true;
    }

    Type sum_ofPrime() {
        Type sum = 0;
        for (int i = 0; i < this->currentSize; i++)
            if (isPrime(this->arr[i])) sum += this->arr[i];
        return sum;
    }

    Type secondMaxEven() {
        Type max1 = INT_MIN, max2 = INT_MIN;
        for (int i = 0; i < this->currentSize; i++) {
            if (this->arr[i] % 2 == 0) {
                if (this->arr[i] > max1) {
                    max2 = max1;
                    max1 = this->arr[i];
                } else if (this->arr[i] > max2 && this->arr[i] != max1) {
                    max2 = this->arr[i];
                }
            }
        }
        return max2;
    }

    Type secondMinOdd() {
        Type min1 = INT_MAX, min2 = INT_MAX;
        for (int i = 0; i < this->currentSize; i++) {
            if (this->arr[i] % 2 != 0) {
                if (this->arr[i] < min1) {
                    min2 = min1;
                    min1 = this->arr[i];
                } else if (this->arr[i] < min2 && this->arr[i] != min1) {
                    min2 = this->arr[i];
                }
            }
        }
        return min2;
    }

    void printDuplicates() {
        cout << "Duplicates: ";
        bool found = false;
        for (int i = 0; i < this->currentSize; i++) {
            for (int j = i + 1; j < this->currentSize; j++) {
                if (this->arr[i] == this->arr[j]) {
                    cout << this->arr[i] << " ";
                    break;
                }
            }
        }
        cout << endl;
    }

    void rotateClockwise(int r) {
        int mid = this->currentSize / 2;
        rotatePart(this->arr, mid, r, true);
        rotatePart(this->arr + mid, this->currentSize - mid, r, true);
    }

    void rotateAnticlockwise(int r) {
        int mid = this->currentSize / 2;
        rotatePart(this->arr, mid, r, false);
        rotatePart(this->arr + mid, this->currentSize - mid, r, false);
    }

private:
    void rotatePart(Type* subArr, int len, int r, bool clockwise) {
        r %= len;
        if (!clockwise) r = len - r;
        reverse(subArr, subArr + len);
        reverse(subArr, subArr + r);
        reverse(subArr + r, subArr + len);
    }

    void reverse(Type* start, Type* end) {
        end--;
        while (start < end) {
            swap(*start, *end);
            start++; end--;
        }
    }
};

int main() {
    CustomList<int> list(20);
    int choice, value, index, rotateCount;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add at start\n2. Add at end\n3. Remove from end\n4. Remove from start\n";
        cout << "5. Insert at index\n6. Search\n7. Print list\n8. Sum of primes\n";
        cout << "9. Second max even\n10. Second min odd\n11. Print duplicates\n";
        cout << "12. Rotate clockwise\n13. Rotate anticlockwise\n0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: cout << "Value: "; cin >> value; list.addElementAtFirstIndex(value); break;
        case 2: cout << "Value: "; cin >> value; list.addElementAtLastIndex(value); break;
        case 3: cout << "Removed: " << list.removeElementFromEnd() << endl; break;
        case 4: list.removeElementFromStart(); break;
        case 5: cout << "Index & Value: "; cin >> index >> value;
            cout << (list.insertAt(index, value) ? "Inserted" : "Failed") << endl;
            break;
        case 6: cout << "Search: "; cin >> value; cout << (list.search(value) ? "Found" : "Not Found") << endl; break;
        case 7: list.print(); break;
        case 8: cout << "Sum of primes: " << list.sum_ofPrime() << endl; break;
        case 9: cout << "Second max even: " << list.secondMaxEven() << endl; break;
        case 10: cout << "Second min odd: " << list.secondMinOdd() << endl; break;
        case 11: list.printDuplicates(); break;
        case 12: cout << "Rotate times: "; cin >> rotateCount; list.rotateClockwise(rotateCount); break;
        case 13: cout << "Rotate times: "; cin >> rotateCount; list.rotateAnticlockwise(rotateCount); break;
        }
    } while (choice != 0);

    return 0;
}

