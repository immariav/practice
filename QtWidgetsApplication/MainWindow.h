#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "WiFiFrame.h"
#include <QFileDialog>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::pair<std::vector<WiFiFrame>, uint32_t> inputData;
    std::vector<WiFiFrame> drone_frames;

public slots:
    void setLogButtonClicked();
    void startButtonClicked();
    void saveToFIleButtonClicked();

private:
    Ui::MainWindowClass ui;
};
