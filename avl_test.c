#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree *pohon;

struct tree {
    int id;
    char nama[50];
    char buku_favorit[50];
    int tinggi;
    pohon kiri;
    pohon kanan;
};

// Fungsi untuk membuat simpul baru
pohon baru(int id, char *nama, char *buku_favorit) {
    pohon br = (pohon)malloc(sizeof(struct tree));
    br->id = id;
    strcpy(br->nama, nama);
    strcpy(br->buku_favorit, buku_favorit);
    br->tinggi = 1;
    br->kiri = NULL;
    br->kanan = NULL;
    return br;
}

// Fungsi untuk mendapatkan tinggi node
int tinggi(pohon ph) {
    return (ph == NULL) ? 0 : ph->tinggi;
}

// Fungsi untuk mendapatkan balance factor
int balanceFactor(pohon ph) {
    return (ph == NULL) ? 0 : tinggi(ph->kiri) - tinggi(ph->kanan);
}

// Fungsi rotasi kanan
pohon rotasiKanan(pohon y) {
    pohon x = y->kiri;
    pohon T = x->kanan;

    x->kanan = y;
    y->kiri = T;

    y->tinggi = 1 + (tinggi(y->kiri) > tinggi(y->kanan) ? tinggi(y->kiri) : tinggi(y->kanan));
    x->tinggi = 1 + (tinggi(x->kiri) > tinggi(x->kanan) ? tinggi(x->kiri) : tinggi(x->kanan));

    return x;
}

// Fungsi rotasi kiri
pohon rotasiKiri(pohon x) {
    pohon y = x->kanan;
    pohon T = y->kiri;

    y->kiri = x;
    x->kanan = T;

    x->tinggi = 1 + (tinggi(x->kiri) > tinggi(x->kanan) ? tinggi(x->kiri) : tinggi(x->kanan));
    y->tinggi = 1 + (tinggi(y->kiri) > tinggi(y->kanan) ? tinggi(y->kiri) : tinggi(y->kanan));

    return y;
}

// Fungsi untuk menyisipkan anggota pada AVL
pohon sisip(pohon ph, int id, char *nama, char *buku_favorit) {
    if (ph == NULL) return baru(id, nama, buku_favorit);

    if (id < ph->id) {
        ph->kiri = sisip(ph->kiri, id, nama, buku_favorit);
    } else if (id > ph->id) {
        ph->kanan = sisip(ph->kanan, id, nama, buku_favorit);
    } else {
        printf("Anggota dengan ID %d sudah ada\n", id);
        return ph;
    }

    ph->tinggi = 1 + (tinggi(ph->kiri) > tinggi(ph->kanan) ? tinggi(ph->kiri) : tinggi(ph->kanan));

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

// Fungsi untuk traversal preorder
void preorder(pohon ph) {
    if (ph != NULL) {
        printf("%d - %s - %s\n", ph->id, ph->nama, ph->buku_favorit);
        preorder(ph->kiri);
        preorder(ph->kanan);
    }
}

// Fungsi untuk traversal inverse
void inverse(pohon ph) {
    if (ph != NULL) {
        inverse(ph->kanan);
        printf("%d - %s - %s\n", ph->id, ph->nama, ph->buku_favorit);
        inverse(ph->kiri);
    }
}

// Fungsi untuk mencari anggota dalam AVL
pohon cari(pohon ph, int id) {
    if (ph == NULL || ph->id == id) {
        return ph;
    }
    if (id < ph->id) {
        return cari(ph->kiri, id);  // Mencari di kiri
    } else {
        return cari(ph->kanan, id);  // Mencari di kanan
    }
}

// Menu utama
int main() {
    pohon br = NULL;
    int pilihan, id;
    char nama[50], buku_favorit[50];
    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Masukkan anggota baru\n");
        printf("2. Hapus anggota\n");
        printf("3. Cari anggota\n");
        printf("4. Lihat daftar anggota (Preorder)\n");
        printf("5. Lihat daftar anggota (Inverse)\n");
        printf("6. Keluar\n");
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
                br = sisip(br, id, nama, buku_favorit);
                break;
            case 2:
                // Hapus anggota belum ditambahkan pada AVL
                break;
            case 3:
                printf("Masukkan ID anggota yang ingin dicari: ");
                scanf("%d", &id);
                pohon hasil = cari(br, id);
                if (hasil) {
                    printf("Anggota dengan ID %d ditemukan: %s - %s\n", id, hasil->nama, hasil->buku_favorit);
                } else {
                    printf("Anggota dengan ID %d tidak ditemukan.\n", id);
                }
                break;
            case 4:
                printf("\nPreorder traversal:\n");
                preorder(br);
                break;
            case 5:
                printf("\nInverse traversal:\n");
                inverse(br);
                break;
            case 6:
                return 0;
            default:
                printf("Pilihan tidak valid\n");
        }
    }
    return 0;
}
