#include <stdio.h>
#include <string.h>

struct Mahasiswa {
    int NPM;
    char Nama[100];
    char prodi[25];
    float IPK;
};

// Fungsi untuk mencetak data mahasiswa
void print(struct Mahasiswa mhs[]) {
    for (int i = 0; i < 3; i++) {
        printf("===== Mahasiswa %d =======\n", i + 1);
        printf("NPM: %d\n", mhs[i].NPM);
        printf("Nama: %s\n", mhs[i].Nama);
        printf("Program Studi: %s\n", mhs[i].prodi);
        printf("IPK: %.02f\n", mhs[i].IPK);
        printf("\n");
    }
}

// Fungsi Bubble Sort untuk mengurutkan berdasarkan IPK (descending)
void BubbleSort(struct Mahasiswa mhs[]) {
    struct Mahasiswa tmp;

    for (int i = 0; i < 3 - 1; i++) {
        for (int j = 0; j < 3 - i - 1; j++) {
            if (mhs[j].IPK < mhs[j + 1].IPK) {
                tmp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = tmp;
            }
        }
    }
}

// Fungsi Selection Sort untuk mengurutkan berdasarkan IPK (ascending)
void SelectionSort(struct Mahasiswa mhs[]) {
    int pos;
    struct Mahasiswa temp;
    for (int i = 0; i < 3; i++) {
        pos = i;
        for (int j = i + 1; j < 3; j++) {
            if (mhs[j].IPK < mhs[pos].IPK) {
                pos = j;
            }
        }
        // Tukar elemen yang lebih kecil ke posisi `i`
        temp = mhs[pos];
        mhs[pos] = mhs[i];
        mhs[i] = temp;
    }
}

// Fungsi untuk menukar dua elemen Mahasiswa (by reference)
void tukar(struct Mahasiswa *a, struct Mahasiswa *b) {
    struct Mahasiswa t = *a;
    *a = *b;
    *b = t;
}

// Fungsi Insertion Sort untuk mengurutkan berdasarkan IPK (ascending)
void insertionSort(struct Mahasiswa mhs[]) {
    for (int i = 1; i < 3; i++) {
        int j = i;

        // Geser elemen-elemen yang lebih besar dari mhs[i] ke kanan
        while (j > 0 && mhs[j - 1].IPK > mhs[j].IPK) {
            // Panggil fungsi tukar jika elemen sebelumnya lebih besar
            tukar(&mhs[j - 1], &mhs[j]);
            j--;
        }
    }
}

void sequentialSearch(struct Mahasiswa mhs[], int query){
    int found = 0;
    for (int i = 0; i < 3; i++){
        if(mhs[i].NPM == query){
            printf("Mahasiswa ditemukan:\n");
            printf("===== Mahasiswa =======\n");
            printf("NPM: %d\n", mhs[i].NPM);
            printf("Nama: %s\n", mhs[i].Nama);
            printf("Program Studi: %s\n", mhs[i].prodi);
            printf("IPK: %.02f\n", mhs[i].IPK);
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found){
        printf("Mahasiswa dengan NPM %d tidak ditemukan", query);
    }
}

// Fungsi Jump Search sederhana untuk mencari mahasiswa berdasarkan NPM
void jumpSearch(struct Mahasiswa mhs[3], int query) {
    int jump = 1; // sqrt(3) dibulatkan ke bawah adalah 1
    int prev = 0;

    // Mencari blok di mana NPM berada
    while (prev < 3 && mhs[jump - 1].NPM < query) {
        prev = jump;
        jump += 1; // Tetap gunakan increment manual

        if (prev >= 3) {
            printf("Mahasiswa dengan NPM %d tidak ditemukan!\n", query);
            return;
        }
    }

    // Linear search di dalam blok yang ditemukan
    for (int i = prev; i < 3 && i < jump; i++) {
        if (mhs[i].NPM == query) {
            printf("Mahasiswa ditemukan:\n");
            printf("===== Mahasiswa =======\n");
            printf("NPM: %d\n", mhs[i].NPM);
            printf("Nama: %s\n", mhs[i].Nama);
            printf("Program Studi: %s\n", mhs[i].prodi);
            printf("IPK: %.02f\n", mhs[i].IPK);
            printf("\n");
            return;
        }
    }

    // Jika NPM tidak ditemukan
    printf("Mahasiswa dengan NPM %d tidak ditemukan!\n", query);
}

int main() {
    struct Mahasiswa mhs[3];
    int pil;
    int query;

    // Inisialisasi data mahasiswa
    mhs[0].NPM = 23083;
    strcpy(mhs[0].Nama, "Aqila Murodah");
    strcpy(mhs[0].prodi, "Informatika");
    mhs[0].IPK = 3.75;

    mhs[1].NPM = 23081;
    strcpy(mhs[1].Nama, "Rahma Erlinda");
    strcpy(mhs[1].prodi, "Sistem Informasi");
    mhs[1].IPK = 3.05;

    mhs[2].NPM = 23085;
    strcpy(mhs[2].Nama, "Nurul Saadeh");
    strcpy(mhs[2].prodi, "Bisnis Digital");
    mhs[2].IPK = 4.00;

    do {
        printf("Manajemen Data Mahasiswa\n");
        printf("1. Data Mahasiswa\n");
        printf("2. Pengurutan Bubblesort (IPK Descending)\n");
        printf("3. Pengurutan Selectionsort (IPK Ascending)\n");
        printf("4. Pengurutan InsertionSort (IPK Ascending)\n");
        printf("5. searching Jumpsearch\n");
        printf("6. Searching Sequentialsearch\n");
        printf("7. Keluar\n");

        printf("Masukkan Pilihan: ");
        scanf("%d", &pil);

        switch (pil) {
            case 1:
                printf("DATA MAHASISWA\n");
                print(mhs);
                break;

            case 2:
                BubbleSort(mhs);
                printf("Hasil Pengurutan berdasarkan IPK (Descending):\n");
                print(mhs);
                break;

            case 3:
                SelectionSort(mhs);
                printf("Hasil Pengurutan berdasarkan IPK (Ascending):\n");
                print(mhs);
                break;

            case 4:
                insertionSort(mhs);
                printf("Hasil Pengurutan berdasarkan IPK (Ascending):\n");
                print(mhs);
                break;

            case 5:
                printf("Masukkan NPM yang ingin dicari: ");
                scanf("%d", &query);
                jumpSearch(mhs, query);
                break;

            case 6:
                printf("Masukkan NPM yang ingin dicari:");
                scanf("%d", &query);
                sequentialSearch(mhs,query);

            case 7:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (pil != 7);

    return 0;
}
