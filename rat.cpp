#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random maze
vector<vector<char>> generateMaze(int n) {
    vector<vector<char>> maze(n, vector<char>(n, '#'));
    for (int i = 1; i < n; i += 2) {
        for (int j = 1; j < n; j += 2) {
            maze[i][j] = ' ';
        }
    }
    return maze;
}

// Function to display the maze
void displayMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

// Function to find a path through the maze using depth-first search
bool findPath(vector<vector<char>>& maze, int x, int y, int n) {
    if (x < 0 || x >= n || y < 0 || y >= n || maze[x][y] == ' ') {
        return false;
    }

    if (x == n - 1 && y == n - 1) {
        return true;
    }

    maze[x][y] = '.';

    if (findPath(maze, x + 2, y, n) || findPath(maze, x, y + 2, n) ||
        findPath(maze, x - 2, y, n) || findPath(maze, x, y - 2, n)) {
        return true;
    }

    maze[x][y] = ' ';

    return false;
}

int main() {
    srand(time(nullptr));
    int n;
    cout << "Enter the size of the maze (n x n): ";
    cin >> n;

    vector<vector<char>> maze = generateMaze(n);
    displayMaze(maze);

    while (true) {
        char option;
        cout << "Choose an option (p - Print path, g - Generate another puzzle, e - Exit): ";
        cin >> option;

        if (option == 'p') {
            vector<vector<char>> mazeCopy = maze;
            if (findPath(mazeCopy, 1, 1, n)) {
                displayMaze(mazeCopy);
            } else {
                cout << "No path found." << endl;
            }
        } else if (option == 'g') {
            maze = generateMaze(n);
            displayMaze(maze);
        } else if (option == 'e') {
            cout << "Exiting the game." << endl;
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
