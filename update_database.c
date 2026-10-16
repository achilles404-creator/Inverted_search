#include "inverted_Search.h"

int update_database(Wlist *head[], Flist **f_head)
{
    char file_name[FNAME_SIZE];

    printf("Enter the filename: ");
    scanf("%s", file_name);

    // Check if file exists
    int empty = isFileEmpty(file_name);

    if (empty == FILE_NOTAVAILABLE)
    {
        printf("File %s is not available\n", file_name);
        return FAILURE;
    }
    else if (empty == FILE_EMPTY)
    {
        printf("File %s is empty\n", file_name);
        return FAILURE;
    }

    // Insert into file linked list
    int ret = create_list_file(f_head, file_name);

    if (ret == REPEATATION)
    {
        printf("File %s already exists in database\n", file_name);
        return FAILURE;
    }
    else if (ret == FAILURE)
    {
        printf("Unable to add file\n");
        return FAILURE;
    }

    printf("File %s added successfully\n", file_name);

    // Create database for this file only
    Flist *temp = *f_head;
    while(temp->link != NULL) // Traverse to the last node
    {
        temp = temp->link;
    }

    create_database(temp, head);
    
    return SUCCESS;
}
