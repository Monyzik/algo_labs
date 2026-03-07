#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void generate_random() {
    freopen("random.txt", "w", stdout);

    int n = 12 + (rand() % 10);

    printf("%d\n", n);

    int pool[n];

    for (int i = 0; i < n; i++) {
        pool[i] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        int j = rand() % n, k = rand() % n;
        int tmp = pool[j];
        pool[j] = pool[k];
        pool[k] = tmp;
    }

    for (int i = 0; i < n; i++) {
        int string_size = 3 + rand() % 20;
        char s[string_size];
        for (int j = 0; j < string_size - 1; j++) {
            s[j] = 'a' + (rand() % 26);
        }
        s[string_size - 1] = '\0';
        int key = pool[i];
        printf("%d\n%s\n", key, s);
    }
}

void generate_reverse_sorted() {
    freopen("reverse_sorted.txt", "w", stdout);

    int n = 12 + (rand() % 10);
    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        int string_size = 3 + rand() % 20;
        char s[string_size];
        for (int j = 0; j < string_size - 1; j++) {
            s[j] = 'a' + (rand() % 26);
        }
        s[string_size - 1] = '\0';
        int key = n - i;
        printf("%d\n%s\n", key, s);
    }
}

void generate_sorted() {
    freopen("sorted.txt", "w", stdout);
    int n = 12 + (rand() % 10);

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        int string_size = 3 + rand() % 20;
        char s[string_size];
        for (int j = 0; j < string_size - 1; j++) {
            s[j] = 'a' + (rand() % 26);
        }
        s[string_size - 1] = '\0';
        int key = i + 1;
        printf("%d\n%s\n", key, s);
    }
}

signed main() {
    srand(time(NULL));
    generate_random();
    generate_reverse_sorted();
    generate_sorted();
}
