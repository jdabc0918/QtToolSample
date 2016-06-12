#include "common.h"
#include "ggtool.h"
#include "tttool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ggTool w;
	w.show();

	ttTool t;
	t.show();

	return a.exec();
}
