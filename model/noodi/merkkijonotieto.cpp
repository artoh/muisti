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


#include "merkkijonotieto.h"

MerkkijonoTieto::MerkkijonoTieto()
{
}

QVariant MerkkijonoTieto::tieto() const
{
    return QVariant(tieto_);
}

QString MerkkijonoTieto::naytettavaTieto() const
{
    return tieto_;
}

bool MerkkijonoTieto::asetaTieto(const QVariant &tieto)
{
    if( tieto.toString().isEmpty())
        return false;

    tieto_ = tieto.toString();
    return true;
}

bool MerkkijonoTieto::asetaTieto(const QString &tieto)
{
    tieto_ = tieto;
    return true;
}
