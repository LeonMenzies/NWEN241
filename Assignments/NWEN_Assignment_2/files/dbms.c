#include <stdio.h>
#include <stdlib.h>
#include "dbms.h"

int db_show_row(const struct db_table *db, unsigned int row)

{
    struct album t = db->table[row];

    if (row < 0 || row > db->rows_used)
    {
        return 0;
    }

    //Print ID with padding
    int add = 6 - sizeof(t.id) / sizeof(int);
    for (int i = 0; i < add; i++)
    {
        printf(" ");
    }
    printf("%lu:", t.id);

    /*
    * Print Title for 20 elements
    */
    int titleLength;

    //Iterate through the title until the null charactor to find the length
    for (int i = 0; i < sizeof(t.title) / sizeof(char); i++)
    {
        if (t.title[i] == '\0')
        {
            titleLength = i;
            break;
        }
    }

    //calculate padding amount
    int titlePad = 20 - titleLength;

    if (titlePad > 0)
    {
        //Add padding
        for (int i = 0; i < titleLength + titlePad; i++)
        {
            if (i < titlePad)
            {
                printf(" ");
            }
            else
            {
                printf("%c", t.title[i - titlePad]);
            }
        }
    }
    else
    {
        //print until 20th element
        int count = 0;
        while (count < 20)
        {
            printf("%c", t.title[count]);
            count++;
        }
    }
    printf(":");

    /*
    * Print artist for 20 elements
    */
    int artistLength;

    for (int i = 0; i < sizeof(t.artist) / sizeof(char); i++)
    {
        if (t.artist[i] == '\0')
        {
            artistLength = i;
            break;
        }
    }

    int artistPad = 20 - artistLength;

    if (artistPad > 0)
    {
        for (int i = 0; i < artistLength + artistPad; i++)
        {
            if (i < artistPad)
            {
                printf(" ");
            }
            else
            {
                printf("%c", t.artist[i - artistPad]);
            }
        }
    }
    else
    {
        int count = 0;
        while (count < 20)
        {
            printf("%c", t.artist[count]);
            count++;
        }
    }

    /*
    * Print year
    */
    printf(":%d\n", t.year);
    printf("\n");

    return 1;
}

int db_add_row(struct db_table *db, struct album *a)
{

    //If there is room for the album add to the end of the table
    if (db->rows_used < db->rows_total)
    {
        db->table[db->rows_used] = *a;
        db->rows_used += 1;
    }
    else
    {
        //Reallocate 5 * the size of an album to the table location
        db->table = realloc(db->table, (db->rows_total + 5) * sizeof(db->table));

        //If memory allocation fails
        if (db->table == NULL)
        {
            return 0;
        }

        db->rows_total += 5;

        //Add
        db->table[db->rows_used] = *a;
        db->rows_used += 1;
    }

    return 1;
}

int db_remove_row(struct db_table *db, unsigned long id)
{
    // Boolean for the found id
    int found = 0;

    for (int i = 0; i < db->rows_used; i++)
    {
        // Check each id
        if (db->table[i].id == id && found == 0)
        {
            found = 1;
        }

        //If found shuffle each album up
        if (found == 1)
        {
            db->table[i] = db->table[i + 1];
        }
    }
    if (found == 1)
    {
        db->rows_used -= 1;
    }

    //Check for more than 5 empty rows
    if (db->rows_total - db->rows_used >= 5)
    {
        db->table = realloc(db->table, (db->rows_total - 5) * sizeof(db->table));

        //Check for failure
        if (db == NULL)
        {
            return 0;
        }

        db->rows_total -= 5;
    }

    return 1;
}
