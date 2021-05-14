#pragma once
#include "ders.h"

struct ogrenci
{
	char ogrno[15];
	char ad[30];
	char soyad[30];
	ders* dersdugumu;
	ogrenci* sonraki;
};
