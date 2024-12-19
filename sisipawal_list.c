#include <stdio.h>
#include <stdlib.h>

// Definisi struktur Node
struct Node
{
    int data;
    struct Node *next;
};

// Fungsi untuk menyisipkan elemen di awal linked list
void insertAtBeginning(struct Node **head, int new_data)
{
    // Alokasi memori untuk node baru
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    // Isi data ke dalam node baru
    new_node->data = new_data;

    // Hubungkan node baru dengan head saat ini
    new_node->next = *head;

    // Pindahkan head ke node baru
    *head = new_node;
}

// Fungsi untuk mencetak elemen-elemen dalam linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main()
{
    // Deklarasi dan inisialisasi node-node yang sudah ada
    struct Node *head = NULL;
    struct Node *second = NULL;
    struct Node *third = NULL;

    // Alokasi memori untuk 3 node
    head = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third = (struct Node *)malloc(sizeof(struct Node));

    // Isi data dan hubungkan node-node
    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = NULL;

    // Cetak linked list sebelum penyisipan
    printf("Linked list sebelum penyisipan: ");
    printList(head);

    // Sisipkan elemen baru di awal linked list
    insertAtBeginning(&head, 5);

    // Cetak linked list setelah penyisipan
    printf("Linked list setelah penyisipan: ");
    printList(head);

    return 0;
}
