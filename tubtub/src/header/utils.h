#ifndef UTILS_H
#define UTILS_H

#include "user.h"
#include "obat.h"
#include "ruangan.h"
#include "antrian.h"

bool isUsernameTaken(UserSet *userSet, char *username);
void registerUser(UserSet *userSet, int id, char *username, char *password, char *role, char *penyakit);
void refreshDokterMap(DokterQueueMap *map, int *jumlahDokter, const UserSet *userSet);


#endif
