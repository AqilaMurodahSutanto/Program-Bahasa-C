#include <stdio.h>
#include <stdlib.h>

// Definisikan struktur DNode untuk doubly linked list
struct DNode
{
    int data;
    struct DNode *next;
    struct DNode *prev;
};

// Fungsi untuk menghapus simpul dari awal list
void deleteAtHead(struct DNode **head_ref)
{
    // Cek apakah list kosong
    if (*head_ref == NULL)
    {
        printf("List kosong, tidak ada yang dihapus.\n");
        return;
    }

    // Simpan simpul yang akan dihapus
    struct DNode *hapus = *head_ref;

    // Atur prev dari simpul berikutnya ke NULL jika ada
    if (hapus->next != NULL)
    {
        hapus->next->prev = NULL;
    }

    // Perbarui head ke simpul berikutnya
    *head_ref = hapus->next;

    // Bebaskan memori dari simpul yang dihapus
    free(hapus);

    printf("Simpul dihapus dari awal.\n");
}

// Fungsi untuk mencetak list secara forward
void printList(struct DNode *head)
{
    printf("Traversing List:\n");
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main()
{
    // Membuat list dengan beberapa simpul
    struct DNode *head = (struct DNode *)malloc(sizeof(struct DNode));
    struct DNode *kedua = (struct DNode *)malloc(sizeof(struct DNode));
    struct DNode *ketiga = (struct DNode *)malloc(sizeof(struct DNode));

    // Inisialisasi dan menghubungkan simpul
    head->data = 10; // Simpul pertama
    head->next = kedua;
    head->prev = NULL; // Simpul pertama tidak memiliki simpul sebelumnya

    kedua->data = 20; // Simpul kedua
    kedua->next = ketiga;
    kedua->prev = head;

    ketiga->data = 30; // Simpul ketiga
    ketiga->next = NULL;
    ketiga->prev = kedua;

    // Mencetak list sebelum penghapusan
    printf("List sebelum dihapus:\n");
    printList(head);

    // Menghapus simpul dari awal
    deleteAtHead(&head);

    // Mencetak list setelah penghapusan
    printf("List setelah dihapus dari awal:\n");
    printList(head);

    // Bebaskan sisa memori
    free(kedua);
    free(ketiga);

    return 0;
}
