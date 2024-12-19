// asumsikan elemen pertama dalam array adalah elemen dengan angka terkecil,
// simpan nilai dan indeks elemen tersebut ke dalam variabel sementara
// dengan pengulangan
// cek satu per satu elemen pada array apakah ada yang lebih kecil dari elemen pertama
// jika iya, simpan nilai dan indeks elemen tersebut ke dalam variabel sementara
// tukarkan elemen yang lebih kecil tersebut
// dengan elemen pertama(paling kiri) dalam pengulangan
// ulangi langkah-langkah tersebut hingga semua elemen terurut

#include <stdio.h>

void Selectionsort (int data[], int n){
    int pos;
    int temp;
    for (int i=0; i < n-1 ; i++){
        pos = i;
        for (int j= i+1; j<n; j++){
            if (data[j] < data[pos])
            {
                pos = j;
            }
                temp = data[pos];
                data[pos] = data[i];
                data[i] = temp;
        }
    }
}
int main(){
    int data[] = {5,7,3,9,8,2};
    int n = 6;

    Selectionsort(data,n);

    for (int i = 0; i < n; i++)
    {
        printf("%d, ", data[i]);
    }

    return 0;

}
