//
// Created by flori on 21/02/2023.
//

#ifndef STRCMP
# define STRCMP fastcmp
#endif

int STRCMP (const char *p1, const char *p2) {
    unsigned int i = 0;
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        i++;
    } while (c1 == c2 && i < 64);
    return c1 - c2;
}