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
        printf("Hesap s�n�r�na ula��ld�.\n");
        return;
    }

    Musteri yeni_musteri;

    printf("Ad�n�z: ");
    scanf("%s", yeni_musteri.isim);

    printf("Hesap numaras�: ");
    scanf("%d", &yeni_musteri.hesapNo);

    printf("Bakiye: ");
    scanf("%f", &yeni_musteri.bakiye);

    musteri[musteriSayac++] = yeni_musteri;

    printf("Hesap olu�turuldu.\n");
}

void paraYatirma() {
    int hesapNo;
    float miktar;

    printf("Hesap numaran�z� girin: ");
    scanf("%d", &hesapNo);

    int i = 0;
    while (i <musteriSayac) {
        if (musteri[i].hesapNo == hesapNo) {
            printf("Yat�r�lacak Miktar: ");
            scanf("%f", &miktar);

            musteri[i].bakiye += miktar;

            printf("Hesaba para yat�r�ld�.\n");
            return;
        }
        i++;
    }

    printf("Hesap bulunamad�.\n");
}

void paraCek() {
    int hesapNo;
    float miktar;

    printf("Hesap numaran�z� girin: ");
    scanf("%d", &hesapNo);

    int i = 0;
    while (i < musteriSayac) {
        if (musteri[i].hesapNo == hesapNo) {
            printf("�ekilecek Miktar: ");
            scanf("%f", &miktar);

            if (miktar > musteri[i].bakiye) {
                printf("Yetersiz bakiye.\n");
                return;
            }

            musteri[i].bakiye -= miktar;

            printf("Hesaptan para �ekildi.\n");
            return;
        }
        i++;
    }

    printf("Hesap bulunamad�.\n");
}

void bakiye() {
    int hesapNo;

    printf("Hesap numaran�z� girin: ");
    scanf("%d", &hesapNo);

    int i = 0;
    while (i < musteriSayac) {
        if (musteri[i].hesapNo == hesapNo) {
            printf("Bakiye: %.2f\n", musteri[i].bakiye);
            return;
        }
        i++;
    }

    printf("Hesap bulunamad�.\n");
}

void dosyakayit() {
    FILE *file = fopen("bank.txt", "w");
    if (file == NULL) {
        printf("Dosya olu�turulamad�.\n");
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
        printf("Dosya bulunamad�.\n");
        return;
    }

    musteriSayac= 0;
    while (fscanf(file, "%s %d %f", musteri[musteriSayac].isim, &musteri[musteriSayac].hesapNo, &musteri[musteriSayac].bakiye) == 3) {
        musteriSayac++;
    }

    fclose(file);

    printf("Dosyadan y�klendi.\n");
}

void menu() {
    printf("1. Yeni hesap olu�tur\n");
    printf("2. Hesap bilgilerini g�r�nt�le\n");
    printf("3. Para yat�r\n");
    printf("4. Para �ek\n");
    printf("5. ��k��\n");
    printf("Se�iminizi yap�n: ");
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
                printf("Ge�ersiz se�im.\n");
                break;
        }
    }

    return 0;
}
