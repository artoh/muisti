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


#include "muistihakuikkuna.h"

#include "../xml/muistixmlmodel.h"
#include "../proxymodel/muistihakuproxymodel.h"
#include "../html/muistihtml.h"

#include <QLineEdit>
#include <QWebView>
#include <QSortFilterProxyModel>
#include <QSettings>

#include <QVBoxLayout>
#include <QMenuBar>

#include <QFileDialog>
#include <QFileInfo>


MuistiHakuIkkuna::MuistiHakuIkkuna(QWidget *parent) :
    QMainWindow(parent)
{
    luoModelit();
    luoIkkuna();
    luoValikko();

    view_->setHtml( html_->html() );

}

void MuistiHakuIkkuna::avaaTiedosto()
{
    QString tiedosto = QFileDialog::getOpenFileName(this, tr("Avaa Muisti-tiedosto"));
    if( tiedosto.isNull())
        return;     // Peruutettu!

    QFileInfo info(tiedosto);

    model_->lataaTiedosto(info.absoluteFilePath());
    model_->haeKoristeet(info.absoluteDir().absolutePath());

    QSettings settings;
    settings.setValue("koristehakemisto", info.absoluteDir().absolutePath());
    settings.setValue("muistitiedosto",info.absoluteFilePath());

}

void MuistiHakuIkkuna::hae()
{
    // Suorittaa haun
    hakuProxy_->hae( hakuLine_->text() );
    // Lajitellaan käänteiseen päivämääräjärjestykseen
    lajitteluProxy_->sort(2, Qt::DescendingOrder);
    // Kirjoitetaan html
    html_->asetaKorostettava( hakuLine_->text());

    view_->setHtml( html_->html() );
}


void MuistiHakuIkkuna::luoModelit()
{
    QSettings settings;

    model_ = new MuistiXmlModel(this);
    model_->haeKoristeet(settings.value("koristehakemisto").toString());

    hakuProxy_ = new MuistiHakuProxyModel(this);
    hakuProxy_->setSourceModel(model_);

    lajitteluProxy_ = new QSortFilterProxyModel(this);
    lajitteluProxy_->setSourceModel(hakuProxy_);

    html_ = new MuistiHtml(this);
    html_->asetaModel(lajitteluProxy_);
    html_->asetaMuistiKoristeModel(model_);

    if( settings.value("muistitiedosto").isValid())
        model_->lataaTiedosto( settings.value("muistitiedosto").toString() );
}

void MuistiHakuIkkuna::luoIkkuna()
{
    hakuLine_ = new QLineEdit;
    hakuLine_->setPlaceholderText("Hae...");

    connect( hakuLine_, SIGNAL(returnPressed()),
             this, SLOT(hae()));

    view_ = new QWebView;

    QVBoxLayout *leiska = new QVBoxLayout;
    leiska->addWidget(hakuLine_);
    leiska->addWidget(view_);

    QWidget *widget = new QWidget;
    widget->setLayout(leiska);

    setCentralWidget(widget);

    setWindowTitle("MuistiHaku");
    setWindowIcon(QIcon(":/html/muisti.png"));
}

void MuistiHakuIkkuna::luoValikko()
{

    menuBar()->addAction( tr("Avaa"), this, SLOT(avaaTiedosto()) );
}
