#pragma once
#include <QImage>
#include <QVector>
#include <qmath.h>
#include <complex>

class ImageTransformer
{
public:

	enum class Transformation
	{
		None,
		Inversion,
		ToBlackAndWhite,
		ThresholdColors,
		ThresholdBrightness,
		LogBrightness,
		DegreeBrightness,
		LineBrightness,
		Equalize,
		Normal,

		BoxFilter,
		MedianFilter,
		GausseFilter,
		SharpnessFilter,
		LaplasFilter,
		SobelFilter,
		Fourier
	};

	static int getBrightness(int r, int g, int b);

	static void invertColors(QImage& img);

	static void toGray(QImage& img);

	static void thresholdColors(QImage& img, int lowR, int highR, int lowG, int highG, int lowB, int highB);

	static void thresholdBrightnes(QImage& img, int topBrightness, int lowBrightness);

	static void logBrightnessFilter(QImage& img);

	static void degreeBrightnessFilter(QImage& img);

	static void lineBrightnessFilter(QImage& img);

	static void equalizationFilter(QImage& img);

	static void normalFilter(QImage& img, int expectedValue, int dispersion);

	static void boxFilter(QImage& img);

	static int compare(const void* a, const void* b);

	static void medianFilter(QImage& img);

	static void gausseFilter(QImage& img);

	static void sharpnessFilter(QImage& img);

	static void laplasFilter(QImage& img);

	static void sobelFilter(QImage& img);

	static QVector < std::complex < double >> fft(const QVector < std::complex < double >>& as);

	static void fourierTransform(QImage& img, bool fast_flag);
};

