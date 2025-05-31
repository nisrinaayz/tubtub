#ifndef REGISTERPASIEN_H
#define REGISTERPASIEN_H

#include "user.h"

// Mendaftarkan akun baru untuk role Pasien
// I.S. userSet terdefinisi
// F.S. Akun baru ditambahkan ke dalam userSet jika username belum terpakai
void F02_registerPasien(UserSet *userSet);

#endif