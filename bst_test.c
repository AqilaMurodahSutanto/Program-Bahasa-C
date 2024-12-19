#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree *pohon;

struct tree {
    int id;
    char nama[50];
    char buku_favorit[50];
    pohon kiri;
    pohon kanan;
};

// Fungsi untuk membuat simpul baru
pohon baru(int id, char *nama, char *buku_favorit) {
    pohon br = (pohon)malloc(sizeof(struct tree));
    br->id = id;
    strcpy(br->nama, nama);
    strcpy(br->buku_favorit, buku_favorit);
    br->kiri = NULL;
    br->kanan = NULL;
    return br;
}

// Fungsi untuk menyisipkan simpul pada BST
void sisip(pohon *ph, pohon sp) {
    if (*ph == NULL) {
        *ph = sp;
    } else {
        if (sp->id < (*ph)->id) {
            sisip(&(*ph)->kiri, sp);  // Menyisipkan di kiri
        } else if (sp->id > (*ph)->id) {
            sisip(&(*ph)->kanan, sp);  // Menyisipkan di kanan
        } else {
            printf("Anggota dengan ID %d sudah ada\n", sp->id);  // Jika anggota sudah ada
        }
    }
}

// Fungsi untuk mencari simpul dalam BST
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

// Fungsi untuk menghapus simpul
pohon hapus(pohon ph, int id) {
    if (ph == NULL) return ph;

    // Mencari simpul yang akan dihapus
    if (id < ph->id) {
        ph->kiri = hapus(ph->kiri, id);  // Mencari di kiri
    } else if (id > ph->id) {
        ph->kanan = hapus(ph->kanan, id);  // Mencari di kanan
    } else {
        // Jika node yang akan dihapus ditemukan
        if (ph->kiri == NULL) {
            pohon temp = ph->kanan;
            free(ph);
            return temp;
        } else if (ph->kanan == NULL) {
            pohon temp = ph->kiri;
            free(ph);
            return temp;
        }

        // Jika simpul memiliki dua anak
        pohon temp = ph->kanan;
        while (temp && temp->kiri != NULL) temp = temp->kiri;
        ph->id = temp->id;
        strcpy(ph->nama, temp->nama);
        strcpy(ph->buku_favorit, temp->buku_favorit);
        ph->kanan = hapus(ph->kanan, temp->id);  // Hapus simpul yang sudah diganti
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

// Fungsi untuk traversal inorder
void inorder(pohon ph) {
    if (ph != NULL) {
        inorder(ph->kiri);
        printf("%d - %s - %s\n", ph->id, ph->nama, ph->buku_favorit);
        inorder(ph->kanan);
    }
}

// Fungsi untuk traversal postorder
void postorder(pohon ph) {
    if (ph != NULL) {
        postorder(ph->kiri);
        postorder(ph->kanan);
        printf("%d - %s - %s\n", ph->id, ph->nama, ph->buku_favorit);
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
        printf("5. Lihat daftar anggota (Inorder)\n");
        printf("6. Lihat daftar anggota (Postorder)\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:  // Insert anggota
                printf("Masukkan ID anggota: ");
                scanf("%d", &id);
                printf("Masukkan nama anggota: ");
                scanf("%s", nama);
                printf("Masukkan buku favorit anggota: ");
                scanf("%s", buku_favorit);
                pohon sp = baru(id, nama, buku_favorit);
                sisip(&br, sp);
                break;
            case 2:  // Delete anggota
                printf("Masukkan ID anggota yang ingin dihapus: ");
                scanf("%d", &id);
                br = hapus(br, id);
                break;
            case 3:  // Search anggota
                printf("Masukkan ID anggota yang ingin dicari: ");
                scanf("%d", &id);
                pohon hasil = cari(br, id);
                if (hasil) {
                    printf("Anggota dengan ID %d ditemukan: %s - %s\n", id, hasil->nama, hasil->buku_favorit);
                } else {
                    printf("Anggota dengan ID %d tidak ditemukan.\n", id);
                }
                break;
            case 4:  // View anggota preorder
                printf("\nPreorder traversal:\n");
                preorder(br);
                break;
            case 5:  // View anggota inorder
                printf("\nInorder traversal:\n");
                inorder(br);
                break;
            case 6:  // View anggota postorder
                printf("\nPostorder traversal:\n");
                postorder(br);
                break;

            case 7:  // Exit
                return 0;
            default:
                printf("Pilihan tidak valid\n");
        }
    }
    return 0;
}
