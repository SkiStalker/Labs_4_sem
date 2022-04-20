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
