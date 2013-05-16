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


#include "muistinoodintieto.h"

MuistiNoodinTieto::MuistiNoodinTieto()
{
}

MuistiNoodinTieto::~MuistiNoodinTieto()
{
}

QString MuistiNoodinTieto::naytettavaTieto() const
{
    return tieto().toString();
}

bool MuistiNoodinTieto::asetaTieto(const QString &tieto)
{
    return asetaTieto( QVariant(tieto));
}

bool MuistiNoodinTieto::onkoTyhja()
{
    return naytettavaTieto().isEmpty();
}
