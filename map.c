#include <stdio.h>
#include <stdlib.h>

#define NLINES 18
#define NCOLUMNS 18
/*
O que cada numero significa na matriz:

1 = reta na horizontal
2 = curva da direta para cima
3 = reta na vertical
4 = curva de baixo para a direta
5 = curva da direta para baixo
6 = curva de cima para direta
7 = fim
*/

int** createMatrix(int lines, int columns);
void printMatrix( int** matrix, int rows, int columns );
void freeMatrix( int** matrix, int rows );
void fillMatrix( int** matrix );

int main()
{
	int ** matrix = createMatrix( NLINES , NCOLUMNS );
	
	fillMatrix( matrix );

	printMatrix( matrix , NLINES , NCOLUMNS);

	freeMatrix( matrix , NLINES );

	return 0;
}

int** createMatrix(int lines, int columns)
{
    int** matrix;
    matrix = ( int** ) malloc( sizeof( int* ) * lines );

    for(int i = 0; i < lines; i++)
    {
        matrix[i] = ( int* ) malloc( sizeof( int ) * columns );
    }
    return matrix;
}


void printMatrix( int** matrix, int rows, int columns )
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
    	{	

			if ( i == 6 && (j == 0 || j == 1 || j == 2 || j == 3))
    		{
    			matrix[i][j] = 1;
    		}
    		if (i == 6 && j == 4)
    		{
    			matrix[i][j] = 2 ;
    		}
    		if ((i == 5 || i == 4 || i == 3) &&  j == 4)
    		{
    			matrix[i][j] = 3;
    		}
    		if (i == 2 && j == 4)
    		{
    			matrix[i][j] = 4;
    		}
    		if( i == 2 && (j == 5 || j == 6 || j == 7))
    		{
    			matrix[i][j] = 1;
    		}
    		if( i == 2 && j == 8)
    		{
    			matrix[i][j] = 5;
    		}
    		if ( (i == 3 || i == 4 || i == 5 || i == 6 ) && j == 8)
    		{
    			matrix[i][j] = 3;
    		}
    		if (i == 7 && j == 8)
    		{
    			matrix[i][j] = 6;
    		}
    		if( i == 7 && ( j == 9 || j == 10 || j == 11))
    		{
    			matrix[i][j] = 1 ;
    		}
    		if( i == 7 && j == 12)
    		{
    			matrix[i][j] = 2 ;
    		}
    		if( (i == 8 || i == 9 || i == 10 || i == 11 || i == 12 ) && j == 12 )
    		{
    			matrix[i][j] = 3;
    		}
    		if ( i == 13 && j == 12)
    		{
    			matrix[i][j] = 4 ;
    		}
    		if ( i == 13 && (j == 13 || j == 14 || j == 15))
    		{
    			matrix[i][j] = 1 ;
    		}
    		if ( i == 13 && j == 16)
    		{
    			matrix[i][j] = 5 ;
    		}
    		if( (i == 14 || i == 15) && j == 16)
    		{
    			matrix[i][j] = 3;
    		}
    		if (i == 16 && j == 16)
    		{
    			matrix[i][j] = 4;
    		}
    		if (i == 16 && j == 17)
    		{
    			matrix[i][j] = 7;
    		}
    		printf("%d ", matrix[i][j] );
    			
        }

        printf("\n");
    }
}


void freeMatrix( int** matrix, int rows )
{
    for(int i = 0; i < rows; i++)
    {
        free( matrix[i] );
    }
    free( matrix );
}

void fillMatrix( int** matrix )
{
    for (int i = 0; i < NLINES; i++) 
    {
        for (int j = 0; j < NCOLUMNS; j++) 
        {
            matrix[i][j] = 0;
        	
        }
    }
}