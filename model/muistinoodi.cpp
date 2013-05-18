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


#include "muistinoodi.h"

MuistiNoodi::MuistiNoodi(int id, QDateTime luotu, QDateTime muokattu, int tyyppi, QString avain)
    : vanhempi_(0), tyyppi_(tyyppi), avain_(avain)
{
    // Päivitetään id
    if(id)
    {
        id_ = id;
        if( id > isoinId__)
            isoinId__ = id;
    }
    else
        id_ = ++isoinId__;

    // Jos ei ole määritelty luotu ja muokattu -kenttiä (on uusi kenttä),
    // ne alustetaan nykyiseen aikaan

    if( luotu.isValid() )
        luotu_ = luotu;
    else
        luotu_ = QDateTime::currentDateTime();

    if( muokattu.isValid())
        muokattu_ = muokattu;
    else
        muokattu_ = QDateTime::currentDateTime();

}

MuistiNoodi::~MuistiNoodi()
{
    qDeleteAll(lapset_);
}

void MuistiNoodi::lisaaLapsi(MuistiNoodi *lapsi, int rivi)
{
    if( rivi < 0)
        lapset_.append(lapsi);
    else
        lapset_.insert(rivi, lapsi);

    lapsi->vanhempi_ = this;
}

MuistiNoodi *MuistiNoodi::otaLapsi(int rivi)
{
    MuistiNoodi *lapsi = lapset_.takeAt(rivi);
    lapsi->vanhempi_ = 0;
    return lapsi;
}

MuistiNoodi *MuistiNoodi::lapsi(const QString &avain)
{
    foreach (MuistiNoodi *noodi, lapset())
    {
        if( noodi->avain() == avain )
            return noodi;
    }
    return 0;
}

QString MuistiNoodi::naytettavaTieto() const
{
    // Muiston tietona näytetään otsikkona jotain muuta ;)
    if( tyyppi() == MuistiModel::MuistoNoodi)
    {
        // Haetaan ensimmäinen sopiva
        foreach( MuistiNoodi* lapsi, lapset())
        {
            if( lapsi->tyyppi() == MuistiModel::HenkiloNoodi ||
                    lapsi->tyyppi() == MuistiModel::TietoNoodi )
                return lapsi->naytettavaTieto();
        }
    }
    else if( tyyppi() == MuistiModel::HenkiloNoodi )
    {
        // Henkilöllä näytetään sukunimi etunimi
        QString etunimi = tieto().toStringList().value(0);
        QString sukunimi = tieto().toStringList().value(1);

        if( !etunimi.isEmpty() && !sukunimi.isEmpty() )
            return sukunimi + " " + etunimi;
        else if( !sukunimi.isEmpty())
            return sukunimi;
        else
            return etunimi;
    }
    else if( tyyppi() == MuistiModel::PvmNoodi)
    {
        return tieto().toDate().toString("dd.MM.yyyy");
    }

    return tieto().toString();
}


bool MuistiNoodi::asetaTyyppi(int tyyppi)
{
    switch (tyyppi) {
    case MuistiModel::TietoNoodi:
    case MuistiModel::SijaintiNoodi:
    case MuistiModel::PuhelinNoodi:
    case MuistiModel::MemoNoodi:

        break;
    case MuistiModel::JuuriNoodi:
    case MuistiModel::MuistoNoodi:
        // Nämä eivät talleta tietoa!
        break;
    default:
        return false;
    }

    tyyppi_ = tyyppi;
    paivitaMuokattuAika();
    return true;
}

void MuistiNoodi::asetaAvain(const QString &avain)
{
    avain_ = avain;
    paivitaMuokattuAika();
}

bool MuistiNoodi::asetaTieto(const QVariant &tieto)
{
    tieto_ = tieto;
    paivitaMuokattuAika();
    return true;
}

void MuistiNoodi::asetaLadattuTieto(const QVariant &tieto)
{
    tieto_ = tieto;
}

void MuistiNoodi::paivitaMuokattuAika()
{
    muokattu_ = QDateTime::currentDateTime();
    // Päivitetään Muokattu-aika myös puussa ylöspäin, jotta näkyy
    // koska kenttää on muokattu
    if( vanhempi() )
        vanhempi()->paivitaMuokattuAika();
}


int MuistiNoodi::isoinId__ = 1000;
