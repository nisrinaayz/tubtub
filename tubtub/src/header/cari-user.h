#ifndef CARI_USER_H
#define CARI_USER_H

#include "boolean.h"

#include "user.h"

int compareByIDAsc(const void *a, const void *b);
int binarySearchByID(UserSet *userSet, int id);              // Mengembalikan indeks atau -1 jika tidak ditemukan
int sequentialSearchByName(UserSet *userSet, char *name);    // Mengembalikan indeks atau -1 jika tidak ditemukan

void F08_cariUser(UserSet *userSet, Session session);
void F08_cariPasien(UserSet *userSet, Session session);
void F08_cariDokter(UserSet *userSet, Session session);

#endif
