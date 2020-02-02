


#include<stdio.h>
#include<string.h>
#define kod 23

int dijkstra(int maliyet[][kod],int kaynak,int hedef );

int main()
{
    int uzaklik,kaynak,hedef,secim,maliyet[kod][kod];
    char ad1[20],ad2[20],ad3[20],sehir[20],sehir1[20],sehir2[20],liste[kod][20];
    int i,j,km,kod1,adres1,adres2,sayac=1;
    FILE *sehirkod,*sehirmesafe;

    printf("iki sehirin birbirlerine olan en kisa yolu icin 1 e basiniz\n");
    printf("Bir sehirin diger tum sehirlere olan en kisa yolu icin 2 ye basiniz\n");

    basadon:

    printf("secim yapiniz:");
    scanf("%d",&secim);

    for(i=0; i<kod; i++)
    {
        for(j=0; j<kod; j++)
        {
            maliyet[i][j]=9999;
        }
    }

    sehirmesafe=fopen("sehirmesafe.txt","r");
    sehirkod=fopen("sehirkod.txt","r");


    if(secim==1)
    {
        printf("\nbaslangic sehrini giriniz:");
        scanf("%s",ad1);
        printf("varis sehrini giriniz:");
        scanf("%s",ad2);

    while(!feof(sehirkod))
    {
        fscanf(sehirkod,"%s - %d",sehir,&kod1);
        strcpy(liste[sayac],sehir);
        sayac++;

        if(strcmp(sehir,ad1)==0)
          kaynak=kod1;
        if(strcmp(sehir,ad2)==0)
          hedef=kod1;
        if(feof(sehirkod))
            break;
    }

        while(!feof(sehirmesafe))
    {

        fscanf(sehirmesafe,"%s - %s - %d",sehir1,sehir2,&km);

        for(i=1; i<kod; i++)
        {
            if(strcmp(liste[i],sehir1)==0)
            {
               adres1=i;
            }

            if(strcmp(liste[i],sehir2)==0)
            {
                adres2=i;
                maliyet[adres1][adres2]=maliyet[adres2][adres1]=km;
            }

        }

    }

        printf("\nGirdiginiz sehirler arasindaki en kisa yol:\n\n");
        uzaklik = dijkstra(maliyet,kaynak,hedef);
        printf("%d km\n",uzaklik);
    }


    else if(secim==2)
    {
        printf("sehir giriniz:");
        scanf("%s",ad3);

        while(!feof(sehirkod))
    {
        fscanf(sehirkod,"%s - %d",sehir,&kod1);
        strcpy(liste[sayac],sehir);
        sayac++;
        if(feof(sehirkod))
            break;
    }

    while(!feof(sehirmesafe))
    {
        fscanf(sehirmesafe,"%s - %s - %d",sehir1,sehir2,&km);

        for(i=1; i<kod; i++)
        {
            if(strcmp(liste[i],sehir1)==0)
            {
               adres1=i;
            }

            if(strcmp(liste[i],sehir2)==0)
            {
                adres2=i;
                maliyet[adres1][adres2]=maliyet[adres2][adres1]=km;
            }

        }
    }
        int hedef2=1;
        int uzaklik2,kaynak2;
        printf("\nGirdiginiz sehrin diger sehirlere olan en kisa yollarin listesi:\n\n");

        for(i=1; i<kod; i++)
        {
            if(strcmp(liste[i],ad3)==0)
            {
                kaynak2=i;
                for(hedef2=1; hedef2<kod; hedef2++)
                {
                if(kaynak2==hedef2)
                hedef2++;

                uzaklik2=dijkstra(maliyet,kaynak2,hedef2);
                printf("%d km\n",uzaklik2);
                }
            }

        }

    }
    else
   {
        printf("yanlis secim yaptiniz\n");
        goto basadon;
    }

    fclose(sehirkod);
    fclose(sehirmesafe);

    return 0;
}

// ALT SATIRDAKI DIJKSTRA FONKSIYONUNDA BU ADRESTEN http://www.codewithc.com/dijkstras-algorithm-in-c/ FAYDALANILMISTIR.

int dijkstra(int maliyet[][kod],int kaynak,int hedef)
{

    int mesafe[kod],onceki[kod],secilmis[kod]={0};
    int d,i,m,min,baslangic;

    for(i=1; i<kod; i++)
    {
        mesafe[i]=9999;
        onceki[i]=-1;
    }
    baslangic=kaynak;
    secilmis[baslangic]=1;
    mesafe[baslangic]= 0;
    while(secilmis[hedef]==0)
    {
        min=9999;
        m=0;
        for(i=1; i<kod; i++)
        {
            d = mesafe[baslangic] + maliyet[baslangic][i];
            if(d< mesafe[i]&&secilmis[i]==0)
            {
                mesafe[i]=d;
                onceki[i]=baslangic;
            }
            if(min>mesafe[i] && secilmis[i]==0)
            {
                min=mesafe[i];
                m=i;
            }
        }
        baslangic=m;
        secilmis[baslangic]=1;
    }
    baslangic=hedef;

    FILE *sehirkod;
    sehirkod=fopen("sehirkod.txt","r");

    int sayi;
    char sehir[kod][20],degis[kod][20];
    int k=1;

        while(!feof(sehirkod))
        {
        fscanf(sehirkod,"%s - %d",sehir[k],&sayi);
        k++;
        if(feof(sehirkod))
             break;
        }

    int j=1;

    while(baslangic!=-1)
    {
        strcpy(degis[j],sehir[baslangic]);
        j++;
        baslangic=onceki[baslangic];
    }

     int a;

    for(a=j-1; a>0; a--)
    {
        printf("%s-",degis[a]);
    }
    fclose(sehirkod);
    return mesafe[hedef];
}
