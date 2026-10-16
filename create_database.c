#include "inverted_Search.h"

char *fname;

void create_database(Flist *f_head, Wlist *head[])
{
    // Traversing through the file linked list
    while(f_head)
    {
        // Read each file one after the other
        read_datafile(f_head, head, f_head->file_name);
        f_head = f_head->link;
    }
}

// Function to read the content of file and create Wlist
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    int flag = 1; // Check for repeatancy
    FILE *fptr = fopen(filename, "r");
    char word[WORD_SIZE];
    fname = filename;

    if (fptr == NULL)
    {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    while(fscanf(fptr, "%14s", word) != EOF)
    {
        int index = tolower(word[0]) % 97;

        if(!(index >= 0  &&  index <= 25))
        {
            index = 26; // Numbers, digits, symbols
        }
        
        Wlist *temp = head[index];
        
        // Traversing in the list to find repeatancy
        while(temp)
        {
            if(!strcmp(temp->word, word)) // If the words are repeated
            {
                update_word_count(&temp, filename); 
                flag = 0;
                break;
            }
            temp = temp->link;
        }

        // If not repeated (or list was empty)
        if(flag == 1)
        {
            insert_at_last(&head[index], word);
        }
        
        flag = 1; // Reset flag for the next word
    }
    fclose(fptr);
    return NULL;
}

int update_word_count(Wlist **head, char *filename)
{
    if (*head == NULL)
        return FAILURE;

    Ltable *temp = (*head)->Tlink;
    Ltable *prev = NULL;

    // Traverse link table
    while (temp != NULL)
    {
        // If filename matches
        if (strcmp(temp->file_name, filename) == 0)
        {
            temp->word_count++;
            return SUCCESS;
        }
        prev = temp;
        temp = temp->table_link;
    }

    // If filename not found → create new Ltable node
    Ltable *new = malloc(sizeof(Ltable));
    if (new == NULL)
        return FAILURE;

    strcpy(new->file_name, filename);
    new->word_count = 1;
    new->table_link = NULL;

    // Increment file count
    (*head)->file_count++;

    // If no link table exists
    if ((*head)->Tlink == NULL)
    {
        (*head)->Tlink = new;
    }
    else
    {
        prev->table_link = new;
    }

    return SUCCESS;
}
