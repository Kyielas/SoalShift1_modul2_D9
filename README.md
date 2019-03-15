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

## Soal No. 2
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

### Jawab

Untuk mengecek siapakah owner dan group dari file elen.ku yang sudah dibuat, maka dibutuhkan sebuah fungsi yang dapat digunakan untuk melihatnya. Untuk itu, maka digunakanlah perintah berikut.

Command | Description 
--- | -----
``` getpwuid() ``` | sebuah perintah yang digunakan untuk mengecek User ID
``` getgrgid() ``` | sebuah perintah yang digunakan untuk mengecek Group ID

Main program dari file tersebut dapat dilihat seperti berikut.

```c
while(1) {
    struct passwd *pwd;
	struct group *grp;
	struct stat fileinfo;

	pid_t child_id;
	int status;
	
	stat("/home/ivan/Sisop/Praktikum2/hatiku/elen.ku", &fileinfo);
	pwd=getpwuid(fileinfo.st_uid);                                  //mengecek owner
	grp=getgrgid(fileinfo.st_gid);                                  //mengecek group
	
	chmod("/home/ivan/Sisop/Praktikum2/hatiku/elen.ku", 0777);      //mengubah permission
	
	if(strcmp(pwd->pw_name, "www-data")==0 && strcmp(grp->gr_name, "www-data")==0) {    //mengecek jika owner dan group == www-data
			char *argv[3] = {"rm", "/home/ivan/Sisop/Praktikum2/hatiku/elen.ku", NULL};
	    	execv("/bin/rm", argv);                                 //menghapus file elen.ku
		
	}
    sleep(3);                                                       //membuat program bekerja setiap 3 detik
  }
```