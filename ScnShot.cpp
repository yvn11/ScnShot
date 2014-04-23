#include "ScnShot.h"
#include <QtGlobal>
#include <QPainter>
#include <QMouseEvent>
#include <QtGui/QDesktopWidget>
#include <QApplication>
#include <QDebug>

ScnShot::ScnShot(QWidget *parent)
{
	Q_UNUSED(parent)

	setCursor(Qt::CrossCursor);
	setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
	setGeometry(QApplication::desktop()->availableGeometry());

	pStart = pCur = pEnd = QPoint(0, 0);
	imgList = new QList<QPixmap>;

	startShot();
	showImage(imgList->last());
}

void ScnShot::prePaint()
{
	pen = new QPainter(this);
	pen->setPen(Qt::red);
	pen->setRenderHint(QPainter::Antialiasing,true);
	pen->setRenderHint(QPainter::SmoothPixmapTransform,true);
	showImage(*imgCur);
}

void ScnShot::postPaint()
{
	delete pen;
}

void ScnShot::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		pStart = QCursor::pos();
		qDebug() << __PRETTY_FUNCTION__ << pStart;
	}
}

void ScnShot::mouseMoveEvent(QMouseEvent *event)
{
	Q_UNUSED(event)

	pCur = QCursor::pos();
	qDebug() << __PRETTY_FUNCTION__ << pStart << ' ' << pCur;

	repaint();
}

void ScnShot::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		pEnd = QCursor::pos();
		qDebug() << __PRETTY_FUNCTION__ << pEnd;

		startShot();
		showImage(imgList->last());
	}
}

void ScnShot::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	int x = pStart.x()>pCur.x() ? pCur.x() : pStart.x();
	int y = pStart.y()>pCur.y() ? pCur.y() : pStart.y();

	prePaint();
	pen->drawRect(x, y,
		qAbs(pCur.x()-pStart.x()),
		qAbs(pCur.y()-pStart.y())
	);
	postPaint();
}

void ScnShot::startShot()
{
	QPixmap newImage = QPixmap::grabWindow(QApplication::desktop()->winId());
	imgList->append(newImage);

	if (MAX_UNDO < imgList->size())
		imgList->removeFirst();
	 qDebug() << __PRETTY_FUNCTION__ << " imgList->size()" << imgList->size();
}

void ScnShot::showImage(QPixmap &image)
{
	qDebug() << __PRETTY_FUNCTION__;
	QPalette scn_buf;
	scn_buf.setBrush(backgroundRole(), QBrush(image));
	setPalette(scn_buf);
}


/* -------------self test--------------*/
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	ScnShot s;
	s.show();

	return app.exec();
}
