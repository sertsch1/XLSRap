#pragma once
#ifndef CONTROLSWIDGET_H
#define CONTROLSWIDGET_H



#include "QtMultimedia\qmediaplayer.h"
#include "qwidget.h"
#include "qabstractbutton.h"
#include "qabstractslider.h"
#include "qcombobox.h"
#include "qboxlayout.h"
#include "qslider.h"
#include "qstyle.h"
#include "qtoolbutton.h"
#include "qcombobox.h"
#include "qaudio.h"

class ControlsWidget : public QWidget
{
	Q_OBJECT
public:
	ControlsWidget(QWidget* Parent);

	QMediaPlayer::State state() const;
	int volume() const;
	bool isMuted() const;
	qreal playbackRate() const;


	public slots:
	void setState(QMediaPlayer::State state);
	void setVolume(int volume);
	void setMuted(bool muted);
	void setPlaybackRate(float rate);

signals:
	void play();
	void pause();
	void stop();
	void next();
	void previous();
	void changeVolume(int volume);
	void changeMuting(bool muting);
	void changeRate(qreal rate);

	private slots:
	void playClicked();
	void muteClicked();
	void updateRate();
	void onVolumeSliderValueChanged();

private:
	QMediaPlayer::State playerState;
	bool playerMuted;
	QAbstractButton *playButton;
	QAbstractButton *stopButton;
	QAbstractButton *nextButton;
	QAbstractButton *previousButton;
	QAbstractButton *muteButton;
	QAbstractSlider *volumeSlider;
	QComboBox *rateBox;
};

#endif // !CONTROLSWIDGET_H