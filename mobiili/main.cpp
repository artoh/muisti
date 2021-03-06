/**************************************************************************
Muisti Notes Manager

(c) Arto Hyvättinen 2013

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


**************************************************************************/



#include <QApplication>
#include "muistihakuikkuna.h"

/**
 * @brief Muisti Haku -mobiiliohjelman pääfunktio
 *
 *
 * Mobiilikäyttöön tarkoitettu ohjelma, jolla haetaan muistiinpanoja
 * paikallisesta xml-tiedostosta
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Muisti");
    a.setOrganizationName("Muisti");

    MuistiHakuIkkuna ikkuna;
    ikkuna.show();

    return a.exec();
}
