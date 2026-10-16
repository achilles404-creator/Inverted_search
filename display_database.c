#include "inverted_Search.h"

void display_database(Wlist *head[])
{
    // Print the header with specific spacing
    printf("\n");
    printf("%-10s %-15s %-12s %-15s %-10s\n", 
           "[Index]", "[Word]", "[File Count]", "[File Name]", "[Word Count]");
    printf("----------------------------------------------------------------------\n");

    for(int i = 0; i < 27; i++)
    {
        if(head[i] != NULL)
        {
            print_word_count(head[i]);
        }
    }
    printf("----------------------------------------------------------------------\n");
}

int print_word_count(Wlist *head)
{
    // Traverse through the Wlist
    while(head != NULL)
    {
        // Calculate index
        int index = tolower(head->word[0]) % 97;
        if(!(index >= 0 && index <= 25))
        {
            index = 26;
        }
        printf("%-10d %-15s %-13d", index, head->word, head->file_count);

        // Traverse the Link Table (Ltable) for file details
        Ltable *Thead = head->Tlink;
        int first_file = 1;

        while(Thead)
        {
            if (!first_file)
            {
                printf("\n%-40s", ""); 
            }

            printf("%-15s %-10d", Thead->file_name, Thead->word_count);
            
            first_file = 0;
            Thead = Thead->table_link;
        }
        
        // End the row for this word
        printf("\n");
        
        head = head->link;
    }
    return SUCCESS;
}