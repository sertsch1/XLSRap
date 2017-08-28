#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

	Player = new QMediaPlayer(this);
	Playlist = new QMediaPlaylist();
	Player->setPlaylist(Playlist);

	connect(Player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
	connect(Player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
	connect(Player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
	connect(Playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
	connect(Player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
		this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
	connect(Player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
	connect(Player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
	connect(Player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));

	ActiveVideoWidget = new VideoWidget(this);
	Player->setVideoOutput(ActiveVideoWidget);
	
	slider = new QSlider(Qt::Horizontal, this);
	slider->setRange(0, Player->duration() / 1000);

	labelDuration = new QLabel(this);
	connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

	AudioProbe = new QAudioProbe(this);
	connect(AudioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
	AudioProbe->setSource(Player);
	
	VideoProbe = new QVideoProbe(this);
	connect(VideoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));
	VideoProbe->setSource(Player);

	connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(OpenSheet()));
	connect(ui->XlsTableModel, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetMediaFile(QModelIndex)));
	ui->PlayerLayout->addWidget(ActiveVideoWidget);

	ControlsWidget* Controls = new ControlsWidget(this);
	ui->ControlsLayout->addWidget(Controls);
	ui->SliderLayout->addWidget(slider);
	ui->gridLayout->addWidget(labelDuration);
	Controls->setState(Player->state());
	Controls->setVolume(Player->volume());
	Controls->setMuted(Controls->isMuted());

	connect(Controls, SIGNAL(play()), Player, SLOT(play()));
	connect(Controls, SIGNAL(pause()), Player, SLOT(pause()));
	connect(Controls, SIGNAL(stop()), Player, SLOT(stop()));
	connect(Controls, SIGNAL(next()), Playlist, SLOT(next()));
	connect(Controls, SIGNAL(previous()), this, SLOT(previousClicked()));
	connect(Controls, SIGNAL(changeVolume(int)), Player, SLOT(setVolume(int)));
	connect(Controls, SIGNAL(changeMuting(bool)), Player, SLOT(setMuted(bool)));
	connect(Controls, SIGNAL(changeRate(qreal)), Player, SLOT(setPlaybackRate(qreal)));

	connect(Controls, SIGNAL(stop()), ActiveVideoWidget, SLOT(update()));

	connect(Player, SIGNAL(stateChanged(QMediaPlayer::State)),
		Controls, SLOT(setState(QMediaPlayer::State)));
	connect(Player, SIGNAL(volumeChanged(int)), Controls, SLOT(setVolume(int)));
	connect(Player, SIGNAL(mutedChanged(bool)), Controls, SLOT(setMuted(bool)));

	if (!Player->isAvailable())
		QMessageBox::warning(this, tr("Service not available"),
			tr("The QMediaPlayer object does not have a valid service.\n"\
				"Please check if the media service plugins are installed."));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadSheet()
{
	ui->StatusLabel->setText(FileName);
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

void MainWindow::GetMediaFile(const QModelIndex& index)
{
	ui->StatusLabel->setText(QString("Loading Media File..."));
	qApp->processEvents();

	QUrl Path = QUrl(QString(QDir::currentPath() + "/" + (ui->XlsTableModel->model()->data(index).toString())));

	if (!Playlist->isEmpty()) {
		QMediaContent CurrentMedia = Playlist->currentMedia();
		QMediaContent NewMedia = QMediaContent(Path);
		if (CurrentMedia == NewMedia) {
			Player->play();
			ui->StatusLabel->setText(QString("Same File."));
			qApp->processEvents();
			return;
		} else {
			Playlist->clear();
		}		
	}
	if (Playlist->addMedia(Path)) {
		ui->StatusLabel->setText(QString("File Loaded."));
		Player->play();
		qApp->processEvents();
		return;
	} else {
		Playlist->clear();
		ui->StatusLabel->setText(QString("Failed!"));
		qApp->processEvents();
	}

}

void MainWindow::Next()
{
}

void MainWindow::Previous()
{
}

std::string MainWindow::QStringToStdString(QString StringToConvert)
{
	return StringToConvert.toUtf8().constData();
}

void MainWindow::OpenSheet() {
	FileName = QFileDialog::getOpenFileName(this, tr("Select Spreadsheet"), QDir::currentPath(), tr("XLS Files (*.xls *.xlsx);;All Files (*.*)"));
	if (FileName != nullptr)
		LoadSheet();
}

void MainWindow::durationChanged(qint64 duration)
{
	this->duration = duration / 1000;
	slider->setMaximum(duration / 1000);
}

void MainWindow::positionChanged(qint64 progress)
{
	if (!slider->isSliderDown()) {
		slider->setValue(progress / 1000);
	}
	updateDurationInfo(progress / 1000);
}

void MainWindow::metaDataChanged()
{
	if (Player->isMetaDataAvailable()) {
		setTrackInfo(QString("%1 - %2")
			.arg(Player->metaData(QMediaMetaData::AlbumArtist).toString())
			.arg(Player->metaData(QMediaMetaData::Title).toString()));

		if (coverLabel) {
			QUrl url = Player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

			coverLabel->setPixmap(!url.isEmpty()
				? QPixmap(url.toString())
				: QPixmap());
		}
	}
}

void MainWindow::previousClicked()
{
	//GetMediaFile();
}

void MainWindow::jump(const QModelIndex &index)
{
	if (index.isValid()) {
		Playlist->setCurrentIndex(index.row());
		Player->play();
	}
}

void MainWindow::seek(int seconds)
{
	Player->setPosition(seconds * 1000);
}

void MainWindow::statusChanged(QMediaPlayer::MediaStatus status)
{
	handleCursor(status);

	// handle status message
	switch (status) {
	case QMediaPlayer::UnknownMediaStatus:
	case QMediaPlayer::NoMedia:
	case QMediaPlayer::LoadedMedia:
	case QMediaPlayer::BufferingMedia:
	case QMediaPlayer::BufferedMedia:
		setStatusInfo(QString());
		break;
	case QMediaPlayer::LoadingMedia:
		setStatusInfo(tr("Loading..."));
		break;
	case QMediaPlayer::StalledMedia:
		setStatusInfo(tr("Media Stalled"));
		break;
	case QMediaPlayer::EndOfMedia:
		QApplication::alert(this);
		break;
	case QMediaPlayer::InvalidMedia:
		displayErrorMessage();
		break;
	}
}


void MainWindow::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
	if (status == QMediaPlayer::LoadingMedia ||
		status == QMediaPlayer::BufferingMedia ||
		status == QMediaPlayer::StalledMedia)
		setCursor(QCursor(Qt::BusyCursor));
	else
		unsetCursor();
#endif
}

void MainWindow::bufferingProgress(int progress)
{
	setStatusInfo(tr("Buffering %4%").arg(progress));
}

void MainWindow::videoAvailableChanged(bool available)
{
	/*
	if (!available) {
		disconnect(fullScreenButton, SIGNAL(clicked(bool)),
			ActiveVideoWidget, SLOT(setFullScreen(bool)));
		disconnect(ActiveVideoWidget, SIGNAL(fullScreenChanged(bool)),
			fullScreenButton, SLOT(setChecked(bool)));
		ActiveVideoWidget->setFullScreen(false);
	}
	else {
		connect(fullScreenButton, SIGNAL(clicked(bool)),
			ActiveVideoWidget, SLOT(setFullScreen(bool)));
		connect(ActiveVideoWidget, SIGNAL(fullScreenChanged(bool)),
			fullScreenButton, SLOT(setChecked(bool)));

		if (fullScreenButton->isChecked())
			ActiveVideoWidget->setFullScreen(true);
	}
	*/
	//colorButton->setEnabled(available);
}

void MainWindow::setTrackInfo(const QString &info)
{
	trackInfo = info;
	if (!statusInfo.isEmpty())
		setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
	else
		setWindowTitle(trackInfo);
}

void MainWindow::setStatusInfo(const QString &info)
{
	statusInfo = info;
	if (!statusInfo.isEmpty())
		setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
	else
		setWindowTitle(trackInfo);
}

void MainWindow::displayErrorMessage()
{
	setStatusInfo(Player->errorString());
}

void MainWindow::updateDurationInfo(qint64 currentInfo)
{
	QString tStr;
	if (currentInfo || duration) {
		QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60, currentInfo % 60, (currentInfo * 1000) % 1000);
		QTime totalTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
		QString format = "mm:ss";
		if (duration > 3600)
			format = "hh:mm:ss";
		tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
	}
	labelDuration->setText(tStr);
}
