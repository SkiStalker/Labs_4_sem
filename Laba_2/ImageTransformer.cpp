#include "ImageTransformer.h"


void ImageTransformer::toGray(QImage& img)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();

	int pixelsQuo = h * w;
	int r, g, b;
	int brightness = 0;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;
		brightness = getBrightness(r, g, b);
		px -= 2;
		*px = brightness;
		*++px = brightness;
		*++px = brightness;
		++px;
		px++;
	}
}

int ImageTransformer::getBrightness(int r, int g, int b)
{
	return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

void ImageTransformer::invertColors(QImage& img)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();

	int pixelsQuo = h * w;
	int r, g, b;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;
		px -= 2;
		*px = 255 - r;
		*++px = 255 - g;
		*++px = 255 - b;
		++px;
		px++;
	}
}

void ImageTransformer::logBrightnessFilter(QImage& img)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();
	double c = 255 / log(256);

	int pixelsQuo = h * w;
	int r, g, b;
	double y, u, v;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
		v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

		y = c * log(1 + y);

		r = y + 1.2803 * v;
		g = y - 0.2148 * u - 0.3805 * v;
		b = y + 2.1279 * u;


		if (r > 255)
			r = 255;

		if (g > 255)
			g = 255;

		if (b > 255)
			b = 255;

		if (r < 0)
			r = 0;

		if (g < 0)
			g = 0;

		if (b < 0)
			b = 0;


		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}

void ImageTransformer::degreeBrightnessFilter(QImage& img)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();
	double c = 255 / pow(255, 1.25);

	int pixelsQuo = h * w;
	int r, g, b;
	double y, u, v;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
		v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

		y = c * pow(y, 1.25);

		r = y + 1.2803 * v;
		g = y - 0.2148 * u - 0.3805 * v;
		b = y + 2.1279 * u;


		if (r > 255)
			r = 255;

		if (g > 255)
			g = 255;

		if (b > 255)
			b = 255;

		if (r < 0)
			r = 0;

		if (g < 0)
			g = 0;

		if (b < 0)
			b = 0;

		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}

void ImageTransformer::lineBrightnessFilter(QImage& img)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();
	int c1 = 80, p1 = 60;
	int c2 = 180, p2 = 220;

	double q1 = (double)p1 / c1;
	double q2 = (double)(255 - p2) / (255 - c2);
	double q3 = (double)(p2 - p1) / (c2 - c1);

	int pixelsQuo = h * w;
	int r, g, b;
	double y, u, v;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
		v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

		if (y < c1)
		{
			y *= q1;
		}
		else if (y > c2)
		{
			y = (double)(y - c2) * q2 + p2;
		}
		else
		{
			y = (double)(y - c1) * q3 + p1;
		}


		r = y + 1.2803 * v;
		g = y - 0.2148 * u - 0.3805 * v;
		b = y + 2.1279 * u;


		if (r > 255)
			r = 255;

		if (g > 255)
			g = 255;

		if (b > 255)
			b = 255;

		if (r < 0)
			r = 0;

		if (g < 0)
			g = 0;

		if (b < 0)
			b = 0;

		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}

void ImageTransformer::equalizationFilter(QImage& img)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();

	int pixelsQuo = h * w;
	unsigned long long histData[256];
	memset(histData, 0, sizeof(size_t) * 256);

	int r, g, b;
	double y, u, v;

	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;

		histData[(int)y]++;
		px += 2;
	}

	unsigned long long hMin = 0;

	for (int i = 0; i < 256; i++)
	{
		if (histData[i])
		{
			if (hMin)
			{
				if (histData[i] < hMin)
					hMin = histData[i];
			}
			else
			{
				hMin = histData[i];
			}
		}
	}

	size_t histDataTransform[256];
	memset(histDataTransform, 0, sizeof(size_t) * 256);

	long long nlightness = 0;
	for (auto p = histData, pt = histDataTransform; p < histData + 256; p++, pt++)
	{
		nlightness += *p;
		*pt = ((double)nlightness - hMin) / pixelsQuo * 255;
	}

	px = img.bits();
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
		v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

		y = histDataTransform[(int)y];


		r = y + 1.2803 * v;
		g = y - 0.2148 * u - 0.3805 * v;
		b = y + 2.1279 * u;


		if (r > 255)
			r = 255;

		if (g > 255)
			g = 255;

		if (b > 255)
			b = 255;

		if (r < 0)
			r = 0;

		if (g < 0)
			g = 0;

		if (b < 0)
			b = 0;

		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}

void ImageTransformer::normalFilter(QImage& img, int expectedValue, int dispersion)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();

	int pixelsQuo = h * w;
	unsigned long long histData[256];
	memset(histData, 0, sizeof(size_t) * 256);

	int r, g, b;
	double y, u, v;

	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;

		histData[(int)y]++;
		px += 2;
	}

	unsigned long long histDataTransform[256];

	memset(histDataTransform, 0, sizeof(size_t) * 256);

	long long nlightness = 0;
	for (auto p = histData, pt = histDataTransform; p < histData + 256; p++, pt++)
	{
		nlightness += *p;
		*pt = (double)nlightness/ pixelsQuo * 255;
	}


	int z0 = expectedValue;
	int m = dispersion;
	if (2 * dispersion - expectedValue > 255 || 2 * dispersion - expectedValue < 0)
		m = (128 + z0) / 2;

	double g1 = 255 + z0 - 2 * m;
	g1 /= 255 * z0;

	double g2 = 2 * m - z0;
	g2 /= 255 * (255 - z0);

	double k = 1;

	px = img.bits();
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
		u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
		v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

		k = (double)histDataTransform[(int)y] / g1 / 255;

		if (k < z0)
			y = k;
		else
		{
			y = (double)histDataTransform[(int)y] / 255 - z0 * (g1 - g2);
			y /= g2;
		}

		r = y + 1.2803 * v;
		g = y - 0.2148 * u - 0.3805 * v;
		b = y + 2.1279 * u;

		if (r > 255)
			r = 255;

		if (g > 255)
			g = 255;

		if (b > 255)
			b = 255;

		if (r < 0)
			r = 0;

		if (g < 0)
			g = 0;

		if (b < 0)
			b = 0;

		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}

void ImageTransformer::boxFilter(QImage& img)
{
	uchar* px = img.bits();
	uchar* spx = img.bits();

	QImage* newImg = new QImage(img);
	uchar* pnx = newImg->bits();

	int h = img.height();
	int w = img.width();

	long long** integralPixTable = new long long* [h];
	for (auto ptr = integralPixTable; ptr < integralPixTable + h; ptr++)
	{
		*ptr = new long long[w];
	}

	int r, g, b;
	double y, u, v;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			r = *px;
			g = *++px;
			b = *++px;
			px += 2;
			y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
			long long temp = y;
			if (i != 0)
				temp += integralPixTable[i - 1][j];
			if (j != 0)
				temp += integralPixTable[i][j - 1];
			if (i != 0 && j != 0)
				temp -= integralPixTable[i - 1][j - 1];
			integralPixTable[i][j] = temp;
		}
	}
	px = spx;

	const int N = 5;
	int low_bound = N / 2;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = *px;
			g = *++px;
			b = *++px;

			u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
			v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

			int ai = low_bound, bi = low_bound, ci = low_bound, di = low_bound;
			int aj = low_bound, bj = low_bound, cj = low_bound, dj = low_bound;
			if (i + low_bound >= h)
			{
				ai = h - i - 1;
				ci = ai;

			}
			if (i - low_bound < 0)
			{
				di = i;
				bi = i;
			}
			if (j + low_bound >= w)
			{
				aj = w - j - 1;
				dj = aj;

			}
			if (j - low_bound < 0)
			{
				bj = j;
				cj = j;
			}
			int k = (ai + di) * (aj + cj);

			y = (integralPixTable[i + ai][j + aj] + integralPixTable[i - bi][j - bj] \
				- integralPixTable[i + ci][j - cj] - integralPixTable[i - di][j + dj]);

			y /= k;

			r = y + 1.2803 * v;
			g = y - 0.2148 * u - 0.3805 * v;
			b = y + 2.1279 * u;

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;

			px++;
			*pnx = r;
			*++pnx = g;
			*++pnx = b;
			*++pnx = *px;
			pnx++;
			px++;
		}
	}

	img = *newImg;

	for (auto ptr = integralPixTable; ptr < integralPixTable + h; ptr++)
	{
		delete[] * ptr;
	}
	delete[] integralPixTable;
	delete newImg;
}

int ImageTransformer::compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

void ImageTransformer::medianFilter(QImage& img)
{
	uchar* px = img.bits();
	uchar* spx = img.bits();

	QImage* newImg = new QImage(img);
	uchar* pnx = newImg->bits();

	int h = img.height();
	int w = img.width();

	int r, g, b;
	double y, u, v;

	const int N = 3;
	int low_bound = N / 2;

	int* values = new int[N * N];

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = *px;
			g = *++px;
			b = *++px;

			u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
			v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

			int count = 0;
			int local_w, local_h;


			for (int k = 0; k < N; k++)
			{
				for (int l = 0; l < N; l++)
				{
					local_h = (px - spx) / w / 4 - low_bound + k;
					local_w = (px - spx) / 4 % w - low_bound + l;
					if (!(local_w > -1 && local_w < w && local_h > -1 && local_h < h))
						continue;
					auto cpx = spx + local_h * w * 4 + local_w * 4;
					r = *cpx;
					g = *++cpx;
					b = *++cpx;
					y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
					values[count++] = y;
				}
			}

			qsort(values, count, sizeof(int), compare);
			y = values[count / 2];

			r = y + 1.2803 * v;
			g = y - 0.2148 * u - 0.3805 * v;
			b = y + 2.1279 * u;

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;

			px++;
			*pnx = r;
			*++pnx = g;
			*++pnx = b;
			*++pnx = *px;
			pnx++;
			px++;
		}
	}
	img = *newImg;
	delete newImg;
}

void ImageTransformer::gausseFilter(QImage& img)
{
	const double PI = 4.0 * atan(1.0);
	int radius = 4;
	int size = radius * 2 + 1;
	double** gaus = new double* [size];

	for (auto ptr = gaus; ptr < gaus + size; ptr++)
	{
		*ptr = new double[size];
	}


	int center = radius;
	double part = 1 / (2 * PI * radius * radius);
	double sum = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			double degree = -(double)((i - center) * (i - center) + (j - center) * (j - center)) / (2 * radius * radius);
			gaus[i][j] = part * exp(degree);
			sum += gaus[i][j];
		}
	}
	double norm = 1 / sum;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			gaus[i][j] *= norm;
		}
	}

	uchar* px = img.bits();
	uchar* spx = img.bits();

	QImage* newImg = new QImage(img);
	uchar* pnx = newImg->bits();

	int h = img.height();
	int w = img.width();

	int r, g, b;
	double y, u, v;


	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = *px;
			g = *++px;
			b = *++px;

			u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
			v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

			double sum = 0;
			int local_w, local_h;
			for (int k = 0; k < size; k++)
			{
				for (int l = 0; l < size; l++)
				{
					local_h = (px - spx) / w / 4 - radius + k;
					local_w = (px - spx) / 4 % w - radius + l;
					if (!(local_w > -1 && local_w < w && local_h > -1 && local_h < h))
						continue;
					auto cpx = spx + local_h * w * 4 + local_w * 4;
					r = *cpx;
					g = *++cpx;
					b = *++cpx;
					y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
					sum += gaus[k][l] * y;
				}
			}


			y = sum;

			r = y + 1.2803 * v;
			g = y - 0.2148 * u - 0.3805 * v;
			b = y + 2.1279 * u;

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;

			px++;
			*pnx = r;
			*++pnx = g;
			*++pnx = b;
			*++pnx = *px;
			pnx++;
			px++;
		}
	}

	for (auto ptr = gaus; ptr < gaus + size; ptr++)
	{
		delete[] * ptr;
	}
	delete[] gaus;

	img = *newImg;
	delete newImg;
}

void ImageTransformer::sharpnessFilter(QImage& img)
{
	uchar* px = img.bits();
	uchar* spx = img.bits();

	QImage* newImg = new QImage(img);
	uchar* pnx = newImg->bits();

	int h = img.height();
	int w = img.width();

	int r, g, b;
	double y, u, v;

	const int N = 3;
	int low_bound = N / 2;

	int transform_matrix[N][N] = { { -1, -2, -1 },{ -2, 22, -2 },{ -1, -2, -1 } };
	double delimetr = (double)1 / 10;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = *px;
			g = *++px;
			b = *++px;

			u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
			v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

			double sum = 0;
			int local_w, local_h;
			for (int k = 0; k < N; k++)
			{
				for (int l = 0; l < N; l++)
				{
					local_h = (px - spx) / w / 4 - low_bound + k;
					local_w = (px - spx) / 4 % w - low_bound + l;
					if (!(local_w > -1 && local_w < w && local_h > -1 && local_h < h))
						continue;
					auto cpx = spx + local_h * w * 4 + local_w * 4;
					r = *cpx;
					g = *++cpx;
					b = *++cpx;
					y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
					sum += transform_matrix[k][l] * y;
				}
			}


			y = sum * delimetr;

			r = y + 1.2803 * v;
			g = y - 0.2148 * u - 0.3805 * v;
			b = y + 2.1279 * u;

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;

			px++;
			*pnx = r;
			*++pnx = g;
			*++pnx = b;
			*++pnx = *px;
			pnx++;
			px++;
		}
	}

	img = *newImg;
	delete newImg;
}

void ImageTransformer::laplasFilter(QImage& img)
{
	uchar* px = img.bits();
	uchar* spx = img.bits();

	QImage* newImg = new QImage(img);
	uchar* pnx = newImg->bits();

	int h = img.height();
	int w = img.width();

	int r, g, b;
	double y, u, v;

	const int N = 3;
	int low_bound = N / 2;

	int transform_matrix[N][N] = { { -1, -1, -1 },{ -1, 8, -1 },{ -1, -1, -1 } };

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = *px;
			g = *++px;
			b = *++px;

			u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
			v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

			double sum = 0;
			int local_w, local_h;
			for (int k = 0; k < N; k++)
			{
				for (int l = 0; l < N; l++)
				{
					local_h = (px - spx) / w / 4 - low_bound + k;
					local_w = (px - spx) / 4 % w - low_bound + l;
					if (!(local_w > -1 && local_w < w && local_h > -1 && local_h < h))
						continue;
					auto cpx = spx + local_h * w * 4 + local_w * 4;
					r = *cpx;
					g = *++cpx;
					b = *++cpx;
					y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
					sum += transform_matrix[k][l] * y;
				}
			}


			y = y + sum;

			r = y + 1.2803 * v;
			g = y - 0.2148 * u - 0.3805 * v;
			b = y + 2.1279 * u;

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;

			px++;
			*pnx = r;
			*++pnx = g;
			*++pnx = b;
			*++pnx = *px;
			pnx++;
			px++;
		}
	}

	img = *newImg;
	delete newImg;
}

void ImageTransformer::sobelFilter(QImage& img)
{
	uchar* px = img.bits();
	uchar* spx = img.bits();

	QImage* newImg = new QImage(img);
	uchar* pnx = newImg->bits();

	int h = img.height();
	int w = img.width();

	int r, g, b;
	double y, u, v;

	const int N = 3;
	int low_bound = N / 2;

	int transform_matrix[N][N] = { { -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 } };

	int transform_matrix_x[N][N] = { { -1, -2, -1 },
		{ 0, 0, 0 },
		{ 1, 2, 1 } };

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			r = *px;
			g = *++px;
			b = *++px;

			u = -0.0999 * r - 0.3360 * g + 0.4360 * b;
			v = 0.6150 * r - 0.5586 * g - 0.0563 * b;

			double sum = 0;
			int local_w, local_h;
			for (int k = 0; k < N; k++)
			{
				for (int l = 0; l < N; l++)
				{
					local_h = (px - spx) / w / 4 - low_bound + k;
					local_w = (px - spx) / 4 % w - low_bound + l;
					if (!(local_w > -1 && local_w < w && local_h > -1 && local_h < h))
					{
						continue;
					}
					auto cpx = spx + local_h * w * 4 + local_w * 4;
					r = *cpx;
					g = *++cpx;
					b = *++cpx;
					y = 0.2126 * r + 0.7152 * g + 0.0722 * b;
					sum += transform_matrix[k][l] * y + y * transform_matrix_x[k][l];
				}
			}


			y = sum;

			r = y + 1.2803 * v;
			g = y - 0.2148 * u - 0.3805 * v;
			b = y + 2.1279 * u;

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;

			px++;
			*pnx = r;
			*++pnx = g;
			*++pnx = b;
			*++pnx = *px;
			pnx++;
			px++;
		}
	}

	img = *newImg;
	delete newImg;
}

QVector<std::complex<double>> ImageTransformer::fft(const QVector<std::complex<double>>& as)
{
	int n = as.size();
	int k = 0;
	while ((1 << k) < n) k++;
	QVector<int> rev(n);
	rev[0] = 0;
	int high1 = -1;
	for (int i = 1; i < n; i++)
	{
		if ((i & (i - 1)) == 0)
			high1++;
		rev[i] = rev[i ^ (1 << high1)];
		rev[i] |= (1 << (k - high1 - 1));
	}

	QVector < std::complex < double >> roots(n);
	for (int i = 0; i < n; i++) {
		double alpha = 2 * M_PI * i / n;
		roots[i] = std::complex <double>(cos(alpha), sin(alpha));
	}

	QVector < std::complex < double >> cur(n);
	for (int i = 0; i < n; i++)
		cur[i] = as[rev[i]];

	for (int len = 1; len < n; len <<= 1) {
		QVector < std::complex < double >> ncur(n);
		int rstep = roots.size() / (len * 2);
		for (int pdest = 0; pdest < n;) {
			int p1 = pdest;
			for (int i = 0; i < len; i++) {
				std::complex <double> val = roots[i * rstep] * cur[p1 + len];
				ncur[pdest] = cur[p1] + val;
				ncur[pdest + len] = cur[p1] - val;
				pdest++, p1++;
			}
			pdest += len;
		}
		cur.swap(ncur);
	}
	return cur;
}

void ImageTransformer::fourierTransform(QImage& img, bool fast_flag)
{
	int h = img.height();
	int w = img.width();

	QVector<QVector<int>> fxy(h);

	for (auto& el : fxy)
	{
		el.resize(w);
	}

	uchar* px = img.bits();
	double y;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			y = 0;
			y += 0.2126 * (*px);
			y += 0.7152 * (*++px);
			y += 0.0722 * (*++px);
			px += 2;
			if ((i + j) % 2)
				y *= -1;
			fxy[i][j] = y;
		}
	}

	QVector<QVector<int>> Fxy(h);
	for (auto& el : Fxy)
	{
		el.resize(w);
	}


	if (fast_flag)
	{
		int k = 0;
		while ((1 << k) < (w)) k++;

		int k2 = 0;
		while ((1 << k2) < (h)) k2++;


		QVector < std::complex < double >> b(1 << (k));
		QVector < std::complex < double >> a(1 << (k2));
		auto ptr = fxy;
		QVector<QVector < std::complex < double >>> box((1 << k2));
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < fxy[i].size(); j++)
			{
				a[j] = fxy.at(i).at(j);
			}
			box[i] = fft(a);
		}

		for (int i = 0; i < h; i++)
		{
			for (int x = 0; x < h; x++)
			{
				b[x] = box.at(x).at(i);
			}
			auto res1d = fft(b);
			for (int j = 0; j < w; j++)
			{
				auto realpart = res1d.at(j).real();
				auto imgpart = res1d.at(j).imag();
				Fxy[i][j] = (int)sqrt(realpart * realpart + imgpart * imgpart);
			}
		}
	}
	else
	{
		const double PI = 4.0 * atan(1.0);

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				double temp = 0, tempy = 0;
				for (int x = 0; x < h; x++)
				{
					for (int y = 0; y < w; y++)
					{

						double alpha = -2 * PI * ((double)i * x / h + (double)j * y / w);
						temp += Fxy[i][j] * cos(alpha);
						tempy += Fxy[i][j] * sin(alpha);
					}
				}
				Fxy[i][j] = sqrt(temp * temp + tempy * tempy);
			}

		}
	}

	px = img.bits();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			auto val = Fxy.at(i).at(j);
			y = 10 * log(1 + val);
			if (y > 255)
			{
				y = 255;
			}
			if (y < 0)
				y = 0;

			*px = y;
			*++px = y;
			*++px = y;
			px += 2;
		}
	}

}

void ImageTransformer::thresholdColors(QImage& img, int lowR, int highR, int lowG, int highG, int lowB, int highB)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();

	int pixelsQuo = h * w;
	int r, g, b;
	int lightness = 0;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		if (r > highR)
			r = 255;

		if (r < lowR)
			r = 0;

		if (g > highG)
			g = 255;

		if (g < lowG)
			g = 0;

		if (b > highB)
			b = 255;

		if (b < lowB)
			b = 0;


		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}

void ImageTransformer::thresholdBrightnes(QImage& img, int topBrightness, int lowBrightness)
{
	uchar* px = img.bits();

	int h = img.height();
	int w = img.width();

	int pixelsQuo = h * w;
	int r, g, b;
	int brightness = 0;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;

		brightness = getBrightness(r, g, b);

		if (brightness > topBrightness)
		{
			r = 255;
			g = 255;
			b = 255;
		}

		if (brightness < lowBrightness)
		{
			r = 0;
			g = 0;
			b = 0;
		}
		px -= 2;
		*px = r;
		*++px = g;
		*++px = b;
		++px;
		px++;
	}
}
