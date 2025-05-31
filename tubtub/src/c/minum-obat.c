#include "minum-obat.h"

void F16_minumObat(InventoryObat *inventory, StackPerut *perut) {
    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < inventory->jumlah; i++) {
        printf("%d. %s\n", i + 1, inventory->namaObat[i]);
    }
    if (inventory->jumlah == 0) {
        printf("Tidak ada obat di inventory.\n");
        return;
    }

    printf("Pilih obat untuk diminum: ");
    int pilihan;
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > inventory->jumlah) {
        printf("Pilihan nomor tidak tersedia!\n");
        return;
    }

    if (perut->top < MAX_PERUT) {
        strcpy(perut->namaObat[perut->top], inventory->namaObat[pilihan-1]);
        perut->top++;
        printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n", inventory->namaObat[pilihan-1]);
        for (int i = pilihan - 1; i < inventory->jumlah - 1; i++) {
            strcpy(inventory->namaObat[i], inventory->namaObat[i+1]);
        }
        inventory->jumlah--;
    } else {
        printf("Perut sudah penuh! Tidak bisa minum obat lagi.\n");
    }
}