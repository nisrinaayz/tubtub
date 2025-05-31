#ifndef RUANGAN_H
#define RUANGAN_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAMA 100
#define MAKS_RUANGAN 100
#define MAKS_PASIEN 3

typedef struct {
    char nama[50];
} Pasien;

typedef struct {
    int id;
    int kapasitas;
    char dokter[50];
    int jumlahPasienDalamRuangan;
    Pasien pasienDalamRuangan[MAKS_PASIEN];
    int jumlahAntrian;
    Pasien antrian[MAKS_PASIEN];
    bool adaDokter;
} Ruangan;

typedef struct {
    Ruangan data[MAKS_RUANGAN];
    int jumlahRuangan;
} RuanganList;

#endif
