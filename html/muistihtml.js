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



// Taulu avoimista kartoista, jotta karttafunktio osaa sulkea
var avoinKartta;
var korostettuSisalto;

// Näyttää tai sulkee kartan
function kartta(id,osoite)
{
    if( avoinKartta != undefined )
    {
        // Suljetaan ensin edellinen kartta
        document.getElementById(avoinKartta).innerHTML= korostettuSisalto;
    }


    if( avoinKartta == id )
    {
        // Oli nykyinen, eli yhtään ei jää auki
        avoinKartta = undefined;
    }
    else
    {
        // Avataan kartta
        avoinKartta = id;
        korostettuSisalto = document.getElementById(id).innerHTML;

        var karttalinkki = "<iframe width=\"600\" height=\"350\" frameborder=\"0\" scrolling=\"no\" marginheight=\"0\" marginwidth=\"0\" "
        + "src=\"https://maps.google.fi/maps?f=q&amp;source=s_q&amp;hl=fi&amp;geocode=&amp;q="
        + String(osoite).replace(" ","+")
        + "&amp;z=14&amp;iwloc=A&amp;output=embed\"></iframe>";

        document.getElementById(id).innerHTML= korostettuSisalto + "<br/> " + karttalinkki ;

    }

}

