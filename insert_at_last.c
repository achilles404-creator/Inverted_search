#include "inverted_Search.h"

// Link the fname from create database
extern char *fname;

int insert_at_last(Wlist **head, data_t *data)
{
    // Create node, whether the list is empty or not
    Wlist *new = malloc(sizeof(Wlist));

    if (new == NULL)
    {
        return FAILURE;
    }

    // Update the fileds
    new->file_count = 1;
    strcpy(new->word, data);
    new->Tlink = NULL;
    new->link = NULL;
    
    update_link_table(&new);

    // Head is empty or not
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    // If non empty
    Wlist *temp = *head;
    while(temp->link)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int update_link_table(Wlist *head[])
{
    // Create node for L table node
    Ltable *new = malloc(sizeof(Ltable));
    if(new == NULL)
    {
        return FAILURE;
    }

    new->word_count = 1;
    strcpy(new->file_name, fname);
    new->table_link = NULL;

    // Link the new L table node to the Wlist node
    (*head)->Tlink = new;
    return SUCCESS;
}