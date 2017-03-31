#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h> 
#include <string.h>

#include "Database.h"

void get_input(char *input_message, char *input_var)
{
    printf("%s > ",input_message);
    fgets(input_var, 100, stdin);
    input_var[strlen(input_var) -1] = '\0';
}

void print_usage()
{
    printf("\n%s\n", "bookie usage:");
    printf("%s\n", "    -l          list of all saved bookmarks");
    printf("%s\n", "    -a          add a new bookmark");
    printf("%s\n", "    -b [id]     detailed view of a bookmark by id number");
    printf("%s\n", "    -d [id]     delete a bookmark by id number");
    printf("%s\n", "    -i          install the database");
    printf("%s\n", "    -u [id]     update a bookmark by id number");
}

int main(int argc, char *argv[])
{
    int opt;
    int index;

    char *id;
    char url[100];
    char tags[100];
    char desc[100];

    while ((opt = getopt(argc, argv, "ab:d:ilu:")) != -1) 
    {
        switch (opt)
        {
            case 'l':
                printf("%s\n", "All bookmarks");
                database_select_all();
                break;
            case 'a':
                printf("%s\n","New bookmark");

                get_input("Url", url); 
                get_input("Tags", tags); 
                get_input("Description", desc); 

                database_insert(url, tags, desc);
                break;
            case 'b':
                printf("%s\n","Select bookmark by id");
                id = optarg;
                database_select(id);
                break;
            case 'd':
                printf("%s\n","Delete a  bookmark by id");
                id = optarg;
                database_delete(id);
                break;
            case 'i':
                printf("%s\n", "Install the database.");
                database_install(id);
                break;
            case 'u':
                printf("%s\n","Update a bookmark");
                id = optarg;
                printf("%s\n", "Existing values:");
                database_select(id);
                printf("\n");
                printf("%s\n", "Enter new data:");
                get_input("Url", url); 
                get_input("Tags", tags); 
                get_input("Description", desc); 

                database_update(id, url, tags, desc);
                break;
            case ':':
                printf("%s\n","something bad" );
                return 1;
            case '?':
                printf("%s\n","Invalid option");
                return 1;
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    if (argc < 2){
        printf("%s\n", "No arguments given");
        print_usage();
    }

    for (index = optind; index < argc; index++)
        printf("Non-optional argument %s\n", argv[index]);

    return 0;
}
