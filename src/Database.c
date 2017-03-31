#include <sqlite3.h> 
#include <stdio.h> 
#include <sys/stat.h>
#include <sys/types.h>

#include "Sqlite.h"
#include "Logger.h"

/**
 * Create the directory, database inside the directory and the bookmark table
 * inside the database
 */
void database_install()
{
    int result = mkdir("/home/miroslav/bookie", 0777);

    if (result){
        logger("directory already exists or couldn't be created", "ERROR");
    }

    sqlite_create_table();
}

/**
 *  
 */
void database_insert(char *url, char *tags, char *desc)
{
    if (url[0] != '\0' && tags[0] != '\0') {
        char *tstamp = timestamp();
        sqlite_insert(url,tags,desc,tstamp);
    } else {
        printf("%s\n", "Url and tags can't be empty.");
    }
}

void database_update(char *id, char *url, char *tags, char *desc){
    if (url[0] != '\0' && tags[0] != '\0') {
        sqlite_update(id, url,tags,desc);
    } else {
        printf("%s\n", "Url and tags can't be empty.");
    }
}

void database_select(char *id){
    sqlite_select_by_id(id);
}

void database_select_all(){
    sqlite_select_all();
}

void database_delete(char *id){
    sqlite_delete(id);
}
