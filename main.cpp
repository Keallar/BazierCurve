#include <QApplication>

#include "baziercurve.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BazierCurve wdg_bazCurve;
    wdg_bazCurve.setWindowTitle("Bazier Curve");
    wdg_bazCurve.show();

    return app.exec();
}
