#ifndef ANTRIAN_H
#define ANTRIAN_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ANTRIAN 100
#define MAX_NAMA 100

typedef struct {
    char namaPasien[MAX_ANTRIAN][MAX_NAMA];
    int head;
    int tail;
} AntrianPasien;

typedef struct {
    char namaDokter[MAX_NAMA];
    AntrianPasien antrian;
} DokterQueueMap;

#endif
