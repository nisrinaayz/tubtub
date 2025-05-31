# Deskripsi Singkat Cara Menjalankan Program

A. Persiapkan file

1. Pastikan semua file `.c` sudah berada di dalam folder `src/c`.
2. Pastikan semua file `.h` sudah berada di dalam folder `src/header`.
3. Pastikan file `Makefile` dan `main.c` ada di dalam folder `src`.

B. Kompilasi program

1. Buka terminal dan masuk ke folder `src`:

   ```
   cd src
   ```
2. Jalankan perintah berikut untuk melakukan kompilasi:

   ```
   make
   ```
3. Setelah build selesai, jalankan program dengan perintah:

   ```
   ./build/rs-nimons <jumlah_ruangan>
   ```

   Contoh:

   ```
   ./build/rs-nimons 5
   ```
