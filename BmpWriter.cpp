#include "BmpWriter.h"
#include <iostream>
using namespace std;
BmpWriter::BmpWriter(int h, int w, char* fn) {
	this->h = h;
	this->w = w;
	r.resize(h);
	g.resize(h);
	b.resize(h);
	for (int i = 0; i < h; i++) {
		r[i].resize(w, 0);
		g[i].resize(w, 0);
		b[i].resize(w, 0);
	}
	data = new char[3 * h * w];
	fileName = new char[strlen(fn) + 1];
	strcpy(fileName, fn);
}

BmpWriter::~BmpWriter() {
	delete[]data;
}
void BmpWriter::print(CornerBlockList& cbl) {
	int n = cbl.getModuleNum();
	double bnd = 0;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) 
			r[i][j] = g[i][j] = b[i][j] = 0;

	for (int i = 0; i < n; i++) {
		Module m = cbl.getModule(i);
		double x = m.getLeftLowerX() + m.getW();
		double y = m.getLeftLowerY() + m.getH();
		if (x > bnd)
			bnd = x;
		if (y > bnd)
			bnd = y;
	}
	for (int i = 0; i < n; i++) {
		Module m = cbl.getModule(i);
		double x1 = m.getLeftLowerX();
		double y1 = m.getLeftLowerY();
		double x2 = x1 + m.getW();
		double y2 = y1 + m.getH();
		int picX1 = int(x1 / bnd * w);
		int picY1 = int(y1 / bnd * h);
		int picX2 = int(x2 / bnd * w);
		int picY2 = int(y2 / bnd * h);
		if (picX1 == w)
			picX1 = w - 1;
		if (picY1 == h)
			picY1 = h - 1;
		if (picX2 == w)
			picX2 = w - 1;
		if (picY2 == h)
			picY2 = h - 1;

		for (int j = picY1; j <= picY2; j++)
			for (int k = picX1; k <= picX2; k++) {
				r[j][k] = 200;
				g[j][k] = 255;
				b[j][k] = 150;
			}

		for (int j = picY1; j <= picY2; j++) {
			r[j][picX1] = 0;
			g[j][picX1] = 0;
			b[j][picX1] = 255;
			r[j][picX2] = 0;
			g[j][picX2] = 0;
			b[j][picX2] = 255;
		}

		for (int j = picX1; j <= picX2; j++) {
			r[picY1][j] = 0;
			g[picY1][j] = 0;
			b[picY1][j] = 255;
			r[picY2][j] = 0;
			g[picY2][j] = 0;
			b[picY2][j] = 255;
		}
	}
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			int offset = (i * w + j) * 3;
			data[offset] = b[i][j];
			data[offset + 1] = g[i][j];
			data[offset + 2] = r[i][j];
		}
	FILE *output = fopen(fileName, "wb");
	
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + 2 + sizeof(BITMAPINFOHEADER) + 3 * h * w;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + 2 + sizeof(BITMAPINFOHEADER);

	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biHeight = h;
	infoHeader.biWidth = w;
	infoHeader.biPlanes = 3;
	infoHeader.biBitCount = 24;
	infoHeader.biSizeImage = 3 * h * w;
	infoHeader.biCompression = 0; //BI_RGB

	WORD bfType = 0x4d42;
	fwrite(&bfType, 1, sizeof(WORD), output);
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, output);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, output);
	fwrite(data, 3 * h * w, 1, output);
	fclose(output);
}