#include "oventimer.h"

#include <cmath>

#include <QFont>
#include <QTimer>
#include <QPointF>
#include <QPainter>
#include <QMouseEvent>

namespace ot {

static constexpr double DEGREES_PER_MINUTE = 7.0;
static constexpr double DEGREES_PER_SECOND = DEGREES_PER_MINUTE / 60;
static constexpr int    MAX_MINUTES = 45;
static constexpr int    MAX_SECONDS = MAX_MINUTES * 60;
static constexpr int    UPDATE_INTERVAL = 5;

constexpr double deg() {return M_PI / 180.0;}
constexpr double rad() {return 1 / deg();}

OvenTimer::OvenTimer(QWidget *parent)
	: QWidget(parent)
{
	_finishTime = QDateTime::currentDateTime();
	{
		_pUpdateTimer = new QTimer(this);
		connect(_pUpdateTimer, SIGNAL(timeout()),
				this,        SLOT(update()));
	}
	{
		_pFinishTimer = new QTimer(this);
		_pFinishTimer->setSingleShot(true);
		connect(_pFinishTimer, &QTimer::timeout,
				this,          &OvenTimer::timeout);
		connect(_pFinishTimer, &QTimer::timeout,
				_pUpdateTimer, &QTimer::stop);
	}

	QFont font;
	font.setPointSize(8);
	setFont(font);
}

void OvenTimer::setDuration(int secs)
{
	secs = qBound(0, secs, MAX_SECONDS);

    _finishTime = QDateTime::currentDateTime().addSecs(secs);

	if (0 < secs) {
		_pUpdateTimer->start(UPDATE_INTERVAL * 1000);
		_pFinishTimer->start(secs * 1000);
	}
	else {
		_pUpdateTimer->stop();
		_pFinishTimer->stop();
	}
	update();
}

int OvenTimer::duration() const
{
	int secs = int(QDateTime::currentDateTime().secsTo(_finishTime));

	if (secs < 0) {
		return 0;
	}
	return secs;
}

void OvenTimer::mousePressEvent(QMouseEvent* event)
{
	QPointF point = event->pos() - rect().center();
	double  theta = atan2(point.x(), point.y()) * rad();
	setDuration(duration() + int(theta / DEGREES_PER_SECOND));
	update();
}

void OvenTimer::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	int side = qMin(width(), height());
	painter.setViewport((width() - side)/2, (height() - side)/2, side, side);
	painter.setWindow(-50,-50,100,100);
	draw(&painter);
}

void OvenTimer::draw(QPainter* painter)
{
	static const int triangle[3][2] = {
		 { -2, -49 }, { +2, -49 }, { 0, -47 }
	 };
	 QPen thickPen(palette().windowText(), 1.5);
	 QPen thinPen(palette().windowText(), 0.5);
	 QColor niceBlue(150, 150, 200);

	 painter->setPen(thinPen);
	 painter->setBrush(palette().windowText());
	 painter->drawPolygon(QPolygon(3, &triangle[0][0]));

	 QConicalGradient coneGradient(0, 0, -90.0);
	 coneGradient.setColorAt(0.0, Qt::darkGray);
	 coneGradient.setColorAt(0.2, niceBlue);
	 coneGradient.setColorAt(0.5, Qt::white);
	 coneGradient.setColorAt(1.0, Qt::darkGray);

	 painter->setBrush(coneGradient);
	 painter->drawEllipse(-46, -46, 92, 92);

	 QRadialGradient haloGradient(0, 0, 20, 0, 0);
	 haloGradient.setColorAt(0.0, Qt::lightGray);
	 haloGradient.setColorAt(0.8, Qt::darkGray);
	 haloGradient.setColorAt(0.9, Qt::white);
	 haloGradient.setColorAt(1.0, Qt::black);

	 painter->setPen(Qt::NoPen);
	 painter->setBrush(haloGradient);
	 painter->drawEllipse(-20, -20, 40, 40);

	 QLinearGradient knobGradient(-7, -25, 7, -25);
	 knobGradient.setColorAt(0.0, Qt::black);
	 knobGradient.setColorAt(0.2, niceBlue);
	 knobGradient.setColorAt(0.3, Qt::lightGray);
	 knobGradient.setColorAt(0.8, Qt::white);
	 knobGradient.setColorAt(1.0, Qt::black);

	 painter->rotate(duration() * DEGREES_PER_SECOND);
	 painter->setBrush(knobGradient);
	 painter->setPen(thinPen);
	 painter->drawRoundedRect(-7, -25, 14, 50, 99, 49);

	 for (int i = 0; i <= MAX_MINUTES; ++i) {
		 if (i % 5 == 0) {
			 painter->setPen(thickPen);
			 painter->drawLine(0, -41, 0, -44);
			 painter->drawText(-15, -41, 30, 30,
							   Qt::AlignHCenter | Qt::AlignTop,
							   QString::number(i));
		 } else {
			 painter->setPen(thinPen);
			 painter->drawLine(0, -42, 0, -44);
		 }
		 painter->rotate(-DEGREES_PER_MINUTE);
	 }
}

OvenTimer::~OvenTimer() = default;

} // namespace ot
