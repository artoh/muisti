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


#ifndef MUISTINOODI_H
#define MUISTINOODI_H

#include "../muistinodemodel.h"

#include <QList>

class MuistiNoodinTieto;

/**
 * @brief MuistiNoodin noodi
 *
 * MuistiNoodit tallentavat tiedot puun muotoon. Noodeilla on tyyppinsä,
 * avaimensa sekä arvonsa
 *
 */
class MuistiNoodi
{
public:
    explicit MuistiNoodi(int id=0);

    ~MuistiNoodi();

    MuistiNoodi* vanhempi() const { return vanhempi_; }
    int lapsiluku() const { return lapset_.count(); }
    QList<MuistiNoodi*> lapset() const { return lapset_; }

    /**
     * @brief Palauttaa ensimmäisen lapsinoodin halutulla avaimella
     * @param avain Etsittävä avain
     * @return Osoitin lapsinoodiin tai 0 ellei löydy
     */
    MuistiNoodi *lapsi(const QString &avain);

    int id() const { return id_; }
    int tyyppi() const { return tyyppi_; }
    QString avain() const { return avain_; }

    QVariant tieto() const;
    QString naytettavaTieto() const;


    /**
     * @brief Asettaa noodin tyypin ja alustaa tiedon
     * @param tyyyppi
     * @return tosi, jos onnistui
     */
    bool asetaTyyppi(int tyyppi);

    void asetaAvain(const QString &avain);
    bool asetaTieto(const QVariant &tieto);
    bool asetaTieto(const QString &tieto);


protected:
    MuistiNoodinTieto *tietoPtr() const { return tieto_; }

private:
    MuistiNoodi* vanhempi_;
    QList<MuistiNoodi*> lapset_;

    int id_;
    int tyyppi_;

    QString avain_;

    MuistiNoodinTieto* tieto_;

    static int isoinId_;

};

#endif // MUISTINOODI_H
