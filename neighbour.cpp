#define MAXSIDE 25
// Function to count the number of mines in the adjacent cells
int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE]) {
    int count = 0;

    // Neighbour coordinates offsets
    int neighbourOffsets[][2] = {
        {-1, 0},    // North
        {1, 0},     // South
        {0, 1},     // East
        {0, -1},    // West
        {-1, 1},    // North-East
        {-1, -1},   // North-West
        {1, 1},     // South-East
        {1, -1}     // South-West
    };

    // Check each neighbour cell
    for (int i = 0; i < 8; ++i) {
        int newRow = row + neighbourOffsets[i][0];
        int newCol = col + neighbourOffsets[i][1];

        // Check if the new cell is valid
        if (isValid(newRow, newCol) && isMine(newRow, newCol, realBoard)) {
            count++;
        }
    }

    return count;
}

const int SIDE = 10; // Define your side length

bool isValid(int row, int col) {
    // Returns true if row number and column number is in range
    return (row >= 0) && (row < SIDE) &&
           (col >= 0) && (col < SIDE);
}

// A Utility Function to check whether given cell (row, col) has a mine or not.
bool isMine(int row, int col, char board[][MAXSIDE]) {
    if (board[row][col] == '*')
        return true;
    else
        return false;
}
