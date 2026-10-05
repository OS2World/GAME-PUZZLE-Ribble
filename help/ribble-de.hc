//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//
// German translation
//

#include "document.h"
#include "help.h"


USERDOC()
TITLE(Ribble Information)

// First major heading ---------------------------------------------

HEADER(1, pMAINPANEL, Allgemeine Hilfe)
INDEX(1 sortkey='a', Allgemeine Hilfe)
PARAGRAPH()
ARTALIGN('..\bitmaps\ribblestatic.bmp', center)
PARAGRAPH()
BOLD(Ribble) ist ein Boulder-Dash-Klon, der speziell
fuer den Presentation Manager von OS/2 geschrieben wurde.
PARAGRAPH()
Waehlen Sie einen der folgenden Hyperlinks:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pPLOT, Die Handlung)
LINEBREAK()
SQBUL() LINK(pSELECTINGLEVELS, Ebenen auswaehlen)
LINEBREAK()
SQBUL() LINK(pEDITINGLEVELS, Ebenen bearbeiten)
LINEBREAK()
SQBUL() LINK(pKEYS, Tastatur)
LINEBREAK()
SQBUL() LINK(pLICENCE, Lizenzbestimmungen)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Kontakt zu den Autoren)
LINEBREAK()
SQBUL() LINK(pSYSTEM_REQUIREMENTS, Systemanforderungen und Hinweise)
LMARGIN(1)

// Information concerning the plot ----------------------------------

HEADER(1, pPLOT, Die Handlung)
INDEX(1, Die Handlung)
PARAGRAPH()
Das Ziel des Spiels ist es, BOLD(Ribble) LINK(pKEYS, zu fuehren)
ARTINLINE('..\bitmaps\repr1.bmp', left) durch eine Reihe
von Ebenen, Diamanten zu sammeln, Monster zu toeten und
Raetsel zu loesen.
PARAGRAPH()
Die Gegenstaende, die man auf den Ebenen findet, sind in drei Gruppen
unterteilt:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Sammelbare Gegenstaende)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monster)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Sonstige Gegenstaende)
LINEBREAK()
LMARGIN(1)
PARAGRAPH()
Jede Ebene muss innerhalb einer bestimmten Zeit beendet werden.  Die
verbleibende Zeit wird oben am Spielfeld angezeigt, zusammen mit
Ihrer LINK(pSCORING, Punktzahl), der Anzahl der Leben und der Anzahl
der Diamanten, die auf der aktuellen Ebene noch eingesammelt werden muessen.
PARAGRAPH()
Die Anzeige der noch verbleibenden Diamanten gibt an,
wie viele Diamanten, Tresore und Kaefig noch einzusammeln sind.

// Help for Keys ---------------------------------------------------

HEADER(1, pKEYS, Tasten)
INDEXID(1, keyshelp, Tasten)
PARAGRAPH()
Verwenden Sie folgende Tasten, um BOLD(Ribble) zu bewegen:
LMARGIN(5)
PARAGRAPH()
BOLD(Cursor-Auf-Taste), um nach oben zu gehen
LINEBREAK()
LINEBREAK()
BOLD(Cursor-Ab-Taste), um nach unten zu gehen
LINEBREAK()
LINEBREAK()
BOLD(Cursor-Links-Taste), um nach links zu gehen
LINEBREAK()
LINEBREAK()
BOLD(Cursor-Rechts-Taste), um nach rechts zu gehen
LINEBREAK()
LINEBREAK()
//(The above keys can be changed by selecting the on the BOLD(Options) menu-item
//under the BOLD(Edit) menu.)
//LINEBREAK()
//LINEBREAK()
//BOLD(Return) key, for status report
//LINEBREAK()
//LINEBREAK()
BOLD(Escape-Taste), um Selbstmord zu begehen und die aktuelle Ebene
von vorn zu beginnen.
LINEBREAK()
LINEBREAK()
//BOLD(Shift + Escape) key, to abandon the current level
//LINEBREAK()
//LINEBREAK()
BOLD(Leertaste), um die Kartenanzeige ein- und auszuschalten
LMARGIN(1)
PARAGRAPH()
Weitere Tasten werden in den On-line-Hilfe-Abschnitten
der jeweiligen Bereiche beschrieben.

// Help for F1 pressed on Help Keys menu item ---------------------

HEADER(2, pKEYSMENUITEM, Hilfe fuer den Menuepunkt Tasten)
PARAGRAPH()
Waehlen Sie den Menuepunkt BOLD(Tasten) fuer Hilfe
zur Tastatur.

// Information concerning map items ----------------------------

HEADER(1, pITEMSHELP, Dinge&comma. Monster und anderes)
INDEXID(1, mapitems, Dinge&comma. Monster und anderes)
PARAGRAPH()
Gegenstaende, die man auf den verschiedenen Ebenen findet:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Sammelbare Gegenstaende)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monster)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Sonstige Gegenstaende)
LINEBREAK()
LMARGIN(1)


// Information concerning collectable items ----------------------------

HEADER(2, pITEMS, Sammelbare Gegenstaende)
INDEX(2, Sammelbare Gegenstaende)
PARAGRAPH()
Dies sind die sammelbaren Gegenstaende, die auf
den Ebenen verstreut zu finden sind:
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left)
Erde
LMARGIN(5)
PARAGRAPH()
Erde findet man auf fast allen Ebenen.  Sie dient als Haltegrund
fuer Felsbrocken und andere Gegenstaende, die herunterfallen koennen.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left)
Diamant
LMARGIN(5)
PARAGRAPH()
Das Hauptziel von BOLD(Ribble) ist es, alle Diamanten auf jeder Ebene
einzusammeln. Diamanten findet man entweder in dieser Form,
oder sie entstehen, wenn Geister in Kaefige gehen,
oder indem man einen Schluessel aufsammelt, um die Tresore zu oeffnen.  Mehr
dazu spaeter.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left)
Schluessel
LMARGIN(5)
PARAGRAPH()
Wenn BOLD(Ribble) einen Schluessel aufhebt, werden alle Tresore ARTINLINE('..\bitmaps\safe.bmp', left)
auf der aktuellen Ebene in Diamanten umgewandelt, die man dann einsammeln kann.
Vorsicht vor Felsbrocken oder anderen Gegenstaenden, die auf Tresoren
balancieren - sie koennen abrutschen, wenn der Tresor sich in einen Diamanten verwandelt.
LMARGIN(1)

// Information concerning monsters ----------------------------

HEADER(2, pMONSTERS, Monster)
INDEX(2, Monster)
PARAGRAPH()
Dies sind die Monster, auf die Sie waehrend Ihrer Wanderungen
durch die verschiedenen Ebenen ungluecklicherweise
treffen werden:
PARAGRAPH()
LMARGIN(1)
ARTINLINE('..\bitmaps\egg.bmp', left)
Ei
LMARGIN(5)
PARAGRAPH()
Wenn Sie ein Ei loesen, bekommt es Risse und schliesslich
schluepft ein Slither-Monster daraus.
PARAGRAPH()
Eier verhalten sich wie Felsbrocken: Sie rutschen von gewoelbten
Flaechen. Sie zaehlen auch als gewoelbte Gegenstaende, sodass
Felsbrocken und andere Eier von ihnen abrutschen. Eier bekommen keine
Risse, wenn etwas auf sie drauffaellt.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\crackedegg.bmp', left)
Angerissenes Ei
LMARGIN(5)
PARAGRAPH()
Nachdem ein Ei geloest wurde, gibt es eine kurze Zeit,
in der das Slither-Monster aus dem Ei bricht.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left)
Slither
LMARGIN(5)
PARAGRAPH()
Am Ende der Schluepfzeit kommt ein ausgewachsenes Slither
aus seinem Ei und nimmt seinen einzigen Lebenszweck auf: Ihren Tod.
PARAGRAPH()
Ein Slither kann nur durch einen Felsbrocken getoetet werden: entweder,
indem man ihm einen auf den Kopf fallen laesst, oder indem man
einen in ihn hineinschiebt.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left)
Geist
LMARGIN(5)
PARAGRAPH()
Geister sind kleine flauschige Kreaturen, die blind
durch die Ebenen wandern. Sie sind bei Beruehrung toedlich,
und muessen vorsichtig in Kaefige
ARTINLINE('..\bitmaps\cage.bmp', left) getrieben werden, wo
sie sich dann in Diamanten verwandeln.


// Information concerning miscellaneous items ----------------------------

HEADER(2, pMISCITEMS, Sonstige Gegenstaende)
INDEX(2, Sonstige Gegenstaende)
PARAGRAPH()
Dies sind die sonstigen Gegenstaende, die auf
den Ebenen verstreut zu finden sind:

PARAGRAPH()
ARTINLINE('..\bitmaps\boulder.bmp', left)
Felsbrocken
LMARGIN(5)
PARAGRAPH()
Felsbrocken koennen geloest werden, indem man entfernt, was sie
stuetzt, oder indem man sie schiebt. Sie rutschen von gewoelbten
Flaechen (einschliesslich Eiern und Diamanten) ab und koennen dazu
benutzt werden, einige Arten von Monstern zu toeten.
Von einem herabfallenden Felsbrocken getroffen zu werden ist meist toedlich.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\teleport.bmp', left)
Teleporter
LMARGIN(5)
PARAGRAPH()
Wenn BOLD(Ribble) in einen Teleporter laeuft, wird er an einen anderen
Ort auf der aktuellen Ebene teleportiert.  Einmal benutzt,
verschwinden Teleporter.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\cage.bmp', left)
Kaefig
LMARGIN(5)
PARAGRAPH()
Treibe die Geister in Kaefige, und sie verwandeln sich in Diamanten.  Um
eine Ebene abzuschliessen, muss jeder Kaefig in einen Diamanten
verwandelt worden sein.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\safe.bmp', left)
Tresor
LMARGIN(5)
PARAGRAPH()
Wenn BOLD(Ribble) den Schluessel ARTINLINE('..\bitmaps\key.bmp', left) aufhebt, werden alle
Tresore auf der aktuellen Ebene in Diamanten umgewandelt.  Wie bei den
Kaefigen muessen Sie alle Tresor-Diamanten eingesammelt haben, um eine Ebene
abzuschliessen.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\bomb.bmp', left)
Bombe
LMARGIN(5)
PARAGRAPH()
Bomben werden scharf, wenn sie auf etwas anderes als
Erde ARTINLINE('..\bitmaps\earth.bmp', left) fallen.  Einmal scharf
ARTINLINE('..\bitmaps\bombli1.bmp', left), haben Sie etwa
fuenf Sekunden, um zur Seite zu gehen, bevor eine Bombe
detoniert
ARTINLINE('..\bitmaps\flame1.bmp', left).
LMARGIN(1)


// Information concerning scoring items ----------------------------

HEADER(2, pSCORING, Punkte)
INDEX(2, Punkte)
PARAGRAPH()
Punkte werden fuer das Einsammeln und Toeten von Dingen auf den Ebenen vergeben, wie folgt:
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left) 1 Punkt
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left) 10 Punkte
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left) 10 Punkte
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left) + ARTINLINE('..\bitmaps\cage.bmp', left) 25 Punkte
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left) + ARTINLINE('..\bitmaps\boulder.bmp', left)  50 Punkte


// Information selecting levels ----------------------------

HEADER(1, pSELECTINGLEVELS, Ebenen auswaehlen)
INDEXID(1, selectlevel, Ebenen auswaehlen)
PARAGRAPH()
Wenn Sie eine Ebene abgeschlossen haben, gelangen Sie automatisch
zur naechsten. Wenn Sie direkt zu einer bestimmten Ebene gehen wollen,
koennen Sie den LINK(pSELECTLEVEL, Dialog zur Ebenenauswahl) verwenden,
der erscheint, wenn Sie den Menuepunkt
BOLD(Oeffnen...) unter dem Menue BOLD(Spiel) waehlen.


// Help for the select level dialog --------------------------------

HEADER(2, pSELECTLEVEL, Dialog Oeffnen... Ebene)
INDEX(2, Dialog Oeffnen... Ebene)
PARAGRAPH()
Verwenden Sie diesen Dialog, um die Ebene auszuwaehlen, die Sie spielen moechten.


// Editing levels ----------------------------

HEADER(1, pEDITINGLEVELS, Ebenen bearbeiten)
INDEX(1, Ebenen bearbeiten)
PARAGRAPH()
Waehlen Sie zu jeder Zeit waehrend Sie eine Ebene spielen den Menuepunkt
BOLD(Level...) unter dem Untermenue BOLD(Karteneditor) des Menues BOLD(Optionen). Das Fenster von BOLD(Ribble) wird
horizontal erweitert, und eine Palette mit allen verfuegbaren
Spielgegenstaenden erscheint auf der rechten Seite des Fensters.
PARAGRAPH()
BOLD(Ribble) wird durch einen Fadenkreuz-Cursor
ARTINLINE('..\bitmaps\edit.bmp', center) ersetzt, der angibt,
welche Kartenzelle Sie aendern wollen.  Die ueblichen BOLD(Ribble)-Tasten
gelten auch beim Bearbeiten, und alle Kreaturen werden angehalten.
PARAGRAPH()
ITALIC(Gegenstaende zum Spielfeld hinzufuegen)
LMARGIN(3)
PARAGRAPH()
Klicken Sie in der Palette auf einen Gegenstand, um ihn auszuwaehlen.
Der momentan ausgewaehlte Palettengegenstand wird neben der Beschriftung
BOLD(Aktuell >>) ueber der Palette angezeigt.
PARAGRAPH()
Durch Drucken der BOLD(Enter)-Taste wird der ausgewaehlte Gegenstand
unter dem Fadenkreuz auf dem Spielfeld platziert.
PARAGRAPH()
Wenn Sie eine Kreatur auf die Karte setzen, wird sie erst
lebendig, wenn Sie den Bearbeitungsmodus verlassen.
LMARGIN(1)
PARAGRAPH()
ITALIC(Kreaturen von der Karte entfernen)
LMARGIN(3)
PARAGRAPH()
Platzieren Sie das Fadenkreuz so, dass es die Kreatur ueberlappt,
und druecken Sie die BOLD(Entf)-Taste.  Die Kreatur wird entfernt.
PARAGRAPH()
Beachten Sie, dass Gegenstaende wie Geister und Teleporter, die
Sie auf dem Spielfeld platzieren, erst zu Kreaturen werden,
bis Sie den Bearbeitungsmodus verlassen.
LMARGIN(1)
PARAGRAPH()
ITALIC(Teleporter-Ziele festlegen)
LMARGIN(3)
PARAGRAPH()
Jeder Teleporter hat einen zugeordneten Zielort.
Diese Zielorte sind mit einer weissen Zahl auf
blauem Grund markiert und werden ueber jedem Gegenstand
am Ziel angezeigt.
PARAGRAPH()
Zusaetzlich zur Ortsmarkierung haben Teleporter
auch eine weisse Zahl auf rotem Grund aufgepraegt, damit
Sie wissen, welche Zielmarkierung zu welchem Teleporter gehoert.
PARAGRAPH()
Um eine Zielmarkierung zu verschieben, platzieren Sie das Fadenkreuz
darueber und druecken die BOLD(Einfg)-Taste.  Wenn Sie nun das
Fadenkreuz bewegen, folgt die Zahl.  Druecken Sie die BOLD(Enter)-Taste,
um die Zahl am neuen Ort abzulegen.
LMARGIN(1)
PARAGRAPH()
Siehe auch:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pSAVINGLEVELS, Ebenen speichern)
LMARGIN(1)


// Saving levels ----------------------------

HEADER(1, pSAVINGLEVELS, Ebenen speichern)
INDEXID(1, saving, Ebenen speichern)
PARAGRAPH()
Waehrend Sie eine Ebene spielen oder bearbeiten, koennen Sie das aktuelle
Spielfeld in einer Ebenen-Datei speichern.
PARAGRAPH()
Verwenden Sie den Menuepunkt BOLD(Speichern...) unter dem Menue BOLD(Spiel),
um einen LINK(pSAVELEVELAS, Dialog) aufzurufen, mit dem Sie Ihre
Ebene speichern koennen.

// Save level dialog ----------------------------

HEADER(2, pSAVELEVELAS, Dialog Ebene speichern)
INDEX(2, Dialog Ebene speichern)
PARAGRAPH()
Mit diesem Dialog koennen Sie verschiedene Informationen
ueber die Ebene ausfuellen, die Sie speichern wollen.
PARAGRAPH()
Klicken Sie auf die Schaltflaeche BOLD(OK), um die Ebene und die
zugehoerigen Informationen zu speichern, oder auf BOLD(Abbrechen), um
den Dialog zu schliessen, ohne die Ebene zu speichern.
PARAGRAPH()
Beachten Sie das auf-und-ab-Zaehlfeld fuer die Ebenennummer
unten im Dialog. Diese Nummer gibt die Position in der
Spielreihenfolge der Ebenen an. Damit BOLD(Ribble) Ihre Ebenen verwenden kann,
muessen sie ab eins (1) aufwaerts fortlaufend nummeriert sein.  Sie
koennen den Dialog zur Ebenenauswahl verwenden, um die
hoechste nummerierte Ebene herauszufinden, oder in das Verzeichnis
"levels" im Verzeichnis der ausfuehrbaren Datei von BOLD(Ribble) schauen.



// Help for the product information dialog ------------------------

HEADER(1, pPRODUCTINFO, Produktinformationen)
INDEXID(1, productinfo, Produktinformationen)
PARAGRAPH()
Ribble ist Copyright (c)1993, 1994 von J.R.Shannon und
D.J.Neades.  Alle Rechte vorbehalten.
PARAGRAPH()
Siehe auch:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pDISCLAIMER, Gewaehrleistungsausschluss)
LINEBREAK()
SQBUL() LINK(pLICENCE, Lizenzbestimmungen)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Kontakt zu den Autoren)
LINEBREAK()
SQBUL() LINK(pGREETINGS, Gruesse)
LMARGIN(1)
PARAGRAPH()
Alle Warenzeichen werden anerkannt.

// System requirements and notes --------------------------------

HEADER(2, pSYSTEM_REQUIREMENTS, Systemanforderungen und Hinweise)
INDEX(2, Systemanforderungen und Hinweise)
PARAGRAPH()
BOLD(Ribble) ist ein Spiel mit hohem CPU- und Grafikaufwand.  Das
Spielfeld wird viele Male pro Sekunde aktualisiert, also sollten
Sie fuer einen zufriedenstellenden Lauf von BOLD(Ribble)
auf Ihrem Rechner folgende Punkte beachten:
PARAGRAPH()
Je schneller Ihr Prozessor, desto besser.  BOLD(Ribble) wurde auf
einem 486DX33, 486DX50 und P60 geschrieben, sodass die Leistung
auf diesen Prozessoren zufriedenstellend ist (besonders auf dem Letzten!).
PARAGRAPH()
Da die von BOLD(Ribble) verwendete Darstellungstechnik darin besteht,
eine recht grosse Bitmap viele Male pro Sekunde auf den Bildschirm zu
blitten, laeuft BOLD(Ribble) auf Systemen mit Local-Bus- oder
PCI-Grafikkarten deutlich besser als auf solchen mit (selbst
beschleunigten) ISA-Karten.  Die beiden 486er, die bei der Entwicklung
von BOLD(Ribble) verwendet wurden, hatten ISA-Karten, und der P60 hatte
eine #9GXE + PCI-Bus.
PARAGRAPH()
Sie koennen die Leistung abstimmen, indem Sie den Menuepunkt
BOLD(Optionen...) unter dem Untermenue BOLD(Karteneditor) des Menues BOLD(Optionen)
waehlen und die Einstellungen in dem
angezeigten LINK(pOPTIONSDIALOG, Dialog) aendern.


// Information concerning licencing ----------------------------

HEADER(2, pLICENCE, Lizenzbestimmungen)
INDEX(2, Lizenzbestimmungen)
ARTALIGN('..\bitmaps\tribble-normal.bmp', center)
PARAGRAPH()
BOLD(Ribble) ist Tribbleware.  Das bedeutet: Wenn es Ihnen gefaellt
und Sie es spielen, waehrend Ihr Chef kurz zum
Rauchen verschwindet, dann sollten Sie sich irgendwie
verpflichtet fuehlen, uns eines dieser pelzigen Tribble-Dinger
mit Antennen, wackeligen Augen und einem amuesanten
Motto als Schwanz zu schicken...  Wenn das nicht geht, waere
eine Postkarte auch nett.
PARAGRAPH()
Benutzer, die an besseren Grafiken, Ebenen
oder weiteren Funktionen des Spiels interessiert sind, sind
eingeladen, sich zu melden.  Nervige kleine .BOLD(MID)-Weisen, die
wir mit MMPM/2 abspielen koennen, waeren sehr nuetzlich.


// Information concerning contacting the authors  -------------------------

HEADER(2, pCONTAUTHOR, Kontakt zu den Autoren)
INDEX(2, Kontakt zu den Autoren)
PARAGRAPH()
Die Autoren sind im Internet erreichbar unter:
LMARGIN(5)
PARAGRAPH()
BOLD(jrs@larch.demon.co.uk),
LMARGIN(2)
PARAGRAPH()
oder (fuer Tribbles usw.),
LMARGIN(5)
PARAGRAPH()
Jason R. Shannon
LINEBREAK()
68 Thornton Close
LINEBREAK()
Girton
LINEBREAK()
Cambridge
LINEBREAK()
CB3 ONG
LINEBREAK()
England
LMARGIN(1)

// Help for Disclaimer -------------------------------

HEADER(2, pDISCLAIMER, Gewaehrleistungsausschluss)
INDEX(2, Gewaehrleistungsausschluss)
PARAGRAPH()
Dieses Produkt wird ohne jede Gewaehrleistung geliefert, weder
ausdruecklich noch stillschweigend. Die Autoren (Daniel J Neades und
Jason R Shannon) uebernehmen keine Verantwortung fuer nachteilige
Folgen, die aus der Benutzung oder dem Missbrauch von BOLD(Ribble)
oder den zugehoerigen Programm- und Datendateien entstehen koennen.
Solche nachteiligen Folgen umfassen, sind aber nicht beschraenkt auf,
Gewinnverlust und Datenverlust.
PARAGRAPH()
Die Autoren lehnen ausdruecklich alle Gewaehrleistungen ab, ob
ausdruecklich oder stillschweigend, einschliesslich, aber nicht
beschraenkt auf, jegliche stillschweigende Gewaehrleistung der
Handelbarkeit oder der Eignung fuer einen bestimmten Zweck.
PARAGRAPH()
So, das haetten wir gesagt!

// Help for Greetings --------------------------------

HEADER(2, pGREETINGS, Gruesse)
PARAGRAPH()
In keiner bestimmten Reihenfolge, Gruesse an:
LMARGIN(5)
PARAGRAPH()
Alan Garde, Jarod Nash, Bob Eager, Mark Hanlon, Steve Wooding,
Keith Rundle, Asif Majid, Trevor Davies, und alle, die
bei IBM mit OS/2 zu tun haben.


// Help for Options dialog --------------------------------

HEADER(1, pOPTIONSDIALOG, Dialog Optionen...)
INDEX(1, Dialog Optionen...)
PARAGRAPH()
Verwenden Sie die Steuerelemente in diesem Dialog, um:
LMARGIN(5)
PARAGRAPH()
SQBUL() die Tasten zu aendern, mit denen BOLD(Ribble) bewegt wird
LMARGIN(8)
PARAGRAPH()
Die drei moeglichen Auswahlmoeglichkeiten sind:
LMARGIN(10)
PARAGRAPH()
SQBUL() ITALIC(Pfeile), Cursortasten.
PARAGRAPH()
SQBUL() ITALIC(Klassisch), wobei Z = links, X = rechts, ' (Apostroph) = oben und
/ (Schraege) = unten.
PARAGRAPH()
SQBUL() ITALIC(Andere), was auch immer Sie wollen.
LMARGIN(5)
PARAGRAPH()
SQBUL() verschiedene Einstellungen zu aendern, um die Leistung abzustimmen
LMARGIN(8)
PARAGRAPH()
SQBUL() ITALIC(Bildwiederholrate), die Verzoegerung in Millisekunden
zwischen den Fensteraktualisierungen.
PARAGRAPH()
SQBUL() ITALIC(Zellenausmasse), die Groesse jeder Zelle im Fenster.
Der Standard ist 64x64, also eine Zelle von 64 mal 64 Bildpunkten.
PARAGRAPH()
SQBUL() ITALIC(Sichtbare Ausmasse), die Groesse des Spielfeldes,
das im Fenster angezeigt wird.  Der Standard ist 14x14, also eine
Ansicht von 14 mal 14 Zellen.
LMARGIN(1)


// -- Los endos --

ENDDOC()