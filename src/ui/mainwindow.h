#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <qfiledialog.h>
#include <qstring.h>
#include <qdir.h>
#include <string>
#include <qvideoprobe.h>
#include <qaudioprobe.h>
#include <QtMultimedia\qmediaplayer.h>
#include <QtMultimedia\qmediaplayercontrol.h>
#include <QtMultimedia\qmediaplaylist.h>
#include <qmessagebox.h>
#include "qtimer.h"
#include "qdatetime.h"
#include "qmediametadata.h"

#include <XLSModel.h>
#include "VideoWidget.h"
#include "ControlsWidget.h"
#include <xlsrap\XLSRap.hpp>


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

	void LoadSheet();

public slots:
	void OpenSheet();

	void GetMediaFile(const QModelIndex& index);

	void Next();

	void Previous();

private slots:
//	void open();
	void durationChanged(qint64 duration);
	void positionChanged(qint64 progress);
	void metaDataChanged();

	void previousClicked();

	void seek(int seconds);
	void jump(const QModelIndex &index);

	void statusChanged(QMediaPlayer::MediaStatus status);
	void bufferingProgress(int progress);
	void videoAvailableChanged(bool available);
	void displayErrorMessage();



private:
    Ui::MainWindow *ui;

	void setTrackInfo(const QString &info);
	void setStatusInfo(const QString &info);
	void handleCursor(QMediaPlayer::MediaStatus status);
	void updateDurationInfo(qint64 currentInfo);

	QMediaPlayer* Player;
	VideoWidget* ActiveVideoWidget;
	QMediaPlaylist* Playlist;
	
	QAudioProbe* AudioProbe;
	QVideoProbe* VideoProbe;

	QPushButton *fullScreenButton;
	QLabel *coverLabel;
	QSlider *slider;
	QLabel *labelDuration;
	QString trackInfo;
	QString statusInfo;
	qint64 duration;

	std::string QStringToStdString(QString StringToConvert);
};

#endif // MAINWINDOW_H
