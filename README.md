# Soal Shift Modul 2 [ Kelompok D9 ]

## Soal No. 1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile] _ grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.
### Jawab
Pertama pastinya sebelum mengubah nama kita melakukan select terhadap suatu file di dalam directory yaitu sbg berikut
```c
struct dirent *entry;
DIR *dir = opendir(".");
```
Command | Description 
--- | -----
struct dirent | sebuah struct yang merepresentasikan *seluruh isi file* dalam sebuah file directory
DIR | merupakan representasi dari lokasi file directory nya

###### Setelah itu saya buat ketentuan jika tidak directory kosong maka tidak terjadi apa
lalu sekarang adalah bagian pengubahan nama file serta pengubahan letak file
```c
char file1[255];  // state awal file
char file2[255];  // state proses
char file3[65];   // state akhir file

while((entry = readdir (dir))!=NULL){
  strcpy(file1,entry->d_name)                      // memasuki nama-nama dari file
  if(strstr(&file1[strlen(file1)-4], ".png")){     // mencari substring dari state awal bahwa di bagian akhirnya terdapat ekstensi ".png"
    memset(file3,0,sizeof(file3));                 // me-reset state proses serta state akhir agar tidak terjadi perulangan
    memset(file2,0,sizeof(file2));                 // terus menerus
    strcpy(file3, "/home/kyielas/modul2/gambar/"); // men-set lokasi file3 di directory 
    strncpy(file2,file1,strlen(file1)-4);          // men-set file2 berisi file1 yang stringnya dikurangi empat 
    strcat(file2, "_grey.png");                    // menambah suffix string "_grey"
    strcat(file3,file2);                           // menggabungkan state file 2 dan file 3 
    rename(file1,file3)                            // mengubah state awal menjadi state akhir
  }
}
```
