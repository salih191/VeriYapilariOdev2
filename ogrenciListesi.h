#pragma once
#include <string>


#include "ogrenci.h"

using namespace std;
struct ogrenciListesi
{
private:
	ogrenci* bas, * son;
	int dugumSayisi;
	string dosya = "ogrenciler.txt";
	void ekle(string adi, string soyadi, string ogrNo, string dersKodu, string dersAdi);
	ogrenci* ogrenciBul(char ogrno[15]);
public:
	void olustur();
	void kapat();
	
	void listeKur(string dosyaAdi);
	void dersSil(char ogrno[15], char dersadi[50]);
	void  ogrenciSil(char ogrno[15]);
	void listele();
	void ara();
	void  kesisimBul(char ders1kodu[10], char ders2kodu[10]);
	void dosyaYaz();
};
