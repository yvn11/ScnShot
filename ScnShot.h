#include <QWidget>
#include <QPixmap>
#include <QList>

#define MAX_UNDO 3

class ScnShot : public QWidget
{
	Q_OBJECT
private:
	QList<QPixmap> *imgList;
	QPoint pStart, pEnd, pCur;
	QPixmap *imgCur;
	QPainter *pen;

public:
	ScnShot(QWidget *parent = 0);
	void startShot();
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void showImage(QPixmap &image);
	void prePaint();
	void postPaint();

//public slots:
//	void onMouseClickedEvent();
};

