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


#ifndef MUISTIHAKUIKKUNA_H
#define MUISTIHAKUIKKUNA_H


class MuistiXmlModel;
class MuistiHakuProxyModel;
class MuistiHtml;

class QLineEdit;
class QWebView;
class QSortFilterProxyModel;


#include <QMainWindow>

/**
 * @brief MuistiHaku mobiilisovelluksen pääikkuna
 *
 * Ikkunassa on LineEdit, johon syötetään haettava teksti, ja löydetyt
 * tapaukset napsahtava alla olevaan selaajaan
 *
 */

class MuistiHakuIkkuna : public QMainWindow
{
    Q_OBJECT
public:
    explicit MuistiHakuIkkuna(QWidget *parent = 0);
    
signals:
    
public slots:
    void avaaTiedosto();
    void hae();

protected:

private:
    QLineEdit *hakuLine_;
    QWebView *view_;

    MuistiXmlModel *model_;
    MuistiHakuProxyModel *hakuProxy_;
    QSortFilterProxyModel *lajitteluProxy_;
    MuistiHtml *html_;
    
    void luoModelit();
    void luoIkkuna();
    void luoValikko();

};

#endif // MUISTIHAKUIKKUNA_H
