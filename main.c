#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global degiskenler
int max_kitap = 100;
int kitapID[100];
char kitapad[100][100];
char kitapyazar[100][100];
int basimyili[100];
int kitapsayisi = 0;

// Fonksiyon prototipleri
void kitap_ekle();
void kitap_listele();
void kitap_ara();
void kitaplari_dosyadan_yukle();
void kitaplari_dosyaya_kaydet();

int main()
{
    // Program baþýnda kitaplarý dosyadan yükle
    kitaplari_dosyadan_yukle();

    printf("***HOSGELDINIZ***\n");

    int girissec = 0;
    do
    {
        printf("\n1- Kullanici Girisi\n");
        printf("2- Cikis Yap\n");
        printf("Seciminizi yapiniz: [1/2] ");
        if (scanf("%d", &girissec) != 1)
        {
            printf("Gecersiz giris! Lutfen sadece sayi giriniz.\n");
            while (getchar() != '\n');
            girissec = 0;
            continue;
        }

        if (girissec != 1 && girissec != 2)
        {
            printf("Gecersiz secim! Lutfen 1 veya 2 giriniz.\n");
        }
    } while (girissec != 1 && girissec != 2);

    if (girissec == 2)
    {
        printf("Cikis yapiliyor.\n");
        return 0;
    }

    char username[30], password[30];
    printf("\nKullanici Adi: ");
    scanf("%s", username);

    printf("Sifre: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0)
    {
        printf("Giris Basarili.\n");
    }
    else
    {
        printf("Gecersiz kullanici adi veya sifre.\n");
        return 0;
    }

    int loop2 = 1;
    while (loop2)
    {
        printf("\n***KUTUPHANE KITAP LISTELEME SISTEMI***\n");
        printf("1) Kitap Ekle\n");
        printf("2) Kitaplari Listele\n");
        printf("3) Kitap Ara\n");
        printf("4) Cikis\n");
        printf("Bir secenek girin: ");
        int menu_secim;
        if (scanf("%d", &menu_secim) != 1)
        {
            printf("Gecersiz giris! Lutfen sadece sayi giriniz.\n");
            while (getchar() != '\n'); // Hatalý giriþleri temizle
            continue;
        }

        switch (menu_secim)
        {
            case 1:
                kitap_ekle();
                break;
            case 2:
                kitap_listele();
                break;
            case 3:
                kitap_ara();
                break;
            case 4:
                printf("Cikis yapiliyor.\n");
                kitaplari_dosyaya_kaydet();
                loop2 = 0;
                break;
            default:
                printf("Gecersiz secenek. Lutfen tekrar deneyiniz.\n");
        }
    }
    return 0;
}

// Kitap ekleme fonksiyonu
void kitap_ekle()
{
    if (kitapsayisi == max_kitap)
    {
        printf("Maksimum kitap sayisina (100) ulasildi.\n");
        return;
    }

    kitapID[kitapsayisi] = kitapsayisi + 1;

    getchar(); 

    printf("Eklemek istediginiz kitabin adini giriniz: ");
    fgets(kitapad[kitapsayisi], sizeof(kitapad[kitapsayisi]), stdin);
    kitapad[kitapsayisi][strcspn(kitapad[kitapsayisi], "\n")] = '\0';

    printf("Bu kitabin yazarinin adini giriniz: ");
    fgets(kitapyazar[kitapsayisi], sizeof(kitapyazar[kitapsayisi]), stdin);
    kitapyazar[kitapsayisi][strcspn(kitapyazar[kitapsayisi], "\n")] = '\0';

    printf("Bu kitabin basim yilini giriniz: ");
    scanf("%d", &basimyili[kitapsayisi]);

    kitapsayisi++;
    printf("Kitap basariyla eklenmistir.\n");
}

// Kitap listeleme fonksiyonu
void kitap_listele()
{
    if (kitapsayisi == 0)
    {
        printf("Hic kitap eklenmemis.\n");
        return;
    }

    printf("\nKitap Listesi:\n");

    int i;
    for (i = 0; i < kitapsayisi; i++)
    {
        printf("ID: %d, Kitap Adi: %s, Yazar: %s, Basim Yili: %d\n", kitapID[i], kitapad[i], kitapyazar[i], basimyili[i]);
    }
}

// Kitap arama fonksiyonu
void kitap_ara()
{
    char arama[100];
    printf("Aranacak kitabin veya yazarin ismini giriniz: ");
    getchar();
    fgets(arama, sizeof(arama), stdin);
    arama[strcspn(arama, "\n")] = '\0';

    int bul = 0;

    int i;
    for (i = 0; i < kitapsayisi; i++)
    {
        if (strstr(kitapad[i], arama) || strstr(kitapyazar[i], arama))
        {
            printf("ID: %d, Kitap Adi: %s, Yazar: %s, Basim Yili: %d\n", kitapID[i], kitapad[i], kitapyazar[i], basimyili[i]);
            bul = 1;
        }
    }

    if (!bul)
    {
        printf("Aradiginiz kitap/yazar bulunamadi.\n");
    }
}

// Dosyadan kitaplari yukleme fonksiyonu
void kitaplari_dosyadan_yukle()
{
    FILE *file = fopen("kitaplar.txt", "r");
    if (file == NULL)
    {
        printf("Kitaplar dosyasi bulunamadi, yeni bir dosya olusturulacak.\n");
        return;
    }

    while (fscanf(file, "%d %99s %99s %d", &kitapID[kitapsayisi], kitapad[kitapsayisi], kitapyazar[kitapsayisi], &basimyili[kitapsayisi]) == 4)
    {
        kitapsayisi++;
    }

    fclose(file);
    printf("%d kitap yüklendi.\n", kitapsayisi);
}


// Dosyaya kitaplari kaydetme fonksiyonu
void kitaplari_dosyaya_kaydet()
{
    FILE *file = fopen("kitaplar.txt", "w");
    if (file == NULL)
    {
        printf("Kitaplar dosyasina kayit yapilamadi.\n");
        return;
    }

    int i;
    for (i = 0; i < kitapsayisi; i++)
    {
        fprintf(file, "%d %s %s %d\n", kitapID[i], kitapad[i], kitapyazar[i], basimyili[i]);
    }

    fclose(file);
    printf("Kitaplar basariyla kaydedildi.\n");
}

