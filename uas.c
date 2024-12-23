#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur pohon untuk BST dan AVL
typedef struct tree {
    int id;
    char nama[50];
    char buku_favorit[50];
    struct tree *kiri;
    struct tree *kanan;
    int tinggi; // Digunakan untuk AVL
} pohon;

// Fungsi untuk membuat simpul baru
pohon *baru(int id, char *nama, char *buku_favorit) {
    pohon *nodeBaru = (pohon *)malloc(sizeof(pohon));
    nodeBaru->id = id;
    strcpy(nodeBaru->nama, nama);
    strcpy(nodeBaru->buku_favorit, buku_favorit);
    nodeBaru->kiri = NULL;
    nodeBaru->kanan = NULL;
    nodeBaru->tinggi = 1;
    return nodeBaru;
}

// Fungsi untuk mendapatkan tinggi simpul (AVL)
int getTinggi(pohon *node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->tinggi;
    }
}

// Fungsi untuk mendapatkan faktor keseimbangan (AVL)
int getBalance(pohon *node) {
    if (node == NULL) {
        return 0;
    } else {
        return getTinggi(node->kiri) - getTinggi(node->kanan);
    }
}

pohon *rotasiKanan(pohon *y) {
    pohon *x = y->kiri;  // Anak kiri menjadi root baru
    pohon *T2 = x->kanan;  // Simpan sub-pohon kanan dari x

    // Lakukan rotasi
    x->kanan = y;  // Anak kanan x menjadi y
    y->kiri = T2;  // Anak kiri y menjadi T2

    // Perbarui tinggi y
    if (y->kiri == NULL && y->kanan == NULL) {
        y->tinggi = 1;
    } else if (y->kiri == NULL) {
        y->tinggi = y->kanan->tinggi + 1;
    } else if (y->kanan == NULL) {
        y->tinggi = y->kiri->tinggi + 1;
    } else {
        y->tinggi = (y->kiri->tinggi > y->kanan->tinggi ? y->kiri->tinggi : y->kanan->tinggi) + 1;
    }

    // Perbarui tinggi x
    if (x->kiri == NULL && x->kanan == NULL) {
        x->tinggi = 1;
    } else if (x->kiri == NULL) {
        x->tinggi = x->kanan->tinggi + 1;
    } else if (x->kanan == NULL) {
        x->tinggi = x->kiri->tinggi + 1;
    } else {
        x->tinggi = (x->kiri->tinggi > x->kanan->tinggi ? x->kiri->tinggi : x->kanan->tinggi) + 1;
    }

    // Kembalikan root baru
    return x;
}

pohon *rotasiKiri(pohon *x) {
    pohon *y = x->kanan;  // Anak kanan menjadi root baru
    pohon *T2 = y->kiri;  // Simpan sub-pohon kiri dari y

    // Lakukan rotasi
    y->kiri = x;  // Anak kiri y menjadi x
    x->kanan = T2;  // Anak kanan x menjadi T2

    // Perbarui tinggi x
    if (x->kiri == NULL && x->kanan == NULL) {
        x->tinggi = 1;
    } else if (x->kiri == NULL) {
        x->tinggi = x->kanan->tinggi + 1;
    } else if (x->kanan == NULL) {
        x->tinggi = x->kiri->tinggi + 1;
    } else {
        if (x->kiri->tinggi > x->kanan->tinggi) {
            x->tinggi = x->kiri->tinggi + 1;
        } else {
            x->tinggi = x->kanan->tinggi + 1;
        }
    }

    // Perbarui tinggi y
    if (y->kiri == NULL && y->kanan == NULL) {
        y->tinggi = 1;
    } else if (y->kiri == NULL) {
        y->tinggi = y->kanan->tinggi + 1;
    } else if (y->kanan == NULL) {
        y->tinggi = y->kiri->tinggi + 1;
    } else {
        if (y->kiri->tinggi > y->kanan->tinggi) {
            y->tinggi = y->kiri->tinggi + 1;
        } else {
            y->tinggi = y->kanan->tinggi + 1;
        }
    }

    // Kembalikan root baru
    return y;
}


// Fungsi untuk menyisipkan anggota pada AVL
pohon *sisipAVL(pohon *node, int id, char *nama, char *buku_favorit) {
    if (node == NULL) return baru(id, nama, buku_favorit);

    if (id < node->id) {
        node->kiri = sisipAVL(node->kiri, id, nama, buku_favorit);
    } else if (id > node->id) {
        node->kanan = sisipAVL(node->kanan, id, nama, buku_favorit);
    } else {
        return node; // ID sudah ada
    }

  if (getTinggi(node->kiri) > getTinggi(node->kanan)) {
    node->tinggi = 1 + getTinggi(node->kiri);
} else {
    node->tinggi = 1 + getTinggi(node->kanan);
}


    int balance = getBalance(node);

    if (balance > 1 && id < node->kiri->id) return rotasiKanan(node);
    if (balance < -1 && id > node->kanan->id) return rotasiKiri(node);
    if (balance > 1 && id > node->kiri->id) {
        node->kiri = rotasiKiri(node->kiri);
        return rotasiKanan(node);
    }
    if (balance < -1 && id < node->kanan->id) {
        node->kanan = rotasiKanan(node->kanan);
        return rotasiKiri(node);
    }

    return node;
}

// Fungsi untuk menyisipkan anggota pada BST
void sisipBST(pohon **root, int id, char *nama, char *buku_favorit) {
    if (*root == NULL) {
        *root = baru(id, nama, buku_favorit);
    } else if (id < (*root)->id) {
        sisipBST(&(*root)->kiri, id, nama, buku_favorit);
    } else if (id > (*root)->id) {
        sisipBST(&(*root)->kanan, id, nama, buku_favorit);
    }
}

// Fungsi untuk mencari anggota
pohon *cari(pohon *root, int id) {
    if (root == NULL || root->id == id) {
        return root;
    } else if (id < root->id) {
        return cari(root->kiri, id);
    } else {
        return cari(root->kanan, id);
    }
}

// Fungsi untuk traversal inorder
void inorder(pohon *root) {
    if (root != NULL) {
        inorder(root->kiri);
        printf("| %-5d | %-20s | %-30s |\n", root->id, root->nama, root->buku_favorit);
        inorder(root->kanan);
    }
}

// Fungsi untuk menghapus simpul terkecil (untuk BST)
pohon *hapusTerkecil(pohon *root) {
    if (root->kiri == NULL) {
        pohon *temp = root->kanan;
        free(root);
        return temp;
    }
    root->kiri = hapusTerkecil(root->kiri);
    return root;
}

// Fungsi untuk menghapus anggota dari BST
pohon *hapusBST(pohon *root, int id) {
    if (root == NULL) {
        return root; // ID tidak ditemukan
    }

    if (id < root->id) {
        root->kiri = hapusBST(root->kiri, id);
    } else if (id > root->id) {
        root->kanan = hapusBST(root->kanan, id);
    } else {
        // Jika ID ditemukan
        if (root->kiri == NULL) {
            pohon *temp = root->kanan;
            free(root);
            return temp;
        } else if (root->kanan == NULL) {
            pohon *temp = root->kiri;
            free(root);
            return temp;
        }

        // Jika memiliki dua anak, cari nilai terkecil di sebelah kanan
        pohon *temp = hapusTerkecil(root->kanan);
        root->id = temp->id;
        strcpy(root->nama, temp->nama);
        strcpy(root->buku_favorit, temp->buku_favorit);
        root->kanan = hapusBST(root->kanan, temp->id);
    }

    return root;
}

// Fungsi untuk menghapus anggota dari AVL
pohon *hapusAVL(pohon *root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->id) {
        root->kiri = hapusAVL(root->kiri, id);
    } else if (id > root->id) {
        root->kanan = hapusAVL(root->kanan, id);
    } else {
        // Jika ID ditemukan
        if (root->kiri == NULL) {
            pohon *temp = root->kanan;
            free(root);
            return temp;
        } else if (root->kanan == NULL) {
            pohon *temp = root->kiri;
            free(root);
            return temp;
        }

        // Jika memiliki dua anak, cari nilai terkecil di sebelah kanan
        pohon *temp = hapusTerkecil(root->kanan);
        root->id = temp->id;
        strcpy(root->nama, temp->nama);
        strcpy(root->buku_favorit, temp->buku_favorit);
        root->kanan = hapusAVL(root->kanan, temp->id);
    }

    // Update tinggi simpul dan lakukan rotasi untuk keseimbangan AVL
    int kiriTinggi = getTinggi(root->kiri);
    int kananTinggi = getTinggi(root->kanan);
    if (kiriTinggi > kananTinggi) {
        root->tinggi = 1 + kiriTinggi;
    } else {
        root->tinggi = 1 + kananTinggi;
    }

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->kiri) >= 0) {
        return rotasiKanan(root);
    }

    if (balance > 1 && getBalance(root->kiri) < 0) {
        root->kiri = rotasiKiri(root->kiri);
        return rotasiKanan(root);
    }

    if (balance < -1 && getBalance(root->kanan) <= 0) {
        return rotasiKiri(root);
    }

    if (balance < -1 && getBalance(root->kanan) > 0) {
        root->kanan = rotasiKanan(root->kanan);
        return rotasiKiri(root);
    }

    return root;
}

// Fungsi untuk membaca data dari file eksternal
typedef struct {
    int id;
    char nama[50];
    char buku_favorit[50];
} data;

void bacaDataFile(pohon **rootBST, pohon **rootAVL, const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (!file) {
        printf("Gagal membuka file: %s\n", namaFile);
        return;
    }

    int id;
    char nama[50], buku_favorit[50];
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &id, nama, buku_favorit) != EOF) {
        sisipBST(rootBST, id, nama, buku_favorit);
        *rootAVL = sisipAVL(*rootAVL, id, nama, buku_favorit);
    }

    fclose(file);
}

void simpanDataKeFile(pohon *root, const char *namaFile) {
    FILE *file = fopen(namaFile, "a"); // Open in append mode
    if (!file) {
        printf("Gagal membuka file untuk menyimpan data.\n");
        return;
    }

    if (root != NULL) {
        fprintf(file, "%d,%s,%s\n", root->id, root->nama, root->buku_favorit);
        simpanDataKeFile(root->kiri, namaFile);
        simpanDataKeFile(root->kanan, namaFile);
    }

    fclose(file);
}

void tampilkanHeaderTabel() {
    printf("+-------+----------------------+--------------------------------+\n");
    printf("|  ID   |        Nama          |          Buku Favorit          |\n");
    printf("+-------+----------------------+--------------------------------+\n");
}

// Fungsi menu utama
void menu() {
    pohon *rootBST = NULL;
    pohon *rootAVL = NULL;

    bacaDataFile(&rootBST, &rootAVL, "dataperpus.txt");

    int pilihan, id, tipe;
    char nama[50], buku_favorit[50];
    int jumlahData = 0; // Menambahkan pembatasan data

    printf("Pilih jenis pohon:\n");
    printf("1. BST\n");
    printf("2. AVL\n");
    printf("Pilihan: ");
    scanf("%d", &tipe);

    if (tipe != 1 && tipe != 2) {
        printf("Pilihan tidak valid. Keluar dari program.\n");
        return;
    }

    do {
        printf("Pilih menu:\n");
        printf("1. Tambah Anggota\n");
        printf("2. Cari Anggota\n");
        printf("3. Hapus Anggota\n");
        printf("4. Tampilkan Semua Anggota\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                if (jumlahData >= 10) {
                    printf("Data telah mencapai maksimal (10 data). Tidak dapat menambah anggota lagi.\n");
                    break;
                }

                printf("Masukkan ID anggota: ");
                scanf("%d", &id);
                printf("Masukkan nama anggota: ");
                scanf("%s", nama);
                printf("Masukkan buku favorit anggota: ");
                scanf("%s", buku_favorit);

                if (tipe == 1) {
                    sisipBST(&rootBST, id, nama, buku_favorit);
                } else {
                    rootAVL = sisipAVL(rootAVL, id, nama, buku_favorit);
                }

                // Simpan data ke dalam file
                simpanDataKeFile(rootBST, "dataperpus.txt");

                jumlahData++;
                break;

            case 2:
                printf("Masukkan ID anggota yang dicari: ");
                scanf("%d", &id);
                if (tipe == 1) {
                    pohon *foundBST = cari(rootBST, id);
                    if (foundBST) {
                        printf("Anggota ditemukan di BST\n");
                        printf("ID: %d\n", foundBST->id);
                        printf("Nama: %s\n", foundBST->nama);
                        printf("Buku Favorit: %s\n", foundBST->buku_favorit);
                    } else {
                        printf("Anggota tidak ditemukan di BST\n");
                    }
                } else {
                    pohon *foundAVL = cari(rootAVL, id);
                    if (foundAVL) {
                        printf("Anggota ditemukan di AVL\n");
                        printf("ID: %d\n", foundAVL->id);
                        printf("Nama: %s\n", foundAVL->nama);
                        printf("Buku Favorit: %s\n", foundAVL->buku_favorit);
                    } else {
                        printf("Anggota tidak ditemukan di AVL\n");
                    }
                }
                break;

            case 3:
                printf("Masukkan ID anggota yang ingin dihapus: ");
                scanf("%d", &id);
                if (tipe == 1) {
                    rootBST = hapusBST(rootBST, id);
                } else {
                    rootAVL = hapusAVL(rootAVL, id);
                }
                break;

            case 4:
                tampilkanHeaderTabel();
                if (tipe == 1) {
                    inorder(rootBST);
                } else {
                    inorder(rootAVL);
                }
                break;

            case 5:
                printf("Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilihan != 5);
}

int main() {
    menu();
    return 0;
}
