#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_ll(const void* a, const void* b) {
    long long x = *(const long long*)a;
    long long y = *(const long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    int n;
    long long S;

    while (1) {
        printf("Введіть кількість килимів n (від 1 до 100000): ");
        if (scanf("%d", &n) != 1 || n < 1 || n > 100000) {
            printf("Помилка! Кількість має бути від 1 до 100000.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    while (1) {
        printf("Введіть час на порятунок S (у хвилинах, >= 0): ");
        if (scanf("%lld", &S) != 1 || S < 0) {
            printf("Помилка! Введіть невід'ємне число.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    long long* d = (long long*)malloc(n * sizeof(long long));
    if (d == NULL) {
        printf("Помилка виділення пам'яті!\n");
        return 1;
    }

    int mode;
    printf("\nЯк задати довжини килимів?\n1. Ввести вручну\n2. Згенерувати випадково\nВаш вибір: ");
    scanf("%d", &mode);

    if (mode == 2) {
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            d[i] = 1 + rand() % 20;
        }
        if (n <= 25) {
            printf("Згенеровані довжини: ");
            for (int i = 0; i < n; i++) printf("%lld ", d[i]);
            printf("\n");
        }
    } else {
        printf("Введіть довжини %d килимів (у метрах, > 0):\n", n);
        for (int i = 0; i < n; i++) {
            long long val;
            if (scanf("%lld", &val) != 1 || val <= 0) {
                printf("Помилка! Довжина має бути додатним числом. Введіть килим #%d знову: ", i + 1);
                while (getchar() != '\n');
                i--;
                continue;
            }
            d[i] = val;
        }
    }

    qsort(d, n, sizeof(long long), compare_ll);

    long long sum_odd_count = 0;
    long long sum_even_count = 0;
    int max_saved = 0;

    for (int i = 0; i < n; i++) {
        int current_count = i + 1;
        long long required_time;

        if (i % 2 == 0) {
            sum_odd_count += d[i];
            required_time = sum_odd_count;
        } else {
            sum_even_count += d[i];
            required_time = sum_even_count;
        }

        if (required_time <= S) {
            max_saved = current_count;
        } else {
            break;
        }
    }

    printf("\n=== Результат ===\n");
    printf("Максимальна кількість врятованих килимів: %d з %d\n", max_saved, n);

    free(d);
    return 0;
}