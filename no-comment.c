// no-comment.c
// Riešenie IJC-DU1, príklad B), 25.3.2024
// Autor: Ronald Bednár (xbednar00), FIT
// Preložené: Apple Clang 15.0.0

#include <stdio.h>
#include "error.h"

// Definovanie stavov, v ktorých sa môže program nachádzať
typedef enum { NORMAL, STRING, CHAR, LINE_COMMENT, BLOCK_COMMENT } State;

int main(int argc, char *argv[]) {
    // Kontrola, či bol na vstupe zadaný presne jeden argument (názov súboru)
    if (argc != 2) {
        error_exit("Použitie: %s <vstupný_súbor>\n", argv[0]);
    }

    // Pokus o otvorenie vstupného súboru na čítanie
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        error_exit("Chyba pri otváraní súboru\n");
    }

    int c, next; // Premenné pre uchovanie aktuálneho a nasledujúceho znaku
    State state = NORMAL; // Inicializácia stavu na NORMAL
    int backslash = 0; // Pomocná premenná pre sledovanie backslash (\)

    // Čítanie znakov až do konca súboru
    while ((c = getc(in)) != EOF) {
        switch (state) {
            case NORMAL:
                // V normálnom stave program hľadá začiatok komentárov, reťazca alebo znakových literálov
                if (c == '/') {
                    next = getc(in);
                    if (next == '/') {
                        state = LINE_COMMENT; // Začiatok single-line komentára
                    } else if (next == '*') {
                        state = BLOCK_COMMENT; // Začiatok blokového komentára
                    } else {
                        putchar(c); // Výpis znaku ak to nie je komentár
                        ungetc(next, in);
                    }
                } else if (c == '"') {
                    putchar(c);
                    state = STRING; // Začiatok reťazcového literálu
                } else if (c == '\'') {
                    putchar(c);
                    state = CHAR; // Začiatok znakového literálu
                } else {
                    putchar(c); // Výpis ostatných znakov
                }
                break;

            case STRING:
                // Spracovanie reťazcových literálov
                putchar(c);
                if (c == '\\') {
                    backslash = 1; //Zapamätanie spätného lomítka
                } else if (c == '"' && !backslash) {
                    state = NORMAL; // Návrat do normálneho stavu
                } else {
                    backslash = 0;
                }
                break;

            case CHAR:
                // Spracovanie znakových literálov
                putchar(c);
                if (c == '\\') {
                    backslash = 1;
                } else if (c == '\'' && !backslash) {
                    state = NORMAL;
                } else {
                    backslash = 0;
                }
                break;

            case LINE_COMMENT:
                //Spracovanie riadkových komentárov
                if (c == '\n' && !backslash) {
                    state = NORMAL;
                    putchar(c); // Výpis znaku nového riadka
                } else if (c == '\\' && !backslash) {
                    backslash = 1;
                } else {
                    backslash = 0;
                }
                break;

            case BLOCK_COMMENT:
                //Spracovanie blokových komentárov
                if (c == '*') {
                    next = getc(in);
                    if (next == '/') {
                        state = NORMAL; // Koniec blokového komentára
                    } else {
                        ungetc(next, in); // Vrátenie znaku, ak to nie je koniec komentára
                    }
                }
                break;

            default:

                break;
        }
    }

    fclose(in);
    return 0;
}
