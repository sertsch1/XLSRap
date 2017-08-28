#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

	connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(SetFileName()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::QStringToStdString(QString StringToConvert)
{
	return StringToConvert.toUtf8().constData();
}


void MainWindow::SetFileName() {
	FileName = QFileDialog::getOpenFileName(this, tr("Select Spreadsheet"), QDir::currentPath(), tr("XLS Files (*.xls *.xlsx);;All Files (*.*)"));
	if (FileName != nullptr) {
		//Load Table and Sheet
		ui->StatusLabel->setText(QString("Loading File..."));
		qApp->processEvents();
		XLSRap.LoadTable(QStringToStdString(FileName));
		XLSRap.LoadSheet();
		//Initalize Model and update the table
		
		XLSModel* CurrentModel = new XLSModel(0, XLSRap.Sheet);
		ui->XlsTableModel->setModel(CurrentModel);
		ui->XlsTableModel->setSortingEnabled(true);
		ui->XlsTableModel->resizeColumnsToContents();
		ui->StatusLabel->setTextFormat(Qt::TextFormat::PlainText);
		ui->StatusLabel->setText(QString("Finished Loading File."));
		ui->StatusLabel->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
		qApp->processEvents();


	}
}