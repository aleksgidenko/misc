/*
** A simple Qt Window using QWidget
*/

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
	// create application object
	QApplication app(argc, argv);

	// create window
	// (any QWidget that has no parent will become a window)
	QWidget win;
	win.resize(640, 480);
	win.setWindowTitle("Simple Window");
	win.show();

	// enter application mainloop and return exit status
	return app.exec();
}

