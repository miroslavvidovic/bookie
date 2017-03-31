#include <stdio.h>
#include <sqlite3.h> 
#include <string.h>
#include "Logger.h"
#include "Database.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/**
 *
 */
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    printf(RED"%s"RESET")"GRN" %s"BLU " =>"RESET " %s\n",argv[0], argv[1], argv[2]);
    return 0;
}

/**
 *  connect to the database
 */
void sqlite_connect(struct sqlite3 **db)
{
    char *dbpath = "/home/miroslav/bookie/bookmarks.db";
    int rc;

    rc = sqlite3_open(dbpath, *(&db));

    if( rc ){
        const char *logMsg = sqlite3_errmsg(*db);
        logger(logMsg, "ERROR");
    }else{
        logger("opened database successfully", "SUCCESS");
    }
}

/**
 *  disconnect from the database
 */
void sqlite_disconnect(struct sqlite3 **db)
{
    int rc = sqlite3_close(*db);
    if (rc == 0){
        logger("database closed", "SUCCESS");
    }
}

/**
 *  insert a bookmark into the database
 */
void sqlite_insert(char *url, char *tags, char *desc, char *tstamp)
{
    sqlite3 *db = NULL;
    char *zErrMsg = 0;
    int rc;

    sqlite_connect(&db);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "INSERT INTO BOOKMARK (URL,TAGS,DESC,TIMESTAMP) VALUES (?1,?2,?3,?4);", -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, url, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, tags, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, desc, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, tstamp, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if( rc != SQLITE_DONE ){
        logger(zErrMsg, "ERROR");
        sqlite3_free(zErrMsg);
    }else{
        logger("records created", "SUCCESS");
    }

    sqlite3_finalize(stmt);

    sqlite_disconnect(&db);
}

/**
 * Select all the bookmarks
 */
void sqlite_select_all()
{
    char *zErrMsg = 0;
    sqlite3 *db = NULL;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    sqlite_connect(&db);

    /* Create SQL statement */
    sql = "SELECT * from BOOKMARK";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ){
        logger(zErrMsg, "ERROR");
        sqlite3_free(zErrMsg);
    }else{
        logger("select query successful", "SUCCESS");
    }

    sqlite_disconnect(&db);
}


/* Create the database table */
void sqlite_create_table()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
    char *sql;

    sqlite_connect(&db);

    /* Create SQL statement */
    sql = "CREATE TABLE BOOKMARK("  \
           "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
           "URL            TEXT    NOT NULL,  " \
           "TAGS           TEXT,              " \
           "DESC           TEXT    DEFAULT ''," \
           "TIMESTAMP      TEXT               " \
           ");";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        logger(zErrMsg, "ERROR");
        sqlite3_free(zErrMsg);
    }else{
        logger("table created", "SUCCESS");
    }

    sqlite_disconnect(&db);
}

/* Select a bookmark by id */
void sqlite_select_by_id(char *id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    sqlite3_stmt *stmt;

    sqlite_connect(&db);

    char *sql = "SELECT * FROM BOOKMARK WHERE ID = ?1";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if( rc == SQLITE_OK ){
        logger("operation done successfully", "SUCCESS");
        sqlite3_bind_text(stmt, 1, id, -1, SQLITE_TRANSIENT);
    }else{
        logger(zErrMsg, "ERROR");
        sqlite3_free(zErrMsg);
    }

    int step = sqlite3_step(stmt);

    if (step == SQLITE_ROW) {
        printf("%s: ", "ID");
        printf("%s\n", sqlite3_column_text(stmt, 0));
        /* printf("%s:", "url"); */
        printf(GRN"%s\n"RESET, sqlite3_column_text(stmt, 1));
        printf("%s: ", "tags");
        printf("%s\n", sqlite3_column_text(stmt, 2));
        printf("%s: ", "description");
        printf("%s\n", sqlite3_column_text(stmt, 3));
        printf("%s: ", "created on");
        printf("%s", sqlite3_column_text(stmt, 4));
    } 

    sqlite3_finalize(stmt);

    sqlite_disconnect(&db);
}


void sqlite_delete(char *id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    sqlite3_stmt *stmt;

    sqlite_connect(&db);

    char *sql = "DELETE FROM BOOKMARK WHERE ID = ?1";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, id, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if( rc == SQLITE_DONE ){
        logger("operation done successfully", "SUCCESS");
    }else{
        logger(zErrMsg, "ERROR");
        sqlite3_free(zErrMsg);
    }

    sqlite3_finalize(stmt);

    sqlite_disconnect(&db);
}

sqlite_update(char *id, char *url, char *tags, char *desc)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    sqlite3_stmt *stmt;

    sqlite_connect(&db);

    char *sql = "UPDATE BOOKMARK set URL = ?1, TAGS = ?2, DESC = ?3 where ID = ?4; ";
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, url, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, tags, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, desc, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, id, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if( rc != SQLITE_DONE ){
        logger(zErrMsg, "ERROR");
        sqlite3_free(zErrMsg);
    }else{
        logger("records updated", "SUCCESS");
    }

    sqlite3_finalize(stmt);

    sqlite_disconnect(&db);
}

