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

MuistiNoodi::MuistiNoodi(int id)
    : tyyppi_(MuistiModel::NullNoodi)
{
    if(id)
        id_ = id;
    else
        id_ = ++isoinId_;
}

MuistiNoodi::~MuistiNoodi()
{

}

void MuistiNoodi::lisaaLapsi(MuistiNode *lapsi, int rivi)
{
    if( rivi < 0)
        lapset_.append(lapsi);
    else
        lapset_.insert(rivi, lapsi);
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
    return true;
}

void MuistiNoodi::asetaAvain(const QString &avain)
{
    avain_ = avain;
}

bool MuistiNoodi::asetaTieto(const QVariant &tieto)
{
    tieto_ = tieto;
    return true;
}


int MuistiNoodi::isoinId_ = 1000;
