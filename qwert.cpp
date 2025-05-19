#include <iostream>
#include <iomanip>

using namespace std;

const int ROWS = 8;
const int COLS = 14;
// Початкова таблиця 1- вільна клітинка 0-недоступна
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

int values[ROWS][COLS]; // Значення у клітинках
bool used[7][7];        // Використані доміно

// Напрямки: вправо та вниз
int dx[] = {0, 1};
int dy[] = {1, 0};

// Перевірка меж поля та статусу клітинки
inline bool in_bounds(int r, int c) {
    return r >= 0 && c >= 0 && r < ROWS && c < COLS;
}
// Перевірка сусідньої клітинки
inline bool in_bounds_and_free(int r, int c) {
    return in_bounds(r, c) && board[r][c] == 1 && values[r][c] == -1;
}

// Функція для друку дошки
void print_board(int step) {
    cout << "\n=== Step: " << step << " ===\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == 1) {
                if (values[i][j] != -1)
                    cout << setw(3) << values[i][j] << " ";
                else
                    cout << "  X ";
            } else {
                cout << "    ";
            }
        }
        cout << endl;
    }
}

// Основна функція пошуку розв'язку
bool solve(int step) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            // Якщо клітинка доступна для заповнення
            if (board[r][c] == 1 && values[r][c] == -1) {
                for (int d = 0; d < 2; ++d) { // Перевіряємо напрямки вправо та вниз
                    int rr = r + dx[d];
                    int cc = c + dy[d];

                    // Перевіряємо межі та доступність другої клітинки
                    if (!in_bounds_and_free(rr, cc)) continue;

                    // Пробуємо всі можливі доміно
                    for (int a = 0; a <= 6; ++a) {
                        for (int b = a; b <= 6; ++b) {
                            if (used[a][b]) continue; // Якщо доміно вже використане

                            // Контроль збігу чисел між клітинками
                            if (d == 0 && values[r][c - 1] != -1 && values[r][c - 1] != a) continue; // Ліве число збігається
                            if (d == 1 && values[r - 1][c] != -1 && values[r - 1][c] != a) continue; // Верхнє число збігається

                            // Розставляємо числа
                            used[a][b] = used[b][a] = true;
                            values[r][c] = a;
                            values[rr][cc] = b;
                            // Вивід поточного етапу вирішення
                            print_board(step);

                            // Рекурсія
                            if (solve(step + 1)) return true;

                            // Відкат у разі невдачі
                            used[a][b] = used[b][a] = false;
                            values[r][c] = -1;
                            values[rr][cc] = -1;
                        }
                    }
                }
                return false; // Якщо немає варіантів
            }
        }
    }
    return true; // Успіх при заповненні всієї дошки
}

int main() {
    // Ініціалізуємо клітинки та доміно
    fill(&values[0][0], &values[0][0] + ROWS * COLS, -1);
    fill(&used[0][0], &used[0][0] + 7 * 7, false);

    cout << "Initial board:\n";
    print_board(0);

    // Пошук розв'язку
    if (solve(1)) {
        cout << "\nFound solution!\n";
        print_board(0);
    } else {
        cout << "\nNo solution found.\n";
    }

    return 0;
}