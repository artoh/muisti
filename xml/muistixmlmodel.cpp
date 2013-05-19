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

#include "muistixmlmodel.h"

#include "../model/muistinoodi.h"

#include <QFile>
#include <QXmlStreamReader>

MuistiXmlModel::MuistiXmlModel(QObject *parent) :
    MuistiNodeModel(parent)
{
}

MuistiNoodi *MuistiXmlModel::lueXml(QXmlStreamReader *reader)
{
    MuistiNoodi* luettuNoodi = 0;

    reader->readNext();
    while( !reader->atEnd())
    {
        if( reader->isStartElement())
        {
            if( reader->name() == "muisti")
            {
                // Luetaan juurielementti
                luettuNoodi = lueNoodi(reader, "muisti");
            }
            else
            {
                reader->raiseError(tr("Väärä xml-muoto"));
            }
        }
        else
        {
            reader->readNext();
        }
    }
    return luettuNoodi;
}

bool MuistiXmlModel::lataaTiedosto(const QString &tiedostonnimi)
{
    QFile tiedosto(tiedostonnimi);
    if( !tiedosto.open(QFile::ReadOnly | QFile::Text ))
    {
        // Virhe - tiedostoa ei saatu auki
        return false;
    }

    QXmlStreamReader reader;
    reader.setDevice(&tiedosto);

    MuistiNoodi *uusiJuuri = lueXml(&reader);

    tiedosto.close();
    if( reader.hasError() || tiedosto.error() != QFile::NoError )
        return false;

    // Lukeminen onnistui, asetetaan uudeksi modelin juureksi
    asetaJuuriNoodi(uusiJuuri);

    return true;
}

bool MuistiXmlModel::tallennaTiedostoon(const QString &tiedostonnimi)
{
    if( !juuriNoodi())
        return false;   // Ei juurta...

    QFile tiedosto(tiedostonnimi);
    if( !tiedosto.open(QFile::WriteOnly | QFile::Text ))
    {
        return false;
    }

    QXmlStreamWriter xmlWriter(&tiedosto);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    // kirjoitaNoodi kirjoittaa noodin ja kaikki lapset, joten
    // riittää käskeä kirjoittamaan juurinoodi
    kirjoitaNoodi(&xmlWriter, juuriNoodi());

    xmlWriter.writeEndDocument();
    tiedosto.close();

    if( tiedosto.error())
    {
        return false;
    }
    return true;
}


MuistiNoodi *MuistiXmlModel::lueNoodi(QXmlStreamReader *lukija, const QString &nimi)
{
    // Tässä vaiheessa ollaan noodin elementissä
    // Määritellään tyyppi
    int tyyppi;

    if( nimi == "muisti")
        tyyppi = JuuriNoodi;
    else if( nimi == "muisto")
        tyyppi = MuistoNoodi;
    else if( nimi == "henkilo")
        tyyppi = HenkiloNoodi;
    else if( nimi == "tieto")
        tyyppi = TietoNoodi;
    else if( nimi == "pvm")
        tyyppi = PvmNoodi;
    else if( nimi == "memo")
        tyyppi = MemoNoodi;
    else if( nimi == "puhelin")
        tyyppi = PuhelinNoodi;
    else if( nimi == "sijainti")
        tyyppi = SijaintiNoodi;


    // Attribuutit
    int id = lukija->attributes().value("id").toString().toInt();
    QDateTime luotu = QDateTime::fromString(
                lukija->attributes().value("luotu").toString(), Qt::ISODate );
    QDateTime muokattu = QDateTime::fromString(
                lukija->attributes().value("muokattu").toString(), Qt::ISODate );


    QString avain;

    if( nimi == "muisto")
        avain = lukija->attributes().value("laji").toString();
    else if( nimi == "henkilo")
        avain = lukija->attributes().value("rooli").toString();
    else
        avain = lukija->attributes().value("avain").toString();

    // Sitten voidaan luoda noodi
    MuistiNoodi *uusiNoodi = new MuistiNoodi(id, luotu, muokattu, tyyppi, avain);

    // Ja päästään lukemaan alakentät

    QString sukunimi;
    QString etunimi;

    lukija->readNext();
    while( !lukija->atEnd())
    {
        if( lukija->isEndElement())
        {
            lukija->readNext();
            break;
        }

        if( lukija->isStartElement())
        {
            // Nyt ollaan alielementissä
            // Ensin pitäisi tarkistaa nimikentät

            if( lukija->name() == "etunimi")
                etunimi = lueNimi(lukija);
            else if( lukija->name() == "sukunimi")
                sukunimi = lueNimi(lukija);
            else
            {
                // Kaikki muut tulkitaan alielementeiksi
                MuistiNoodi *lapsiNoodi = lueNoodi(lukija, lukija->name().toString());
                if( lapsiNoodi)
                    uusiNoodi->lisaaLapsi(lapsiNoodi);
            }
        }
        else if( lukija->isCharacters())
        {
            // Ollaan noodin sisällössä, elikkä tekstissä
            QString tekstia = lukija->text().toString().trimmed();

            // Ja nyt toimitaan moodin mukaan
            if( tyyppi == MuistiModel::TietoNoodi ||
                    tyyppi == MuistiModel::MemoNoodi ||
                    tyyppi == MuistiModel::PuhelinNoodi ||
                    tyyppi == MuistiModel::SijaintiNoodi )
            {
                // Tekstiä sisältönä
                uusiNoodi->asetaLadattuTieto( QVariant(tekstia));
            }
            else if( tyyppi == MuistiModel::PvmNoodi)
            {
                QDate pvm = QDate::fromString(tekstia,"yyyy-MM-dd");
                uusiNoodi->asetaLadattuTieto(pvm);
            }
            lukija->readNext();

        }
        else
        {
            lukija->readNext();
        }

    }

    // Asetetaan henkilön tiedot
    if( tyyppi == MuistiModel::HenkiloNoodi)
    {
        uusiNoodi->asetaLadattuTieto( QStringList() << sukunimi << etunimi );
    }

    // Jos tyyppi kelpo, niin palautetaan noodi
    if( tyyppi )
        return uusiNoodi;

    // Muuten palautetaan 0
    delete uusiNoodi;
    return 0;
}

QString MuistiXmlModel::lueNimi(QXmlStreamReader *lukija)
{
    QString nimi;
    lukija->readNext();
    while( !lukija->atEnd())
    {
        if( lukija->isEndElement())
        {
            lukija->readNext();
            break;
        }

        if( lukija->isStartElement())
        {
            // Nimellä ei saa olla sisäkkäistä elementtiä
            // joten tässä on virhe
            // Tyylikkäämpää voisi olla skipata ???
            lukija->raiseError(tr("Nimellä sisäkkäinen elemenetti"));
        }
        else if(lukija->isCharacters())
        {
            nimi = lukija->text().toString().trimmed();
        }

        lukija->readNext();

    }

    return nimi;
}

void MuistiXmlModel::kirjoitaNoodi(QXmlStreamWriter *kirjoittaja, MuistiNoodi *noodi)
{

    switch (noodi->tyyppi())
    {
    case MuistiModel::JuuriNoodi:
        kirjoittaja->writeStartElement("muisti");
        // Versio pitäisi laittaa vakioksi...
        kirjoittaja->writeAttribute("versio", "0.00");
        break;
    case MuistiModel::MuistoNoodi:
        kirjoittaja->writeStartElement("muisto");
        kirjoittaja->writeAttribute("laji", noodi->avain());
        break;
    case MuistiModel::HenkiloNoodi :
        kirjoittaja->writeStartElement("henkilo");
        if( !noodi->avain().isEmpty())
            kirjoittaja->writeAttribute("rooli", noodi->avain());
        break;
    case MuistiModel::TietoNoodi :
        kirjoittaja->writeStartElement("tieto");

        if( !noodi->avain().isEmpty())
            kirjoittaja->writeAttribute("avain", noodi->avain());
        break;
    case MuistiModel::PvmNoodi :
        kirjoittaja->writeStartElement("pvm");

        if( !noodi->avain().isEmpty())
            kirjoittaja->writeAttribute("avain", noodi->avain());
        break;
    case MuistiModel::SijaintiNoodi:
        kirjoittaja->writeStartElement("sijainti");
        kirjoittaja->writeAttribute("avain", noodi->avain());
        break;
    case MuistiModel::PuhelinNoodi :
        kirjoittaja->writeStartElement("puhelin");
        if( !noodi->avain().isEmpty())
            kirjoittaja->writeAttribute("avain", noodi->avain());
        break;
    case MuistiModel::MemoNoodi :
        kirjoittaja->writeStartElement("memo");
        if( !noodi->avain().isEmpty())
            kirjoittaja->writeAttribute("avain", noodi->avain());
        break;
    default:
        // Ei kirjoiteta tuntemattomia tyyppejä
        return;
    }



    // Kirjoitetaan vakioattribuutit
    kirjoittaja->writeAttribute("id", QString::number(noodi->id()));
    kirjoittaja->writeAttribute("luotu", noodi->luotu().toString(Qt::ISODate)  );
    kirjoittaja->writeAttribute("muokattu", noodi->muokattu().toString(Qt::ISODate));

    // Kirjoitetaan tietosisältö
    if( noodi->tyyppi() == MuistiModel::TietoNoodi ||
            noodi->tyyppi() == MuistiModel::SijaintiNoodi ||
            noodi->tyyppi() == MuistiModel::PuhelinNoodi ||
            noodi->tyyppi() == MuistiModel::MemoNoodi )
    {
        if( !noodi->tieto().toString().isEmpty())
            kirjoittaja->writeCharacters(noodi->tieto().toString());
    }
    else if( noodi->tyyppi() == MuistiModel::PvmNoodi)
    {
        if( noodi->tieto().toDate().isValid())
            kirjoittaja->writeCharacters( noodi->tieto().toDate().toString("yyyy-MM-dd") );
    }
    else if( noodi->tyyppi() == MuistiModel::HenkiloNoodi)
    {
        QStringList listana = noodi->tieto().toStringList();
        if( !listana.value(0).isEmpty())
        {
            kirjoittaja->writeStartElement("sukunimi");
            kirjoittaja->writeCharacters( listana.value(0) );
            kirjoittaja->writeEndElement();
        }
        if( !listana.value(1).isEmpty())
        {
            kirjoittaja->writeStartElement("etunimi");
            kirjoittaja->writeCharacters( listana.value(1));
            kirjoittaja->writeEndElement();
        }
    }

    // Kirjoitetaan lapsielementit
    foreach( MuistiNoodi* lapsi, noodi->lapset() )
        kirjoitaNoodi(kirjoittaja, lapsi);

    kirjoittaja->writeEndElement();

}


