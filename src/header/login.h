#ifndef F01_LOGIN_H
#define F01_LOGIN_H

#include "user.h"

// Melakukan proses login dengan memverifikasi username dan password
// I.S. Belum login, userSet dan session terdefinisi
// F.S. session diisi dengan user yang login jika berhasil, atau menampilkan pesan error jika gagal
void F01_login(UserSet *userSet, Session *session);

#endif