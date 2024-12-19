#include <stdio.h>

// Fungsi rekursif untuk elemen segitiga Pascal
int pascal(int baris, int posisi)
{
    if ((posisi == 0) || (posisi == baris))
    {
        return 1;
    }
    else
    {
        return pascal(baris - 1, posisi) + pascal(baris - 1, posisi - 1);
    }
}

int main()
{
    int tinggi = 6; // Mentukan tinggi segitiga Pascal

    for (int i = 0; i < tinggi; i++)
    {
        // Mencetak spasi untuk menjaga format segitiga
        for (int spasi = 0; spasi < tinggi - i; spasi++)
        {
            printf(" ");
        }

        // Mencetak elemen segitiga Pascal
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", pascal(i, j)); // Menambahkan spasi antara elemen
        }

        // Baris baru setelah setiap baris selesai
        printf("\n");
    }

    return 0;
}
