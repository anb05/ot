#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

namespace ot {

class Application : public QApplication
{
public:
	explicit Application(int& argc, char** argv);
	~Application();

public:
	explicit Application(const Application& )    = delete;
	explicit Application(Application&& )         = delete;

public:
	Application& operator= (const Application& ) = delete;
	Application& operator= (Application&& )      = delete;
};

} // namespace ot

#endif // APPLICATION_H
