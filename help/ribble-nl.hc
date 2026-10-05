//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//
// Dutch translation
//

#include "document.h"
#include "help.h"


USERDOC()
TITLE(Ribble Information)

// First major heading ---------------------------------------------

HEADER(1, pMAINPANEL, Algemene help)
INDEX(1 sortkey='a', Algemene help)
PARAGRAPH()
ARTALIGN('..\bitmaps\ribblestatic.bmp', center)
PARAGRAPH()
BOLD(Ribble) is een Boulder-dash-kloon, speciaal geschreven
voor de Presentation Manager van OS/2.
PARAGRAPH()
Selecteer een van de volgende hyperlinks:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pPLOT, Het verhaal)
LINEBREAK()
SQBUL() LINK(pSELECTINGLEVELS, Levels selecteren)
LINEBREAK()
SQBUL() LINK(pEDITINGLEVELS, Levels bewerken)
LINEBREAK()
SQBUL() LINK(pKEYS, Toetsenbord)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licentie)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contact met de auteurs)
LINEBREAK()
SQBUL() LINK(pSYSTEM_REQUIREMENTS, Systeemvereisten en opmerkingen)
LMARGIN(1)

// Information concerning the plot ----------------------------------

HEADER(1, pPLOT, Het verhaal)
INDEX(1, Het verhaal)
PARAGRAPH()
Het doel van het spel is om BOLD(Ribble) LINK(pKEYS, te besturen)
ARTINLINE('..\bitmaps\repr1.bmp', left) door een aantal
levels, diamanten te verzamelen, monsters te doden en
puzzels op te lossen.
PARAGRAPH()
De voorwerpen die je op de levels vindt, zijn in drie groepen verdeeld:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Verzamelbaar)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monsters)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Overige voorwerpen)
LINEBREAK()
LMARGIN(1)
PARAGRAPH()
Elk level moet binnen een bepaalde tijd worden voltooid.  De
resterende tijd wordt bovenaan het speelveld weergegeven, samen met
je LINK(pSCORING, score), het aantal levens en het aantal
diamanten dat nog op het huidige level verzameld moet worden.
PARAGRAPH()
De waarde van het resterende aantal diamanten geeft aan
hoeveel diamanten, kluizen en kooien nog verzameld moeten worden.

// Help for Keys ---------------------------------------------------

HEADER(1, pKEYS, Toetsen)
INDEXID(1, keyshelp, Toetsen)
PARAGRAPH()
Gebruik de volgende toetsen om BOLD(Ribble) te verplaatsen:
LMARGIN(5)
PARAGRAPH()
BOLD(Toets Cursor omhoog), om omhoog te gaan
LINEBREAK()
LINEBREAK()
BOLD(Toets Cursor omlaag), om omlaag te gaan
LINEBREAK()
LINEBREAK()
BOLD(Toets Cursor links), om naar links te gaan
LINEBREAK()
LINEBREAK()
BOLD(Toets Cursor rechts), om naar rechts te gaan
LINEBREAK()
LINEBREAK()
//(The above keys can be changed by selecting the on the BOLD(Options) menu-item
//under the BOLD(Edit) menu.)
//LINEBREAK()
//LINEBREAK()
//BOLD(Return) key, for status report
//LINEBREAK()
//LINEBREAK()
BOLD(Toets Escape), om jezelf te doden en het huidige level
van voren af aan te starten.
LINEBREAK()
LINEBREAK()
//BOLD(Shift + Escape) key, to abandon the current level
//LINEBREAK()
//LINEBREAK()
BOLD(Toets Spatie), om de kaartweergave aan of uit te zetten
LMARGIN(1)
PARAGRAPH()
Andere toetsen worden beschreven in de on-line help-secties
van de betreffende onderdelen.

// Help for F1 pressed on Help Keys menu item ---------------------

HEADER(2, pKEYSMENUITEM, Help voor het menu-item Toetsen)
PARAGRAPH()
Selecteer het menu-item BOLD(Toetsen) voor hulp
over toetsen.

// Information concerning map items ----------------------------

HEADER(1, pITEMSHELP, Leuke dingen&comma. monsters en andere zaken)
INDEXID(1, mapitems, Leuke dingen&comma. monsters en andere zaken)
PARAGRAPH()
Voorwerpen op de verschillende levels:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Verzamelbaar)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monsters)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Overige voorwerpen)
LINEBREAK()
LMARGIN(1)


// Information concerning collectable items ----------------------------

HEADER(2, pITEMS, Verzamelbaar)
INDEX(2, Verzamelbaar)
PARAGRAPH()
Dit zijn de verzamelbare voorwerpen die je verspreid over
de levels kunt vinden:
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left)
Aarde
LMARGIN(5)
PARAGRAPH()
Aarde vind je op vrijwel alle levels.  Het dient als steunpunt
voor rotsblokken en andere voorwerpen die kunnen vallen.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left)
Diamant
LMARGIN(5)
PARAGRAPH()
Het belangrijkste doel van BOLD(Ribble) is om alle diamanten op elk
level te verzamelen. Diamanten vind je ofwel in deze vorm,
ofwel ontstaan ze wanneer geesten kooien binnengaan,
of door een sleutel op te rapen om de kluizen te openen.  Meer
hierover later.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left)
Sleutel
LMARGIN(5)
PARAGRAPH()
Wanneer BOLD(Ribble) een sleutel oppakt, worden alle kluizen ARTINLINE('..\bitmaps\safe.bmp', left)
op het huidige level omgezet in diamanten die vervolgens verzameld
kunnen worden. Pas op voor rotsblokken of andere voorwerpen die op
de kluizen liggen - ze kunnen wegglijden als de kluis verandert in een diamant.
LMARGIN(1)

// Information concerning monsters ----------------------------

HEADER(2, pMONSTERS, Monsters)
INDEX(2, Monsters)
PARAGRAPH()
Dit zijn de monsters die je helaas
zult tegenkomen tijdens je tochten door de verschillende
levels:
PARAGRAPH()
LMARGIN(1)
ARTINLINE('..\bitmaps\egg.bmp', left)
Ei
LMARGIN(5)
PARAGRAPH()
Als je een ei losmaakt, barst het en uiteindelijk
komt er een Slither-monster uit.
PARAGRAPH()
Eieren zijn net rotsblokken: ze glijden van gebogen
oppervlakken. Ze tellen ook als gebogen voorwerpen, dus rotsblokken
en andere eieren glijden er vanaf. Eieren barsten niet
als er iets op wordt laten vallen.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\crackedegg.bmp', left)
Gebarsten ei
LMARGIN(5)
PARAGRAPH()
Nadat een ei is losgemaakt, is er een korte periode
waarin het Slither-monster uit het ei breekt.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left)
Slither
LMARGIN(5)
PARAGRAPH()
Aan het einde van de broedperiode komt een volgroeide Slither
uit het ei, en begint aan het enige doel in zijn leven: jouw dood.
PARAGRAPH()
Een Slither kan alleen door een rotsblok worden gedood:  door
er een op zijn kop te laten vallen, of er een tegenaan te duwen.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left)
Geest
LMARGIN(5)
PARAGRAPH()
Geesten zijn kleine pluizige wezens die blind
ronddwalen door de levels. Ze zijn dodelijk om aan
te raken, en moeten voorzichtig naar kooien
ARTINLINE('..\bitmaps\cage.bmp', left) worden geleid, waar
ze vervolgens in diamanten veranderen.


// Information concerning miscellaneous items ----------------------------

HEADER(2, pMISCITEMS, Overige voorwerpen)
INDEX(2, Overige voorwerpen)
PARAGRAPH()
Dit zijn de overige voorwerpen die je verspreid over
de levels kunt vinden:

PARAGRAPH()
ARTINLINE('..\bitmaps\boulder.bmp', left)
Rotsblok
LMARGIN(5)
PARAGRAPH()
Rotsblokken kunnen vallen door te verwijderen wat ze ondersteunt,
of door ze te duwen. Ze glijden van gebogen oppervlakken
(inclusief eieren en diamanten), en kunnen worden gebruikt om
sommige soorten monsters te doden.
Door een vallend rotsblok geraakt worden is meestal dodelijk.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\teleport.bmp', left)
Teleporter
LMARGIN(5)
PARAGRAPH()
Wanneer BOLD(Ribble) een teleporter binnengaat, wordt hij
geteleporteerd naar een andere plaats op het huidige level.
Eenmaal gebruikt, verdwijnen teleporters.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\cage.bmp', left)
Kooi
LMARGIN(5)
PARAGRAPH()
Leid geesten naar kooien, en ze veranderen in diamanten.  Om
een level te voltooien, moet elke kooi in een diamant zijn
omgezet.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\safe.bmp', left)
Kluis
LMARGIN(5)
PARAGRAPH()
Wanneer BOLD(Ribble) de sleutel ARTINLINE('..\bitmaps\key.bmp', left) oppakt, worden alle
kluizen op het huidige level omgezet in diamanten.  Net als bij de kooien,
moet je alle kluisdiamanten hebben verzameld om een level te voltooien.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\bomb.bmp', left)
Bom
LMARGIN(5)
PARAGRAPH()
Bommen worden actief wanneer ze op iets anders
dan aarde ARTINLINE('..\bitmaps\earth.bmp', left) vallen.  Eenmaal actief
ARTINLINE('..\bitmaps\bombli1.bmp', left), heb je ongeveer
vijf seconden om uit de weg te gaan voordat een bom
ontploft
ARTINLINE('..\bitmaps\flame1.bmp', left).
LMARGIN(1)


// Information concerning scoring items ----------------------------

HEADER(2, pSCORING, Score)
INDEX(2, Score)
PARAGRAPH()
Punten worden verdiend door op de levels dingen te verzamelen en te doden, als volgt:
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left) 1 punt
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left) 10 punten
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left) 10 punten
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left) + ARTINLINE('..\bitmaps\cage.bmp', left) 25 punten
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left) + ARTINLINE('..\bitmaps\boulder.bmp', left)  50 punten


// Information selecting levels ----------------------------

HEADER(1, pSELECTINGLEVELS, Levels selecteren)
INDEXID(1, selectlevel, Levels selecteren)
PARAGRAPH()
Wanneer je een level voltooit, ga je automatisch door naar het volgende.
Als je rechtstreeks naar een bepaald level wilt, dan
kun je het LINK(pSELECTLEVEL, levelselectievenster) gebruiken
dat wordt geopend wanneer je het
menu-item
BOLD(Openen...) onder het menu BOLD(Spel) selecteert.


// Help for the select level dialog --------------------------------

HEADER(2, pSELECTLEVEL, Dialoogvenster Openen... level)
INDEX(2, Dialoogvenster Openen... level)
PARAGRAPH()
Gebruik dit dialoogvenster om het level te selecteren dat je wilt spelen.


// Editing levels ----------------------------

HEADER(1, pEDITINGLEVELS, Levels bewerken)
INDEX(1, Levels bewerken)
PARAGRAPH()
Selecteer op elk moment tijdens het spelen van een level het menu-item
BOLD(Level...) onder het submenu BOLD(Kaarteditor) van het menu BOLD(Opties). Het venster van BOLD(Ribble) wordt
horizontaal uitgebreid, en een palet met alle beschikbare spelvoorwerpen
verschijnt aan de rechterkant van het venster.
PARAGRAPH()
BOLD(Ribble) wordt vervangen door een kruiscursor
ARTINLINE('..\bitmaps\edit.bmp', center) die aangeeft
welke kaartcel je wilt wijzigen.  De gebruikelijke BOLD(Ribble)-toetsen
blijven van toepassing tijdens het bewerken, en alle wezens worden gestopt.
PARAGRAPH()
ITALIC(Voorwerpen toevoegen aan het speelveld)
LMARGIN(3)
PARAGRAPH()
Klik op een voorwerp in het palet om het te selecteren.  Het
momentane geselecteerde paletvoorwerp wordt naast het bijschrift BOLD(Huidig >>)
boven het palet weergegeven.
PARAGRAPH()
De toets BOLD(Enter) plaats het geselecteerde voorwerp onder
de kruiscursor op het speelveld.
PARAGRAPH()
Wanneer je een wezen op de kaart plaatst, wordt het pas
levend als je de bewerkingsmodus verlaat.
LMARGIN(1)
PARAGRAPH()
ITALIC(Wezens van de kaart verwijderen)
LMARGIN(3)
PARAGRAPH()
Zet de kruiscursor zo dat deze het wezen overlapt, en
druk op de toets BOLD(Delete).  Het wezen wordt verwijderd.
PARAGRAPH()
Merk op dat voorwerpen zoals geesten en teleporters die je
op het speelveld plaatst pas wezens worden
als je de bewerkingsmodus verlaat.
LMARGIN(1)
PARAGRAPH()
ITALIC(Teleportbestemmingen instellen)
LMARGIN(3)
PARAGRAPH()
Elke teleporter heeft een bestemmingslocatie.
Deze bestemmingslocaties worden gemarkeerd met een wit nummer op
een blauwe achtergrond, en worden weergegeven over welk voorwerp
zich dan ook op de bestemming bevindt.
PARAGRAPH()
Naast de locatiemarker hebben teleporters
ook een wit-op-rood nummer erop gedrukt, zodat je kunt zien
welke bestemmingsmarker bij welke teleporter hoort.
PARAGRAPH()
Om een bestemmingsmarker te verplaatsen, zet je de kruiscursor erboven,
en druk je op de toets BOLD(Invoegen).  Beweg je nu de kruiscursor,
dan volgt het nummer.  Druk op de toets BOLD(Enter) om het
nummer op de nieuwe locatie neer te zetten.
LMARGIN(1)
PARAGRAPH()
Zie ook:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pSAVINGLEVELS, Levels opslaan)
LMARGIN(1)


// Saving levels ----------------------------

HEADER(1, pSAVINGLEVELS, Levels opslaan)
INDEXID(1, saving, Levels opslaan)
PARAGRAPH()
Tijdens het spelen of bewerken van een level kun je het huidige
speelveld opslaan in een levelbestand.
PARAGRAPH()
Gebruik het menu-item BOLD(Opslaan...) onder het menu BOLD(Spel)
om een LINK(pSAVELEVELAS, dialoogvenster) te openen waarmee je je
level kunt opslaan.

// Save level dialog ----------------------------

HEADER(2, pSAVELEVELAS, Dialoogvenster level opslaan)
INDEX(2, Dialoogvenster level opslaan)
PARAGRAPH()
Met dit dialoogvenster kun je verschillende gegevens invullen
over het level dat je gaat opslaan.
PARAGRAPH()
Klik op de knop BOLD(OK) om het level en de bijbehorende gegevens
op te slaan, of op BOLD(Annuleren) om het dialoogvenster
te sluiten zonder het level op te slaan.
PARAGRAPH()
Let op het draaiknopje voor het levelnummer onderaan
het dialoogvenster. Dit nummer geeft de positie in de levelvolgorde aan.
Wil BOLD(Ribble) je levels gebruiken, dan
moeten ze opeenvolgend genummerd zijn vanaf één (1) naar boven.  Je
kunt het levelselectievenster gebruiken om het hoogste
genummerde level te vinden, of kijken in de map "levels"
in de map van het uitvoerbare bestand BOLD(Ribble).



// Help for the product information dialog ------------------------

HEADER(1, pPRODUCTINFO, Productinformatie)
INDEXID(1, productinfo, Productinformatie)
PARAGRAPH()
Ribble is Copyright (c)1993, 1994 van J.R.Shannon en
D.J.Neades.  Alle rechten voorbehouden.
PARAGRAPH()
Zie ook:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pDISCLAIMER, Vrijwaring)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licentie)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contact met de auteurs)
LINEBREAK()
SQBUL() LINK(pGREETINGS, Begroetingen)
LMARGIN(1)
PARAGRAPH()
Alle handelsmerken worden erkend.

// System requirements and notes --------------------------------

HEADER(2, pSYSTEM_REQUIREMENTS, Systeemvereisten en opmerkingen)
INDEX(2, Systeemvereisten en opmerkingen)
PARAGRAPH()
BOLD(Ribble) is een spel dat veel CPU en grafisch rekenwerk vereist.  Het
speelveld wordt vele malen per seconde bijgewerkt, dus, wil BOLD(Ribble)
naar behoren op je machine draaien, let dan op
de volgende punten:
PARAGRAPH()
Hoe sneller je processor, hoe beter.  BOLD(Ribble) is geschreven
op een 486DX33, 486DX50 en P60, dus de prestaties op deze processors
zijn bevredigend (vooral die laatste!).
PARAGRAPH()
Omdat de renderingtechniek van BOLD(Ribble) bestaat uit het blitten
van een vrij grote bitmap naar het scherm, vele malen per seconde, draait BOLD(Ribble)
aanzienlijk beter op systemen met Local Bus- of PCI-videokaarten
dan op systemen met (zelfs versnelde) ISA-kaarten.  Beide 486's
die bij de ontwikkeling van BOLD(Ribble) werden gebruikt hadden ISA-kaarten,
en de P60 had een #9GXE
+ PCI-bus.
PARAGRAPH()
Je kunt de prestaties afstemmen door het menu-item BOLD(Opties...)
onder het submenu BOLD(Kaarteditor) van het menu BOLD(Opties) te selecteren en de
instellingen wijzigen die in het
LINK(pOPTIONSDIALOG, dialoogvenster) staan.


// Information concerning licencing ----------------------------

HEADER(2, pLICENCE, Licentie)
INDEX(2, Licentie)
ARTALIGN('..\bitmaps\tribble-normal.bmp', center)
PARAGRAPH()
BOLD(Ribble) is Tribbleware.  Dat betekent dat als je het leuk
vindt, en het speelt terwijl je baas even een
sigaretje gaat roken, je je min of meer
verplicht zou moeten voelen om ons een van die pluizige Tribble-beestjes
met antennes, wiebeloogjes en een grappig
motto als staart te sturen...  Lukt dat niet, dan is een ansichtkaart ook prima.
PARAGRAPH()
Gebruikers die geinteresseerd zijn in betere graphics, levels,
of andere functies toevoegen aan het spel, mogen gerust
contact opnemen.  Irritante kleine .BOLD(MID)-deuntjes die we
via MMPM/2 kunnen afspelen zouden zeer welkom zijn.


// Information concerning contacting the authors  -------------------------

HEADER(2, pCONTAUTHOR, Contact met de auteurs)
INDEX(2, Contact met de auteurs)
PARAGRAPH()
De auteurs zijn bereikbaar op het internet via:
LMARGIN(5)
PARAGRAPH()
BOLD(jrs@larch.demon.co.uk),
LMARGIN(2)
PARAGRAPH()
of (voor Tribbles, enz.),
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
Engeland
LMARGIN(1)

// Help for Disclaimer -------------------------------

HEADER(2, pDISCLAIMER, Vrijwaring)
INDEX(2, Vrijwaring)
PARAGRAPH()
Dit product wordt geleverd zonder enige garantie, noch uitdrukkelijk noch impliciet.
De auteurs (Daniel J Neades en Jason R Shannon) aanvaarden
geen verantwoordelijkheid voor eventuele nadelige gevolgen die kunnen
ontstaan door gebruik of misbruik van BOLD(Ribble) of de bijbehorende
programma- en gegevensbestanden. Zulke nadelige gevolgen omvatten, maar zijn niet
beperkt tot, verlies van winst en verlies van gegevens.
PARAGRAPH()
De auteurs wijzen alle garanties uitdrukkelijk af, uitdrukkelijk of impliciet,
inclusief, maar niet beperkt tot, elke impliciete garantie van verkoopbaarheid
of geschiktheid voor een bepaald doel.
PARAGRAPH()
Ziedaar, we hebben het gezegd!

// Help for Greetings --------------------------------

HEADER(2, pGREETINGS, Begroetingen)
PARAGRAPH()
Zonder bepaalde volgorde, begroetingen aan:
LMARGIN(5)
PARAGRAPH()
Alan Garde, Jarod Nash, Bob Eager, Mark Hanlon, Steve Wooding,
Keith Rundle, Asif Majid, Trevor Davies, en iedereen die bij
OS/2 bij IBM betrokken is.


// Help for Options dialog --------------------------------

HEADER(1, pOPTIONSDIALOG, Dialoogvenster Opties...)
INDEX(1, Dialoogvenster Opties...)
PARAGRAPH()
Gebruik de besturingselementen in dit dialoogvenster om:
LMARGIN(5)
PARAGRAPH()
SQBUL() de toetsen te wijzigen die worden gebruikt om BOLD(Ribble) te verplaatsen
LMARGIN(8)
PARAGRAPH()
De drie mogelijke keuzes zijn:
LMARGIN(10)
PARAGRAPH()
SQBUL() ITALIC(Pijltjes), cursortoetsen.
PARAGRAPH()
SQBUL() ITALIC(Klassiek), waarbij Z = links, X = rechts, ' (apostrof) = omhoog en
/ (schuine streep) = omlaag.
PARAGRAPH()
SQBUL() ITALIC(Anders), wat je maar wilt.
LMARGIN(5)
PARAGRAPH()
SQBUL() verschillende instellingen wijzigen om de prestaties af te stemmen
LMARGIN(8)
PARAGRAPH()
SQBUL() ITALIC(Verversingssnelheid), de vertraging in milliseconden
tussen vensterverversingen.
PARAGRAPH()
SQBUL() ITALIC(Celafmetingen), de grootte van elke cel in het venster.
De standaard is 64x64, voor een cel van 64 bij 64 beeldpunten.
PARAGRAPH()
SQBUL() ITALIC(Zichtbare afmetingen), de grootte van het speelveld
dat in het venster wordt bekeken.  De standaard is 14x14 voor een
zicht van 14 bij 14 cellen.
LMARGIN(1)


// -- Los endos --

ENDDOC()