#pragma warning(disable : 4996)
#include "ogrenciListesi.h"

#include <cstring>
#include <iostream>
#include<fstream> 
using namespace std;


void ogrenciListesi::ekle(string adi, string soyadi, string ogrNo, string dersKodu, string dersAdi)
{
	ogrenci* tara, * yeni,*onceki=nullptr;
	tara = bas;
	yeni = new ogrenci;
	strcpy(yeni->ad, adi.c_str());
	strcpy(yeni->ogrno, ogrNo.c_str());
	strcpy(yeni->soyad, soyadi.c_str());
	ders* ders = new ::ders;
	strcpy(ders->dersadi, dersAdi.c_str());
	strcpy(ders->derskodu, dersKodu.c_str());
	ders->sonraki = nullptr;
	yeni->dersdugumu = ders;
	yeni->sonraki = nullptr;
	
	ogrenci* ogr = ogrenciBul(yeni->ogrno);
	if(ogr)
	{
		delete yeni;
		struct ders* tara = ogr->dersdugumu,*onceki=nullptr;
		if (strcmp(ders->derskodu, tara->derskodu) < 0)
		{
			ders->sonraki = ogr->dersdugumu;
			ogr->dersdugumu = ders;
			return;
		}
		while (tara && (strcmp(ders->derskodu, tara->derskodu) > 0))
		{
			onceki = tara;
			tara = tara->sonraki;
		}
		if (tara)
		{
			ders->sonraki = tara;
		}
		onceki->sonraki = ders;
		return;
	}
	dugumSayisi++;
	if (bas == nullptr)
	{
		bas = yeni;
		son = yeni;
		return;
	}
	if (strcmp(yeni->ogrno, bas->ogrno) < 0)
	{
		yeni->sonraki = bas;
		bas = yeni;
		return;
	}
	while (tara && (strcmp(yeni->ogrno, tara->ogrno) > 0))
	{
		onceki = tara;
		tara = tara->sonraki;
	}
	if (tara)
	{
		yeni->sonraki = tara;
	}
	onceki->sonraki = yeni;
}

ogrenci* ogrenciListesi::ogrenciBul(char ogrno[15])
{
	ogrenci* tara;
	tara = bas;
	while (tara)
	{
		if (strcmp(tara->ogrno, ogrno) == 0)
		{
			return tara;
		}
		tara = tara->sonraki;
	}
	return nullptr;
}

void ogrenciListesi::olustur()
{
	dugumSayisi = 0;
	bas = nullptr;
	son = nullptr;
}

void ogrenciListesi::kapat()
{
	ogrenci* p;
	ders* d;
	while (bas)
	{
		p = bas;
		d = p->dersdugumu;
		bas = bas->sonraki;
		while (d)
		{
			p->dersdugumu = p->dersdugumu->sonraki;
			delete d;
			d = p->dersdugumu;
		}

		delete p;
	}
	dugumSayisi = 0;
}

void ogrenciListesi::listeKur(string dosyaAdi)
{
	ifstream dosyaOku(dosyaAdi);
	string satir = "";
	string dersKodustr = "";
	string dersAdistr = "";
	if (dosyaOku.is_open())
	{
		int i = 0;
		while (getline(dosyaOku, satir)) {
			if (i != 0)
			{
				int no = 0;
				int adi = satir.find("\t") + 1;
				int soyadi = satir.find_last_of(" ",satir.length()-3) + 1;

				string noStr = satir.substr(no, adi - no - 1);
				string adistr = satir.substr(adi, soyadi - adi - 1);
				string soyadistr = satir.substr(soyadi);
				ekle(adistr, soyadistr, noStr, dersKodustr, dersAdistr);
			}
			else
			{
				int dersKodu = 0;
				int dersAdi = satir.find(" ") + 1;
				dersKodustr = satir.substr(dersKodu, dersAdi - 1);
				dersAdistr = satir.substr(dersAdi);
			}
			i++;
		}
		dosyaOku.close();
	}
}

void ogrenciListesi::dersSil(char ogrno[15], char dersadi[50])
{
	ogrenci*ogr=ogrenciBul(ogrno);
	if(!ogr)
	{
		cout << "ogrenci bulunamadi\n";
		return;
	}
	ders* tara = ogr->dersdugumu;
	ders* temp = nullptr;
	while (tara)
	{
		if (strcmp(tara->dersadi,dersadi)==0)
		{
			if (!temp)
			{
				ogr->dersdugumu = tara->sonraki;
			}else
			{
				temp->sonraki = tara->sonraki;
			}
			delete tara;
			return;
		}
		temp = tara;
		tara = tara->sonraki;
	}
}

void ogrenciListesi::ogrenciSil(char ogrno[15])
{
	ogrenci* tara=bas, * onceki=nullptr;
	ders* ders;
	while (tara)
	{
		if(strcmp(tara->ogrno,ogrno)==0)
		{
			if (!onceki)
			{
				bas = bas->sonraki;
			}else
			{
				onceki->sonraki = tara->sonraki;
			}
			while (tara->dersdugumu)
			{
				ders = tara->dersdugumu;
				tara->dersdugumu = tara->dersdugumu->sonraki;
				delete ders;
			}
			delete tara;
			dugumSayisi--;
			return;
		}
		onceki = tara;
		tara = tara->sonraki;
	}
}

void ogrenciListesi::listele()
{
	ogrenci* tara;
	tara = bas;
	ders* ders;
	while (tara)
	{
		cout << tara->ogrno << " " << tara->ad <<" " << tara->soyad;
		ders = tara->dersdugumu;
		while (ders)
		{
			cout <<" "<< ders->derskodu<< " " << ders->dersadi;
			ders = ders->sonraki;
		}
		cout << "\n";
		tara = tara->sonraki;
	}
}

void ogrenciListesi::ara()
{
	ogrenci* tara;
	tara = bas;
	ders* ders;
	cout << "Numaraya gore arama yapmak icin: N\n";
	cout << "Soyada gore arama yapmak icin: S\n";
	char secim;
	cin >> secim;
	if (secim=='N')
	{
		cout << "Ogrenci Numarasi:";
		char ogrno[15];
		cin >> ogrno;
		ogrenci* ogr = ogrenciBul(ogrno);
		if(ogr)
		{
			cout << ogr->ogrno << " " << ogr->ad << " " << ogr->soyad;
			ders = ogr->dersdugumu;
			while (ders)
			{
				cout << " " << ders->derskodu << " " << ders->dersadi;
				ders = ders->sonraki;
			}
			cout << "\n";
			return;
		}
		cout << "Ogrenci bulunamadi\n";
		
	}else if(secim=='S')
	{
		int sayac = 0;
		cout << "Ogrenci Soyadi:";
		char soyadi[30];
		cin >> soyadi;
		while (tara)
		{
			if (strcmp(tara->soyad, soyadi) == 0)
			{
				cout << tara->ogrno << " " << tara->ad << " " << tara->soyad;
				ders = tara->dersdugumu;
				while (ders)
				{
					cout << " " << ders->derskodu << " " << ders->dersadi;
					ders = ders->sonraki;
				}
				cout << "\n";
				tara = tara->sonraki;
				sayac++;
			}
			tara = tara->sonraki;
		}
		cout << sayac << " ogrenci bulundu\n";
	}
}

void ogrenciListesi::kesisimBul(char ders1kodu[10], char ders2kodu[10])
{
	ogrenci* tara = bas;
	ders* d;
	int sayac = 0;
	while (tara)
	{
		int kesisim = 0;
		d = tara->dersdugumu;
		while (d)
		{
			if(strcmp(d->derskodu,ders1kodu)==0 || strcmp(d->derskodu,ders2kodu)==0)
			{
				kesisim++;
			}
			if (kesisim==2)
			{
				sayac++;
				ders* ders = nullptr;
				cout << tara->ogrno << " " << tara->ad << " " << tara->soyad;
				ders = tara->dersdugumu;
				while (ders)
				{
					cout << " " << ders->derskodu << " " << ders->dersadi;
					ders = ders->sonraki;
				}
				cout << "\n";
				break;
			}
			d = d->sonraki;
		}
		tara = tara->sonraki;
	}
	cout << sayac << " ogrenci bulundu";
}

void ogrenciListesi::dosyaYaz()
{
	ogrenci* tara = bas;
	ders* ders;
	string satir = "";
	ofstream dosyaYaz(dosya);
	if (dosyaYaz.is_open())
	{
		while (tara)
		{
			dosyaYaz << tara->ogrno << " " << tara->ad << " " << tara->soyad;
			ders = tara->dersdugumu;
			while (ders)
			{
				dosyaYaz << " " << ders->derskodu << " " << ders->dersadi;
				ders = ders->sonraki;
			}
			dosyaYaz << "\n";
			tara = tara->sonraki;
		}
		dosyaYaz.close();
	}
}