#ifndef DENAHRUMAHSAKIT_H
#define DENAHRUMAHSAKIT_H

#include "ruangan.h"
#include "utils.h"

// Menampilkan denah rumah sakit berbasis ruangan satu baris
// I.S. ruanganList terdefinisi
// F.S. Menampilkan denah ruangan secara visual
void S01_lihatDenah(RuanganList ruanganList);

// Menampilkan detail ruangan tertentu berdasarkan nomor
// I.S. ruanganList terdefinisi
// F.S. Menampilkan informasi dokter dan pasien dalam ruangan yang dipilih
void S01_lihatRuangan(RuanganList *ruanganList);


#endif