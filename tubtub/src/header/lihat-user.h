#ifndef LIHAT_USER_H
#define LIHAT_USER_H

#include "user.h"

int id_asc(const void *a, const void *b);
int id_desc(const void *a, const void *b);
int nama_asc(const void *a, const void *b);
int nama_desc(const void *a, const void *b);


void F07_lihatUser(User users[], int n, Session session);
void F07_lihatPasien(User users[], int n, Session session);
void F07_lihatDokter(User users[], int n, Session session);

#endif