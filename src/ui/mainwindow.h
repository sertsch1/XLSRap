#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <qfiledialog.h>
#include <qstring.h>
#include <qdir.h>
#include <xlsrap\XLSRap.hpp>
#include <string>

#include <XLSModel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
	xlsrap::XLSRap XLSRap;

	QString FileName;



public slots:
	void SetFileName();

private:
    Ui::MainWindow *ui;

	std::string QStringToStdString(QString StringToConvert);
};

#endif // MAINWINDOW_H
