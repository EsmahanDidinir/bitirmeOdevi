#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_kullanici 100

typedef struct {
    char isim[100];
    int hesapNo;
    float bakiye;
} Musteri;

Musteri musteri[MAX_kullanici];
int musteriSayac = 0;

void kayit() {
    if (musteriSayac == MAX_kullanici) {
        printf("Hesap sýnýrýna ulaþýldý.\n");
        return;
    }

    Musteri yeni_musteri;

    printf("Adýnýz: ");
    scanf("%s", yeni_musteri.isim);

    printf("Hesap numarasý: ");
    scanf("%d", &yeni_musteri.hesapNo);

    printf("Bakiye: ");
    scanf("%f", &yeni_musteri.bakiye);

    musteri[musteriSayac++] = yeni_musteri;

    printf("Hesap oluþturuldu.\n");
}

void paraYatirma() {
    int hesapNo;
    float miktar;

    printf("Hesap numaranýzý girin: ");
    scanf("%d", &hesapNo);

    int i = 0;
    while (i <musteriSayac) {
        if (musteri[i].hesapNo == hesapNo) {
            printf("Yatýrýlacak Miktar: ");
            scanf("%f", &miktar);

            musteri[i].bakiye += miktar;

            printf("Hesaba para yatýrýldý.\n");
            return;
        }
        i++;
    }

    printf("Hesap bulunamadý.\n");
}

void paraCek() {
    int hesapNo;
    float miktar;

    printf("Hesap numaranýzý girin: ");
    scanf("%d", &hesapNo);

    int i = 0;
    while (i < musteriSayac) {
        if (musteri[i].hesapNo == hesapNo) {
            printf("Çekilecek Miktar: ");
            scanf("%f", &miktar);

            if (miktar > musteri[i].bakiye) {
                printf("Yetersiz bakiye.\n");
                return;
            }

            musteri[i].bakiye -= miktar;

            printf("Hesaptan para çekildi.\n");
            return;
        }
        i++;
    }

    printf("Hesap bulunamadý.\n");
}

void bakiye() {
    int hesapNo;

    printf("Hesap numaranýzý girin: ");
    scanf("%d", &hesapNo);

    int i = 0;
    while (i < musteriSayac) {
        if (musteri[i].hesapNo == hesapNo) {
            printf("Bakiye: %.2f\n", musteri[i].bakiye);
            return;
        }
        i++;
    }

    printf("Hesap bulunamadý.\n");
}

void dosyakayit() {
    FILE *file = fopen("bank.txt", "w");
    if (file == NULL) {
        printf("Dosya oluþturulamadý.\n");
        return;
    }

    int i = 0;
    while (i < musteriSayac) {
        fprintf(file, "%s %d %.2f\n", musteri[i].isim, musteri[i].hesapNo, musteri[i].bakiye);
        i++;
    }

    fclose(file);

    printf("Dosyaya kaydedildi.\n");
}

void dosya() {
    FILE *file = fopen("bank.txt", "r");
    if (file == NULL) {
        printf("Dosya bulunamadý.\n");
        return;
    }

    musteriSayac= 0;
    while (fscanf(file, "%s %d %f", musteri[musteriSayac].isim, &musteri[musteriSayac].hesapNo, &musteri[musteriSayac].bakiye) == 3) {
        musteriSayac++;
    }

    fclose(file);

    printf("Dosyadan yüklendi.\n");
}

void menu() {
    printf("1. Yeni hesap oluþtur\n");
    printf("2. Hesap bilgilerini görüntüle\n");
    printf("3. Para yatýr\n");
    printf("4. Para çek\n");
    printf("5. Çýkýþ\n");
    printf("Seçiminizi yapýn: ");
}

int main() {
    int secim;

    dosya();

    while (1) {
        menu();
        scanf("%d", &secim);

        if (secim== 5) {
            dosyakayit();
            break;
        }

        switch (secim) {
            case 1:
                kayit();
                break;
            case 2:
                bakiye();
                break;
            case 3:
                paraYatirma();
                break;
            case 4:
                paraCek();
                break;
            default:
                printf("Geçersiz seçim.\n");
                break;
        }
    }

    return 0;
}
