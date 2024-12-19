#include <stdio.h>

// Fungsi untuk menukar dua nilai menggunakan pointer
void tukar(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Fungsi Insertion Sort
void insertionSort(int data[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;

        // Geser elemen-elemen yang lebih besar dari data[i] ke kanan
        while (j > 0 && data[j - 1] > data[j]) {
            // Panggil fungsi tukar jika elemen sebelumnya lebih besar
            tukar(&data[j - 1], &data[j]);
            j--;
        }
    }
}

int main() {
    int data[100] = {5, 7, 3, 9, 8, 2}; // Deklarasi array
    int n = 6; // Jumlah elemen dalam array

    insertionSort(data, n);

    printf("Array setelah diurutkan:\n");
    for (int i = 0; i < n; i++) {
        printf("%d, ", data[i]);
    }

    return 0;
}
