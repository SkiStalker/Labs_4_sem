#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_Laba_3.h"
#include "ImageWidget.h"
#include "HistogramWidget.h"
#include "ImageTransformer.h"

class Laba_3 : public QMainWindow
{
    Q_OBJECT

public:
    Laba_3(QWidget *parent = Q_NULLPTR);

public slots:
    void loadNewImage();
    void showAuthor();
    void showAbout();
    void selectColorInversion();
    void selectToBlackAndWhite();
    void selectThresholdColors();
    void selectThresholdBrightness();
    void selectLogBrightness();
    void selectDegreeBrightness();
    void selectLineBrightness();
    void selectEqualizeHistogram();
    void selectNormalHistogram();

    void changeFirstSliderValue();
    void changeSecondSliderValue();
    void changeThirdSliderValue();
    void changeFourthSliderValue();
    void changeFifthSliderValue();
    void changeSixthSliderValue();

private:
    using Transformation = ImageTransformer::Transformation;

    uint redData[256];
    uint greenData[256];
    uint blueData[256];
    uint brightnessData[256];

    Transformation curTransform = Transformation::None;
    Ui::Laba_2Class ui;
    HistogramWidget* redHistogram = nullptr;
    HistogramWidget* greenHistogram = nullptr;
    HistogramWidget* blueHistogram = nullptr;
    HistogramWidget* brightnessHistogram = nullptr;

    ImageWidget* originalImage = nullptr;
    ImageWidget* transformedImage = nullptr;


    void loadImage(const QString& path);

    void applyTransformation();
    void tryChangeTransformation(Transformation transformation);


    void makeHistograms();
    void addHistograms();

    void init();
    void setConnections();
    void setLabelAndSliders();
};
