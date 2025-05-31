#include "lupa-password.h"

void runLengthEncode(char input[], char output[]){
    int i = 0;
    int j = 0;
    int len = strlen(input);

    while (i<len){
        int count = 1;
        while (i + count < len && input[i]==input[i+count]){
            count ++;
        }
        if (count>1){
            if (count >= 10){
                output[j++]= (count/10) + '0';
            }
            output [j++] = (count %10) + '0';
        }
        output[j++]= input[i];
        i += count;
    }
    output[j]='\0';
}

void F04_lupaPassword(UserSet *userSet){
    char username[MAX_USERNAME];
    char kodeUnik[2*MAX_USERNAME];
    char hasilEncode[2*MAX_USERNAME];

    printf("Username: ");
    scanf("%s", username);
    printf("Kode Unik: ");
    scanf("%s", kodeUnik);

    int idx = -1;
    for (int i=0; i<userSet->count; i++){
        if (strcmp(userSet->data[i].username, username)== 0){
            idx = i;
        }
    }
    if (idx== -1){
        printf("Username tidak terdaftar!\n");
    } else {
        runLengthEncode(username, hasilEncode);
        if (strcmp(kodeUnik, hasilEncode)== 0){
            if (strcmp(userSet->data[idx].role, "Manager")==0){
                printf("Halo Manager %s, silahkan daftarkan ulang password anda!\n", username);
            }
            else if(strcmp(userSet->data[idx].role, "Dokter")==0){
                printf("Halo Dokter %s, silahkan daftarkan ulang password anda!\n",username);
            }
            else {
                printf("Halo %s, silahkan daftarkan ulang password anda!\n",username);
            }

            char newPassword[MAX_PASSWORD];
            printf("Password Baru: ");
            scanf("%s", newPassword);
            strcpy(userSet->data[idx].password, newPassword);
        } 
        else {
            printf("Kode unik salah!\n");
        }
    }
}
