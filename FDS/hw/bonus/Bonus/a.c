#include <stdio.h>

Index Hash3(const char *x, int TableSize) {
    unsigned int HashVal = 0;
    while (*x != '\0') 
        HashVal = (HashVal << 5) + *x++;
    return HashVal % TableSize;
}

int main() {
    const char *str = "abc";
    int tableSize = 10;
    Index hashValue = Hash3(str, tableSize);

    printf("String: %s\n", str);
    printf("TableSize: %d\n", tableSize);
    printf("Hash Value: %d\n", hashValue);

    return 0;
}
