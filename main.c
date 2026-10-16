#include "inverted_Search.h"

int main(int argc, char *argv[])
{
    system("clear");
    // Validate CLA
    if (argc <= 1)
    {
        printf("Enter the valid number of arguents\n");
        printf("./Inverted.exe file1.txt file2.txt.......\n");
        return 0;
    }

    // Create a head pointer for linked list creation
    Flist *f_head = NULL;
    // Array of structre to map all the words from files
    Wlist *head[27] = {NULL};

    // validation of CLA(Availability, File content, Duplicate files)
    file_validation_list(&f_head, argv);

    if (f_head == NULL)
    {
        printf("No files added to file linked list\n");
        printf("Hence process got terminated\n");
        return 1;
    }

    int choice, created = 0;
    char word[WORD_SIZE];

    do
    {
        printf("\nSelect your choice among following options:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search Database\n");
        printf("5. Save Database\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number. ");
            while(getchar() != '\n');
            choice = -1;
        }

        switch (choice)
        {
            case 1:
                if(created == 0)
                {
                    create_database(f_head, head);
                    printf("Database created successfully\n");
                    created = 1;
                }
                else
                {
                    printf("Database already created. Use Update Database to add more files.\n");
                }
                break;

            case 2:
                display_database(head);
                break;

            case 3:
                update_database(head, &f_head);
                break;

            case 4:
                printf("Enter the word to search: ");
                scanf("%s", word);
                int index = tolower(word[0]) % 97;
                search(head[index], word);
                break;

            case 5:
                save_database(head);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}