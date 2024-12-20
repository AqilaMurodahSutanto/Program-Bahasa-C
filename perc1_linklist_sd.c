#include <stdio.h>
#include <stdlib.h>

// Definisi struktur untuk node (simpul) dalam linked list
struct Node
{
    int data;
    struct Node *next;
};

// Fungsi untuk menambahkan simpul baru di bagian depan (LIFO)
void push(struct Node **head, int newData)
{
    // 1. Alokasi simpul baru
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    // 2. Isi data ke dalam simpul baru
    newNode->data = newData;

    // 3. Hubungkan simpul baru ke head lama
    newNode->next = *head;

    // 4. Jadikan simpul baru sebagai head
    *head = newNode;
}

// Fungsi untuk menampilkan isi linked list
void printList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    struct Node *head = NULL; // Linked list awalnya kosong

    // Tambahkan data ke linked list
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);

    // Cetak isi linked list
    printList(head);

    return 0;
}
