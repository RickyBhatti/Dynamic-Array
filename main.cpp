#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.cpp"

int main() {
    // Planned on making actual tests, but I'm lazy. This shows the general concept of how it works, and that it works.
    DynamicArray<char> charArray;
    DynamicArray<int> intArray;

    charArray.add('a');
    charArray.add('b');
    charArray.add('c');
    charArray.add('d');
    charArray.add('e');
    charArray.add('f');

    charArray.remove(0);
    charArray.remove(0);
    charArray.remove(0);
    charArray.remove(0);
    charArray.remove(0);
    charArray.remove(0);

    printf(charArray.getCurrentIndex() == 0 ? "Passed\n" : "Failed\n");

    return 0;
}