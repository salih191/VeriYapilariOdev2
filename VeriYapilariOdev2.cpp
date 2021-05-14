
#include <iostream>

#include "ogrenciListesi.h"
ogrenciListesi ogrenciler;
using namespace std;
void islemMenusu();

int main()
{
	
	string anadosya = "C://Users//salih//Downloads//";
	string matDosya = anadosya+ "mat101.txt";
	string fizDosya =anadosya+ "fiz101.txt";
	string engDosya =anadosya+ "eng101.txt";
	ogrenciler.olustur();
	ogrenciler.listeKur(matDosya);
	ogrenciler.listeKur(fizDosya);
	ogrenciler.listeKur(engDosya);
	islemMenusu();
	ogrenciler.kapat();
	
}



void islemMenusu()
{
	cout << "\t\t\t---ISLEM MENUSU---\n";
	cout << "Yapmak istediginiz islem icin asagidaki durumlardan birini giriniz...\n";
	cout << "Arama yapmak icin: A\n";
	cout << "Ders silmek icin: D\n";
	cout << "Kesisim bulmak icin: K\n";
	cout << "Listeyi ekrana yazdirmak icin: L\n";
	cout << "Ogrenci silmek icin: O\n";
	cout << "Dosya yaz: Y\n";
	cout << "Cikis icin: C\n";

	char islem;
	cin >> islem;
	islem=toupper(islem);
	switch (islem)
	{
		case 'A':
			ogrenciler.ara();
			break;
	case 'D':
		char ogrNo[15], dersadi[50];
		cout << "Dersi silinicek Ogrencinin;\n";
		cout << "numarasi:";
		cin >> ogrNo;
		cout << "dersi:";
		cin >> dersadi;
		ogrenciler.dersSil(ogrNo,dersadi);
		break;
	case 'K':
		char ders1kodu[10], ders2kodu[10];
		cout << "Kesisim bulunacak derslerin kodlari;\n";
		cout << "1. dersin kodu:";
		cin >> ders1kodu;
		cout << "2. dersin kodu:";
		cin >> ders2kodu;
		ogrenciler.kesisimBul(ders1kodu, ders2kodu);
		break;
	case 'L':
		ogrenciler.listele();
		break;
	case 'O':
		char ogrno[15];
		cout << "Silinicek Ogrencinin numarasi:";
		cin >> ogrno;
		ogrenciler.ogrenciSil(ogrno);
		break;
	case 'Y':
		ogrenciler.dosyaYaz();
		break;
	case 'C':
		return;
	default:
		break;
	}
	islemMenusu();
}
