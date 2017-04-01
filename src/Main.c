#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h> 
#include <string.h>

#include "Database.h"
#include "Helpers.h"

void print_usage()
{
    printf("\n%s\n", "bookie usage:");
    printf("%s\n", "    -l          list of all saved bookmarks");
    printf("%s\n", "    -a          add a new bookmark");
    printf("%s\n", "    -b [id]     detailed view of a bookmark by id number");
    printf("%s\n", "    -d [id]     delete a bookmark by id number");
    printf("%s\n", "    -u [id]     update a bookmark by id number");
    printf("%s\n", "    -i          install the database");
    printf("%s\n", "    -h          help");
}

int main(int argc, char *argv[])
{
    int opt;
    int index;

    char *id;
    char url[100];
    char tags[100];
    char desc[100];

    while ((opt = getopt(argc, argv, "ab:d:ilu:h")) != -1) 
    {
        switch (opt)
        {
            case 'l':
                database_select_all();
                break;
            case 'a':
                printf("%s\n","New bookmark");
                separator('-',20);

                get_input("Url", url); 
                get_input("Tags", tags); 
                get_input("Description", desc); 

                database_insert(url, tags, desc);
                break;
            case 'b':
                printf("%s\n","Bookmark details");
                separator('-',20);
                id = optarg;
                database_select(id);
                break;
            case 'd':
                printf("%s\n","Deleting a bookmark");
                id = optarg;
                database_delete(id);
                break;
            case 'i':
                printf("%s\n", "Installing the database");
                database_install();
                break;
            case 'u':
                printf("%s\n","Update a bookmark");
                separator('-',20);
                id = optarg;

                printf("%s\n", "* Existing values:");
                database_select(id);

                printf("%s\n", "* Enter new data:");
                get_input("Url", url); 
                get_input("Tags", tags); 
                get_input("Description", desc); 

                database_update(id, url, tags, desc);
                break;
            case 'h':
                print_usage();
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
