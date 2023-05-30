#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::setLogButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Input File", QString(), "All Files (*.*)");
    if (!fileName.isEmpty()) 
	{

       ui.label_allFrames->setText("Processing data...");
       inputData = WiFiFrame::parse(fileName.toStdString());
       if (inputData.second == 0)
        {
            ui.label_allFrames->setText(QString::number(inputData.first.size()));
            ui.statusBar->showMessage("The data was successfully read. Click next button to start processing.");
        }
       else if (inputData.second == -1)
       {
           ui.label_allFrames->setText("Error");
           ui.statusBar->showMessage("Error: Failed to open input file.");
       }
       else
       {
           ui.label_allFrames->setText("Error");
           ui.statusBar->showMessage("Error: Failed to parse input data. Error line: " + QString::number(inputData.second));
       }
    }
}

void MainWindow::startButtonClicked()
{
	if (!inputData.first.empty())
	{
		ui.label_checkSum->setText("Processing data...");
		ui.label_dataFrames->setText("Processing data...");
		ui.label_MAC->setText("Processing data...");
		ui.label_SSID->setText("Processing data...");
		
		std::string droneSSID; std::string droneMAC;

		std::vector<WiFiFrame> frames_sorted;

		std::vector<WiFiFrame> data_frames; // a vector to hold data frames for the last task

		for (size_t i = 0; i < inputData.first.size(); i++)
		{
			if (WiFiFrame::checkCRC32(inputData.first[i].bits, inputData.first[i].size))
				frames_sorted.push_back(inputData.first[i]);
		}

		inputData.first.clear();
		inputData.first.shrink_to_fit();
		ui.label_checkSum->setText(QString::number(frames_sorted.size()));

		for (size_t i = 0; i < frames_sorted.size(); i++)
		{
			if (frames_sorted[i].getType() == 0)
			{
				if (frames_sorted[i].isBeacon())
				{
					std::string SSID = frames_sorted[i].getBeaconSSID();
					if (WiFiFrame::compareSSID(SSID))
					{
						droneSSID = SSID;
						droneMAC = frames_sorted[i].getSA();
					}
				}
			}
			if (frames_sorted[i].getType() == 2)
				data_frames.push_back(frames_sorted[i]);
		}

		ui.label_SSID->setText(QString::fromStdString(droneSSID));
		ui.label_MAC->setText(QString::fromStdString(droneMAC));

		frames_sorted.clear();
		frames_sorted.shrink_to_fit();

		for (size_t i = 0; i < data_frames.size(); i++)
		{
			if (droneMAC == data_frames[i].getSA())
					drone_frames.push_back(data_frames[i]);
					
		}

		data_frames.clear();
		data_frames.shrink_to_fit();
		ui.label_dataFrames->setText(QString::number(drone_frames.size()));
		ui.statusBar->showMessage("The data was successfully processed. Click next button if you want to save it to file.");
	}

	else
	{
		ui.statusBar->showMessage("Select input data first!");
	}
	
}

void MainWindow::saveToFIleButtonClicked()
{
	if (!drone_frames.empty())
	{
		QString fileName = QFileDialog::getOpenFileName(this, "Select Input File", QString(), "All Files (*.*)");
		if (!fileName.isEmpty()) 
		{
			WiFiFrame::writeToFile(drone_frames, fileName.toStdString());
			ui.statusBar->showMessage("Data has been successfully written to " + fileName);
		}
	}
	else
	{
		ui.statusBar->showMessage("Process data first!");
	}

}

