#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
float tab1[100];         // bu dizi icinde yatirim yapmak için para
float tab2[100];        // bu dizi icinde ekipman satin almak için harcanan para
float tab3[100];       // bu dizi icinde  calisan sayisi
float tab4[100];       //bu dizi icinde  şirketin karlari
float *tab6;         //tab1 70% deger alacak      
float *tab7;       //tab2 70% deger alacak        
float *tab8;       //tab3 70% deger alacak   
float *tab9;       //tab4 70% deger alacak
float *tab10; 
int i1=0,i2=0,i3=0,i4=0,tahmin_cmp;
float *tahmin_deger;
float *testVeriX;
float *testVeriY;
int   testVericmpx;
int   testVericmpy;
float *testVeritahmin_deger;
int   testVeritahmin_cmp;
int reference=1;
/*
    x1=tab6
    x2=tab7
    x3=tab8
    y=tab9
*/
int cmp;
float r1;      //r1 = korelasyon(x1, y)
float r2;      //r2 = korelasyon(x2, y)
float r3;      //r3 = korelasyon(x3, y)
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
    float tab5_ortalama=aritmetik_ortalama(tab5,n);
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
    product2=n*tab5_ortalama*tab_ortalama;
    
    product3=sqrt((x_kare_som-(n*(tab_ortalama*tab_ortalama)))*(y_kare_som-(n*(tab5_ortalama*tab5_ortalama))));
    //product3=pow((x_kare_som-(n*(tab_ortalama*tab_ortalama)))*(x_kare_som-(n*(tab_ortalama*tab_ortalama))));

    return (product1-product2)/product3;
}
void percent_deger(int percent){                                         //bu function tab1,tab2,tab3,tab4 %70 degerler alacak
    cmp=(i1*percent)/100;
    srand(time(NULL));
    tab6=(float *)malloc(sizeof(float)*cmp);
    tab7=(float *)malloc(sizeof(float)*cmp);
    tab8=(float *)malloc(sizeof(float)*cmp);
    tab9=(float *)malloc(sizeof(float)*cmp);
    int j=0;
    for (int i = 0; i < cmp; i++)
    {
        int say=rand()%100;
        tab6[j]=tab1[say];
        tab7[j]=tab2[say];
        tab8[j]=tab3[say];
        tab9[j]=tab4[say];
        j++;
    }
}

float b_degeri_bul(float Tab[],float Tab1[],int n){
    //Tab x icin  Tab1 y icin
    float sumxy=0;                       //x ve y'nin çarpımının toplamı
    float sumx=0;                        //x 'nin toplamı
    float sumy=0;                        //y 'nin toplamı
    float sumx_kare=0;                   // x 'nin karesinin toplamı
    for (int i = 0; i < n; i++)
    {
        sumxy+=Tab[i]*Tab1[i];
    }
    for (int i = 0; i < n; i++)
    {
        sumx+=Tab[i];
    }
    for (int i = 0; i < n; i++)
    {
        sumy+=Tab1[i];
    }
    for (int i = 0; i < n; i++)
    {
        sumx_kare+=(Tab[i]*Tab[i]);
    }
    float b=0;
    b=((n*sumxy)-(sumx*sumy))/((n*sumx_kare)-(sumx*sumx));

    return b;
}
float a_degeri_bul(float Tab[],float Tab1[],int n){
    //Tab x icin  Tab1 y icin
    float b=b_degeri_bul(Tab,Tab1,n);
    float a=(aritmetik_ortalama(Tab1,n))-b*(aritmetik_ortalama(Tab,n));
    return a;
}

void denklem_olustur(float Tab1[],float Tab2[],float Tab3[],float Tab4[],int n){
    /*
        Tab1 x1 icin   Tab2 x2 icin    Tab3 x3 icin  Tab4 y icin    */
    float max;
    tab10=(float *)malloc(sizeof(float)*n);               // en buyuk korelation x degeri 
    max=r1;
    for (int l = 0; l < n; l++)
    {
        tab10[l]=Tab1[l];
    }
    if (r2>max)
    {
        max=r2;
        for (int l = 0; l < n; l++)
        {
            tab10[l]=Tab2[l];
        }
        printf("En buyuk korelasyona sahip degisken x2 ekipman satin almak icin harcanan para o zaman Regresyon denklem onda bulalim\n");
        printf("---------------------------------------------------------------------------------------\n");
        reference=2;
    }
    if (r3>max)
    {
        max=r3;
        for (int l = 0; l < n; l++)
        {
            tab10[l]=Tab3[l];
        }
        printf("En buyuk korelasyona sahip degisken x3 calisan sayisi o zaman Regresyon denklem onda bulalim\n");
        printf("---------------------------------------------------------------------------------------\n");
        reference=3;
    }
    if(max==r1)
    {
        printf("En buyuk korelasyona sahip degisken x1 yatirim yapmak icin para o zaman Regresyon denklem onda bulalim\n");
        printf("---------------------------------------------------------------------------------------\n");
    }
    
    // 𝒚 =𝒂+𝒃x  bu denklem olusturmaya calisalim
    printf("Bu veri setileri dogrusal oldugun icin Model denklemini y=a+bx sekilde bulacaktir\n");
    
    //b degeri bulacak
    // tab10 x icin    tab9 y icin
    float b=b_degeri_bul(tab10,Tab4,n);
    float a=a_degeri_bul(tab10,Tab4,n);
    printf("Denklemin farkli katsayilari a=%f  b=%f\n",a,b);
    printf("---------------------------------------------------------------------------------------\n");
    if (b>0)
    {
        printf("Regresion denklem Y=%.3f+%.3fx\n",a,b);
    }
    else
        printf("Regresion denklem Y=%.3f %.3fx\n",a,b);
}

void tahmin_deger_bul(float Tab1[],float Tab2[] ,int n){
    //Tab 1 x icin Tab2 y icin 
    tahmin_deger=(float *)malloc(sizeof(float)*n); 
    tahmin_cmp=0;
    float b=b_degeri_bul(Tab1,Tab2,n);
    float a=a_degeri_bul(Tab1,Tab2,n);
    float y;
    for (int i = 0; i < n; i++)
    {
       y=a+(Tab1[i]*b);
       tahmin_deger[tahmin_cmp]=y;
       tahmin_cmp++;
       printf("%.4f  ",y);
    }
}

float sse_bul(float Tab1[],float Tab2[],int n){
    //Tab 1 y icin Tab2 tahmin deger icin 
    float sum_karee=0;                     //y ve tahmin deger'nin kare farkının toplamı
    for (int i = 0; i < n; i++)
    {
        sum_karee+=((Tab1[i]-Tab2[i])*(Tab1[i]-Tab2[i]));
    }
    return sum_karee;
}

void testVeri_tahmindeger(int n){
    testVeriX=(float *)malloc(sizeof(float)*n);
    testVeriY=(float *)malloc(sizeof(float)*n);
    testVeritahmin_deger=(float *)malloc(sizeof(float)*n);
    testVericmpx=0;
    testVericmpy=0;
    testVeritahmin_cmp=0;

    if (reference==1)
    {
        for (int  i = 0; i < i1; i++)
        {
            int repere=0;
            for (int j = 0; j < cmp; j++)
            {
                if (tab10[j]==tab1[i])
                {
                    repere=1;
                    break;
                } 
            }
            if (repere==0)
           {
                testVeriX[testVericmpx]=tab1[i];
                testVericmpx++;
                testVeriY[testVericmpy]=tab4[i];
                testVericmpy++;
           }
            
        }
        
    }
    if (reference==2)
    {
        for (int  i = 0; i < i1; i++)
        {
            int repere=0;
            for (int j = 0; j < cmp; j++)
            {
                if (tab10[j]==tab2[i])
                {
                    repere=1;
                    break;
                } 
            }
            if (repere==0)
           {
                testVeriX[testVericmpx]=tab2[i];
                testVericmpx++;
                testVeriY[testVericmpy]=tab4[i];
                testVericmpy++;
           }
            
        }
        
    }

    if (reference==3)
    {
        for (int  i = 0; i < i1; i++)
        {
            int repere=0;
            for (int j = 0; j < cmp; j++)
            {
                if (tab10[j]==tab3[i])
                {
                    repere=1;
                    break;
                } 
            }
            if (repere==0)
           {
                testVeriX[testVericmpx]=tab3[i];
                testVericmpx++;
                testVeriY[testVericmpy]=tab4[i];
                testVericmpy++;
           }
            
        }
        
    }

    printf("%d",testVericmpy);
    /*for (int i = 0; i < testVericmpy; i++)
    {
        printf("%f ",testVeriX[i]);
    }
    for (int i = 0; i < testVericmpy; i++)
    {
        printf("%f ",testVeriY[i]);
    }*/


}


int main(){
    verioku();
    percent_deger(70);
    printf("\n\n");
    printf("---------------------------------------------------------------------------------------\n");
    // Yatırım tutarı ile kazanılan tutar arasındaki korelasyon katsayısını hesaplayalım  r1 = korelasyon(x1, y)
    r1=korelation(tab6,tab9,cmp);
    // Ekipman satın almak için harcanan miktar ile kazanılan miktar arasındaki korelasyon katsayısını hesaplayalım  r2 = korelasyon(x2, y)
    r2=korelation(tab7,tab9,cmp); 
    //Çalışan sayısı ile kazanılan miktar arasındaki korelasyon katsayısını hesaplayalım  r3 = korelasyon(x3, y)
    r3=korelation(tab8,tab9,cmp); 



    printf("Yatirim tutari ile kazanilan tutar arasindaki korelasyon katsayisini hesaplayalim  r1 = korelasyon(x1, y)\n");
    printf("r1 = korelasyon(x1, y)= %f\n",r1);
    printf("Ekipman satin almak icin harcanan miktar ile kazanilan miktar arasindaki korelasyon katsayisini hesaplayalim  r2 = korelasyon(x2, y)\n");
    printf("r2 = korelasyon(x2, y)= %f\n",r2);
    printf("Calisan sayisi ile kazanilan miktar arasindaki korelasyon katsayisini hesaplayalim  r3 = korelasyon(x3, y)\n");
    printf("r3 = korelasyon(x3, y)= %f\n",r3);
    printf("\n\n");
    denklem_olustur(tab6,tab7,tab8,tab9,cmp);
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("Tahmin degeri :\n");
    tahmin_deger_bul(tab10,tab9,cmp);
    printf("\n\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("SSE degeri budur : %f\n",sse_bul(tab9,tahmin_deger,cmp));
    testVeri_tahmindeger(testVericmpy);


    




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
    /*float lin3[]={117,120,100,121,118,116,112,120};
    float lin4[]={6.7,6.5,5.5,6.4,6.5,6.3,6,6.6};
    printf("%f\n",korelation(lin3,lin4,8));
    printf("La valeur de B est de :%f\n",b_degeri_bul(lin3,lin4,8));
    printf("La valeur de a est de :%f\n",a_degeri_bul(lin3,lin4,8));
    tahmin_deger_bul(lin3,lin4,8);
    printf("\n");
    for (int l = 0; l < 8; l++)
    {
        printf("%.2f ",tahmin_deger[l]);
    }
    printf("La valeur de SSE  de :%f\n",sse_bul(lin4,tahmin_deger,8));*/
    





}
