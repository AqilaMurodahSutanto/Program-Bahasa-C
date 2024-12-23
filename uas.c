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

// Rotasi kanan (AVL)
pohon *rotasiKanan(pohon *y) {
    pohon *x = y->kiri;
    pohon *T2 = x->kanan;

    x->kanan = y;
    y->kiri = T2;

    if (y->kiri == NULL && y->kanan == NULL) {
        y->tinggi = 1;
    } else if (getTinggi(y->kiri) > getTinggi(y->kanan)) {
        y->tinggi = 1 + getTinggi(y->kiri);
    } else {
        y->tinggi = 1 + getTinggi(y->kanan);
    }

    if (x->kiri == NULL && x->kanan == NULL) {
        x->tinggi = 1;
    } else if (getTinggi(x->kiri) > getTinggi(x->kanan)) {
        x->tinggi = 1 + getTinggi(x->kiri);
    } else {
        x->tinggi = 1 + getTinggi(x->kanan);
    }

    return x;
}

// Rotasi kiri (AVL)
pohon *rotasiKiri(pohon *x) {
    pohon *y = x->kanan;
    pohon *T2 = y->kiri;

    y->kiri = x;
    x->kanan = T2;

    if (x->kiri == NULL && x->kanan == NULL) {
        x->tinggi = 1;
    } else if (getTinggi(x->kiri) > getTinggi(x->kanan)) {
        x->tinggi = 1 + getTinggi(x->kiri);
    } else {
        x->tinggi = 1 + getTinggi(x->kanan);
    }

    if (y->kiri == NULL && y->kanan == NULL) {
        y->tinggi = 1;
    } else if (getTinggi(y->kiri) > getTinggi(y->kanan)) {
        y->tinggi = 1 + getTinggi(y->kiri);
    } else {
        y->tinggi = 1 + getTinggi(y->kanan);
    }

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

    if (node->kiri == NULL && node->kanan == NULL) {
        node->tinggi = 1;
    } else if (getTinggi(node->kiri) > getTinggi(node->kanan)) {
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


// Fungsi untuk menampilkan header tabel
void tampilkanHeaderTabel() {
    printf("+-------+----------------------+--------------------------------+\n");
    printf("|  ID   |        Nama          |          Buku Favorit          |\n");
    printf("+-------+----------------------+--------------------------------+\n");
}

// Fungsi menu utama
// Fungsi untuk menambahkan data awal
void masukkanDataAwal(pohon **root, int tipe) {
    if (tipe == 1) {
        // Untuk BST
        sisipBST(root, 1, "Ali", "Ketika Cinta Bertasbih");
        sisipBST(root, 2, "Budi", "Hujan-Tere Liye");
        sisipBST(root, 3, "Citra", "Bedebah di Ujung Tanduk");
        sisipBST(root, 4, "Dewi", "Pulang-Tere liye");
        sisipBST(root, 5, "Eko", "Jaringan Komputer");
        sisipBST(root, 6, "Abi", "Ayahku Bukan Pembohong");
        sisipBST(root, 7, "Toryl", "Buku Minta Dibanting");
        sisipBST(root, 8, "Rahma", "Overthingking-Alvin Syahrin");
        sisipBST(root, 9, "Liza", "Struktur Data");
        sisipBST(root, 10, "Aqila", "Pemrograman Bahasa C");
    } else if (tipe == 2) {
        // Untuk AVL
        *root = sisipAVL(*root, 1, "Ali", "Ketika Cinta Bertasbih");
        *root = sisipAVL(*root, 2, "Citra", "Bedebah di Ujung Tanduk");
        *root = sisipAVL(*root, 4, "Dewi", "Pulang-Tere liye");
        *root = sisipAVL(*root, 5, "Eko", "Jaringan Komputer");
        *root = sisipAVL(*root, 6, "Abi", "Ayahku Bukan Pembohong");
        *root = sisipAVL(*root, 7, "Toryl", "Buku Minta Dibanting");
        *root = sisipAVL(*root, 8, "Rahma", "Overthingking-Alvin Syahrin");
        *root = sisipAVL(*root, 9, "Liza", "Struktur Data");
        *root = sisipAVL(*root, 10, "Aqila", "Pemrograman Bahasa C");
    }
}

// Fungsi menu utama
void menu() {
    pohon *rootBST = NULL;
    pohon *rootAVL = NULL;
    int pilihan, id, tipe;
    char nama[50], buku_favorit[50];

    printf("Pilih jenis pohon:\n");
    printf("1. BST\n");
    printf("2. AVL\n");
    printf("Pilihan: ");
    scanf("%d", &tipe);

    if (tipe != 1 && tipe != 2) {
        printf("Pilihan tidak valid. Keluar dari program.\n");
        return;
    }

    // Menambahkan data awal
    if (tipe == 1) {
        masukkanDataAwal(&rootBST, tipe);
    } else {
        masukkanDataAwal(&rootAVL, tipe);
    }

    do {
        printf("\n=== Menu ===\n");
        printf("1. Tambah anggota\n");
        printf("2. Cari anggota\n");
        printf("3. Hapus anggota\n");
        printf("4. Lihat anggota (Inorder)\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            printf("Masukkan ID anggota: ");
            scanf("%d", &id);
            printf("Masukkan nama anggota: ");
            scanf("%s", nama);
            printf("Masukkan buku favorit anggota: ");
            scanf("%s", buku_favorit);
            if (tipe == 1) {
                sisipBST(&rootBST, id, nama, buku_favorit); // Menambah anggota ke BST
            } else if (tipe == 2) {
                rootAVL = sisipAVL(rootAVL, id, nama, buku_favorit); // Menambah anggota ke AVL
            }
        } else if (pilihan == 2) {
            printf("Masukkan ID anggota yang dicari: ");
            scanf("%d", &id);
            pohon *result = (tipe == 1) ? cari(rootBST, id) : cari(rootAVL, id);
            if (result != NULL) {
                printf("Anggota ditemukan: ID=%d, Nama=%s, Buku Favorit=%s\n", result->id, result->nama, result->buku_favorit);
            } else {
                printf("Anggota dengan ID %d tidak ditemukan.\n", id);
            }
        } else if (pilihan == 3) {
            printf("Masukkan ID anggota yang akan dihapus: ");
            scanf("%d", &id);
            if (tipe == 1) {
                rootBST = hapusBST(rootBST, id); // Menghapus anggota dari BST
            } else if (tipe == 2) {
                rootAVL = hapusAVL(rootAVL, id); // Menghapus anggota dari AVL
            }
        } else if (pilihan == 4) {
            tampilkanHeaderTabel();
            if (tipe == 1) {
                inorder(rootBST); // Menampilkan anggota pada BST
            } else if (tipe == 2) {
                inorder(rootAVL); // Menampilkan anggota pada AVL
            }
            printf("+-------+----------------------+--------------------------------+\n");
        } else if (pilihan == 5) {
            printf("Keluar dari program...\n");
            break;
        } else {
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 5);
}

int main() {
    menu(); // Menjalankan menu utama
    return 0;
}


