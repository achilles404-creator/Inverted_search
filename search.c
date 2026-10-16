#include "inverted_Search.h"

int search(Wlist *head, char *word)
{
    //check whether the list empty
    if(head == NULL)
    {
        printf("List is empty\n");
        return FAILURE;
    }
    
    // Non empty
    while(head)
    {
        if(!(strcmp(head->word, word)))
        {
            printf("Word %s is present in %d files\n\n", word, head->file_count);
            Ltable *Thead = head->Tlink;
            while(Thead)
            {
                printf("In file: %s %d times\n", Thead->file_name, Thead->word_count);
                Thead = Thead->table_link;
            }
            return SUCCESS;
        }
        head = head->link;
    }

    printf("Search word not found\n");
    return FAILURE;
}