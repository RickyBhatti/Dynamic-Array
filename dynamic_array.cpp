#include "stdio.h" // printf
#include "stdlib.h" // malloc, realloc, free

template <typename T>
class DynamicArray {
private:
    #pragma region Private Variables
    // Array 
    T *array;

    // Interal values
    int startingSize, currentIndex, currentSize;
    #pragma endregion Private Variables

    #pragma region Interal Methods
    /**
     * @brief Validates the array size, and expands or shrinks the array as needed.
     * 
     */
    void validateArraySize() {
        // Increase the size of the array if the current index is equal to the current size
        if (this->currentIndex == this->currentSize) {
            this->currentSize *= 2;
            this->array = (T *) realloc(this->array, sizeof(T) * this->currentSize);
            printf("Reallocated array to size %d\n", this->currentSize);
        }

        // Decrease the size of the array if it's not more than 50% full. (Also ensures that the array never gets smaller than the starting size.)
        if (this->currentSize > this->startingSize && this->currentSize / 2 > this->currentIndex) {
            this->currentSize /= 2;
            this->array = (T *) realloc(this->array, sizeof(T) * this->currentSize);
            printf("Reallocated array to size %d\n", this->currentSize);
        }
    }
    #pragma endregion Interal Methods
public:
    #pragma region Constructors
    /**
     * @brief Construct a new Dynamic Array object
     * 
     */
    DynamicArray() {
        this->currentIndex = 0;
        this->currentSize = 1;
        this->startingSize = 1;

        this->array = (T *) malloc(sizeof(T) * this->currentSize);
    }

    /**
     * @brief Construct a new Dynamic Array object
     * 
     * @param startingSize The starting size of the array
     */
    DynamicArray(int startingSize) {
        this->currentIndex = 0;
        this->currentSize = startingSize;
        this->startingSize = startingSize;

        this->array = (T *) malloc(sizeof(T) * startingSize);
    }

    /**
     * @brief Construct a new Dynamic Array object
     * 
     * @param other The DynamicArray object to copy
     */
    DynamicArray(const DynamicArray<T> &toCopy) {
        this->currentIndex = toCopy.currentIndex;
        this->currentSize = toCopy.currentSize;
        this->startingSize = toCopy.startingSize;

        this->array = (T *) malloc(sizeof(T) * this->currentSize);
        for (int i = 0; i < this->getSize(); i++) { this->array[i] = toCopy.array[i]; }
    }
    #pragma endregion Constructors

    #pragma region Destructor
    /**
     * @brief Destroy the Dynamic Array object
     * 
     */
    ~DynamicArray() {
        free(this->array);
    }
    #pragma endregion Destructor

    #pragma region Public Methods
    /**
     * @brief Adds an item to the end of the array
     * 
     * @param toAdd The item to add
     */
    void add(T toAdd) {
        this->validateArraySize();

        this->array[this->currentIndex] = toAdd;
        this->currentIndex++;
    }

    /**
     * @brief Removes an item from the array at the specified index
     * 
     * @param index The index of the item to remove
     */
    void remove(int index) {
        if (index < 0 || index >= this->currentIndex) { printf("Error: Index out of bounds.\n"); return; }
        
        for (int i = index; i < this->currentIndex - 1; i++) { this->array[i] = this->array[i + 1]; }

        this->currentIndex--;
        this->validateArraySize();
    }

    /**
     * @brief Push an item to the end of the array
     * 
     * @param toAdd The item to add
     */
    void push(T toAdd) {
        this->validateArraySize();

        this->array[this->currentIndex] = toAdd;
        this->currentIndex++;
    }

    /**
     * @brief Pops the last item from the array
     * 
     */
    void pop() {
        if (this->currentIndex == 0) { printf("Error: Array is empty.\n"); return; }

        this->currentIndex--;
        this->validateArraySize();
    }

    /**
     * @brief Push an item to the front of the array
     * 
     * @param toAdd The item to add
     */
    void push_front(T toAdd) {
        this->validateArraySize();

        for (int i = this->currentIndex; i > 0; i--) { this->array[i] = this->array[i - 1]; }

        this->array[0] = toAdd;
        this->currentIndex++;
    }

    /**
     * @brief Pops the first item from the array
     * 
     */
    void pop_front() {
        if (this->currentIndex == 0) { printf("Error: Array is empty.\n"); return; }

        for (int i = 0; i < this->currentIndex - 1; i++) { this->array[i] = this->array[i + 1]; }

        this->currentIndex--;
        this->validateArraySize();
    }

    /**
     * @brief Clears the array
     * 
     */
    void clear() { // Unsure if this method will even work, but I'll figure it out later.
        this->currentIndex = 0;
        this->validateArraySize();
    }
    #pragma endregion Public Methods

    #pragma region Getters
    /**
     * @brief Gets the item at the specified index
     * 
     * @param index The index of the item to get
     * @return const T The item at the specified index
     */
    const T get(int index) {
        if (index < 0 || index >= this->currentIndex) { printf("Error: Index out of bounds.\n"); return 0; }

        return this->array[index];
    }

    /**
     * @brief Get the starting size of the object
     * 
     * @return const int The starting size of the array
     */
    const int getStartingSize() {
        return this->startingSize;
    }

    /**
     * @brief Get the current "size" of the object (How many items are in the array)
     * 
     * @return const int The current "size" of the array
     */
    const int getSize() {
        return this->currentIndex;
    }

    /**
     * @brief Get the current index object
     * 
     * @return const int The current index
     */
    const int getCurrentIndex() {
        return this->currentIndex;
    }

    /**
     * @brief Get the actual size of the array (How many items the array can hold)
     * 
     * @return const int The actual size of the array
     */
    const int getActualSize() {
        return this->currentSize;
    }
    #pragma endregion Getters

    #pragma region Setters
    /**
     * @brief Sets the item at the specified index
     * 
     * @param index The index of the item to set
     * @param toSet The value to set the item to
     */
    void set(int index, T toSet) {
        this->array[index] = toSet;
    }
    #pragma endregion Setters
};