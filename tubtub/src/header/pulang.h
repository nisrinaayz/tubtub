#ifndef PULANG_H
#define PULANG_H

#include "penyakit.h"
#include "user.h"
#include "antrian.h"
#include "ruangan.h"
#include "obat.h"

void F13_pulangDok(Session session, UserSet *userSet, InventoryObat *inventorySet, StackPerut *perutSet, PenyakitObatMap *peta, int jumlahPenyakit, RuanganList *ruanganList, DokterQueueMap *map, int jumlahDokter);

#endif