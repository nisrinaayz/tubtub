#include "penawar.h"

void F17_penawar(StackPerut *perut, InventoryObat *inventory) {
    if (perut->top == 0) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    perut->top--;
    char obatKeluar[NAMA_OBAT_LEN];
    strcpy(obatKeluar, perut->namaObat[perut->top]);

    if (inventory->jumlah < MAX_INVENTORY) {
        strcpy(inventory->namaObat[inventory->jumlah], obatKeluar);
        inventory->jumlah++;
    }
    printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", obatKeluar);
}