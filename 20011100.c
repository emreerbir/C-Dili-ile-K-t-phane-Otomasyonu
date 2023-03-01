#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Ogrenci { 
	char ogrID[9];
	char ad[30];
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}ogrenci;

typedef struct Yazar { 
	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}yazar;

typedef struct KitapOrnek { 
	char EtiketNo[20]; 
	char Durum[8]; 
	struct KitapOrnek *next; 
}kitapOrnek;

typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[13]; 
	int adet; 
	struct Kitap *next; 
	struct KitapOrnek *head; 
}kitap;

typedef struct KitapYazar{ 
	char ISBN[13]; 
	int YazarID;
}kitapYazar;

typedef struct Tarih{
	unsigned int gun:5; 
	unsigned int ay:4; 
	unsigned int yil:12;
}tarih;

typedef struct KitapOdunc{ 
	char EtiketNo[20]; 
	char ogrID[9]; 
	unsigned int islemTipi:1; 
	struct Tarih islemTarihi;
}kitapOdunc;


void ogrenci_guncelleme();																		// yapildi
ogrenci* ogrenciAra(ogrenci* head_ogrenciler, char ogrID[9]);									// yapildi
ogrenci* ogrenciEkle(ogrenci* head_ogrenciler);													// yapildi		
ogrenci* ogrenciSil(ogrenci* head_ogrenciler);													// yapildi
void ogrenciGuncelle(ogrenci* head_ogrenciler);													// yapildi	
void ogrenciBilgi(ogrenci* head_ogrenciler, kitapOdunc* oduncTeslim, int boyut);				// yapildi
void teslimEtmeyenler(kitapOdunc* oduncTeslim, int boyut);										// yapildi
void cezalilar(ogrenci* head_ogrenciler);														// yapildi
void tumOgrenciler(ogrenci* head_ogrenciler);													// yapildi
void odunc_teslim(kitapOdunc* oduncTeslim, int boyut);											// yapildi

void kitap_guncelleme();																		// yapildi
kitap* kitapAra(kitap* head_kitaplar, char ISBN[13]);											// yapildi
kitap* kitapEkle(kitap* head_kitaplar);															// yapildi
kitap* kitapSil(kitap* head_kitaplar);															// yapildi	
void kitapGuncelle(kitap* head_kitaplar);														// yapildi
void kitapBilgi(kitap* head_kitaplar);															// yapildi
void raftakiKitaplar(kitap* head_kitaplar);														// yapildi
void zamaniGecenler(kitapOdunc* oduncTeslim, int boyut);										// yapildi
void kitap_yazar_eslestir(kitap* head_kitaplar, yazar* head_yazarlar, kitapYazar* eslestirme);	// yapildi			
void yazar_kitap_guncelle(kitapYazar* eslestirme);												// yapildi          

void yazar_guncelleme();																		// yapildi
yazar* yazarAra(yazar* head_yazarlar, int yazarID);												// yapildi
yazar* yazarEkle(yazar* head_yazarlar);															// yapildi
yazar* yazarSil(yazar* head_yazarlar);															// yapildi
void yazarGuncelle(yazar* head_yazarlar);														// yapildi
void yazarBilgi(yazar* head_yazarlar);															// yapildi











int main(int argc, char *argv[]) {
	ogrenci* head_ogrenciler = (ogrenci*)malloc(sizeof(ogrenci));
	head_ogrenciler->next=NULL;
	head_ogrenciler->prev=NULL;
	
	FILE* ogDosya = fopen("ogrenciler.csv", "r");
	if(ogDosya!=NULL){
		
		char satir[200];
		while(fgets(satir, sizeof(satir), ogDosya)){
			ogrenci* tmp = (ogrenci*)malloc(sizeof(ogrenci));
			char* token;
			
			token = strtok(satir, ",");
			strcpy(tmp->ogrID,token);
			token = strtok(NULL, ",");
			strcpy(tmp->ad,token);
			token = strtok(NULL, ",");
			strcpy(tmp->soyad,token);
			tmp->puan=100;
			tmp->next=head_ogrenciler;
			tmp->prev=NULL;
			head_ogrenciler->prev=tmp;
			head_ogrenciler=tmp;
			
			//printf("girdi %s\n", head_ogrenciler->ad);
		}
	}
	//printf("%s\n", head_ogrenciler->next->next->ad);
	fclose(ogDosya);
	
	
	
	kitap* head_kitaplar = (kitap*)malloc(sizeof(kitap));
	head_kitaplar->next = NULL;
	head_kitaplar->head = (kitapOrnek*)malloc(sizeof(kitapOrnek));
	
	yazar* head_yazarlar = (yazar*)malloc(sizeof(yazar));
	head_yazarlar->next=NULL;
	
	kitapYazar* eslestirme = (kitapYazar*)malloc(sizeof(kitapYazar));
	
	int boyut=2;
	kitapOdunc* oduncTeslim = (kitapOdunc*)malloc(sizeof(kitapOdunc));
	int i=0;
	
	int secim=0;
	while(secim!=4){
		int secim2=0;
		int secim3=0;
		int secim4=0;
		printf("Ogrenci islemleri icin 1 giriniz: \n");
		printf("Kitap islemleri icin 2 giriniz: \n");
		printf("Yazar islemleri icin 3 giriniz: \n");
		printf("Cikmak icin 4 giriniz: \n");
		scanf("%d", &secim);
		switch(secim){
			case 1:
				printf("Ogrenci eklemek icin 1 giriniz: \n");
				printf("Ogrenci silmek icin 2 giriniz: \n");
				printf("Ogrenci guncellemek icin 3 giriniz: \n");
				printf("Ogrenci bilgisi goruntulemek icin 4 giriniz: \n");
				printf("Teslim etmeyenleri goruntulemek icin 5 giriniz: \n");
				printf("Cezalilari goruntulemek icin 6 giriniz: \n");
				printf("Tum ogrencileri goruntulemek icin 7 giriniz: \n");
				printf("Odunc teslim islemi icin 8 giriniz: \n");
				printf("Cikmak icin 9 giriniz: \n");
				scanf("%d", &secim2);
				switch(secim2){
					case 1:
						head_ogrenciler = ogrenciEkle(head_ogrenciler);
						break;
					case 2:
						head_ogrenciler = ogrenciSil(head_ogrenciler);
						ogrenci* tmp9 = head_ogrenciler;
						FILE* dosya=fopen("Ogrenciler.csv", "w");
						while(tmp9->next!=NULL){
						fprintf(dosya,"%s,%s,%s,%d\n", tmp9->ogrID, tmp9->ad, tmp9->soyad, tmp9->puan);
						tmp9=tmp9->next;
						}
						fclose(dosya);
						break;	
					case 3:
						ogrenciGuncelle(head_ogrenciler);
						ogrenci* tmp8 = (ogrenci*)malloc(sizeof(ogrenci));
						tmp8 = head_ogrenciler;
						FILE* dosya8=fopen("Ogrenciler.csv", "w");
						while(tmp8->next!=NULL){
						fprintf(dosya8,"%s,%s,%s,%d\n", tmp8->ogrID, tmp8->ad, tmp8->soyad, tmp8->puan);
						tmp8=tmp8->next;
						}
						fclose(dosya8);
						break;
					case 4:
						ogrenciBilgi(head_ogrenciler, oduncTeslim, boyut);
						break;
					case 5:
						teslimEtmeyenler(oduncTeslim, boyut);
						break;
					case 6:
						cezalilar(head_ogrenciler);
						break;
					case 7:
						tumOgrenciler(head_ogrenciler);
						break;
					case 8:
						odunc_teslim(oduncTeslim, boyut);
						boyut++;
						i=0;
						FILE* OTdosya = fopen("oduncDurum.csv", "w");
						while(i<boyut-2){
							fprintf(OTdosya,"%s,%s,%d,%d,%d,%d\n", oduncTeslim[i].EtiketNo, oduncTeslim[i].ogrID, oduncTeslim[i].islemTipi, oduncTeslim[i].islemTarihi.gun, oduncTeslim[i].islemTarihi.ay, oduncTeslim[i].islemTarihi.yil);
							i++;
						}
						fclose(OTdosya);
						break;
					case 9:
						break;
					default:
						printf("Yanlis giris yaptiniz tekrar deneyiniz!");
						break;		
				}
				break;
			case 2:
				printf("Kitap eklemek icin 1 giriniz: \n");
				printf("Kitap silmek icin 2 giriniz: \n");
				printf("Kitap guncellemek icin 3 giriniz: \n");
				printf("Kitap bilgisi goruntulemek icin 4 giriniz: \n");
				printf("Raftaki kitaplari goruntulemek icin 5 giriniz: \n");
				printf("Teslim zamani gecen kitaplari goruntulemek icin 6 giriniz: \n");
				printf("Kitap yazar eslestirmek icin 7 giriniz: \n");
				printf("Kitap yazar eslesmesini guncellemek icin 8 giriniz: \n");
				printf("Cikmak icin 9 giriniz: \n");
				scanf("%d", &secim2);
				switch(secim2){
					case 1:
						head_kitaplar = kitapEkle(head_kitaplar);
						break;
					case 2:
						head_kitaplar = kitapSil(head_kitaplar);
						break;
					case 3:
						kitapGuncelle(head_kitaplar);
						break;
					case 4:
						kitapBilgi(head_kitaplar);
						break;
					case 5:
						raftakiKitaplar(head_kitaplar);
						break;
					case 6:
						zamaniGecenler(oduncTeslim, boyut);
						break;
					case 7:
						kitap_yazar_eslestir(head_kitaplar, head_yazarlar,eslestirme);
						break;
					case 8:
						yazar_kitap_guncelle(eslestirme);
						break;
					case 9:
						break;
					default:
						printf("Yanlis sayi girdiniz tekrar deneyiniz!\n");
						break;
				}
				break;
			case 3:
				printf("Yazar eklemek icin 1 giriniz: \n");
				printf("Yazar silmek icin 2 giriniz: \n");
				printf("Yazar guncellemek icin 3 giriniz: \n");
				printf("Yazar bilgisi goruntulemek icin 4 giriniz: \n");
				printf("Cikmak icin 5 giriniz: \n");
				scanf("%d", &secim3);
				switch(secim3){
					case 1:
						head_yazarlar = yazarEkle(head_yazarlar);
						break;
					case 2:
						head_yazarlar = yazarSil(head_yazarlar);
						yazar* tmp2 = (yazar*)malloc(sizeof(yazar));
						tmp2 = head_yazarlar;
						FILE* dosya=fopen("yazarlar.csv", "w");
						while(tmp2->next!=NULL){
							fprintf(dosya, "%s,%s,%d\n", tmp2->yazarAd, tmp2->yazarSoyad, tmp2->yazarID);
							tmp2=tmp2->next;
						}
						fclose(dosya);
						break;
					case 3:
						yazarGuncelle(head_yazarlar);
						break;
					case 4:
						yazarBilgi(head_yazarlar);
						break;
					case 5:
						break;
					default:
						printf("Yanlis sayi girdiniz tekrar deneyiniz!\n");
						break;
				}
				break;
			case 4:
				break;
			default:
				printf("Yanlis sayi girdiniz tekrar deneyiniz!\n");
				break;
		}
		
	}
	
	
	
	
	
	
	
	return 0;
}








ogrenci* ogrenciAra(ogrenci* head_ogrenciler, char *ogrID){
	ogrenci* current = head_ogrenciler;
	while(current!=NULL){
		if(strcmp(current->ogrID, ogrID)==0){
			return current;
		}
		current=current->next;
	}
	printf("Ogrenci bulunamadi!");
	return NULL;
}

ogrenci* ogrenciEkle(ogrenci* head_ogrenciler){
	ogrenci* tmp = (ogrenci*)malloc(sizeof(ogrenci));
	printf("Ogrenci ID giriniz: ");
	scanf("%s", &tmp->ogrID);
	printf("Ogrenci adini giriniz: ");
	scanf("%s", &tmp->ad);
	printf("Ogrenci soyadini giriniz: ");
	scanf("%s", &tmp->soyad);
	tmp->puan=100;
	tmp->next=head_ogrenciler;
	tmp->prev=NULL;
	head_ogrenciler->prev=tmp;
	
	FILE* dosya=fopen("Ogrenciler.csv", "a");
	fprintf(dosya,"%s, %s, %s, %d\n", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
	fclose(dosya);
	
	
	
	return tmp;
}

ogrenci* ogrenciSil(ogrenci* head_ogrenciler){	
	char ogrID[9];
	printf("Silinecek ogrencinin ID numarisini giriniz: \n");
	scanf("%s", ogrID);
	
	ogrenci* tmp = ogrenciAra(head_ogrenciler, ogrID);
	
	
	if(tmp==NULL){
		printf("Ogrenci bulunamadi!");
		return head_ogrenciler;
	}
	
	if(tmp->prev==NULL){
		head_ogrenciler = tmp->next;
		head_ogrenciler->prev=NULL;
		
		return head_ogrenciler;
	}
	if(tmp->next==NULL){
		tmp->prev->next=NULL;
		return head_ogrenciler;
	}
	
	tmp->prev->next=tmp->next;
	tmp->next->prev=tmp->prev;
	
	return head_ogrenciler;
	
}

void ogrenciGuncelle(ogrenci* head_ogrenciler){
	int choice=0;
	char ID[8];
	ogrenci* tmp = (ogrenci*)malloc(sizeof(ogrenci));
	printf("Guncellecek ogrencinin ID numarasini giriniz: ");
	scanf("%s", &ID);
	tmp = ogrenciAra(head_ogrenciler, ID);
	if(tmp!=NULL){
	
		while(choice!=4){
			ogrenci_guncelleme();
			scanf("%d", &choice);
			switch(choice){
				case 1:
					printf("Yeni adini giriniz: ");
					scanf("%s", tmp->ad);
					break;
				
				case 2:
					printf("Yeni soyadini giriniz: ");
					scanf("%s", tmp->soyad);
					break;
				
				case 3:
					printf("Yeni puanini giriniz: ");
					scanf("%d", &tmp->puan);
					break;
				case 4:
					break;
				default:
					printf("Yanlis giris yaptiniz tekrar deneyiniz!\n");
					break;			
			}
			
		}
	}
	
}

void ogrenciBilgi(ogrenci* head_ogrenciler, kitapOdunc* oduncTeslim, int boyut){
	char ogrID[9];
	int i=0;
	printf("Goruntulenecek ogrencinin ID numarasini giriniz: \n");
	scanf("%s", ogrID);
	ogrenci* tmp = ogrenciAra(head_ogrenciler, ogrID);
	if(tmp!=NULL){
		printf("Ad: %s  Soyad: %s ID: %s Puan: %d\n", tmp->ad, tmp->soyad, tmp->ogrID, tmp->puan);
	}
	
	
	// !!!!             KÝTAP HAREKETLERÝNÝ LÝSTELE                   !!!!!!!!!!!//
	
	while(i<boyut-2){
		if(strcmp(oduncTeslim[i].ogrID, ogrID)==0){
			printf("Etiket NO: %s, Ogrenci ID: %s, Islem Tipi: %d, Islem Yili: %d, Islem Ayi: %d, Islem Gunu: %d\n", oduncTeslim[i].EtiketNo, oduncTeslim[i].ogrID, oduncTeslim[i].islemTipi, oduncTeslim[i].islemTarihi.yil, oduncTeslim[i].islemTarihi.ay, oduncTeslim[i].islemTarihi.gun);
		}
		i++;
	}
	
}


void teslimEtmeyenler(kitapOdunc* oduncTeslim, int boyut){
	int i=0,j=0,k=0, flag=0;
	
	printf("Teslim etmeyenler: \n");
	while(i<boyut-2){
		flag=0;
		if(oduncTeslim[i].islemTipi==0){
			j=i;
			while(j<boyut-2 && flag==0){
				if(strcmp(oduncTeslim[j].EtiketNo, oduncTeslim[i].EtiketNo)==0 && oduncTeslim[j].islemTipi==1){
					flag=1;
				}
				j++;
			}
			if(flag==0){
				printf("Etiket NO: %s, Ogrenci ID: %s, Islem Tipi: %d, Islem Yili: %d, Islem Ayi: %d, Islem Gunu: %d\n", oduncTeslim[i].EtiketNo, oduncTeslim[i].ogrID, oduncTeslim[i].islemTipi, oduncTeslim[i].islemTarihi.yil, oduncTeslim[i].islemTarihi.ay, oduncTeslim[i].islemTarihi.gun);
			}
		}
		i++;
	}
	
	
}

void cezalilar(ogrenci* head_ogrenciler){
	ogrenci* tmp = head_ogrenciler;
	while(tmp!=NULL){
		if(tmp->puan<100){
			printf("Ad: %s  Soyad: %s ID: %s Puan: %d\n", tmp->ad, tmp->soyad, tmp->ogrID, tmp->puan);
		}
		tmp=tmp->next;
	}
}

void tumOgrenciler(ogrenci* head_ogrenciler){
	ogrenci* tmp = head_ogrenciler;
	while(tmp->next!=NULL){
		printf("Ad: %s  Soyad: %s ID: %s Puan: %d\n", tmp->ad, tmp->soyad, tmp->ogrID, tmp->puan);
		tmp=tmp->next;
	}
}

void odunc_teslim(kitapOdunc* oduncTeslim, int boyut){
	int secim;
	int yil, ay, gun, i=0;
	printf("Odunc islemi icin 1 giriniz: \n");
	printf("Teslim islemi icin 2 giriniz: \n");
	scanf("%d", &secim);
	
	if(secim==1){
		
		printf("Etiket NO giriniz: \n");
		scanf("%s", oduncTeslim[boyut-2].EtiketNo);
		printf("Ogrenci ID giriniz: \n");
		scanf("%s", oduncTeslim[boyut-2].ogrID);
		printf("Islem yili giriniz: \n");
		scanf("%d", &yil);
		oduncTeslim[boyut-2].islemTarihi.yil=yil;
		printf("Islem ayini giriniz: \n");
		scanf("%d", &ay);
		oduncTeslim[boyut-2].islemTarihi.ay=ay;
		printf("Islem gununu giriniz: \n");
		scanf("%d", &gun);
		oduncTeslim[boyut-2].islemTarihi.gun=gun;
		oduncTeslim[boyut-2].islemTipi=0;
		
		oduncTeslim = (kitapOdunc*)realloc(oduncTeslim,boyut*sizeof(kitapOdunc));
	}
	
	else{
		printf("Etiket NO giriniz: \n");
		scanf("%s", oduncTeslim[boyut-2].EtiketNo);
		printf("Ogrenci ID giriniz: \n");
		scanf("%s", oduncTeslim[boyut-2].ogrID);
		printf("Islem yili giriniz: \n");
		scanf("%d", &yil);
		oduncTeslim[boyut-2].islemTarihi.yil=yil;
		printf("Islem ayini giriniz: \n");
		scanf("%d", &ay);
		oduncTeslim[boyut-2].islemTarihi.ay=ay;
		printf("Islem gununu giriniz: \n");
		scanf("%d", &gun);
		oduncTeslim[boyut-2].islemTarihi.gun=gun;
		oduncTeslim[boyut-2].islemTipi=1;
		
		oduncTeslim = (kitapOdunc*)realloc(oduncTeslim,boyut*sizeof(kitapOdunc));
	}
}







kitap* kitapAra(kitap* head_kitaplar, char ISBN[13]){
	kitap* current = head_kitaplar;
	if(strcmp(current->ISBN, ISBN)==0){
		return current;
	}
	while(current->next!=NULL){
		if(strcmp(current->next->ISBN, ISBN)==0){
			return current;
		}
		current=current->next;
	}
	
	printf("Kitap bulunamadi!\n");
	return NULL;
}

kitap* kitapEkle(kitap* head_kitaplar){
	kitap* tmp = (kitap*)malloc(sizeof(kitap));

	printf("Kitap adi giriniz: ");
	scanf("%s", tmp->kitapAdi);
	printf("ISBN numarasi giriniz: ");
	scanf("%s", tmp->ISBN);
	printf("Kitap adetini giriniz: ");
	scanf("%d", &tmp->adet);
	
	tmp->head = (kitapOrnek*)malloc((sizeof(kitapOrnek)));
	tmp->head->next=NULL;
	int i=0;
	for(i=0;i<tmp->adet;i++){
		
		kitapOrnek* tmp2 = (kitapOrnek*)malloc(sizeof(kitapOrnek));
		tmp2->next=NULL;
		strcpy(tmp2->EtiketNo, tmp->ISBN);
		strcpy(&(tmp2->EtiketNo[13]), "_");
		sprintf(&(tmp2->EtiketNo[14]), "%d",i);
	//	itoa(i,tmp2->EtiketNo[14],1);
		strcpy(&(tmp2->EtiketNo[15]), "\0");
	
		strcpy(tmp2->Durum, "rafta");
		
		tmp2->next = tmp->head;
		tmp->head = tmp2;
	}
			
	tmp->next = head_kitaplar;
	return tmp;
}

kitap* kitapSil(kitap* head_kitaplar){
	char ISBN[13];
	printf("Silinecek kitabin ISBN numarasini giriniz: \n");
	scanf("%s", ISBN);
	
	if(kitapAra(head_kitaplar, ISBN)!=NULL){
		kitap* tmp = kitapAra(head_kitaplar, ISBN);
		if(tmp==NULL){
			return NULL;
		}
		if(strcmp(ISBN, head_kitaplar->ISBN)==0){
			return head_kitaplar->next;
		}
		
		tmp->next=tmp->next->next;
		return head_kitaplar;
	}
	else{
		return NULL;
	}
}

void kitapGuncelle(kitap* head_kitaplar){
	int choice=0, i;
	char ISBN[13];
	kitap* tmp = (kitap*)malloc(sizeof(kitap));
	tmp->head = (kitapOrnek*)malloc(sizeof(kitapOrnek));
	printf("Guncellenecek kitabin ISBN numarasini giriniz: ");
	scanf("%s", ISBN);
	if(kitapAra(head_kitaplar, ISBN)!=NULL){
		
		tmp = kitapAra(head_kitaplar, ISBN);
		if(strcmp(head_kitaplar->ISBN, ISBN)!=0){
			tmp=tmp->next;
		}
		
		while(choice!=4){
			kitap_guncelleme();
			scanf("%d", &choice);
			switch(choice){
				case 1:
					printf("Yeni adini giriniz: ");
					scanf("%s", tmp->kitapAdi);
					break;
				case 2:
					printf("Yeni ISBN numarasini giriniz: ");
					scanf("%s", tmp->ISBN);
					break;
				case 3:
					printf("Yeni adet sayisini giriniz: ");
					scanf("%d", &tmp->adet);
					for(i=0;i<tmp->adet;i++){
						kitapOrnek* tmp2 = (kitapOrnek*)malloc(sizeof(kitapOrnek));
						tmp2->next=NULL;
						strcpy(tmp2->EtiketNo, tmp->ISBN);
						strcpy(&(tmp2->EtiketNo[13]), "_");
						sprintf(&(tmp2->EtiketNo[14]), "%d",i);
						strcpy(&(tmp2->EtiketNo[15]), "\0");
					
						strcpy(tmp2->Durum, "rafta");
						
						tmp2->next = tmp->head;
						tmp->head = tmp2;
					}
					break;
				case 4:
					break;
				default:
					printf("Yanlis sayi girdiniz! Tekrar deneyiniz!");	
					break;		
			}
		}
	}
}


void kitapBilgi(kitap* head_kitaplar){
	char ISBN[13];
	printf("Goruntulenecek kitabin ISBN numarasini giriniz: \n");
	scanf("%s", ISBN);
	int i;
	if(kitapAra(head_kitaplar, ISBN)!=NULL){
	
	
		kitap* tmp = (kitap*)malloc(sizeof(kitap));
		tmp->head = (kitapOrnek*)malloc(sizeof(kitapOrnek));
		
		if(strcmp(ISBN, head_kitaplar->ISBN)==0){
			tmp=head_kitaplar;
			printf("Kitap Adi: %s, ISBN: %s, Adet Sayisi: %d\n", tmp->kitapAdi, tmp->ISBN, tmp->adet);
			kitapOrnek* tmp2 = (kitapOrnek*)malloc(sizeof(kitapOrnek));
			tmp2 = tmp->head;
			for(i=0;i<tmp->adet;i++){
				printf("Etiket NO: %s, Durum: %s\n", tmp2->EtiketNo, tmp2->Durum);
				tmp2 = tmp2->next;
			}
		}
		else{
			tmp = kitapAra(head_kitaplar, ISBN);
			if(tmp!=NULL){
					printf("Kitap Adi: %s, ISBN: %s, Adet Sayisi: %d\n", tmp->next->kitapAdi, tmp->next->ISBN, tmp->next->adet);
			}
			kitapOrnek* tmp2 = (kitapOrnek*)malloc(sizeof(kitapOrnek));
			tmp2 = tmp->next->head;
			for(i=0;i<tmp->next->adet;i++){
				printf("Etiket NO: %s, Durum: %s\n", tmp2->EtiketNo, tmp2->Durum);
				tmp2 = tmp2->next;
			}
			
		}
	}
	
}


void raftakiKitaplar(kitap* head_kitaplar){
	kitap* tmp = (kitap*)malloc(sizeof(kitap));
	int i;
	tmp = head_kitaplar;
	while(tmp->next!=NULL){

			printf("Kitap Adi: %s, ISBN: %s, Adet Sayisi: %d\n", tmp->kitapAdi, tmp->ISBN, tmp->adet);

			kitapOrnek* tmp2 = (kitapOrnek*)malloc(sizeof(kitapOrnek));
			tmp2 = tmp->head;
			for(i=0;i<tmp->adet;i++){
				printf("Etiket NO: %s, Durum: %s\n", tmp2->EtiketNo, tmp2->Durum);
				tmp2 = tmp2->next;
			}
			tmp=tmp->next;
	}
}

void zamaniGecenler(kitapOdunc* oduncTeslim, int boyut){
	int ay, yil, gun, i=0;
	
	printf("Suanki yili, ayi, gunu giriniz: ");
	scanf("%d %d %d", &yil, &ay, &gun);
	printf("\nZamani gecenler: \n");
	while(i<boyut-2){
		if(oduncTeslim[i].islemTipi==0){
			if(yil-oduncTeslim[i].islemTarihi.yil>0){
				printf("Etiket NO: %s, Ogrenci ID: %s, Islem Tipi: %d, Islem Yili: %d, Islem Ayi: %d, Islem Gunu: %d\n", oduncTeslim[i].EtiketNo, oduncTeslim[i].ogrID, oduncTeslim[i].islemTipi, oduncTeslim[i].islemTarihi.yil, oduncTeslim[i].islemTarihi.ay, oduncTeslim[i].islemTarihi.gun);
			}
			else if(ay-oduncTeslim[i].islemTarihi.ay>0){
				printf("Etiket NO: %s, Ogrenci ID: %s, Islem Tipi: %d, Islem Yili: %d, Islem Ayi: %d, Islem Gunu: %d\n", oduncTeslim[i].EtiketNo, oduncTeslim[i].ogrID, oduncTeslim[i].islemTipi, oduncTeslim[i].islemTarihi.yil, oduncTeslim[i].islemTarihi.ay, oduncTeslim[i].islemTarihi.gun);
			}
			else if(gun-oduncTeslim[i].islemTarihi.gun>15){
				printf("Etiket NO: %s, Ogrenci ID: %s, Islem Tipi: %d, Islem Yili: %d, Islem Ayi: %d, Islem Gunu: %d\n", oduncTeslim[i].EtiketNo, oduncTeslim[i].ogrID, oduncTeslim[i].islemTipi, oduncTeslim[i].islemTarihi.yil, oduncTeslim[i].islemTarihi.ay, oduncTeslim[i].islemTarihi.gun);
			}
		}
		i++;
	}
	
}

void kitap_yazar_eslestir(kitap* head_kitaplar, yazar* head_yazarlar, kitapYazar* eslestirme){
	int tmpID;
	char tmpISBN[13];
	printf("Yazar ID giriniz: ");
	scanf("%d", &tmpID);
	yazar* tmpYazar = yazarAra(head_yazarlar, tmpID);
	if(tmpYazar==NULL){
		printf("Yazar bulunamadi!");
		exit(1);
	} 
	
	printf("Kitap ISBN numarasini giriniz: ");
	scanf("%s", &tmpISBN);
	kitap* tmpKitap = kitapAra(head_kitaplar, tmpISBN);
	if(tmpKitap==NULL){
		printf("Kitap bulunamadi!");
		exit(1);
	}	
	
	FILE* dosya = fopen("KitapYazar.csv", "a");
	fprintf(dosya,"%d,%s\n", tmpID, tmpISBN);
	fclose(dosya);
	
	
	eslestirme = (kitapYazar*)malloc(sizeof(kitapYazar));
	FILE* rdosya = fopen("KitapYazar.csv", "r");
	char line[200];
	int n=0;
	
	while(fgets(line, sizeof(line), rdosya)){
		char* token;
		
		token = strtok(line, ", ");
		strcpy(eslestirme[n].ISBN, token);
		token = strtok(NULL, ", ");
		eslestirme[n].YazarID=atoi(token);
		
		n++;
		eslestirme = (kitapYazar*)realloc(eslestirme, n+1*sizeof(kitapYazar));
	}	
	
	fclose(rdosya);
	
	
}

void yazar_kitap_guncelle(kitapYazar* eslestirme){
	int i,j=0,k=0,n;
	char* tmpISBN;
	
	printf("Guncellenecek kitabýn ISBN numarasini giriniz: \n");
	scanf("%s", tmpISBN);
	n = sizeof(eslestirme);
	
	while(i<n){
		if(strcmp(eslestirme[i].ISBN, tmpISBN)==0){
			j++;
		}
		i++;
	}
	
	i=0;
	
	while(i!=j && k<n){
		if(strcmp(eslestirme[k].ISBN, tmpISBN)==0){
			printf("Yeni yazar ID'sini giriniz: ");
			scanf("%d", eslestirme[k].YazarID);
			i++;
		}
		k++;
	}
	
	i=0;
	
	FILE* dosya = fopen("KitapYazar.csv", "w");
	while(i<n){
		fprintf(dosya,"%d,%s\n", eslestirme[i].YazarID, eslestirme[i].ISBN);
		i++;
	}
	fclose(dosya);
	
	
	eslestirme = (kitapYazar*)malloc(sizeof(kitapYazar));
	FILE* rdosya = fopen("KitapYazar.csv", "r");
	char line[200];
	n=0;
	
	while(fgets(line, sizeof(line), rdosya)){
		char* token;
		
		token = strtok(line, ", ");
		strcpy(eslestirme[n].ISBN, token);
		token = strtok(NULL, ", ");
		eslestirme[n].YazarID=atoi(token);
		
		n++;
		eslestirme = (kitapYazar*)realloc(eslestirme, n+1*sizeof(kitapYazar));
	}	
	
}



yazar* yazarAra(yazar* head_yazarlar, int yazarID){
	yazar* current = head_yazarlar;
	if(current->yazarID==yazarID){
		return current;
	}
	while(current->next!=NULL){
		if(current->next->yazarID==yazarID){
			return current;
		}
		current = current->next;
	}
	printf("Yazar bulunamadi!\n");
	return NULL;
}

yazar* yazarEkle(yazar* head_yazarlar){
	yazar* tmp=(yazar*)malloc(sizeof(yazar));
	printf("Yazar adi giriniz: ");
	scanf("%s", tmp->yazarAd);
	printf("Yazar soyadi giriniz: ");
	scanf("%s", tmp->yazarSoyad);
	printf("Yazar ID giriniz: ");
	scanf("%d", &tmp->yazarID);
	
	tmp->next=head_yazarlar;
	head_yazarlar=tmp;
	
	FILE* dosya=fopen("yazarlar.csv", "a");
	fprintf(dosya, "%s,%s,%d\n", tmp->yazarAd, tmp->yazarSoyad, tmp->yazarID);
	fclose(dosya);
	
	
	return head_yazarlar;
}


yazar* yazarSil(yazar* head_yazarlar){
	int yazarID;
	printf("Silmek istediginiz yazarin ID numarasini giriniz: \n");
	scanf("%d", &yazarID);
	if(yazarAra(head_yazarlar, yazarID)!=NULL){
			
		
		yazar* tmp = yazarAra(head_yazarlar, yazarID);
		if(tmp->yazarID==head_yazarlar->yazarID){
			yazar* tmp2 = head_yazarlar->next;
			return head_yazarlar->next;
		}
		
		tmp->next=tmp->next->next;
		
		yazar* tmp2 = head_yazarlar;
		
		return head_yazarlar;
	}
	else{
		return head_yazarlar;
	}
}

void yazarGuncelle(yazar* head_yazarlar){
	int ID;
	printf("Guncellenecek yazarin ID'sini giriniz: \n");
	scanf("%d", &ID);
	
	if(yazarAra(head_yazarlar, ID)!=NULL){
			
		yazar* tmp = yazarAra(head_yazarlar, ID);
		if(ID!=head_yazarlar->yazarID){
			tmp=tmp->next;
		}
		
		
		int choice=0;
		while(choice!=4){
			yazar_guncelleme();
			scanf("%d", &choice);
			
			
			switch(choice){
				case 1:
					printf("Yeni adini giriniz: ");
					scanf("%s", tmp->yazarAd);
					break;
				case 2:
					printf("Yeni soyadini giriniz: ");
					scanf("%s", tmp->yazarSoyad);
					break;
				case 3:
					printf("Yeni ID giriniz: ");
					scanf("%d", &tmp->yazarID);
					break;
				case 4:
					break;
				default:
					printf("Yanlis sayi girdiniz! Tekrar deneyiniz!");	
					break;		
			}
		}
		
		yazar* tmp2 = head_yazarlar;
		FILE* dosya=fopen("yazarlar.csv", "w");
		while(tmp2!=NULL){
			fprintf(dosya, "%s,%s,%d\n", tmp->yazarAd, tmp->yazarSoyad, tmp->yazarID);
			tmp2=tmp2->next;
		}
		fclose(dosya);
	}
	
}

void yazarBilgi(yazar* head_yazarlar){
	
	int yazarID;
	printf("Goruntulemek istediginiz yazarin ID numarasini giriniz: \n");
	scanf("%d", &yazarID);
	
	if(yazarAra(head_yazarlar, yazarID)!=NULL){
	
		yazar* tmp = (yazar*)malloc(sizeof(yazar));	
		tmp = yazarAra(head_yazarlar, yazarID);
		if(yazarID==head_yazarlar->yazarID){
			printf("%s, %s, %d\n", head_yazarlar->yazarAd, head_yazarlar->yazarSoyad, head_yazarlar->yazarID);
		}
		else{
			tmp=tmp->next;
			printf("%s, %s, %d\n", tmp->yazarAd, tmp->yazarSoyad, tmp->yazarID);
		}
	}
}


void yazar_guncelleme(){
	printf("Adini guncellemek icin 1 giriniz: \n");
	printf("Soyadini guncellemek icin 2 giriniz: \n");
	printf("ID guncellemek icin 3 giriniz: \n");
	printf("Cikmak icin 4 giriniz: \n");
}

void kitap_guncelleme(){
	printf("Adini guncellemek icin 1 giriniz: \n");
	printf("ISBN numarasini guncellemek icin 2 giriniz: \n");
	printf("Adet sayisini guncellemek icin 3 giriniz: \n");
	printf("Cikmak icin 4 giriniz: \n");
}

void ogrenci_guncelleme(){
	printf("Adini guncellemek icin 1 giriniz: \n");
	printf("Soyadini guncellemek icin 2 giriniz: \n");
	printf("Puanini guncellemek icin 3 giriniz: \n");
	printf("Cikmak icin 4 giriniz: \n");
}
