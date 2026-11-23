#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main() {
    int n, m;

    // 1. Спочатку питаємо у користувача реальні розміри графа
    while (1) {
        printf("Введіть кількість зірок n (2..100) та кількість ліній m (1..1000): ");
        if (scanf("%d %d", &n, &m) != 2 || n < 2 || n > 100 || m < 1 || m > 1000) {
            printf("Помилка вводу! Перевірте межі значень.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    // 2. Динамічно виділяємо матрицю суміжності рівно під (n + 1) x (n + 1)
    int** d = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        d[i] = (int*)calloc(n + 1, sizeof(int)); // calloc одразу заповнює нулями
    }

    // 3. Зчитуємо m ліній між зірками
    printf("Введіть %d ліній у форматі (зірка_1 зірка_2 вартість):\n", m);
    for (int edge = 0; edge < m; edge++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3 || u < 1 || u > n || v < 1 || v > n || w <= 0) {
            printf("Помилка! Номери зірок від 1 до %d, вартість > 0. Повторіть лінію #%d: ", n, edge + 1);
            while (getchar() != '\n');
            edge--;
            continue;
        }
        if (d[u][v] == 0 || w < d[u][v]) {
            d[u][v] = w;
            d[v][u] = w;
        }
    }

    // 4. Запитуємо початкову зірку k та кінцеву зірку l
    int k_start, l_end;
    while (1) {
        printf("Введіть початкову зірку k та кінцеву зірку l (1..%d): ", n);
        if (scanf("%d %d", &k_start, &l_end) != 2 || k_start < 1 || k_start > n || l_end < 1 || l_end > n) {
            printf("Помилка! Номери зірок мають бути від 1 до %d.\n", n);
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    // 5. Динамічно виділяємо робочі масиви рівно під n зірок
    int* point = (int*)calloc(n + 1, sizeof(int));
    int* dist  = (int*)malloc((n + 1) * sizeof(int));
    int* from  = (int*)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        point[i] = 0;
        if (d[k_start][i] == 0) {
            dist[i] = INF;
            from[i] = -1;             // Ще не знаємо, звідки сюди прийти
        } else {
            dist[i] = d[k_start][i];
            from[i] = k_start;        // Є пряма лінія зі стартової зірки
        }
    }
    point[k_start] = 1;
    from[k_start] = 0;
    dist[k_start] = 0;

    // 6. Алгоритм Дейкстри
    int count = 1;
    while (count < n) {
        int min_dist = INF;
        int curr = -1;

        for (int i = 1; i <= n; i++) {
            if (point[i] == 0 && dist[i] < min_dist) {
                min_dist = dist[i];
                curr = i;
            }
        }

        if (curr == -1) break;

        for (int i = 1; i <= n; i++) {
            if (point[i] == 0 && d[curr][i] > 0 && dist[i] > dist[curr] + d[curr][i]) {
                dist[i] = dist[curr] + d[curr][i];
                from[i] = curr;
            }
        }

        point[curr] = 1;
        count++;
    }

    // 7. Відновлення та вивід результату
    printf("\n=== Результат ===\n");
    if (dist[l_end] == INF) {
        printf("Утворити сузір'я неможливо: немає шляху між зіркою %d та зіркою %d.\n", k_start, l_end);
    } else {
        printf("Мінімальна вартість сузір'я: %d\n", dist[l_end]);

        int* path = (int*)malloc((n + 1) * sizeof(int));
        int path_len = 0;
        int temp = l_end;

        while (temp != 0) {
            path[path_len++] = temp;
            if (temp == k_start) break;
            temp = from[temp];
        }

        printf("Порядок обходу зірок у сузір'ї: ");
        for (int i = path_len - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
        free(path);
    }

    // 8. Очищення всієї виділеної пам'яті
    for (int i = 0; i <= n; i++) {
        free(d[i]);
    }
    free(d);
    free(point);
    free(dist);
    free(from);

    return 0;
}

