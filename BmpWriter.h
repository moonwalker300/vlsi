#ifndef BMPWRITER_H
#define BMPWRITER_H
#include "CornerBlockList.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

typedef struct {
	//WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes; 
	WORD biBitCount;
	DWORD  biCompression;
	DWORD  biSizeImage; 
	LONG  biXPelsPerMeter; 
	LONG  biYPelsPerMeter; 
	DWORD  biClrUsed;
	DWORD  biClrImportant; 
} BITMAPINFOHEADER; 

class BmpWriter {
private:
	std::vector < std::vector<int> > r;
	std::vector < std::vector<int> > g;
	std::vector < std::vector<int> > b;
	char* data;
	char* fileName;
	int h, w;
public:
	void print(CornerBlockList&);
	BmpWriter(int, int, char*);
	~BmpWriter();
};

#endif