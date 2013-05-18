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

#ifndef MUISTIXMLMODEL_H
#define MUISTIXMLMODEL_H

#include "../model/muistinodemodel.h"

class QXmlStreamReader;
class QXmlStreamWriter;

/**
 * @brief XML-tiedostoon tallennus ja lataus MuistiModelissa
 *
 */
class MuistiXmlModel : public MuistiNodeModel
{
    Q_OBJECT
public:
    explicit MuistiXmlModel(QObject *parent = 0);

    bool lataaTiedosto(const QString &tiedostonnimi);
    bool tallennaTiedostoon(const QString &tiedostonnimi);
    
signals:
    

    
protected:
    MuistiNoodi *lueXml(QXmlStreamReader *reader);

    static MuistiNoodi *lueNoodi(QXmlStreamReader *lukija, const QString &nimi);
    static QString lueNimi(QXmlStreamReader *lukija);

    void kirjoitaNoodi(QXmlStreamWriter* kirjoittaja, MuistiNoodi* noodi);


};

#endif // MUISTIXMLMODEL_H
