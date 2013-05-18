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

#include "muistinodemodel.h"

#include <QList>
#include <QVariant>
#include <QDateTime>

/**
 * @brief MuistiNoodin noodi
 *
 * MuistiNoodit tallentavat tiedot puun muotoon. Noodeilla on tyyppinsä,
 * avaimensa sekä arvonsa (QVariant)
 *
 */
class MuistiNoodi
{
public:
    /**
     * @brief MuistiNoodi rakentaja
     *
     * Parametrit annetaan vain silloin, kun noodi ladataan, sillä rakentaja säilyttää
     * muutosajan, toisin kuin asetaAvain(), asetaTieto() ja asetaTyyppi()
     *
     * @param id Noodin id
     * @param luotu Noodin luomisaikaleima
     * @param muokattu Noodin muokkausaikaleima
     * @param tyyppi Noodin tyyppi (MuistiModel::MuistiNoodiTyyppi)
     * @param avain Noodin avainkenttä
     */
    MuistiNoodi(int id=0, QDateTime luotu = QDateTime(), QDateTime muokattu = QDateTime(),
                int tyyppi = MuistiModel::NullNoodi,QString avain = QString() );

    ~MuistiNoodi();

    MuistiNoodi* vanhempi() const { return vanhempi_; }
    int lapsiluku() const { return lapset_.count(); }
    QList<MuistiNoodi*> lapset() const { return lapset_; }

    /**
     * @brief Lisää noodin lapseksi
     * @param lapsi Lisättävä noodi
     * @param rivi Sijainti lasten joukossa, -1 viimeinen
     */
    void lisaaLapsi(MuistiNoodi *lapsi, int rivi = -1);

    /**
     * @brief Ottaa lapsen pois puusta
     * @param rivi Lapsen indeksi
     * @return Palauttaa lapsinoodin, joka ei enää ole puussa
     */
    MuistiNoodi* otaLapsi(int rivi);

    /**
     * @brief Palauttaa ensimmäisen lapsinoodin halutulla avaimella
     * @param avain Etsittävä avain
     * @return Osoitin lapsinoodiin tai 0 ellei löydy
     */
    MuistiNoodi *lapsi(const QString &avain);

    int id() const { return id_; }
    int tyyppi() const { return tyyppi_; }
    QString avain() const { return avain_; }

    QVariant tieto() const { return tieto_; }
    QString naytettavaTieto() const;


    QDateTime luotu() const { return luotu_; }
    QDateTime muokattu() const { return muokattu_; }

    /**
     * @brief Asettaa noodin tyypin ja alustaa tiedon
     * @param tyyyppi
     * @return tosi, jos onnistui
     */
    bool asetaTyyppi(int tyyppi);

    void asetaAvain(const QString &avain);

    /**
     * @brief Asettaa tiedon muokkauksen perusteella
     *
     * Tämä funktio päivittää muokkausaikaleiman
     * @param tieto
     * @return
     */

    bool asetaTieto(const QVariant &tieto);
    /**
     * @brief Asettaa tiedon latauksen perusteella
     *
     * Tämä funktio ei päivitä muokkausaikaleimaa
     * @param tieto
     */
    void asetaLadattuTieto(const QVariant &tieto);


protected:
    void paivitaMuokattuAika();

private:
    MuistiNoodi* vanhempi_;
    QList<MuistiNoodi*> lapset_;

    int id_;
    int tyyppi_;

    QDateTime luotu_;
    QDateTime muokattu_;

    QString avain_;
    QVariant tieto_;

    static int isoinId__;

};

#endif // MUISTINOODI_H
