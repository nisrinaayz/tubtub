#ifndef PENYAKIT_H
#define PENYAKIT_H

#define JUMLAH_PENYAKIT 5

typedef struct {
    char nama[50];
    float suhu_min, suhu_max;
    int sistol_min, sistol_max;
    int diastol_min, diastol_max;
    int detak_min, detak_max;
    float saturasi_min, saturasi_max;
    float gula_min, gula_max;
    float berat_min, berat_max;
    int tinggi_min, tinggi_max;
    int kolesterol_min, kolesterol_max;
    int trombosit_min, trombosit_max;
} Penyakit;

extern const Penyakit daftarPenyakit[JUMLAH_PENYAKIT];

#endif