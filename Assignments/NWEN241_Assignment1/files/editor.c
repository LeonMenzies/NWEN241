
#include <stdio.h>
#include <string.h>
#include "editor.h"

int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos)
{

    //Starting from the end of the array move the elements to the right 1
    for (int i = editing_buflen - 1; i > pos - 1; i--)
    {
        editing_buffer[i + 1] = editing_buffer[i];
    }

    //Insert the char to the now empty postion
    editing_buffer[pos] = to_insert;

    //Check if the char is in the correct positon and not outside of the array
    if (editing_buffer[pos] == to_insert && pos < editing_buflen)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset)
{
    //Start at the offset and iterate until the charactor is found
    for (int i = offset; i < editing_buflen; i++)
    {
        if (editing_buffer[i] == to_delete)
        {
            //Move all charactors from the point left one
            for (int j = i; j < editing_buflen; j++)
            {
                editing_buffer[j] = editing_buffer[j + 1];
            }
            //Fill in the space at the end and return 1
            editing_buffer[editing_buflen] = '\0';
            return 1;
        }
    }
    return 0;
}

int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset)
{
    int wordPoint;
    int strLength = strlen(str);
    int replacementLength = strlen(replacement);

    char foundStr[strLength];

    //Check if offest is valid
    if (offset < 0 || offset > editing_buflen || strLength == 0)
    {
        return -1;
    }

    //Find the word and its starting point
    for (int i = offset; i < editing_buflen; i++)
    {
        if (editing_buffer[i] == str[0])
        {
            wordPoint = i;
            for (int j = 0; j < strLength + 1; j++)
            {
                foundStr[j] = editing_buffer[i + j];

                if (strcmp(foundStr, str) == 0)
                {
                    goto found;
                }
                else

                    if (editing_buffer[i + j] != str[j])
                {
                    break;
                }
            }
        }
    }
    return -1;
found:
    //Make sure the start of the word is not before the offset

    if (wordPoint < offset)
    {
        return -1;
    }

    int moveBy = strLength - replacementLength;

    //Shift remaining right
    if (strLength < replacementLength)
    {
        int absMove = -moveBy;

        for (int i = editing_buflen; i > wordPoint + strLength; i--)

        {
            editing_buffer[i] = editing_buffer[i - absMove];
        }
    }
    //Shift ramianing left
    else
    {
        for (int i = wordPoint; i < editing_buflen; i++)
        {
            editing_buffer[i] = editing_buffer[i + moveBy];
        }
    }
    for (int f = 0; f < editing_buflen; f++)
    {
        printf("%c", editing_buffer[f]);
    }
    printf("\n");

    //Insert the word
    for (int i = 0; i < replacementLength; i++)
    {
        editing_buffer[wordPoint + i] = replacement[i];
    }

    editing_buffer[editing_buflen] = '\0';

    //Return = if the replacement was to long else return the final replaced char
    if (wordPoint + replacementLength - 1 > editing_buflen)
    {
        return -1;
    }
    else
    {
        return wordPoint + replacementLength - 1;
    }
}

void editor_view(int rows, int cols, char viewing_buffer[rows][cols], const char editing_buffer[], int editing_buflen, int wrap)
{

    //Set values to null
    for (int reseti = 0; reseti < rows; reseti++)
    {
        for (int resetj = 0; resetj < cols; resetj++)
        {
            viewing_buffer[reseti][resetj] = '\0';
        }
    }

    //Iterate the editing buffer and put into the viewing buffer accordingly
    int row = 0;
    int col = 0;

    for (int i = 0; i < editing_buflen; ++i)
    {
        char c = editing_buffer[i];

        //Check for a null and terminate if found
        if (c == '\0')
        {
            return;
        }

        //If a newline charactor is found go back to the first column, go to the next row and then continue
        if (c == '\n')
        {
            col = 0;
            row++;
            continue;
        }

        //Check if at the end of the columns, go to the next row
        if (col == cols - 1 && wrap != 0)
        {
            col = 0;
            row++;
        }

        //Add the charactor if the col variable is still inside the column width
        if (col < cols - 1)
        {
            viewing_buffer[row][col] = c;
        }
        ++col;
    }
}
