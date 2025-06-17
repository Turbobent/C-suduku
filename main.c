#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9
int isSafe(int grid[N][N], int row, int col, int num);

void shuffle(int *array, int size){
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i+1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int fillGrid(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N)
        return 1;

    if (col == N) {
        row++;
        col = 0;
    }

    if (grid[row][col] > 0)
        return fillGrid(grid, row, col + 1);

    int nums[N];
    for (int i = 0; i < N; i++) nums[i] = i + 1;
    shuffle(nums, N);

    for (int i = 0; i < N; i++) {
        int num = nums[i];
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (fillGrid(grid, row, col + 1))
                return 1;
            grid[row][col] = 0;
        }
    }

    return 0;
}

void generateValidGrid(int grid[N][N]) {
    // Initialize empty grid
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    fillGrid(grid, 0, 0);
}

/*print grid */
void print(int arr[N][N])
{
     for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

// Checks whether it will be legal
// to assign num to the
// given row, col
int isSafe(int grid[N][N], int row, int col, int num)
{

    // Check if we find the same num
    // in the similar row , we return 0
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;

    // Check if we find the same num in the
    // similar column , we return 0
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;

    int startRow = row - row % 3, startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

int main() {
    // Seed randomness for shuffle
    srand(time(NULL)); 

    int grid[N][N];
    generateValidGrid(grid);

    printf("Generated valid Sudoku grid:\n");
    print(grid);

    return 0;
}
