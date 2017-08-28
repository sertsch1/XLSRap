#pragma once
#include <QtMultimedia\qmediaplayer.h>
#include <QtGui\qmovie.h>
#include <QtWidgets\qwidget.h>
#include "QtMultimedia\qvideosurfaceformat.h"
#include "QtMultimediaWidgets\qvideowidget.h"

class VideoWidget : public QVideoWidget
{
Q_OBJECT

public:
	VideoWidget(QWidget* Parent = nullptr);

private:
	void keyPressEvent(QKeyEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
};

