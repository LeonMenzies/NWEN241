#include <stdio.h>
#include "dbms.h"

int db_show_row(const struct db_table *db, unsigned int row)

{
    if (row < 0 || row > db->rows_total)
    {
        return 0;
    }
    struct album t = *db->table;

    printf("SIZE OF TABLE: %d\n", row);

    printf("    %d:%s:          %s:%d\n", t.id, t.title, t.artist, t.year);
    return 1;
}
