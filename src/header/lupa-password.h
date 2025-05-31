#ifndef LUPAPASSWORD_H
#define LUPAPASSWORD_H

#include "user.h"

// Melakukan run-length encoding pada string input
// I.S. input string terdefinisi
// F.S. output string berisi hasil RLE dari input
void runLengthEncode(char input[], char output[]);

// Melakukan reset password menggunakan validasi kode unik
// I.S. userSet terdefinisi, user lupa password
// F.S. Password user akan diganti jika kode unik cocok, atau muncul pesan kesalahan
void F04_lupaPassword(UserSet *userSet);

#endif