//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//
// Italian translation
//

#include "document.h"
#include "help.h"


USERDOC()
TITLE(Ribble Information)

// First major heading ---------------------------------------------

HEADER(1, pMAINPANEL, Aiuto generale)
INDEX(1 sortkey='a', Aiuto generale)
PARAGRAPH()
ARTALIGN('..\bitmaps\ribblestatic.bmp', center)
PARAGRAPH()
BOLD(Ribble) e' un clone di Boulder Dash scritto appositamente
per il Presentation Manager di OS/2.
PARAGRAPH()
Seleziona uno dei seguenti collegamenti ipertestuali:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pPLOT, La trama)
LINEBREAK()
SQBUL() LINK(pSELECTINGLEVELS, Selezione dei livelli)
LINEBREAK()
SQBUL() LINK(pEDITINGLEVELS, Modifica dei livelli)
LINEBREAK()
SQBUL() LINK(pKEYS, Tastiera)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licenza)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contattare gli autori)
LINEBREAK()
SQBUL() LINK(pSYSTEM_REQUIREMENTS, Requisiti di sistema e note)
LMARGIN(1)

// Information concerning the plot ----------------------------------

HEADER(1, pPLOT, La trama)
INDEX(1, La trama)
PARAGRAPH()
Lo scopo del gioco e' di LINK(pKEYS, guidare) BOLD(Ribble)
ARTINLINE('..\bitmaps\repr1.bmp', left) attraverso una serie
di livelli, raccogliendo diamanti, uccidendo mostri e
risolvendo puzzle.
PARAGRAPH()
Gli oggetti presenti nei livelli sono divisi in tre gruppi:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Raccoglibili)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Mostri)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Oggetti vari)
LINEBREAK()
LMARGIN(1)
PARAGRAPH()
Ogni livello deve essere completato entro un certo tempo.  Il tempo
rimanente viene visualizzato in alto nell'area di gioco, insieme
al tuo LINK(pSCORING, punteggio), al numero di vite e al
numero di diamanti ancora da raccogliere nel livello corrente.
PARAGRAPH()
Il valore del numero di diamanti rimanenti indica
quanti diamanti, casseforti e gabbie restano da raccogliere.

// Help for Keys ---------------------------------------------------

HEADER(1, pKEYS, Tasti)
INDEXID(1, keyshelp, Tasti)
PARAGRAPH()
Per spostare BOLD(Ribble), usa i seguenti tasti:
LMARGIN(5)
PARAGRAPH()
BOLD(Tasto cursore Su), per andare verso l'alto
LINEBREAK()
LINEBREAK()
BOLD(Tasto cursore Giu'), per andare verso il basso
LINEBREAK()
LINEBREAK()
BOLD(Tasto cursore Sinistra), per andare a sinistra
LINEBREAK()
LINEBREAK()
BOLD(Tasto cursore Destra), per andare a destra
LINEBREAK()
LINEBREAK()
//(The above keys can be changed by selecting the on the BOLD(Options) menu-item
//under the BOLD(Edit) menu.)
//LINEBREAK()
//LINEBREAK()
//BOLD(Return) key, for status report
//LINEBREAK()
//LINEBREAK()
BOLD(Tasto Esc), per ucciderti e ricominciare il livello corrente
da capo.
LINEBREAK()
LINEBREAK()
//BOLD(Shift + Escape) key, to abandon the current level
//LINEBREAK()
//LINEBREAK()
BOLD(Tasto Spazio), per attivare/disattivare la visualizzazione della mappa
LMARGIN(1)
PARAGRAPH()
Gli altri tasti sono descritti nelle sezioni della guida in linea
relative alle aree in cui vengono usati.

// Help for F1 pressed on Help Keys menu item ---------------------

HEADER(2, pKEYSMENUITEM, Guida per la voce di menu Tasti)
PARAGRAPH()
Seleziona la voce di menu BOLD(Tasti) per ottenere aiuto
relativo ai tasti.

// Information concerning map items ----------------------------

HEADER(1, pITEMSHELP, Oggetti&comma. mostri e altre cose)
INDEXID(1, mapitems, Oggetti&comma. mostri e altre cose)
PARAGRAPH()
Oggetti trovati nei vari livelli:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Raccoglibili)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Mostri)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Oggetti vari)
LINEBREAK()
LMARGIN(1)


// Information concerning collectable items ----------------------------

HEADER(2, pITEMS, Raccoglibili)
INDEX(2, Raccoglibili)
PARAGRAPH()
Questi sono gli oggetti raccoglibili che si possono trovare
sparsi per i livelli:
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left)
Terra
LMARGIN(5)
PARAGRAPH()
La terra si trova in quasi tutti i livelli.  Serve come supporto
per i massi e altri oggetti che possono cadere.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left)
Diamante
LMARGIN(5)
PARAGRAPH()
L'obiettivo principale di BOLD(Ribble) e' raccogliere tutti i diamanti
di ogni livello. I diamanti si trovano in questa forma, oppure vengono
creati quando gli spiriti entrano nelle gabbie, oppure raccogliendo
una chiave per aprire le casseforti.  Altro
su questo piu' avanti.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left)
Chiave
LMARGIN(5)
PARAGRAPH()
Quando BOLD(Ribble) raccoglie una chiave, tutte le casseforti ARTINLINE('..\bitmaps\safe.bmp', left)
del livello corrente si trasformano in diamanti che possono essere raccolti.
Attento ai massi o ad altri oggetti che possono cadere posti sopra le casseforti - 
potrebbero scivolare via se la cassaforte si trasforma in un diamante.
LMARGIN(1)

// Information concerning monsters ----------------------------

HEADER(2, pMONSTERS, Mostri)
INDEX(2, Mostri)
PARAGRAPH()
Questi sono i mostri che avrai la sfortuna
di incontrare durante i tuoi giri attraverso i vari
livelli:
PARAGRAPH()
LMARGIN(1)
ARTINLINE('..\bitmaps\egg.bmp', left)
Uovo
LMARGIN(5)
PARAGRAPH()
Se sposti un uovo, si incrinera' e, alla fine,
un mostro Slither uscira' fuori.
PARAGRAPH()
Le uova sono come i massi: scivolano via dalle superfici
curve. Contano anche come oggetti curvi, quindi i massi
e le altre uova scivoleranno via. Le uova non si incrinano
se qualcosa viene lasciato cadere sopra.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\crackedegg.bmp', left)
Uovo incrinato
LMARGIN(5)
PARAGRAPH()
Dopo che un uovo e' stato spostato, c'e' un breve periodo
durante il quale il mostro Slither esce dall'uovo.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left)
Slither
LMARGIN(5)
PARAGRAPH()
Alla fine del periodo di schiusa, uno Slither completamente
cresciuto emerge dall'uovo e inizia il suo unico scopo
nella vita - la tua morte.
PARAGRAPH()
Uno Slither puo' essere ucciso solo da un masso:  facendoglielo
cadere sulla testa, oppure spingendoglielo addosso.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left)
Spirito
LMARGIN(5)
PARAGRAPH()
Gli spiriti sono piccole creature pelose che vagano
alla cieca per i livelli.  Sono letali al contatto,
e devono essere condotti con cura nelle gabbie
ARTINLINE('..\bitmaps\cage.bmp', left) dove
si trasformeranno in diamanti.


// Information concerning miscellaneous items ----------------------------

HEADER(2, pMISCITEMS, Oggetti vari)
INDEX(2, Oggetti vari)
PARAGRAPH()
Questi sono gli oggetti vari che si possono trovare
sparsi per i livelli:

PARAGRAPH()
ARTINLINE('..\bitmaps\boulder.bmp', left)
Masso
LMARGIN(5)
PARAGRAPH()
I massi possono cadere rimuovendo cio' che li sostiene,
oppure spingendoli. Scivolano via dalle superfici curve (comprese
uova e diamanti) e possono essere usati per uccidere
alcuni tipi di mostri.
Essere colpiti da un masso che cade e' di solito fatale.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\teleport.bmp', left)
Teletrasportatore
LMARGIN(5)
PARAGRAPH()
Quando BOLD(Ribble) entra in un teletrasportatore, viene
teletrasportato in un punto diverso del livello corrente.
Una volta usati, i teletrasportatori scompaiono.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\cage.bmp', left)
Gabbia
LMARGIN(5)
PARAGRAPH()
Guida gli spiriti nelle gabbie e si trasformeranno in
diamanti.  Per completare un livello, ogni gabbia deve essere
stata convertita in un diamante.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\safe.bmp', left)
Cassaforte
LMARGIN(5)
PARAGRAPH()
Quando BOLD(Ribble) raccoglie la chiave ARTINLINE('..\bitmaps\key.bmp', left), tutte le
casseforti del livello corrente si trasformano in diamanti.  Come
per le gabbie, devi aver raccolto tutti i diamanti delle casseforti
per completare un livello.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\bomb.bmp', left)
Bomba
LMARGIN(5)
PARAGRAPH()
Le bombe si attivano quando cadono su qualcosa che non sia
terra ARTINLINE('..\bitmaps\earth.bmp', left).  Una volta attiva
ARTINLINE('..\bitmaps\bombli1.bmp', left), hai circa
cinque secondi per metterti al riparo prima che una bomba
esploda
ARTINLINE('..\bitmaps\flame1.bmp', left).
LMARGIN(1)


// Information concerning scoring items ----------------------------

HEADER(2, pSCORING, Punteggio)
INDEX(2, Punteggio)
PARAGRAPH()
I punti vengono guadagnati raccogliendo e uccidendo cose nei livelli, come segue:
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left) 1 punto
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left) 10 punti
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left) 10 punti
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left) + ARTINLINE('..\bitmaps\cage.bmp', left) 25 punti
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left) + ARTINLINE('..\bitmaps\boulder.bmp', left)  50 punti


// Information selecting levels ----------------------------

HEADER(1, pSELECTINGLEVELS, Selezione dei livelli)
INDEXID(1, selectlevel, Selezione dei livelli)
PARAGRAPH()
Quando completi un livello, passi automaticamente a quello
successivo.  Se vuoi andare direttamente a un livello particolare,
allora puoi usare la
LINK(pSELECTLEVEL, finestra di selezione del livello) che si apre
quando selezioni la voce di menu
BOLD(Apri...) sotto il menu BOLD(Gioco).


// Help for the select level dialog --------------------------------

HEADER(2, pSELECTLEVEL, Finestra di dialogo Apri... livello)
INDEX(2, Finestra di dialogo Apri... livello)
PARAGRAPH()
Usa questa finestra di dialogo per selezionare il livello che vuoi giocare.


// Editing levels ----------------------------

HEADER(1, pEDITINGLEVELS, Modifica dei livelli)
INDEX(1, Modifica dei livelli)
PARAGRAPH()
Seleziona la voce di menu BOLD(Livello...) sotto il sottomenu BOLD(Editor di mappa) del
menu BOLD(Opzioni) in qualsiasi momento mentre stai giocando a un livello. La finestra di BOLD(Ribble) si espandera'
orizzontalmente e una tavolozza di tutti gli oggetti di gioco disponibili
apparira' sul lato destro della finestra.
PARAGRAPH()
BOLD(Ribble) sara' sostituito da un cursore a mirino
ARTINLINE('..\bitmaps\edit.bmp', center) che indica
quale cella della mappa vuoi modificare.  I soliti tasti di
BOLD(Ribble) si applicano durante la modifica e tutte le creature
vengono fermate.
PARAGRAPH()
ITALIC(Aggiunta di oggetti all'area di gioco)
LMARGIN(3)
PARAGRAPH()
Fai clic su un oggetto della tavolozza per selezionarlo.  L'oggetto
della tavolozza attualmente selezionato viene visualizzato accanto alla
didascalia BOLD(Corrente >>) sopra la tavolozza.
PARAGRAPH()
Premendo il tasto BOLD(Invio) si posizionera' l'oggetto selezionato
sotto il mirino nell'area di gioco.
PARAGRAPH()
Quando posizioni una creatura sulla mappa, non diventa viva
finche' non esci dalla modalita' di modifica.
LMARGIN(1)
PARAGRAPH()
ITALIC(Rimozione delle creature dalla mappa)
LMARGIN(3)
PARAGRAPH()
Posiziona il mirino in modo che si sovrapponga alla creatura
e premi il tasto BOLD(Canc).  La creatura verra' rimossa.
PARAGRAPH()
Nota che oggetti come spiriti e teletrasportatori che
posizioni nell'area di gioco non diventano creature
vere e proprie finche' non esci dalla modalita' di modifica.
LMARGIN(1)
PARAGRAPH()
ITALIC(Impostazione delle destinazioni dei teletrasportatori)
LMARGIN(3)
PARAGRAPH()
Ogni teletrasportatore ha una destinazione associata.
Queste destinazioni sono contrassegnate da un numero bianco su
uno sfondo blu e sono sovrapposte a qualunque oggetto
si trovi a destinazione.
PARAGRAPH()
Oltre al contrassegno di posizione, i teletrasportatori
hanno anche un numero bianco su rosso impresso
cosi' puoi sapere quale contrassegno di destinazione e' associato
a quale teletrasportatore.
PARAGRAPH()
Per spostare un contrassegno di destinazione, posiziona il mirino
sopra di esso e premi il tasto BOLD(Ins).  Se ora sposti il mirino,
il numero lo seguira'.  Premi il tasto BOLD(Invio) per posare il
numero nella nuova posizione.
LMARGIN(1)
PARAGRAPH()
Vedi anche:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pSAVINGLEVELS, Salvataggio dei livelli)
LMARGIN(1)


// Saving levels ----------------------------

HEADER(1, pSAVINGLEVELS, Salvataggio dei livelli)
INDEXID(1, saving, Salvataggio dei livelli)
PARAGRAPH()
Mentre giochi o modifichi un livello, puoi salvare l'attuale
area di gioco in un file di livello.
PARAGRAPH()
Usa la voce di menu BOLD(Salva...) sotto il menu BOLD(Gioco)
per aprire una LINK(pSAVELEVELAS, finestra di dialogo) con cui
puoi salvare il tuo livello.

// Save level dialog ----------------------------

HEADER(2, pSAVELEVELAS, Finestra di dialogo di salvataggio livello)
INDEX(2, Finestra di dialogo di salvataggio livello)
PARAGRAPH()
Questa finestra di dialogo ti permette di compilare varie informazioni
sul livello che stai per salvare.
PARAGRAPH()
Fai clic sul pulsante BOLD(OK) per salvare il livello e le
informazioni associate, oppure su BOLD(Annulla) per chiudere la
finestra di dialogo senza salvare il livello.
PARAGRAPH()
Nota la casella di selezione del numero di livello in fondo alla
finestra di dialogo. Questo numero indica la posizione nella sequenza
di gioco dei livelli.  Affinche' BOLD(Ribble) usi i tuoi livelli,
devono essere numerati consecutivamente a partire da uno (1) in su.
Puoi usare la finestra di selezione del livello per scoprire
il livello con il numero piu' alto, oppure guardare nella cartella
"levels" contenuta nella directory dell'eseguibile di BOLD(Ribble).



// Help for the product information dialog ------------------------

HEADER(1, pPRODUCTINFO, Informazioni sul prodotto)
INDEXID(1, productinfo, Informazioni sul prodotto)
PARAGRAPH()
Ribble e' Copyright (c)1993, 1994 di J.R.Shannon e
D.J.Neades.  Tutti i diritti riservati.
PARAGRAPH()
Vedi anche:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pDISCLAIMER, Negazione di responsabilita')
LINEBREAK()
SQBUL() LINK(pLICENCE, Licenza)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contattare gli autori)
LINEBREAK()
SQBUL() LINK(pGREETINGS, Saluti)
LMARGIN(1)
PARAGRAPH()
Tutti i marchi registrati sono riconosciuti.

// System requirements and notes --------------------------------

HEADER(2, pSYSTEM_REQUIREMENTS, Requisiti di sistema e note)
INDEX(2, Requisiti di sistema e note)
PARAGRAPH()
BOLD(Ribble) e' un gioco che richiede molta CPU e grafica.  L'area
di gioco viene aggiornata molte volte al secondo, quindi, affinche'
BOLD(Ribble) giri in modo accettabile sulla tua macchina, tieni
conto dei seguenti punti:
PARAGRAPH()
Piu' veloce e' il processore, meglio e'.  BOLD(Ribble) e' stato scritto
su un 486DX33, un 486DX50 e un P60, quindi le prestazioni su questi
processori sono soddisfacenti (soprattutto sull'ultimo!).
PARAGRAPH()
Poiche' la tecnica di rendering impiegata da BOLD(Ribble) consiste
nel blittare una bitmap abbastanza grande sullo schermo molte volte
al secondo, BOLD(Ribble) girera' notevolmente meglio su sistemi
con schede grafiche Local Bus o PCI che su quelli
con schede ISA (anche accelerate).  Entrambi i 486 usati
nello sviluppo di BOLD(Ribble) avevano schede ISA e il P60 aveva
una #9GXE + bus PCI.
PARAGRAPH()
Puoi regolare le prestazioni selezionando la voce di menu BOLD(Opzioni...)
sotto il sottomenu BOLD(Editor di mappa) del menu BOLD(Opzioni) e
modificando le impostazioni contenute nella
LINK(pOPTIONSDIALOG, finestra di dialogo) che viene visualizzata.


// Information concerning licencing ----------------------------

HEADER(2, pLICENCE, Licenza)
INDEX(2, Licenza)
ARTALIGN('..\bitmaps\tribble-normal.bmp', center)
PARAGRAPH()
BOLD(Ribble) e' Tribbleware.  Cio' significa che se ti piace,
e ci giochi mentre il tuo capo esce a fumare una
sigaretta, dovresti sentirti in qualche modo
obbligato a mandarci una di quelle cose pelose tipo Tribble
con le antenne, gli occhi ondeggianti e un motto
divertente come coda...  In mancanza di cio', andrebbe bene
anche una cartolina.
PARAGRAPH()
Gli utenti interessati a progettare grafica migliore, livelli,
o ad aggiungere altre funzioni al gioco sono invitati
a contattarci.  Piccole melodie .BOLD(MID) irritanti
che possiamo eseguire con MMPM/2 sarebbero molto utili.


// Information concerning contacting the authors  -------------------------

HEADER(2, pCONTAUTHOR, Contattare gli autori)
INDEX(2, Contattare gli autori)
PARAGRAPH()
Gli autori possono essere contattati su Internet come:
LMARGIN(5)
PARAGRAPH()
BOLD(jrs@larch.demon.co.uk),
LMARGIN(2)
PARAGRAPH()
o (per i Tribble, ecc.),
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
Inghilterra
LMARGIN(1)

// Help for Disclaimer -------------------------------

HEADER(2, pDISCLAIMER, Negazione di responsabilita')
INDEX(2, Negazione di responsabilita')
PARAGRAPH()
Questo prodotto viene fornito senza alcuna garanzia, esplicita o implicita.
Gli autori (Daniel J Neades e Jason R Shannon) non
accettano alcuna responsabilita' per eventuali conseguenze avverse che
possano derivare dall'uso o dall'abuso di BOLD(Ribble) o del suo
programma e dei relativi file di dati associati. Tali conseguenze avverse
includono, ma non sono limitate a, perdita di profitto e perdita
di dati.
PARAGRAPH()
Gli autori declinano specificamente tutte le garanzie, esplicite o
implicite, incluse ma non limitate a, qualsiasi garanzia implicita di
commerciabilita' o idoneita' a uno scopo particolare.
PARAGRAPH()
Ecco, l'abbiamo detto!

// Help for Greetings --------------------------------

HEADER(2, pGREETINGS, Saluti)
PARAGRAPH()
In nessun ordine particolare, saluti a:
LMARGIN(5)
PARAGRAPH()
Alan Garde, Jarod Nash, Bob Eager, Mark Hanlon, Steve Wooding,
Keith Rundle, Asif Majid, Trevor Davies, e a tutti coloro
che hanno a che fare con OS/2 in IBM.


// Help for Options dialog --------------------------------

HEADER(1, pOPTIONSDIALOG, Finestra di dialogo Opzioni...)
INDEX(1, Finestra di dialogo Opzioni...)
PARAGRAPH()
Usa i controlli di questa finestra di dialogo per:
LMARGIN(5)
PARAGRAPH()
SQBUL() modificare i tasti usati per spostare BOLD(Ribble)
LMARGIN(8)
PARAGRAPH()
Le tre possibili scelte sono:
LMARGIN(10)
PARAGRAPH()
SQBUL() ITALIC(Frecce), tasti cursore.
PARAGRAPH()
SQBUL() ITALIC(Classico), dove Z = sinistra, X = destra, ' (apostrofo) = su e
/ (barra) = giu'.
PARAGRAPH()
SQBUL() ITALIC(Altro), come preferisci.
LMARGIN(5)
PARAGRAPH()
SQBUL() modificare varie impostazioni per regolare le prestazioni
LMARGIN(8)
PARAGRAPH()
SQBUL() ITALIC(Frequenza di aggiornamento), il ritardo in millisecondi
tra gli aggiornamenti della finestra.
PARAGRAPH()
SQBUL() ITALIC(Dimensioni celle), la dimensione di ogni cella
nella finestra. Il valore predefinito e' 64x64, ovvero una cella
di 64 per 64 pel.
PARAGRAPH()
SQBUL() ITALIC(Dimensioni visibili), la dimensione dell'area di gioco
visualizzata nella finestra.  Il valore predefinito e' 14x14 per una
vista di 14 per 14 celle.
LMARGIN(1)


// -- Los endos --

ENDDOC()