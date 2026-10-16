#include "inverted_Search.h"

int save_database(Wlist *head[])
{
    char file_name[FNAME_SIZE];
    printf("Enter the file name: ");
    scanf("%s", file_name);

    // Open the file in write mode
    FILE *fptr = fopen(file_name, "w");

    // Validate file opening
    if (fptr == NULL)
    {
        printf("Error: Could not open file %s for writing.\n", file_name);
        return FAILURE;
    }

    for(int i = 0; i < 27; i++)
    {
        if(head[i] != NULL)
        {
            write_databasefile(head[i], fptr);
        }
    }

    // Close the file to save changes
    fclose(fptr);
    printf("Database saved successfully in %s\n", file_name);
    
    return SUCCESS;
}

void write_databasefile(Wlist *head, FILE *databasefile)
{
    // Traverse the Wlist (Word List) for the current index
    while (head != NULL)
    {
        int index = tolower(head->word[0]) % 97;
        if (index < 0 || index > 25)
        {
            index = 26;
        }

        // Write: #index;word;file_count;
        fprintf(databasefile, "#%d;%s;%d;", index, head->word, head->file_count);

        // Traverse the Link Table (Ltable)
        Ltable *temp = head->Tlink;
        while (temp != NULL)
        {
            // Write: file_name;word_count;
            fprintf(databasefile, "%s;%d;", temp->file_name, temp->word_count);
            temp = temp->table_link;
        }

        //Add a newline (and #)
        fprintf(databasefile, "#\n");

        head = head->link;
    }
}