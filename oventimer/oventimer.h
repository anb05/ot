#ifndef OVEN_TIMER_H
#define OVEN_TIMER_H

#include <QWidget>
#include <QDateTime>

class QTimer;

namespace ot {

class OvenTimer : public QWidget
{
	Q_OBJECT

public:
	explicit OvenTimer(QWidget *parent = nullptr);
	~OvenTimer() override;

public:
	explicit OvenTimer(const OvenTimer& )    = delete;
	explicit OvenTimer(OvenTimer&& )         = delete;

public:
	OvenTimer& operator= (const OvenTimer& ) = delete;
	OvenTimer& operator= (OvenTimer&& )      = delete;

public:
	void setDuration(int secs);
	int  duration() const;
	void draw(QPainter* painter);

signals:
	void timeout();

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	QDateTime _finishTime;
	QTimer*   _pUpdateTimer;
	QTimer*   _pFinishTimer;
};

} // namespace ot

#endif // OVEN_TIMER_H
