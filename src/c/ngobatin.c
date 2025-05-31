#include "ngobatin.h"

void F12_ngobatin(RuanganList *ruanganList, UserSet *userSet, PenyakitObatMap *peta, int jumlahPenyakit, InventoryObat *inventorySet, Session session) {
    Ruangan *ruanganDokter = NULL;
    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        if (strcmp(ruanganList->data[i].dokter, session.currentUser.username) == 0) {
            ruanganDokter = &ruanganList->data[i];
            break;
        }
    }    

    if (ruanganDokter == NULL || ruanganDokter->jumlahPasienDalamRuangan == 0) {
        printf("Tidak ada pasien untuk diobati!\n");
        return;
    }

    char *namaPasien = ruanganDokter->pasienDalamRuangan[0].nama;
    User *userPasien = NULL;
    for (int i = 0; i < userSet->count; i++) {
        if (strcmp(userSet->data[i].username, namaPasien) == 0) {
            userPasien = &userSet->data[i];
            break;
        }
    }

    if (inventorySet[userPasien->id].jumlah > 0) {
        printf("Pasien sudah diberikan obat! Tidak bisa diberikan obat lagi.\n");
        return;
    }

    printf("Dokter sedang mengobati pasien!\n");

    if (strcmp(userPasien->penyakit, "-") == 0) {
        printf("Pasien belum di diagnosis!\n");
        return;
        }
    if (strcmp(userPasien->penyakit, "Sehat") == 0) {
        printf("Pasien sudah didiagnosis dan dinyatakan sehat, tidak perlu diberi obat.\n");
        return;
    }

    printf("Pasien memiliki penyakit %s\n", userPasien->penyakit);

    int idxPenyakit = -1;
    for (int i = 0; i < jumlahPenyakit; i++) {
        if (strcmp(peta[i].penyakit, userPasien->penyakit) == 0) {
            idxPenyakit = i;
            break;
        }
    }

    if (idxPenyakit == -1) {
        printf("Obat tidak ditemukan untuk penyakit ini!\n");
        return;
    }

    printf("Obat yang harus diberikan:\n");
    for (int j = 0; j < peta[idxPenyakit].jumlahObat; j++) {
        printf("%d. %s\n", j + 1, peta[idxPenyakit].daftarObat[j]);
        if (inventorySet[userPasien->id].jumlah < MAX_INVENTORY) {
            strcpy(inventorySet[userPasien->id].namaObat[inventorySet[userPasien->id].jumlah], peta[idxPenyakit].daftarObat[j]);
            inventorySet[userPasien->id].jumlah++;
        }
    }
}