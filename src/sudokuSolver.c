#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Row {
    char * row;
} Row;

typedef struct Puzzle {
    Row * rows;
    int populatedRows;
} Puzzle;

int printRow(Row r)
{
    printf("|");
    for(int i = 0; i < 9; i++)
    {
        if(r.row[i] == 'x' || r.row[i] == 'X')
            r.row[i] = ' ';
        printf("%c|", r.row[i]);
    }
    printf("\n|―|―|―|―|―|―|―|―|―|\n");
    return 0;
}

int gatherRow(Puzzle * p)
{
    int currentRow = p->populatedRows;
    char newRow[100] = "";
    int i;
    scanf("%100s", newRow);
    // printf("Length of new row is: %d.\n", (int)strlen(newRow));
    if(strlen(newRow) > 9)
    {
        newRow[9] = '\0';
    }
    if(strlen(newRow) < 9)
    {
        for(i = strlen(newRow); i < 9; i++)
        {
            newRow[i] = 'N';
        }
    }
    for(i = 0; i < 9; i++)
    {
        if(newRow[i] > 'a' && newRow[i] < 'z')
        {
            newRow[i] = newRow[i] - ('a' - 'A');
        }
        if((newRow[i] < '0' || newRow[i] > '9') && newRow[i] != 'N' && newRow[i] != 'X')
        {
            if(newRow[i] != 'X')
                newRow[i] = 'N';
        }
    }
    // strcpy(p->rows[currentRow+1].row, newRow);
    p->rows[currentRow].row = malloc(9 * sizeof(char));
    for(i = 0; i < 9; i++)
    {
        (p->rows + currentRow)->row[i] = newRow[i];
    }
    p->populatedRows++;
    return 0;
}

int printPuzzle(Puzzle * p)
{
    printf("|―|―|―|―|―|―|―|―|―|\n");
    for(int i = 0; i < p->populatedRows; i++)
    {
        printRow(p->rows[i]);
    }
    return 0;
}

Puzzle * createPuzzle()
{
    Puzzle * p;
    p = malloc(sizeof(Puzzle));
    p->rows = malloc(9 * sizeof(Row));
    p->populatedRows = 0;

    return p;
}

int destroyPuzzle(Puzzle * p)
{
    for(int i = 0; i < 9; i++)
    {
        free(p->rows);
    }
    free(p);
    return 0;
}
int main(int argc, char **argv)
{
    printf("Welcome to the Sudoku Solver!\n");
    printf("Please input the rows of the puzzle:\n");
    int rc = 0;
    Puzzle * puzzle1 = createPuzzle();
    for(int i = 0; i < 9; i++)
    {
        rc = gatherRow(puzzle1);
        if(rc)
            return -1;
    }
    rc = printPuzzle(puzzle1);

    if(rc)
        return -1;
    return 0;
}