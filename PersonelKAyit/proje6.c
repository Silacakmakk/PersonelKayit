#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Personel
{
    char tc[12];
    char isim[16];
    char soyisim[16];
    char telefon[12];
    char bolum[31];
};

void menu();
void kayit_listele();
void kayit_ara();
void kayit_ekle();
void kayit_sil();
int tcKontrol(char temptc[]);
void temizle(char *buffer); // Yeni eklenen fonksiyon

int main()
{
    int secim;
    menu();

    while (1)
    {
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            kayit_listele();
            break;
        case 2:
            kayit_ara();
            break;
        case 3:
            kayit_ekle();
            break;
        case 4:
            kayit_sil();
            break;
        case 6:
            printf("Programdan Cikiliyor.\n");
            exit(0);
        default:
            printf("Yanlis tuslama yaptiniz\n");
        }

        menu();
    }

    return 0;
}

void menu()
{
    printf("\n\nPERSONEL KAYIT PROGRAMI\n");
    printf("-----------------------\n");
    printf("1- Kayit Listele\n");
    printf("2- Kayit Ara\n");
    printf("3- Kayit Ekle\n");
    printf("4- Kayit Sil\n");
    printf("5- Kayit Guncellestir\n");
    printf("6- Programdan Cikis\n");
    printf("-----------------------\n");
    printf("%18s      :", "Seciminiz ?");
}

void kayit_listele()
{
    FILE *dosya = fopen("personel.txt", "r");

    if (!dosya)
    {
        printf("Dosya acilamadi\n");
        exit(1);
    }

    int c;

    while ((c = getc(dosya)) != EOF)
    {
        putchar(c);
    }

    fclose(dosya);
}

void kayit_ara()
{
    FILE *a;
    a = fopen("personel.txt", "r");
    if ((a = fopen("personel.txt", "r")) == NULL)
    {
        printf("dosya acilamadi\n");

        exit(1); //basarisiz çikiş
    }
    struct Personel personel;

    char aranan[31];

    printf("Aranacak kayit  ? :\n\n");
    scanf("%s", aranan);

    int kayitYok = 0;
    while (!feof(a)) //dosya sonuna erişilmediği sürece devam eder
    {
        fscanf(a, "%12s%16s%16s%12s%31s\n", personel.tc, personel.isim, personel.soyisim, personel.telefon, personel.bolum);

        if (strstr(personel.tc, aranan) || strstr(personel.isim, aranan) || strstr(personel.soyisim, aranan) ||
            strstr(personel.telefon, aranan) || strstr(personel.bolum, aranan))
        {
            printf(" %12s  %16s   %16s  %12s  %31s\n", personel.tc, personel.isim, personel.soyisim, personel.telefon, personel.bolum);
            kayitYok++;
        }
    }
    if (!kayitYok)
        printf("Aranilan Kayit Bulunamadi : %31s \n", aranan);

    fclose(a);
}

void kayit_ekle()
{
    struct Personel ekle;

    do
    {
        char temptc[12];
        printf("\n TC kimlik no :");
       

        fgets(temptc, sizeof(temptc), stdin);
        temizle(temptc);

        if (strlen(temptc) != 11)
        {
            printf("Hata: TC kimlik numarasi 11 haneli olmalidir.\n");
        }
        else
        {
            if (tcKontrol(temptc))
            {
                printf("Bu TC Kimlik Numarasi daha once kullanildi. Lutfen tekrar giriniz.\n");
            }
            else
            {
                strcpy(ekle.tc, temptc);
                break;
            }
        }
    } while (1);

    do
    {
        printf("\n Kisinin adi :");
        fgets(ekle.isim, sizeof(ekle.isim), stdin);
        temizle(ekle.isim);

        if (strlen(ekle.isim) > 15)
        {
            printf("Hata: Kisinin adi en fazla 15 haneli olmalidir.\n");
        }
        else
        {
            break;
        }
    } while (1);

    do
    {
        printf("\n Kisinin soyadi :");
        fgets(ekle.soyisim, sizeof(ekle.soyisim), stdin);
        temizle(ekle.soyisim);

        if (strlen(ekle.soyisim) > 15)
        {
            printf("Hata: Kisinin soyadi en fazla 15 haneli olmalidir.\n");
        }
        else
        {
            break;
        }
    } while (1);

    while (1)
    {
        printf("\n Kisinin telefonu :");
        fgets(ekle.telefon, sizeof(ekle.telefon), stdin);
        temizle(ekle.telefon);

        if (strlen(ekle.telefon) != 11)
        {
            printf("Hata: Kisinin telefonu 11 haneli olmalidir.\n");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("\n Kisinin calistigi bolum:");
        fgets(ekle.bolum, sizeof(ekle.bolum), stdin);
        temizle(ekle.bolum);

        if (strlen(ekle.bolum) > 30)
        {
            printf("Hata: Kisinin calistigi bolum en fazla 30 haneli olmalidir.\n");
        }
        else
        {
            break;
        }
    }

    FILE *e = fopen("personel.txt", "a");

    if (!e)
    {
        printf("Dosya acilamadi\n");
        exit(1);
    }

    fprintf(e, "\n%12s %16s %16s %12s %31s", ekle.tc, ekle.isim, ekle.soyisim, ekle.telefon, ekle.bolum);

    fclose(e);
}

void kayit_sil()
{
    FILE *dosya = fopen("personel.txt", "r");
    FILE *tempDosya = fopen("temp.txt", "w");

    if (!dosya || !tempDosya)
    {
        perror("Dosya acilamadi");
        exit(1);
    }

    char silinecekTC[12];

    printf("Silinecek kayidin TC kimlik numarasini giriniz: ");
    

    fgets(silinecekTC, sizeof(silinecekTC), stdin);
    temizle(silinecekTC);

    struct Personel personel;

    int kayitBulundu = 0;

    while (fscanf(dosya, "%12s %16s %16s %12s %31[^\n]", personel.tc, personel.isim, personel.soyisim, personel.telefon, personel.bolum) != EOF)
    {
        if (strcmp(personel.tc, silinecekTC) == 0)
        {
            printf("Kayit bulundu ve siliniyor...\n");
            kayitBulundu = 1;
        }
        else
        {
            fprintf(tempDosya, "%12s %16s %16s %12s %31s\n", personel.tc, personel.isim, personel.soyisim, personel.telefon, personel.bolum);
        }
    }

    fclose(dosya);
    fclose(tempDosya);

    if (!kayitBulundu)
    {
        printf("Silinecek kayit bulunamadi.\n");
    }
    else
    {
        remove("personel.txt");
        rename("temp.txt", "personel.txt");
        printf("Kayit basariyla silindi.\n");
    }
}

int tcKontrol(char temptc[])
{
    FILE *dosya = fopen("personel.txt", "r");

    if (!dosya)
    {
        perror("Dosya açma hatasi");
        exit(1);
    }

    struct Personel ekle;

    while (fscanf(dosya, "%s", ekle.tc) != EOF)
    {
        if (strcmp(ekle.tc, temptc) == 0)
        {
            fclose(dosya);
            return 1;
        }
    }

    fclose(dosya);
    return 0;
}

// Temizleme fonksiyonunu güncelliyoruz
void temizle(char *buffer)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    buffer[strcspn(buffer, "\n")] = '\0';  // Satır sonundaki newline karakterini temizle
}
