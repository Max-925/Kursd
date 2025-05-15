#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;

const int ROWS = 8;
const int COLS = 14;

int board[ROWS][COLS] = {
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int values[ROWS][COLS];
bool used[7][7];

int dx[] = {0, 1};
int dy[] = {1, 0};

vector<vector<int>> row_hints = {
    {},         // Рядок 0
    {4, 6},     // Рядок 1
    {},         // Рядок 2
    {0, 2, 4, 6}, // Рядок 3
    {},         // Рядок 4
    {1, 3, 6},  // Рядок 5
    {},         // Рядок 6
    {},         // Рядок 7
};

vector<vector<int>> col_hints = {
    {2, 5, 6}, // Колонка 0
    {}, // Колонка 1
    {}, // Колонка 2
    {0, 1, 4}, // Колонка 3
    {}, // Колонка 4
    {0, 3, 6}, // Колонка 5
    {}, {}, // Колонки 6-7
    {0, 1, 3}, // Колонка 8
    {}, // Колонка 9
    {1, 2, 4}, // Колонка 10
    {}, {},    // Колонки 11-12
    {2, 3, 5, 6} // Колонка 13
};

void init_values() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == 1) {
                values[i][j] = -1;}
            else{
              values[i][j] = 0;
              }
              }
              }
              }

void print_board() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == 1) {
                if (values[i][j] != -1) {
                    cout << setw(3) << values[i][j] << " ";
                } else {
                    cout << "  X ";
                }
            } else {
                cout << "    ";
            }
        }
        cout << endl;
    }
}
int main(){
  init_values();
  print_board();
  return 0;
}