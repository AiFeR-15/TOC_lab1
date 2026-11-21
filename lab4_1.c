#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int coins;
    int steps;
} Cell;

// Функція порівняння: повертає 1, якщо варіант 'a' кращий за 'b'
int is_better(Cell a, Cell b) {
    if (a.coins != b.coins) {
        return a.coins > b.coins; // Пріоритет 1: більше монет
    }
    return a.steps < b.steps;     // Пріоритет 2: менше стрибків
}

int main() {
    int N, M;

    // 1. Зчитування та перевірка розмірів поля (1 <= N, M <= 1000)
    while (1) {
        printf("Введіть розміри поля N та M (від 1 до 1000): ");
        if (scanf("%d %d", &N, &M) != 2) {
            printf("Помилка вводу! Потрібно ввести два цілих числа.\n");
            while (getchar() != '\n');
            continue;
        }
        if (N < 1 || N > 1000 || M < 1 || M > 1000) {
            printf("Помилка! Розміри мають бути не менше 1 і не більше 1000.\n");
            continue;
        }
        break;
    }

    // 2. Виділяємо пам'ять під поле та таблицю ДП розміром N x M
    int** field = (int**)malloc(N * sizeof(int*));
    Cell** dp = (Cell**)malloc(N * sizeof(Cell*));
    for (int i = 0; i < N; i++) {
        field[i] = (int*)malloc(M * sizeof(int));
        dp[i] = (Cell*)malloc(M * sizeof(Cell));
    }

    // 3. Заповнення поля монетками (0 або 1)
    int mode;
    printf("\nЯк заповнити поле?\n1. Ввести вручну (0 або 1)\n2. Згенерувати випадково\nВаш вибір: ");
    scanf("%d", &mode);

    if (mode == 2) {
        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                field[i][j] = rand() % 2;
            }
        }
        if (N <= 20 && M <= 20) {
            printf("\nЗгенероване поле:\n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    printf("%d ", field[i][j]);
                }
                printf("\n");
            }
        }
    } else {
        printf("Введіть елементи поля (%d рядків по %d чисел: 0 або 1):\n", N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int val;
                scanf("%d", &val);
                if (val != 0 && val != 1) {
                    printf("Помилка! У клітинці [%d][%d] може бути тільки 0 або 1. Введіть знову: ", i, j);
                    j--;
                    continue;
                }
                field[i][j] = val;
            }
        }
    }

    // 4. Масиви "стікерів" (найкраща клітинка зліва в рядку і зверху в стовпці)
    Cell* best_row = (Cell*)malloc(N * sizeof(Cell));
    Cell* best_col = (Cell*)malloc(M * sizeof(Cell));

    // Стартова клітинка (0, 0): стрибків ще 0, монет стільки, скільки лежить на старті
    dp[0][0].coins = field[0][0];
    dp[0][0].steps = 0;
    best_row[0] = dp[0][0];
    best_col[0] = dp[0][0];

    // 5. Основний цикл динамічного програмування
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 && j == 0) continue; // Старт вже порахували

            Cell prev_best;
            if (i == 0) {
                // У першому рядку можна стрибати тільки зліва
                prev_best = best_row[0];
            } else if (j == 0) {
                // У першому стовпці можна стрибати тільки зверху
                prev_best = best_col[0];
            } else {
                // Порівнюємо чемпіона зліва в рядку та чемпіона зверху в стовпці
                if (is_better(best_row[i], best_col[j])) {
                    prev_best = best_row[i];
                } else {
                    prev_best = best_col[j];
                }
            }

            // Записуємо результат для поточної клітинки
            dp[i][j].coins = prev_best.coins + field[i][j];
            dp[i][j].steps = prev_best.steps + 1;

            // Оновлюємо "стікер" для поточного рядка
            if (j == 0 || is_better(dp[i][j], best_row[i])) {
                best_row[i] = dp[i][j];
            }

            // Оновлюємо "стікер" для поточного стовпця
            if (i == 0 || is_better(dp[i][j], best_col[j])) {
                best_col[j] = dp[i][j];
            }
        }
    }

    // 6. Вивід результату (дивимося на правий нижній кут [N-1][M-1])
    Cell finish = dp[N - 1][M - 1];
    printf("\n=== Результат ===\n");
    if (finish.coins > 0) {
        printf("Буратіно ЗАЛИШИТЬСЯ В ЖИВИХ!\n");
        printf("Максимальна кількість монет: %d\n", finish.coins);
        printf("Мінімальна кількість стрибків: %d\n", finish.steps);
    } else {
        printf("Буратіно НЕ ВИЖИВЕ (на шляху немає жодної монети для викупу).\n");
    }

    // 7. Очищаємо всю виділену пам'ять
    for (int i = 0; i < N; i++) {
        free(field[i]);
        free(dp[i]);
    }
    free(field);
    free(dp);
    free(best_row);
    free(best_col);

    return 0;
}