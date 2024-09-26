#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STACKSIZE 30 
char stack[STACKSIZE]; // Global, but let's go with it
int top = 0;

void push(char x) {
    if (top == STACKSIZE)
        puts("Stack Full");
    else
        stack[top++] = x;
}

bool popExpect(char c) { // compare expected char on top with passed char
    return top && c == stack[--top];
}

bool chk(const char *str) {
    char *cp, pairs[] = "(){}[]"; // three important pairs
    bool isGood = true; // optimism

    for (int i = 0; isGood && str[i]; i++)
        // is this char one of the "special" ones?
        if ((cp = strchr(pairs, str[i])) != NULL) {
            int off = cp - pairs;
            // because "paired" 0,2,4 are open, 1,3,5 are close
            if (off % 2 == 0) // opening
                push(cp[1]); // push the close that matches this open
            else // special closing
                isGood = popExpect(str[i]); // does this close match?
        }

    return isGood && top == 0;
}

int main() {
    const char *s1 = "(foobar)({}){bar}[[[(foo)]]]"; // balanced
    const char *s2 = "(foobar)({}){ { bar}[[[(foo)]]]"; // unbalanced open
    const char *s3 = "(foobar)({}){ ] bar}[[[(foo)]]]"; // unbalanced close

    puts(chk(s1) ? "Balanced" : "Unbalanced");
    puts(chk(s2) ? "Balanced" : "Unbalanced");
    puts(chk(s3) ? "Balanced" : "Unbalanced");

    return 0;
}

