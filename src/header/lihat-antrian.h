#ifndef LIHAT_ANTRIAN_H
#define LIHAT_ANTRIAN_H

#include <stdio.h>
#include <stdbool.h>
#include "ruangan.h"
#include "user.h"
#include "denah-rumah-sakit.h"

void S02_lihatAntrian(RuanganList *ruanganList, DokterQueueMap *dokterMap, int jumlahDokter, Session session);


#endif
