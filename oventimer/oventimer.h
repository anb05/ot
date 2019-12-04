#ifndef OVEN_TIMER_H
#define OVEN_TIMER_H

#include <QWidget>

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
};

} // namespace ot

#endif // OVEN_TIMER_H
