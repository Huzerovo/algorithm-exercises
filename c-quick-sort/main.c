#include <stdio.h>

#define N 10

void swap(int *arr, int p, int q)
{
    int t  = arr[p];
    arr[p] = arr[q];
    arr[q] = t;
}

int partition(int *arr, int p, int q)
{
    int x = arr[p];
    int i = p;
    for (int j = p + 1; j < q; j++) {
        if (arr[j] <= x) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i, p);
    return i;
}

void quick_sort(int *arr, int p, int q)
{
    if (p >= q) {
        return;
    }
    int r = partition(arr, p, q);
    quick_sort(arr, p, r);
    quick_sort(arr, r + 1, q);
}

int main()
{
    printf("Input %d number:\n", N);
    int a[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    printf("Before sort:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }

    quick_sort(a, 0, N);

    printf("\nAfter sort:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
