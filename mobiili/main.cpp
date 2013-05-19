
#include <QApplication>
#include "muistihakuikkuna.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Muisti");
    a.setOrganizationName("Muisti");

    MuistiHakuIkkuna ikkuna;
    ikkuna.show();

    return a.exec();
}
