/*
Create a menu-based program for the following functions, using the class made in task 1; make a class
named as MyList, having the following additional functionalities:
• bool empty(): Returns whether the MyList is empty or not
• bool full(): Returns whether the MyList is full or not
int size(): Returns the current size of the MyList
• bool insertAt(int index, T value): Adds a value at the index passed to the function,
returns true if the index is present and value is added else returns false.
Type last(): Returns the last element of the MyList
• bool search(Type): Returns true if the searched value is present in the list else returns false
• Write a parameterized constructor with default arguments for the above class.
• Write a copy constructor for the above class.
• Write destructor for the above class.
*/
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
