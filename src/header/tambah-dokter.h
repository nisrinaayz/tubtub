#ifndef TAMBAHDOKTER_H
#define TAMBAHDOKTER_H

#include "user.h"
#include "ruangan.h"
#include "utils.h"

// Menambahkan dokter baru oleh Manager
// I.S. session harus login sebagai Manager, userSet terdefinisi
// F.S. Dokter baru ditambahkan ke dalam userSet jika username unik
void F10_tambahDokter(UserSet *userSet, Session session);

// Meng-assign dokter ke ruangan tertentu (jika belum memiliki ruangan)
// I.S. userSet dan ruanganList terdefinisi
// F.S. Dokter diassign ke ruangan jika belum ditempati dan belum punya ruangan
void F10_assignDokter(UserSet *userSet, RuanganList *ruanganList);

#endif