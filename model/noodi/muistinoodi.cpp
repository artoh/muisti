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

#include "muistinoodintieto.h"
#include "merkkijonotieto.h"

MuistiNoodi::MuistiNoodi(int id)
    : tyyppi_(MuistiModel::NullNoodi), tieto_(0)
{
    if(id)
        id_ = id;
    else
        id_ = ++isoinId_;
}

MuistiNoodi::~MuistiNoodi()
{
    if( tietoPtr())
        delete tietoPtr();
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

QVariant MuistiNoodi::tieto() const
{
    if( tietoPtr())
        return tietoPtr()->tieto();
    else
        return QVariant();
}

QString MuistiNoodi::naytettavaTieto() const
{
    if( tietoPtr())
        return tietoPtr()->naytettavaTieto();
    else
        return QString();
}


bool MuistiNoodi::asetaTyyppi(int tyyppi)
{
    MuistiNoodinTieto *uusiTieto = 0;


    switch (tyyppi) {
    case MuistiModel::TietoNoodi:
    case MuistiModel::SijaintiNoodi:
    case MuistiModel::PuhelinNoodi:
    case MuistiModel::MemoNoodi:
        // Tässä vaiheessa kaikki merkkijonomuotoiset samalla
        uusiTieto = new MerkkijonoTieto();
        break;
    case MuistiModel::JuuriNoodi:
    case MuistiModel::MuistoNoodi:
        // Nämä eivät talleta tietoa!
        break;
    default:
        return false;
    }


    // Siirretään tieto uuteen
    // Koska tyyppi vaihtuu, käytetetään merkkijonon kautta
    if( tietoPtr() && uusiTieto)
    {
        uusiTieto->asetaTieto( tietoPtr()->naytettavaTieto());
        delete tieto_;
    }
    tieto_ = uusiTieto;
    tyyppi_ = tyyppi;

    return true;
}

void MuistiNoodi::asetaAvain(const QString &avain)
{
    avain_ = avain;
}

bool MuistiNoodi::asetaTieto(const QVariant &tieto)
{
    if( tietoPtr())
        return tietoPtr()->asetaTieto(tieto);
    else
        return false;
}

bool MuistiNoodi::asetaTieto(const QString &tieto)
{
    if( tietoPtr())
        return tietoPtr()->asetaTieto(tieto);
    else
        return false;
}

int MuistiNoodi::isoinId_ = 1000;
