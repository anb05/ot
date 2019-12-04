#include "./oventimer/oventimer.h"

#include "./app/application.h"

int main(int argc, char *argv[])
{
	ot::Application a(argc, argv);
	ot::OvenTimer w;

	w.resize(200,200);
	w.setWindowTitle(QObject::tr("Oven Timer"));

	w.show();
	return a.exec();
}
