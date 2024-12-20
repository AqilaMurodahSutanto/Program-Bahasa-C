#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
};

void printList(struct Node *node)
{ // fungsi untuk mencetak data
    while (node != NULL)
    {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main()
{
    // Deklarasi dan inisialisasi node-node
    struct Node n1, n2, n3, n4;

    // Isi data dan hubungkan node-node
    n1.data = 10;
    n1.next = &n2;

    n2.data = 20;
    n2.next = &n3;

    n3.data = 30;
    n3.next = &n4;

    n4.data = 40;
    n4.next = NULL;

    // Cetak linked list
    printList(&n1);

    return 0;
}
