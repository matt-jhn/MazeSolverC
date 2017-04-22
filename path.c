#include <stdio.h>
#define  M 100
#define N 100
void solveMaze(char[100][100], int, int);

main()
{
    char array[M][N]= {0};
    FILE *fptr;
    char c;
    char file_name[20];
    int i,j;
    int x,y;


    //find dimensions of the maze inside the 100x100
    printf("How many rows does your array have?: ");
    scanf("%d", &x);
    printf("How many columns does your array have?: ");
    scanf("%d", &y);

    printf("Type in the name of the file containing the Field\n");
    scanf("%s",file_name);
    fptr=fopen(file_name,"r");
    //loop code altered to only assign values in the dimesions specified by the user
    for (i=0; i<x; i++)
        for (j=0; j<y; j++)
        {
            c=fgetc(fptr);
            while ( !((c == '1')||(c =='0')) ) c=fgetc(fptr);
            array[i][j]=c;
        }
    fclose(fptr);

    //printing code altered slightly to only print the nonempty part of the 100x100 array.
    for (i=0; i<x; i++)
        for (j=0; j<y; j++)
        {
            if (j == 0) printf("\n");
            printf("%c  ",array[i][j]);
        }
    printf("\n");

    solveMaze(array, x, y);
}

void solveMaze(char a[100][100], int aSize, int bSize)
{
    //X and Y are used as a sort of coordinate system to keep track of positions in the maze.
    //top, right, bottom, and left are used to search the walls for entrances and exits
    //direction is used to utilize the right wall algorithm
    int entranceX = -1;
    int entranceY = -1;
    int exitX = -1;
    int exitY = -1;
    int top = 0;
    int right = 0;
    int i = 0;
    int j = 0;
    int bottom = bSize - 1;
    int left = aSize - 1;
    int currentX;
    int currentY;
    char direction;

    //search the first row for an entrance
    while (top < bSize && entranceX == -1)
    {
        if (a[0][top] == '0')
        {
            entranceX = 0;
            entranceY = top;
            currentX = 0;
            currentY = top;
            direction = 'S';
            a[entranceX][entranceY] = 'X';
            //printf("Code is running");
        }
        top++;
    }

    //search for an exit on the remainder of the top row if an entrance existed there
    if (entranceX != -1)
    {
        while (top < bSize && exitX == -1)
        {
            if (a[0][top] == '0')
            {
                exitX = 0;
                exitY = top;
            }
            top++;
        }
    }

    //search the right wall for an entrance if it wasn't found on the top
    if (entranceX == -1)
    {
        while (right < aSize && entranceX == -1)
        {
            if (a[right][bSize - 1] == '0')
            {
                entranceX = right;
                entranceY = bSize - 1;
                currentX = right;
                currentY = bSize - 1;
                a[entranceX][entranceY] = 'X';
                direction = 'W';
            }
            right++;
        }
    }

    //search the right wall for an exit if the entrance was already found
    if (entranceX != -1)
    {
        while (right < aSize && exitX == -1)
        {
            if (a[right][bSize - 1] == '0')
            {
                exitX = right;
                exitY = bSize - 1;
            }
            right++;
        }
    }

    //find an entrance along the bottom if one is not already found
    if (entranceX == -1)
    {
        while (bottom > -1 && entranceX == -1)
        {
            if (a[aSize - 1][bottom] == '0')
            {
                entranceX = aSize - 1;
                entranceY = bottom;
                a[entranceX][entranceY] = 'X';
                currentX = aSize - 1;
                currentY = bottom;
                direction = 'N';
            }
            bottom--;
        }
    }

    //search for an exit on the bottom row if there is an entrance
    if (entranceX != -1)
    {
        while (bottom > -1 && exitX == -1)
        {
            if (a[aSize - 1][bottom] == '0')
            {
                exitX = aSize - 1;
                exitY = bottom;
            }
            bottom--;
        }
    }

    //search for an entrance on the left side if there is not already one
    if (entranceX == -1)
    {
        while (left > -1 && entranceX == -1)
        {
            if (a[left][0] == '0')
            {
                entranceX = left;
                entranceY = 0;
                currentX = left;
                currentY = 0;
                a[entranceX][entranceY] = 'X';
                direction = 'E';
            }
            left--;
        }
    }

    //search for an exit on the left if there is already an entrance
    if (entranceX != -1)
    {
        while (left > -1 && exitX == -1)
        {
            if (a[left][0] == '0')
            {
                exitX = left;
                exitY = 0;
            }
            left--;
        }
    }

    //will loop until you either find the exit or return to the entrance
    //will not execute if there is no entrance
    if (entranceX != -1)
    {
        do
        {
            //Each if condition will check the right, forward, and left positions in that priority and move to the best spot.
            //Uses the right-wall algorithm by using a direction variable to keep track of which way the user is facing per move.
            if (direction == 'N')
            {
                if (a[currentX][currentY + 1] == '0' || a[currentX][currentY + 1] == 'X')
                {
                    currentY++;
                    a[currentX][currentY] = 'X';
                    direction = 'E';
                }
                else if (a[currentX - 1][currentY] == '0' || a[currentX - 1][currentY] == 'X')
                {
                    currentX--;
                    a[currentX][currentY] = 'X';
                    direction = 'N';
                }
                else if (a[currentX][currentY - 1] == '0' || a[currentX][currentY - 1] == 'X')
                {
                    currentY--;
                    a[currentX][currentY] = 'X';
                    direction = 'W';
                }
                else
                {
                    currentX++;
                    direction = 'S';
                }
            }
            else if (direction == 'E')
            {
                if (a[currentX + 1][currentY] == '0' || a[currentX + 1][currentY] == 'X')
                {
                    currentX++;
                    a[currentX][currentY] = 'X';
                    direction = 'S';
                }
                else if (a[currentX][currentY + 1] == '0' || a[currentX][currentY + 1] == 'X')
                {
                    currentY++;
                    a[currentX][currentY] = 'X';
                    direction = 'E';
                }
                else if (a[currentX -1][currentY] == '0' || a[currentX - 1][currentY] == 'X')
                {
                    currentX--;
                    a[currentX][currentY] = 'X';
                    direction = 'N';
                }
                else
                {
                    currentY--;
                    direction = 'W';
                }
            }
            else if (direction == 'W')
            {
                if (a[currentX - 1][currentY] == '0' || a[currentX - 1][currentY] == 'X')
                {
                    currentX--;
                    a[currentX][currentY] = 'X';
                    direction = 'N';
                }
                else if (a[currentX][currentY - 1] == '0' || a[currentX][currentY - 1] == 'X')
                {
                    currentY--;
                    a[currentX][currentY] = 'X';
                    direction = 'W';
                }
                else if (a[currentX + 1][currentY] == '0' || a[currentX + 1][currentY] == 'X')
                {
                    currentX++;
                    a[currentX][currentY] = 'X';
                    direction = 'S';
                }
                else
                {
                    currentY++;
                    direction = 'E';
                }
            }
            //will execute if the direction is southward
            else
            {
                if (a[currentX][currentY - 1] == '0' || a[currentX][currentY - 1] == 'X')
                {
                    currentY--;
                    a[currentX][currentY] = 'X';
                    direction = 'W';
                }
                else if (a[currentX + 1][currentY] == '0' || a[currentX + 1][currentY] == 'X')
                {
                    currentX++;
                    a[currentX][currentY] = 'X';
                    direction = 'S';
                }
                else if (a[currentX][currentY + 1] == '0' || a[currentX][currentY + 1] == 'X')
                {
                    currentY++;
                    a[currentX][currentY] = 'X';
                    direction = 'E';
                }
                else
                {
                    currentX--;
                    direction = 'N';
                }
            }
        }
        while (currentX > 0 && currentX < aSize - 1 && currentY > 0 && currentY < bSize - 1);

        //Printing solved maze
        for (i=0; i<aSize; i++)
            for (j=0; j<bSize; j++)
            {
                if (j == 0) printf("\n");
                printf("%c  ",a[i][j]);
            }
        //printf("\nLoop ran %d time(s)\nEntrance Coordinates: %d, %d\nFinal Coordinates: %d, %d", testcount, entranceX, entranceY, currentX, currentY);

        if (currentX == entranceX && currentY == entranceY)
        {
            printf("\nNo path found to the exit, returned to entrance.");
        }
        else
        {
            printf("\nPath to exit found, maze solved.");
        }
    }
    else
    {
        printf("\nMaze has no entrance, cannot solve.");
    }
}
