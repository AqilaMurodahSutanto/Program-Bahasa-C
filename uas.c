#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur pohon untuk BST dan AVL
typedef struct tree *pohon;

struct tree {
    int id;
    char nama[50];
    char buku_favorit[50];
    int tinggi;  // Digunakan untuk AVL
    pohon kiri;
    pohon kanan;
};

// Fungsi untuk membuat simpul baru
pohon baru(int id, char *nama, char *buku_favorit) {
    pohon br = (pohon)malloc(sizeof(struct tree));
    br->id = id;
    strcpy(br->nama, nama);
    strcpy(br->buku_favorit, buku_favorit);
    br->tinggi = 1;  // Default tinggi untuk AVL
    br->kiri = NULL;
    br->kanan = NULL;
    return br;
}

// Fungsi untuk mendapatkan tinggi node (khusus AVL)
int tinggi(pohon ph) {
    if (ph == NULL) {
        return 0;  // Jika simpul NULL, kembalikan tinggi 0
    } else {
        return ph->tinggi;  // Jika simpul tidak NULL, kembalikan tinggi simpul
    }
}

// Fungsi untuk mendapatkan balance factor (khusus AVL)
int balanceFactor(pohon ph) {
    if (ph == NULL) {
        return 0;  // Jika simpul NULL, balance factor adalah 0
    } else {
        int tinggiKiri = tinggi(ph->kiri);  // Tinggi anak kiri
        int tinggiKanan = tinggi(ph->kanan);  // Tinggi anak kanan
        return tinggiKiri - tinggiKanan;  // Selisih tinggi kiri dan kanan
    }
}

// Fungsi rotasi kanan (AVL)
pohon rotasiKanan(pohon y) {
    pohon x = y->kiri;       // Simpul x adalah anak kiri dari y
    pohon T = x->kanan;      // Simpan subpohon kanan dari x

    // Proses rotasi
    x->kanan = y;            // x menjadi anak kanan dari y
    y->kiri = T;             // y menjadi anak kiri dari subpohon kanan x

    // Perbarui tinggi simpul y
    int tinggiKiriY = tinggi(y->kiri);  // Tinggi anak kiri y
    int tinggiKananY = tinggi(y->kanan);  // Tinggi anak kanan y
    y->tinggi = 1 + (tinggiKiriY > tinggiKananY ? tinggiKiriY : tinggiKananY);

    // Perbarui tinggi simpul x
    int tinggiKiriX = tinggi(x->kiri);  // Tinggi anak kiri x
    int tinggiKananX = tinggi(x->kanan);  // Tinggi anak kanan x
    x->tinggi = 1 + (tinggiKiriX > tinggiKananX ? tinggiKiriX : tinggiKananX);

    // Kembalikan simpul baru sebagai akar
    return x;
}

// Fungsi rotasi kiri (AVL)
pohon rotasiKiri(pohon x) {
    pohon y = x->kanan;      // Simpul y adalah anak kanan dari x
    pohon T = y->kiri;       // Simpan subpohon kiri dari y

    // Proses rotasi
    y->kiri = x;             // y menjadi anak kiri dari x
    x->kanan = T;            // x menjadi anak kanan dari subpohon kiri y

    // Perbarui tinggi simpul x
    int tinggiKiriX = tinggi(x->kiri);  // Tinggi anak kiri x
    int tinggiKananX = tinggi(x->kanan);  // Tinggi anak kanan x
    x->tinggi = 1 + (tinggiKiriX > tinggiKananX ? tinggiKiriX : tinggiKananX);

    // Perbarui tinggi simpul y
    int tinggiKiriY = tinggi(y->kiri);  // Tinggi anak kiri y
    int tinggiKananY = tinggi(y->kanan);  // Tinggi anak kanan y
    y->tinggi = 1 + (tinggiKiriY > tinggiKananY ? tinggiKiriY : tinggiKananY);

    // Kembalikan simpul baru sebagai akar
    return y;
}

// Fungsi untuk menyisipkan anggota pada BST
void sisipBST(pohon *ph, pohon sp) {
    if (*ph == NULL) {
        *ph = sp;
    } else {
        if (sp->id < (*ph)->id) {
            sisipBST(&(*ph)->kiri, sp);  // Menyisipkan di kiri
        } else if (sp->id > (*ph)->id) {
            sisipBST(&(*ph)->kanan, sp);  // Menyisipkan di kanan
        } else {
            printf("Anggota dengan ID %d sudah ada\n", sp->id);
        }
    }
}

// Fungsi untuk menyisipkan anggota pada AVL
pohon sisipAVL(pohon ph, int id, char *nama, char *buku_favorit) {
    if (ph == NULL) {
        return baru(id, nama, buku_favorit);
    }

    if (id < ph->id) {
        ph->kiri = sisipAVL(ph->kiri, id, nama, buku_favorit);
    } else if (id > ph->id) {
        ph->kanan = sisipAVL(ph->kanan, id, nama, buku_favorit);
    } else {
        printf("Anggota dengan ID %d sudah ada\n", id);
        return ph;
    }

    int tinggiKiri = tinggi(ph->kiri);
    int tinggiKanan = tinggi(ph->kanan);
    ph->tinggi = 1 + (tinggiKiri > tinggiKanan ? tinggiKiri : tinggiKanan);

    int balance = balanceFactor(ph);

    if (balance > 1 && id < ph->kiri->id) {
        return rotasiKanan(ph);
    }
    if (balance < -1 && id > ph->kanan->id) {
        return rotasiKiri(ph);
    }
    if (balance > 1 && id > ph->kiri->id) {
        ph->kiri = rotasiKiri(ph->kiri);
        return rotasiKanan(ph);
    }
    if (balance < -1 && id < ph->kanan->id) {
        ph->kanan = rotasiKanan(ph->kanan);
        return rotasiKiri(ph);
    }

    return ph;
}

// Fungsi untuk mencari anggota
pohon cari(pohon ph, int id) {
    if (ph == NULL || ph->id == id) {
        return ph;
    }
    if (id < ph->id) {
        return cari(ph->kiri, id);
    } else {
        return cari(ph->kanan, id);
    }
}

// Fungsi untuk menampilkan header tabel
void tampilkanHeaderTabel() {
    printf("+-------+----------------------+--------------------------------+\n");
    printf("|  ID   |        Nama          |          Buku Favorit          |\n");
    printf("+-------+----------------------+--------------------------------+\n");
}

// Fungsi untuk traversal preorder
void preorder(pohon ph) {
    if (ph != NULL) {
        printf("| %-5d | %-20s | %-30s |\n", ph->id, ph->nama, ph->buku_favorit);
        preorder(ph->kiri);
        preorder(ph->kanan);
    }
}

// Fungsi untuk traversal inorder
void inorder(pohon ph) {
    if (ph != NULL) {
        inorder(ph->kiri);
        printf("| %-5d | %-20s | %-30s |\n", ph->id, ph->nama, ph->buku_favorit);
        inorder(ph->kanan);
    }
}

// Fungsi untuk mencari simpul dengan nilai terkecil
pohon cariTerkecil(pohon ph) {
    while (ph->kiri != NULL) {
        ph = ph->kiri;
    }
    return ph;
}

// Fungsi untuk menghapus anggota pada BST
pohon hapusBST(pohon ph, int id) {
    if (ph == NULL) {
        return ph;
    }

    if (id < ph->id) {
        ph->kiri = hapusBST(ph->kiri, id);
    } else if (id > ph->id) {
        ph->kanan = hapusBST(ph->kanan, id);
    } else {
        if (ph->kiri == NULL) {
            pohon temp = ph->kanan;
            free(ph);
            return temp;
        } else if (ph->kanan == NULL) {
            pohon temp = ph->kiri;
            free(ph);
            return temp;
        }

        pohon temp = cariTerkecil(ph->kanan);
        ph->id = temp->id;
        strcpy(ph->nama, temp->nama);
        strcpy(ph->buku_favorit, temp->buku_favorit);
        ph->kanan = hapusBST(ph->kanan, temp->id);
    }
    return ph;
}

// Fungsi untuk menghapus anggota pada AVL
pohon hapusAVL(pohon ph, int id) {
    if (ph == NULL) {
        return ph;
    }

    if (id < ph->id) {
        ph->kiri = hapusAVL(ph->kiri, id);
    } else if (id > ph->id) {
        ph->kanan = hapusAVL(ph->kanan, id);
    } else {
        if (ph->kiri == NULL) {
            pohon temp = ph->kanan;
            free(ph);
            return temp;
        } else if (ph->kanan == NULL) {
            pohon temp = ph->kiri;
            free(ph);
            return temp;
        }

        pohon temp = cariTerkecil(ph->kanan);
        ph->id = temp->id;
        strcpy(ph->nama, temp->nama);
        strcpy(ph->buku_favorit, temp->buku_favorit);
        ph->kanan = hapusAVL(ph->kanan, temp->id);
    }

    int tinggiKiri = tinggi(ph->kiri);
    int tinggiKanan = tinggi(ph->kanan);
    ph->tinggi = 1 + (tinggiKiri > tinggiKanan ? tinggiKiri : tinggiKanan);

    int balance = balanceFactor(ph);

    if (balance > 1 && balanceFactor(ph->kiri) >= 0) {
        return rotasiKanan(ph);
    }
    if (balance < -1 && balanceFactor(ph->kanan) <= 0) {
        return rotasiKiri(ph);
    }
    if (balance > 1 && balanceFactor(ph->kiri) < 0) {
        ph->kiri = rotasiKiri(ph->kiri);
        return rotasiKanan(ph);
    }
    if (balance < -1 && balanceFactor(ph->kanan) > 0) {
        ph->kanan = rotasiKanan(ph->kanan);
        return rotasiKiri(ph);
    }

    return ph;
}

//Fungsi Menu Utama
void menuPohon(int tipe) {
    pohon root = NULL;
    int pilihan, id;
    char nama[50], buku_favorit[50];

    do {
        printf("\n=== Menu ");
        if (tipe == 1) {
            printf("BST ===\n");
        } else {
            printf("AVL ===\n");
        }

        printf("1. Tambah anggota\n");
        printf("2. Cari anggota\n");
        printf("3. Lihat anggota (Preorder)\n");
        printf("4. Hapus anggota\n");
        printf("5. Lihat anggota (Inorder)\n");
        printf("6. Kembali\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukkan ID anggota: ");
                scanf("%d", &id);
                printf("Masukkan nama anggota: ");
                scanf("%s", nama);
                printf("Masukkan buku favorit anggota: ");
                scanf("%s", buku_favorit);

                if (tipe == 1) {
                    pohon sp = baru(id, nama, buku_favorit);
                    sisipBST(&root, sp);
                } else {
                    root = sisipAVL(root, id, nama, buku_favorit);
                }
                break;
            case 2:
                printf("Masukkan ID anggota yang ingin dicari: ");
                scanf("%d", &id);
                pohon hasil = cari(root, id);
                if (hasil) {
                    printf("Anggota ditemukan: %d - %s - %s\n", hasil->id, hasil->nama, hasil->buku_favorit);
                } else {
                    printf("Anggota dengan ID %d tidak ditemukan.\n", id);
                }
                break;
            case 3:
                printf("\nDaftar anggota (Preorder):\n");
                tampilkanHeaderTabel();
                preorder(root);
                break;
            case 4:
                printf("Masukkan ID anggota yang ingin dihapus: ");
                scanf("%d", &id);
                if (tipe == 1) {
                    root = hapusBST(root, id);
                } else {
                    root = hapusAVL(root, id);
                }
                break;
            case 5:
                printf("\nDaftar anggota (Inorder):\n");
                tampilkanHeaderTabel();
                inorder(root);
                break;
            case 6:
                break; // Keluar dari loop
            default:
                printf("Pilihan tidak valid\n");
        }
    } while (pilihan != 6); // Loop terus berjalan sampai pengguna memilih untuk kembali (pilihan 6)
}


int main() {
    int tipe;
    printf("Pilih tipe pohon:\n");
    printf("1. BST\n");
    printf("2. AVL\n");
    printf("Pilihan: ");
    scanf("%d", &tipe);
    menuPohon(tipe);
    return 0;
}
