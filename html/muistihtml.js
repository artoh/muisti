
function kartta(id,osoite)
{

    var karttalinkki = "<iframe width=\"600\" height=\"350\" frameborder=\"0\" scrolling=\"no\" marginheight=\"0\" marginwidth=\"0\" "
    + "src=\"https://maps.google.fi/maps?f=q&amp;source=s_q&amp;hl=fi&amp;geocode=&amp;q=" 
    + String(osoite).replace(" ","+")
    + "&amp;z=14&amp;iwloc=A&amp;output=embed\"></iframe>";
    
    document.getElementById(id).innerHTML= osoite + "<br/> " + karttalinkki ;

}
