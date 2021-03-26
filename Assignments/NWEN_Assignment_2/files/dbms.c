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
