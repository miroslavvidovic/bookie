#ifndef SQLITE_H
#define SQLITE_H value

void sqlite_connect(struct sqlite3 **db);
void sqlite_disconnect(struct sqlite3 **db);
void sqlite_create_table();
void sqlite_insert(char *url, char *tags, char *desc, char *tstamp);
void sqlite_select_all();
void sqlite_select_by_id(char *id);
void sqlite_delete(char *id);
void sqlite_update(char *id, char *url, char *tags, char *desc);

#endif /* ifndef SQLITE_H */
