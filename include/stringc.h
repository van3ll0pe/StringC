#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StringC StringC;

struct StringC {
    char *str;          //the string
    size_t len;         //the len of the string

    void (*destroy)(StringC *stringc);                                  //pointer of function stringc_destroy
    void (*append)(StringC *stringc, char *str);                        //pointer of function stringc_append_end
    void (*push_back)(StringC *stringc, char letter);                   //pointer of function stringc_push_back
    void (*clear)(StringC *stringc);                                    //pointer of function stringc_clear
    void (*insert)(StringC *stringc, char *str, size_t position);       //pointer of function stringc_insert
    void (*assign)(StringC *stringc, char *str);                        //pointer of function stringc_assign
    void (*pop_back)(StringC *stringc);                                 //pointer of function stringc_pop_back
    void (*dinsert)(StringC *stringc, size_t position);                 //pointer of function stringc_dinsert
    void (*dinsert_limit)(StringC *stringc, size_t start, size_t end);  //pointer of function stringc_dinsert_limit
    char *(*find)(StringC *stringc, char *str, char *occurence); //pointer of function stringc_find
};


//---- prototypes --------------

StringC StringC_init(char *str);
void stringc_destroy(StringC *stringc);
void stringc_append(StringC *stringc, char *str);
void stringc_push_back(StringC *stringc, char letter);
void stringc_clear(StringC *stringc);
void stringc_insert(StringC *stringc, char *str, size_t position);
void stringc_assign(StringC *stringc, char *str);
void stringc_pop_back(StringC *stringc);
void stringc_dinsert(StringC *stringc, size_t position);
void stringc_dinsert_limit(StringC *stringc, size_t start, size_t end);
char *stringc_find(StringC *stringc, char *str, char *occurence);