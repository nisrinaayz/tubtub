#ifndef OBAT_H
#define OBAT_H

#include <stdio.h>
#include <string.h>
#include "user.h"
#include "ruangan.h"

#define MAX_OBAT_PER_PENYAKIT 10
#define MAX_OBAT 50
#define MAX_INVENTORY 20
#define MAX_PERUT 20
#define NAMA_OBAT_LEN 50

typedef struct {
    char penyakit[50];
    int jumlahObat;
    char daftarObat[MAX_OBAT_PER_PENYAKIT][NAMA_OBAT_LEN];
} PenyakitObatMap;

typedef struct {
    int jumlah;
    char namaObat[MAX_INVENTORY][NAMA_OBAT_LEN];
} InventoryObat;

typedef struct {
    int top;
    char namaObat[MAX_PERUT][NAMA_OBAT_LEN];
} StackPerut;

#endif
