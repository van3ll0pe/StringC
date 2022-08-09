#include "../include/stringc.h"

/**
 * @brief Init the variable StringC
 * 
 * @param str 
 * @return StringC 
 */
StringC StringC_init(char *str)
{
    StringC stringc;

    stringc.len = strlen(str);
    stringc.str = malloc(sizeof(char) * (stringc.len + 1));

    if (stringc.str == NULL)
    {
        fprintf(stderr, "Impossible to alloc memory for the string\n");
        exit(1);
    }

    strcpy(stringc.str, str);

    stringc.destroy = &stringc_destroy;
    stringc.append = &stringc_append;
    stringc.push_back = &stringc_push_back;
    stringc.clear = &stringc_clear;
    stringc.insert = &stringc_insert;
    stringc.assign = &stringc_assign;
    stringc.pop_back = &stringc_pop_back;
    stringc.dinsert = &stringc_dinsert;
    stringc.dinsert_limit = &stringc_dinsert_limit;
    stringc.find = &stringc_find;
    
    return stringc;
}





/**
 * @brief Function to free the buffer in the structure StringC
 * 
 * @param stringc 
 */
void stringc_destroy(StringC *stringc)
{
    free(stringc->str);
    stringc->str = NULL;
}




/**
 * @brief Function to append text of the stringc variable
 * 
 * @param stringc, str
 */
void stringc_append(StringC *stringc, char *str)
{
    
    char *tmp = malloc(sizeof(char) * (stringc->len + strlen(str) + 1));
    if (tmp == NULL) //si la reallocation mémoire a raté
    {
        fprintf(stderr, "Impossible to realloc memory for append text\n");
        free(stringc->str);
        exit(1);
    }
    stringc->len += strlen(str); //on va récupérer la nouvelle taille de la chaine de caractères
    strcpy(tmp, stringc->str);
    strcat(tmp, str);

    free(stringc->str); //on libère les anciennes adresses mémoires

    stringc->str = tmp; //et str pointe sur les nouvelles
}




/**
 * @brief Function to append only one caractere to the string
 * 
 * @param stringc 
 * @param letter 
 */
void stringc_push_back(StringC *stringc, char letter)
{

    char *tmp = malloc(sizeof(char) * (stringc->len + 2));
    if (tmp == NULL)
    {
        fprintf(stderr, "Impossible to alloc memory for append the caracter\n");
        free(stringc->str);
        exit(1);
    }
    stringc->len++;  //the caracter en plus
    strcpy(tmp, stringc->str);
    tmp[stringc->len - 1] = letter;
    tmp[stringc->len] = '\0';

    free(stringc->str);
    stringc->str = tmp;

}



/**
 * @brief erase all the string to put a \0 on the index 0 of the array
 * 
 * @param stringc 
 */
void stringc_clear(StringC *stringc)
{
    free(stringc->str);


    stringc->str = malloc(sizeof(char) * 1);
    if (stringc->str == NULL)
    {
        fprintf(stderr, "Impossible to alloc memory to clear the text\n");
        exit(1);
    }
    stringc->len = 0;
    stringc->str[0] = '\0';

}

/**
 * @brief Add string on the existant string at the position index of the array string.
 * 
 * @param stringc 
 * @param str 
 * @param position 
 */
void stringc_insert(StringC *stringc, char *str, size_t position)
{
    if (position < 0 || position > stringc->len) {
        printf("Insert : invalid Position");
        return ;
    }

    char *tmp = malloc(sizeof(char) * (stringc->len + strlen(str) + 1));
    if (tmp == NULL)
    {
        fprintf(stderr, "Impossible to malloc memory to insert text\n");
        exit(1);
    }

    stringc->len += strlen(str);
    
    size_t i = 0; //parcourir stringc->str
    size_t j = 0; //parcourir str
    size_t l = 0; //parcourir tmp

    while (l < stringc->len)
    {
        if (l >= position && l < position + strlen(str))
        {
            tmp[l] = str[j];
            j++;
        }
        else
        {
            tmp[l] = stringc->str[i];
            i++;
        }

        l++;
    }
    
    tmp[l] = '\0';

    free(stringc->str);
    stringc->str = tmp;
}



/**
 * @brief Delete all the existant string to replace by another one
 * 
 * @param stringc 
 * @param str 
 */
void stringc_assign(StringC *stringc, char *str)
{
    char *tmp = malloc(sizeof(char) *(strlen(str) + 1));

    if (tmp == NULL)
    {
        free(stringc->str);
        fprintf(stderr, "Impossible to malloc in assign function\n");
        exit(1);
    }

    strcpy(tmp, str);

    free(stringc->str);
    stringc->str = tmp;

    stringc->len = strlen(tmp);
}


/**
 * @brief Delete the last caractere of the string and if the string is empty, nothing is done
 * 
 * @param stringc 
 */
void stringc_pop_back(StringC *stringc)
{ 
    if (stringc->len <= 0)
    {
        fprintf(stderr, "Impossible to delete last caracter because there isn't caractere\n");
        return ;
    }

    char *tmp = malloc(sizeof(char) * stringc->len); //pas le +1 car le \0 ira sur la position len-1
    if (tmp == NULL)
    {
        fprintf(stderr, "Impossible to malloc in the function pop_back\n");
        free(stringc->str);
        exit(1);
    }

    for (size_t i = 0; i < stringc->len - 1; i++) //strlen - 1 pour s'arrêter au dernier caractère de nombre phrase len - 1 représente le \0 dans l'index du tableau
    {
        tmp[i] = stringc->str[i];
    }

    tmp[stringc->len - 1] = '\0';

    free(stringc->str);
    stringc->str = tmp;
    stringc->len--;

}




/**
 * @brief Allow to remove a part of the string from the position (index of the array) to the end of the string
 * If you put 0 for position then you will remove the sentence
 * 
 * @param stringc 
 * @param position 
 */
void stringc_dinsert(StringC *stringc, size_t position)
{
    if (position < 0 || position > stringc->len) //on vérifie si la position correspond au index du tableau
    {
        fprintf(stderr, "Position is invalid index of the array\n");
        return ;
    }

    if (stringc->len <= 0)  //on vérifie si le tableau est vide, ça ne sert à rien s'il est
    {
        fprintf(stderr, "Nothing to remove because the string is already empty\n");
        return ;
    }

    size_t difference = stringc->len - position;

    char *tmp = malloc(sizeof(char) * (stringc->len - difference + 1));

    if (tmp == NULL)
    {
        fprintf(stderr, "Impossible to malloc at the function dinsert\n");
        free(stringc->str);
        exit(1);
    }

    for (size_t i = 0; i < stringc->len - difference; i++)
    {
        tmp[i] = stringc->str[i];
    }

    tmp[stringc->len - difference] = '\0';


    stringc->len -= difference;
    free(stringc->str);
    stringc->str = tmp;
}

/**
 * @brief Remove the part of string between start and end position on the array.
 * 
 * 
 * @param stringc 
 * @param start 
 * @param end 
 */
void stringc_dinsert_limit(StringC *stringc, size_t start, size_t end)
{
    if (start < 0 || start > stringc->len) //check des limites pour le début
    {
        fprintf(stderr, "Start position is out of the string index\nNothin is done\n");
        return ;
    }

    if (end < start || end > stringc->len) //check si la fin n'est pas avant la position de départ et si il ne sort pas (mais end peut-être égal à start)
    {
        fprintf(stderr, "End position is false\nNothing is done\n");
        return ;
    }

    if (stringc->len <= 0) //check if the string is empty
    {
        fprintf(stderr, "Nothing to remove because the string is already empty\n");
        return ;
    }

    size_t difference = end - start + 1; //le +1 permet de comprendre le dernier caractère à supprimer
    char *tmp = malloc(sizeof(char) * (stringc->len - difference + 1)); //le +1 permet de mettre le \0

    if (tmp == NULL)
    {
        fprintf(stderr, "Impossible to malloc at the function dinsert\n");
        free(stringc->str);
        exit(1);
    }

    size_t i = 0; //parcourir tmp
    size_t j = 0; //parcourir stringc->str

    while (j < stringc->len)
    {
        if (!(j >= start && j <= end))
        {
            tmp[i] = stringc->str[j];
            i++;
        }
        j++;
    }
    
    tmp[stringc->len - difference] = '\0';

    stringc->len = stringc->len - difference;
    free(stringc->str);
    stringc->str = tmp;
}


/**
 * @brief Function to find the string given in parameter in the string type of stringc.
 * The research begin from the index 0 of the string (stringc) ands if the string is found the function return the memory address of the string founded
 * in stringc else it returns NULL.
 * 
 * The parameter occurence allow to find other occurence in the stringc.
 * Because if the occurence is NULL, the function will always find the first occurence and return it, but if you give to occurence the memory address of the string founded
 * in stringc, the function will find the next occurence after the one.
 * 
 * @param stringc 
 * @param str 
 * @return char* 
 */
char *stringc_find(StringC *stringc, char *str, char *occurence)
{

    if (!((occurence >= stringc->str && occurence <= (stringc->str + stringc->len)) || (occurence == NULL))) //si occurence n'est pas une adresse comprise dans le tableau de char de stringc
    {
        fprintf(stderr, "Occurence invalid\n");
        return NULL;
    }

    
    int j; //parcourir str

    if (occurence == NULL) //si c'est null on commence au début
    {
        j = 0;

        for (int i = 0; stringc->str[i] != '\0'; i++) {

            if (stringc->str[i] == str[j]) {
                j++;
            } else {
                j = 0;
            }

            if (j == strlen(str)) {
                return ((stringc->str + i) - (strlen(str) - 1));
            }
        }
        
    }
    else    //sinon on commence à partir de l'adresse trouvé
    {
        j = 0;
        for (; *occurence != '\0'; occurence++) { //je parcours avec le pointeur occurence car je ne connais pas sa position I dans la chaîne de caractère. Je modifie la valeur de occurence mais ça importe peu car ce n'est qu'un paramètre qui ne modifie rien
            
            if (*occurence == str[j]) {
                j++;
            } else {
                j = 0;
            }

            if (j == strlen(str)) {
                return (occurence - (strlen(str) - 1));
            }
        }

    }

    return NULL;
}

  