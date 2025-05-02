#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
float tab1[100];         // bu dizi icinde yatirim yapmak için para
float tab2[100];        // bu dizi icinde ekipman satin almak için harcanan para
float tab3[100];       // bu dizi icinde  calisan sayisi
float tab4[100];       //bu dizi icinde  şirketin karlari
int i1=0,i2=0,i3=0,i4=0;
/**
 * bu fonksyon dosya.txt verileri okuyup dizilerde koyuyor
 */
void verioku(){
    FILE *f=fopen("veriler.txt","r");
    if (f==NULL)
    {
        printf("Dosya acilmaz hata var!!!\n");
        exit(1);
    }
    char yatirim[20],ekipman[20],calisan[20],karlari[20];
   while ((fscanf(f,"%s %s %s %s",yatirim,ekipman,calisan,karlari))!=EOF)
   {    int position = ftell(f);
        if (position!=33)
        {
            float sayi1=strtof(yatirim,NULL);
            float sayi2=strtof(ekipman,NULL);
            float sayi3=strtof(calisan,NULL);
            float sayi4=strtof(karlari,NULL);
            tab1[i1]=sayi1;
            tab2[i2]=sayi2;
            tab3[i3]=sayi3;
            tab4[i4]=sayi4;
            i1++;
            i2++;
            i3++;
            i4++;
        }
   }
   fclose(f);
}

/**
 * aritmetik ortalamasi hesapla
 */
float aritmetik_ortalama(float tab[],int n){
    float topla=0;
    for (int i = 0; i < n; i++)
    {
        topla+=tab[i];
    }
    return topla/n;
}

float korelation(float tab[],float tab5[],int n){
    
    float tab_ortalama=aritmetik_ortalama(tab,n);
    float tab1_ortalama=aritmetik_ortalama(tab5,n);
    float product1=0;                             //bu değişkende xi ve yi'nin çarpımının toplamı var (somme du prooduit xi*yi)
    float product2;                                //Bu değişken, iki ortalamanın çarpımının değerlerin n çarpımını içerir  (produit de n*ortax*ortay)
    float x_kare_som=0;                              // toplam x karesi bulunur  ( la somme des x*x)
    float y_kare_som=0;                                //toplam y karesi bulunur  (la somme des y*y)
    double product3;

    for (int i = 0; i < n; i++)
    {
        x_kare_som+=tab[i]*tab[i];                    
        y_kare_som+=tab5[i]*tab5[i];
    }

    for (int i = 0; i < n; i++)
    {
        product1+=tab[i]*tab5[i];
    }
    product2=n*tab1_ortalama*tab_ortalama;
    
    product3=sqrt((x_kare_som-(n*(tab_ortalama*tab_ortalama)))*(y_kare_som-(n*(tab1_ortalama*tab1_ortalama))));
    //product3=pow((x_kare_som-(n*(tab_ortalama*tab_ortalama)))*(x_kare_som-(n*(tab_ortalama*tab_ortalama))));

    return (product1-product2)/product3;
}

int main(){
    verioku();
    int cmp=(i1*70)/100;
    srand(time(NULL));

    float tab6[cmp];    //tab1 70% deger alacak      
    float tab7[cmp];    //tab2 70% deger alacak        
    float tab8[cmp];    //tab3 70% deger alacak   
    float tab9[cmp];    //tab4 70% deger alacak
    int j=0;
    for (int i = 0; i < cmp; i++)
    {
        tab6[j]=tab1[rand()%100];
        tab7[j]=tab2[rand()%100];
        tab8[j]=tab3[rand()%100];
        tab9[j]=tab4[rand()%100];
        j++;
    }
    /*
        x1=tab6
        x2=tab7
        x3=tab8
        y=tab9
    */

    // Yatırım tutarı ile kazanılan tutar arasındaki korelasyon katsayısını hesaplayalım  r1 = korelasyon(x1, y)
    float r1=korelation(tab6,tab9,cmp);
    // Ekipman satın almak için harcanan miktar ile kazanılan miktar arasındaki korelasyon katsayısını hesaplayalım  r2 = korelasyon(x2, y)
    float r2=korelation(tab7,tab9,cmp); 
    //Çalışan sayısı ile kazanılan miktar arasındaki korelasyon katsayısını hesaplayalım  r3 = korelasyon(x3, y)
    float r3=korelation(tab8,tab9,cmp); 



    printf("Yatirim tutari ile kazanilan tutar arasindaki korelasyon katsayisini hesaplayalim  r1 = korelasyon(x1, y)\n");
    printf("r1 = korelasyon(x1, y)= %f\n",r1);
    printf("Ekipman satin almak icin harcanan miktar ile kazanilan miktar arasindaki korelasyon katsayisini hesaplayalim  r2 = korelasyon(x2, y)\n");
    printf("r2 = korelasyon(x2, y)= %f\n",r2);
    printf("Calisan sayisi ile kazanilan miktar arasindaki korelasyon katsayisini hesaplayalim  r3 = korelasyon(x3, y)\n");
    printf("r3 = korelasyon(x3, y)= %f\n",r3);


    




    /*printf("correlation= %f\n",korelation(tab1,tab4,i1));
    printf("correlation= %f\n",korelation(tab2,tab4,i1));
    printf("correlation= %f\n",korelation(tab3,tab4,i1));*/



    
    /*for (int l = 0; l < i1; l++)
    {
        printf("%.2f ",tab1[l]);
    }
    printf("\n");
    for (int l = 0; l < i2; l++)
    {
        printf("%.2f ",tab2[l]);
    }
    printf("\n");
    for (int l = 0; l < i3; l++)
    {
        printf("%.0f ",tab3[l]);
    }
    printf("\n");
    for (int l = 0; l < i4; l++)
    {
        printf("%.2f ",tab4[l]);
    }
    printf("\n");*/

   /* printf("Tab1  aritmetik ortalamasi = %.2f\n",aritmetik_ortalama(tab1,i1));
    printf("Tab2  aritmetik ortalamasi = %.2f\n",aritmetik_ortalama(tab2,i2));
    printf("Tab3  aritmetik ortalamasi = %.2f\n",aritmetik_ortalama(tab3,i3));
    printf("Tab4  aritmetik ortalamasi = %.2f\n",aritmetik_ortalama(tab4,i4));

    float lin1[]={100,110,112,115,117,116,118,120,121,120,117,123};
    float lin2[]={5.5,5.8,6,5.9,6.2,6.3,6.5,6.6,6.4,6.5,6.7,6.8};
    printf("%f\n",korelation(lin1,lin2,12));*/



}
