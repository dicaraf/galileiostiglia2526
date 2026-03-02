#include <stdio.h>


int main() {
    int i = 1;

    while(i <= 10) {
        printf("Hai visto questo messaggio %d volte\n", i);
        i = i + 1;
    }
    
    printf("%d è troppo grande, fine while\n", i);
}