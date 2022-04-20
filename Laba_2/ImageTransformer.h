#pragma once
#include <QImage>

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
		Normal
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
};

