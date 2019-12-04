#include "./oventimer/oventimer.h"

#include "./app/application.h"

int main(int argc, char *argv[])
{
	ot::Application a(argc, argv);
	ot::OvenTimer w;
	w.show();
	return a.exec();
}
