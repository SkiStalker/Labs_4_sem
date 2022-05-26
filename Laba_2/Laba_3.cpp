#include "Laba_3.h"

Laba_3::Laba_3(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
}

void Laba_3::showAuthor()
{
	QMessageBox::information(this, "Author", "Zabelin Nikita M8O-210b-20");
}

void Laba_3::showAbout()
{
	QMessageBox::information(this, "About", "Laboratory work 2 ");
}

void Laba_3::selectColorInversion()
{
	tryChangeTransformation(Transformation::Inversion);
}

void Laba_3::selectToBlackAndWhite()
{
	tryChangeTransformation(Transformation::ToBlackAndWhite);
}

void Laba_3::selectThresholdColors()
{
	tryChangeTransformation(Transformation::ThresholdColors);
}

void Laba_3::selectThresholdBrightness()
{
	tryChangeTransformation(Transformation::ThresholdBrightness);
}

void Laba_3::selectLogBrightness()
{
	tryChangeTransformation(Transformation::LogBrightness);
}

void Laba_3::selectDegreeBrightness()
{
	tryChangeTransformation(Transformation::DegreeBrightness);
}

void Laba_3::selectLineBrightness()
{
	tryChangeTransformation(Transformation::LineBrightness);
}

void Laba_3::selectEqualizeHistogram()
{
	tryChangeTransformation(Transformation::Equalize);
}

void Laba_3::selectNormalHistogram()
{
	tryChangeTransformation(Transformation::Normal);
}

void Laba_3::selectBoxFilter()
{
	tryChangeTransformation(Transformation::BoxFilter);
}

void Laba_3::selectMedianFilter()
{
	tryChangeTransformation(Transformation::MedianFilter);
}

void Laba_3::selectGausseFilter()
{
	tryChangeTransformation(Transformation::GausseFilter);
}

void Laba_3::selectSharpnessFilter()
{
	tryChangeTransformation(Transformation::SharpnessFilter);
}

void Laba_3::selectLaplasFilter()
{
	tryChangeTransformation(Transformation::LaplasFilter);
}

void Laba_3::selectSobelFilter()
{
	tryChangeTransformation(Transformation::SobelFilter);
}

void Laba_3::selectFourier()
{
	tryChangeTransformation(Transformation::Fourier);
}

void Laba_3::changeFirstSliderValue()
{
	applyTransformation();
}

void Laba_3::changeSecondSliderValue()
{
	applyTransformation();
}

void Laba_3::changeThirdSliderValue()
{
	applyTransformation();
}

void Laba_3::changeFourthSliderValue()
{
	applyTransformation();
}

void Laba_3::changeFifthSliderValue()
{
	applyTransformation();
}

void Laba_3::changeSixthSliderValue()
{
	applyTransformation();
}

void Laba_3::loadNewImage()
{
	auto res = QFileDialog::getOpenFileName(this, QString(), qApp->applicationDirPath());
	if (res.length())
	{
		loadImage(res);
		applyTransformation();
		makeHistograms();
	}
}

void Laba_3::loadImage(const QString& path)
{
	if (!originalImage->loadImage(path))
		QMessageBox::warning(this, "Load file error", "Can not load this file as picture");
}

void Laba_3::applyTransformation()
{
	transformedImage->getImage() = originalImage->getImage();

	QImage& curImg = transformedImage->getImage();

	switch (curTransform)
	{
	case Transformation::None:
		break;
	case Transformation::Inversion:
		ImageTransformer::invertColors(curImg);
		break;
	case Transformation::ToBlackAndWhite:
		ImageTransformer::toGray(curImg);
		break;
	case Transformation::ThresholdColors:
		ImageTransformer::thresholdColors(curImg, ui.firstHSlider->value(), ui.secondHSlider->value(),
			ui.thirdHSlider->value(), ui.fourthHSlider->value(),
			ui.fifthHSlider->value(), ui.sixthHSlider->value());
		break;
	case Transformation::ThresholdBrightness:
		ImageTransformer::thresholdBrightnes(curImg, ui.firstHSlider->value(), ui.secondHSlider->value());
		break;
	case Transformation::LogBrightness:
		ImageTransformer::logBrightnessFilter(curImg);
		break;
	case Transformation::DegreeBrightness:
		ImageTransformer::degreeBrightnessFilter(curImg);
		break;
	case Transformation::LineBrightness:
		ImageTransformer::lineBrightnessFilter(curImg);
		break;
	case Transformation::Equalize:
		ImageTransformer::equalizationFilter(curImg);
		break;
	case Transformation::Normal:
		ImageTransformer::normalFilter(curImg, ui.firstHSlider->value(), ui.secondHSlider->value());
		break;
	case Transformation::BoxFilter:
		ImageTransformer::boxFilter(curImg);
		break;
	case Transformation::MedianFilter:
		ImageTransformer::medianFilter(curImg);
		break;
	case Transformation::GausseFilter:
		ImageTransformer::gausseFilter(curImg);
		break;
	case Transformation::SharpnessFilter:
		ImageTransformer::sharpnessFilter(curImg);
		break;
	case Transformation::LaplasFilter:
		ImageTransformer::laplasFilter(curImg);
		break;
	case Transformation::SobelFilter:
		ImageTransformer::sobelFilter(curImg);
		break;
	case Transformation::Fourier:
		ImageTransformer::fourierTransform(curImg, true);
		break;
	default:
		break;
	}

	transformedImage->repaint();
	makeHistograms();
}

void Laba_3::makeHistograms()
{
	memset(redData, 0, sizeof(uint) * 256);
	memset(greenData, 0, sizeof(uint) * 256);
	memset(blueData, 0, sizeof(uint) * 256);
	memset(brightnessData, 0, sizeof(uint) * 256);

	uchar* px = transformedImage->getImage().bits();

	int h = transformedImage->getImage().height();
	int w = transformedImage->getImage().width();

	int pixelsQuo = h * w;

	int r, g, b;
	int lightness = 0;
	for (int i = 0; i < pixelsQuo; i++)
	{
		r = *px;
		g = *++px;
		b = *++px;
		px++;
		lightness = ImageTransformer::getBrightness(r, g, b);

		redData[r]++;
		blueData[b]++;
		greenData[g]++;
		brightnessData[lightness]++;
	}

	redHistogram->setData(redData);
	greenHistogram->setData(greenData);
	blueHistogram->setData(blueData);
	brightnessHistogram->setData(brightnessData);
}

void Laba_3::addHistograms()
{
	redHistogram = new HistogramWidget(this);
	greenHistogram = new HistogramWidget(this);
	blueHistogram = new HistogramWidget(this);
	brightnessHistogram = new HistogramWidget(this);

	ui.verticalLayout_6->addWidget(new QLabel("Histograms:", this));
	ui.verticalLayout_6->addWidget(new QLabel("Red:", this));
	ui.verticalLayout_6->addWidget(redHistogram);
	ui.verticalLayout_6->addWidget(new QLabel("Green:", this));
	ui.verticalLayout_6->addWidget(greenHistogram);
	ui.verticalLayout_6->addWidget(new QLabel("Blue:", this));
	ui.verticalLayout_6->addWidget(blueHistogram);
	ui.verticalLayout_6->addWidget(new QLabel("Brightness:", this));
	ui.verticalLayout_6->addWidget(brightnessHistogram);

}

void Laba_3::tryChangeTransformation(Transformation transformation)
{
	if (curTransform != transformation)
	{
		curTransform = transformation;
		setLabelAndSliders();
		applyTransformation();
	}
}

void Laba_3::init()
{
	ui.centralWidget->setLayout(ui.verticalLayout);
	originalImage = new ImageWidget(this);
	ui.verticalLayout_2->addWidget(originalImage);

	transformedImage = new ImageWidget(this);
	ui.verticalLayout_4->addWidget(transformedImage);

	addHistograms();

	setConnections();
}

void Laba_3::setConnections()
{
	connect(ui.actionLoad_image, &QAction::triggered, this, &Laba_3::loadNewImage);
	connect(ui.actionInfo_2, &QAction::triggered, this, &Laba_3::showAuthor);
	connect(ui.actionInfo, &QAction::triggered, this, &Laba_3::showAbout);


	connect(ui.actionColor_inversion, &QAction::triggered, this, &Laba_3::selectColorInversion);
	connect(ui.actionTo_Black_and_White, &QAction::triggered, this, &Laba_3::selectToBlackAndWhite);
	connect(ui.actionThreshold, &QAction::triggered, this, &Laba_3::selectThresholdColors);
	connect(ui.actionLogarithm, &QAction::triggered, this, &Laba_3::selectLogBrightness);
	connect(ui.actionDegree, &QAction::triggered, this, &Laba_3::selectDegreeBrightness);
	connect(ui.actionLine, &QAction::triggered, this, &Laba_3::selectLineBrightness);
	connect(ui.actionEqualization, &QAction::triggered, this, &Laba_3::selectEqualizeHistogram);
	connect(ui.actionNormal, &QAction::triggered, this, &Laba_3::selectNormalHistogram);
	connect(ui.actionBrightnessThreshold, &QAction::triggered, this, &Laba_3::selectThresholdBrightness);

	connect(ui.actionBox, &QAction::triggered, this, &Laba_3::selectBoxFilter);
	connect(ui.actionMedian, &QAction::triggered, this, &Laba_3::selectMedianFilter);
	connect(ui.actionGausse, &QAction::triggered, this, &Laba_3::selectGausseFilter);
	connect(ui.actionSharpness, &QAction::triggered, this, &Laba_3::selectSharpnessFilter);
	connect(ui.actionLaplas, &QAction::triggered, this, &Laba_3::selectLaplasFilter);
	connect(ui.actionSobel, &QAction::triggered, this, &Laba_3::selectSobelFilter);
	connect(ui.actionFourier, &QAction::triggered, this, &Laba_3::selectFourier);

	connect(ui.firstHSlider, &QSlider::valueChanged, this, &Laba_3::changeFirstSliderValue);
	connect(ui.secondHSlider, &QSlider::valueChanged, this, &Laba_3::changeSecondSliderValue);
	connect(ui.thirdHSlider, &QSlider::valueChanged, this, &Laba_3::changeThirdSliderValue);
	connect(ui.fourthHSlider, &QSlider::valueChanged, this, &Laba_3::changeFourthSliderValue);
	connect(ui.fifthHSlider, &QSlider::valueChanged, this, &Laba_3::changeFifthSliderValue);
	connect(ui.sixthHSlider, &QSlider::valueChanged, this, &Laba_3::changeSixthSliderValue);

}

void Laba_3::setLabelAndSliders()
{
	switch (curTransform)
	{
	case Transformation::None: 	case Transformation::Inversion: case Transformation::ToBlackAndWhite:
	case Transformation::LogBrightness: 	case Transformation::DegreeBrightness: 	case Transformation::LineBrightness:
	case Transformation::Equalize: case Transformation::BoxFilter: case Transformation::MedianFilter: case Transformation::GausseFilter: 
	case Transformation::SharpnessFilter: case Transformation::SobelFilter: case Transformation::Fourier: case Transformation::LaplasFilter:

		ui.firstHSlider->setEnabled(false);
		ui.firstLabel->setText("");
		ui.secondHSlider->setEnabled(false);
		ui.secondLabel->setText("");
		ui.thirdHSlider->setEnabled(false);
		ui.thirdLabel->setText("");
		ui.fourthHSlider->setEnabled(false);
		ui.fourthLabel->setText("");
		ui.fifthHSlider->setEnabled(false);
		ui.fifthLabel->setText("");
		ui.sixthHSlider->setEnabled(false);
		ui.sixthLabel->setText("");
		break;

	case Transformation::ThresholdColors:
		ui.firstHSlider->setEnabled(true);
		ui.firstLabel->setText("Bottom R");
		ui.firstHSlider->setMaximum(255);
		ui.firstHSlider->setValue(0);
		ui.secondHSlider->setEnabled(true);
		ui.secondHSlider->setMaximum(255);
		ui.secondHSlider->setValue(255);
		ui.secondLabel->setText("Top R");
		ui.thirdHSlider->setEnabled(true);
		ui.thirdHSlider->setMaximum(255);
		ui.thirdHSlider->setValue(0);
		ui.thirdLabel->setText("Bottom G");
		ui.fourthHSlider->setEnabled(true);
		ui.fourthHSlider->setMaximum(255);
		ui.fourthHSlider->setValue(255);
		ui.fourthLabel->setText("Top G");
		ui.fifthHSlider->setEnabled(true);
		ui.fifthHSlider->setMaximum(255);
		ui.fifthHSlider->setValue(0);
		ui.fifthLabel->setText("Bottom B");
		ui.sixthHSlider->setEnabled(true);
		ui.sixthHSlider->setMaximum(255);
		ui.sixthHSlider->setValue(255);
		ui.sixthLabel->setText("Top B");
		break;
	case Transformation::ThresholdBrightness:
		ui.firstHSlider->setEnabled(true);
		ui.firstHSlider->setMaximum(255);
		ui.firstHSlider->setValue(254);
		ui.firstLabel->setText("Top brightness");
		ui.secondHSlider->setEnabled(true);
		ui.firstHSlider->setMaximum(255);
		ui.secondLabel->setText("Bottom brightness");
		ui.thirdHSlider->setEnabled(false);
		ui.thirdLabel->setText("");
		ui.fourthHSlider->setEnabled(false);
		ui.fourthLabel->setText("");
		ui.fifthHSlider->setEnabled(false);
		ui.fifthLabel->setText("");
		ui.sixthHSlider->setEnabled(false);
		ui.sixthLabel->setText("");
		break;

	case Transformation::Normal:
		ui.firstHSlider->setEnabled(true);
		ui.firstHSlider->setMaximum(255);
		ui.firstHSlider->setValue(125);
		ui.firstLabel->setText("Expected value");
		ui.secondHSlider->setEnabled(true);
		ui.secondHSlider->setMaximum(100);
		ui.secondHSlider->setValue(0);
		ui.secondLabel->setText("Dispersion");
		ui.thirdHSlider->setEnabled(false);
		ui.thirdLabel->setText("");
		ui.fourthHSlider->setEnabled(false);
		ui.fourthLabel->setText("");
		ui.fifthHSlider->setEnabled(false);
		ui.fifthLabel->setText("");
		ui.sixthHSlider->setEnabled(false);
		ui.sixthLabel->setText("");
		break;
	default:
		break;
	}
}
