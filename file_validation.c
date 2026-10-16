#include"inverted_Search.h"

void file_validation_list(Flist **f_head, char *argv[])
{
    int i = 1 , empty;
    while(argv[i] != NULL)
    {
        empty = isFileEmpty(argv[i]);
        if(empty == FILE_NOTAVAILABLE)
        {
            printf("File : %s is not available.\n" , argv[i]);
            printf("Hence we are not adding that file into file linked list.\n");
            i++;
            continue;
        }
        else if(empty == FILE_EMPTY)
        {
            printf("File : %s is not having any content\n" , argv[i]);
            printf("Hence we are not adding that file into file linked list\n");
            i++;
            continue;
        }
        else
        {
            int ret_val = create_list_file(f_head , argv[i]);

            if(ret_val == SUCCESS)
            {
                printf("Successfully inserted the file %s into file linked list\n", argv[i]);
            }
            else if(ret_val == REPEATATION)
            {
                printf("This file %s is already present\n" , argv[i]);
            }
            else
            {
                printf("Failure\n");
            }
            i++;
            continue;
        }
    }
}

// Check the file availability and for file contents
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename , "r");
    if(fptr == NULL)
    {
        if(errno == ENOENT)
        {
            return FILE_NOTAVAILABLE;
        }
    }
    fseek(fptr , 0 , SEEK_END);
    if(ftell(fptr) == 0)
    {
        fclose(fptr);
        return FILE_EMPTY;
    }

    fclose(fptr);
    return SUCCESS;
}

// Creating linked list(insert_last())
int create_list_file(Flist **f_head, char *name)
{
    Flist *temp = *f_head;
    Flist *new = malloc(sizeof(Flist));

    if (new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->file_name, name);
    new->link = NULL;

    // If list is empty
    if (*f_head == NULL)
    {
        *f_head = new;
        return SUCCESS;
    }

    // Check for duplicate
    while (temp != NULL)
    {
        if (strcmp(temp->file_name, name) == 0)
        {
            free(new);
            return REPEATATION;
        }
        if (temp->link == NULL)
            break;
        temp = temp->link;
    }

    // Insert at last
    temp->link = new;
    return SUCCESS;
}

