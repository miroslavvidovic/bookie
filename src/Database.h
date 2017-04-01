#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED value

void database_insert(char *url, char *tags, char *desc);
void database_install();
void database_select_all();
void database_select(char *id);
void database_delete(char *id);
void database_update(char *id, char *url, char *tags, char *desc);

#endif /* ifndef DATABASE_H_INCLUDED */
