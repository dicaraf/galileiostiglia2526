#include <stdio.h>
#include <stdlib.h>
#include "libstring.h"
#include "libstring.c"

int main() {
    Stringa s1 = crea_stringa_dinamica('\n');
    Stringa s2 = crea_stringa_dimensionata(3);
    Stringa s3 = concatena_stringhe(s1, s2, ',');
    char c = 'a';
    printf("%s\n", s3);
    printf("%d\n", conta_occorrenze(s1, c));
    printf("%d\n", stringa_in_stringa(s1, s2));
}