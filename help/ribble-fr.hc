//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//
// French translation
//

#include "document.h"
#include "help.h"


USERDOC()
TITLE(Ribble Information)

// First major heading ---------------------------------------------

HEADER(1, pMAINPANEL, Aide generale)
INDEX(1 sortkey='a', Aide generale)
PARAGRAPH()
ARTALIGN('..\bitmaps\ribblestatic.bmp', center)
PARAGRAPH()
BOLD(Ribble) est un clone de Boulder Dash ecrit specialement
pour le Presentation Manager d'OS/2.
PARAGRAPH()
Selectionnez l'un des hyperliens suivants:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pPLOT, Le synopsis)
LINEBREAK()
SQBUL() LINK(pSELECTINGLEVELS, Choix des niveaux)
LINEBREAK()
SQBUL() LINK(pEDITINGLEVELS, Edition des niveaux)
LINEBREAK()
SQBUL() LINK(pKEYS, Clavier)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licence)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contacter les auteurs)
LINEBREAK()
SQBUL() LINK(pSYSTEM_REQUIREMENTS, Configuration requise et remarques)
LMARGIN(1)

// Information concerning the plot ----------------------------------

HEADER(1, pPLOT, Le synopsis)
INDEX(1, Le synopsis)
PARAGRAPH()
Le but du jeu est de LINK(pKEYS, guider) BOLD(Ribble)
ARTINLINE('..\bitmaps\repr1.bmp', left) a travers une serie
de niveaux, en ramassant des diamants, en tuant des monstres et
en resolvant des enigmes.
PARAGRAPH()
Les objets presents dans les niveaux sont divises en trois groupes:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Objets a ramasser)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monstres)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Objets divers)
LINEBREAK()
LMARGIN(1)
PARAGRAPH()
Chaque niveau doit etre termine dans un temps limite.  Le temps
restant est affiche en haut de la zone de jeu, a cote de
votre LINK(pSCORING, score), du nombre de vies et du nombre
de diamants restants sur le niveau en cours.
PARAGRAPH()
La valeur du nombre de diamants restants indique combien
de diamants, de coffres et de cages restent a ramasser.

// Help for Keys ---------------------------------------------------

HEADER(1, pKEYS, Touches)
INDEXID(1, keyshelp, Touches)
PARAGRAPH()
Pour deplacer BOLD(Ribble), utilisez les touches suivantes:
LMARGIN(5)
PARAGRAPH()
BOLD(Touche de curseur Haut), pour monter
LINEBREAK()
LINEBREAK()
BOLD(Touche de curseur Bas), pour descendre
LINEBREAK()
LINEBREAK()
BOLD(Touche de curseur Gauche), pour aller a gauche
LINEBREAK()
LINEBREAK()
BOLD(Touche de curseur Droite), pour aller a droite
LINEBREAK()
LINEBREAK()
//(The above keys can be changed by selecting the on the BOLD(Options) menu-item
//under the BOLD(Edit) menu.)
//LINEBREAK()
//LINEBREAK()
//BOLD(Return) key, for status report
//LINEBREAK()
//LINEBREAK()
BOLD(Touche Echap), pour vous suicider et recommencer le niveau
en cours depuis le debut.
LINEBREAK()
LINEBREAK()
//BOLD(Shift + Escape) key, to abandon the current level
//LINEBREAK()
//LINEBREAK()
BOLD(Touche Espace), pour afficher ou masquer la carte
LMARGIN(1)
PARAGRAPH()
Les autres touches sont decrites dans les sections d'aide en ligne
des domaines ou elles s'appliquent.

// Help for F1 pressed on Help Keys menu item ---------------------

HEADER(2, pKEYSMENUITEM, Aide pour l'element de menu Touches)
PARAGRAPH()
Selectionnez l'element de menu BOLD(Touches) pour obtenir de l'aide
relative aux touches.

// Information concerning map items ----------------------------

HEADER(1, pITEMSHELP, Objets&comma. monstres et autres choses)
INDEXID(1, mapitems, Objets&comma. monstres et autres choses)
PARAGRAPH()
Objets trouves sur les differents niveaux:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Objets a ramasser)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monstres)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Objets divers)
LINEBREAK()
LMARGIN(1)


// Information concerning collectable items ----------------------------

HEADER(2, pITEMS, Objets a ramasser)
INDEX(2, Objets a ramasser)
PARAGRAPH()
Ce sont les objets ramassables que l'on trouve eparpilles
sur les niveaux:
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left)
Terre
LMARGIN(5)
PARAGRAPH()
La terre se trouve sur a peu pres tous les niveaux.  Elle sert de
support aux rochers et autres objets pouvant tomber.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left)
Diamant
LMARGIN(5)
PARAGRAPH()
Le but principal de BOLD(Ribble) est de ramasser tous les diamants de chaque
niveau. Les diamants se trouvent soit sous cette forme, soit sont
crees lorsque les esprits entrent dans des cages, soit en ramassant
une cle pour ouvrir les coffres.  Nous y
reviendrons plus loin.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left)
Cle
LMARGIN(5)
PARAGRAPH()
Lorsque BOLD(Ribble) ramasse une cle, tous les coffres ARTINLINE('..\bitmaps\safe.bmp', left)
du niveau en cours sont convertis en diamants que l'on peut ensuite ramasser.
Attention aux rochers ou autres objets susceptibles de tomber poses sur les coffres - 
ils peuvent glisser si le coffre se transforme en diamant.
LMARGIN(1)

// Information concerning monsters ----------------------------

HEADER(2, pMONSTERS, Monstres)
INDEX(2, Monstres)
PARAGRAPH()
Ce sont les monstres que vous aurez le malheur
de rencontrer au cours de vos peregrinations dans les
differents niveaux:
PARAGRAPH()
LMARGIN(1)
ARTINLINE('..\bitmaps\egg.bmp', left)
Oeuf
LMARGIN(5)
PARAGRAPH()
Si vous dechaussez un oeuf, il se fissurera et, finalement,
un monstre Slither en sortira.
PARAGRAPH()
Les oeufs sont comme les rochers: ils glissent des surfaces
courbes. Ils comptent egalement comme objets courbes, de sorte que
les rochers et autres oeufs glissent dessus. Les oeufs ne se fissurent
pas si quelque chose tombe dessus.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\crackedegg.bmp', left)
Oeuf fissure
LMARGIN(5)
PARAGRAPH()
Apres qu'un oeuf a ete dechausse, il y a une courte
periode pendant laquelle le monstre Slither sort de l'oeuf.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left)
Slither
LMARGIN(5)
PARAGRAPH()
A la fin de la periode d'eclosion, un Slither adulte
sort de son oeuf et commence son unique but dans la vie - votre mort.
PARAGRAPH()
Un Slither ne peut etre tue que par un rocher:  soit
en lui en faisant tomber un sur la tete, soit en lui en poussant un.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left)
Esprit
LMARGIN(5)
PARAGRAPH()
Les esprits sont de petites creatures duveteuses qui errent
aveuglement dans les niveaux.  Ils sont mortels au toucher,
et doivent etre soigneusement achemines vers des cages
ARTINLINE('..\bitmaps\cage.bmp', left) ou
ils se transformeront en diamants.


// Information concerning miscellaneous items ----------------------------

HEADER(2, pMISCITEMS, Objets divers)
INDEX(2, Objets divers)
PARAGRAPH()
Ce sont les objets divers que l'on trouve eparpilles
sur les niveaux:

PARAGRAPH()
ARTINLINE('..\bitmaps\boulder.bmp', left)
Rocher
LMARGIN(5)
PARAGRAPH()
Les rochers peuvent etre dechausses en retirant ce qui les soutient,
ou en les poussant. Ils glissent sur les surfaces courbes (y compris
les oeufs et les diamants) et peuvent servir a tuer certains
types de monstres.
Etre frappe par un rocher qui tombe est generalement mortel.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\teleport.bmp', left)
Teleporteur
LMARGIN(5)
PARAGRAPH()
Lorsque BOLD(Ribble) entre dans un teleporteur, il est teleporte
vers un autre endroit du niveau en cours.  Une fois utilises,
les teleporteurs disparaissent.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\cage.bmp', left)
Cage
LMARGIN(5)
PARAGRAPH()
Acheminez les esprits vers les cages et ils se transformeront en
diamants.  Pour terminer un niveau, chaque cage doit avoir ete
convertie en diamant.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\safe.bmp', left)
Coffre
LMARGIN(5)
PARAGRAPH()
Lorsque BOLD(Ribble) ramasse la cle ARTINLINE('..\bitmaps\key.bmp', left), tous les
coffres du niveau en cours sont convertis en diamants.  Comme pour
les cages, vous devez avoir ramasse tous les diamants des coffres
pour terminer un niveau.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\bomb.bmp', left)
Bombe
LMARGIN(5)
PARAGRAPH()
Les bombes s'activent lorsqu'elles tombent sur autre chose que
de la terre ARTINLINE('..\bitmaps\earth.bmp', left).  Une fois activee
ARTINLINE('..\bitmaps\bombli1.bmp', left), vous disposez d'environ
cinq secondes pour vous ecarter avant qu'une bombe
ne detone
ARTINLINE('..\bitmaps\flame1.bmp', left).
LMARGIN(1)


// Information concerning scoring items ----------------------------

HEADER(2, pSCORING, Score)
INDEX(2, Score)
PARAGRAPH()
Des points sont gagnes en ramassant et en tuant des choses sur les niveaux, comme suit:
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left) 1 point
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left) 10 points
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left) 10 points
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left) + ARTINLINE('..\bitmaps\cage.bmp', left) 25 points
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left) + ARTINLINE('..\bitmaps\boulder.bmp', left)  50 points


// Information selecting levels ----------------------------

HEADER(1, pSELECTINGLEVELS, Choix des niveaux)
INDEXID(1, selectlevel, Choix des niveaux)
PARAGRAPH()
Lorsque vous terminez un niveau, vous passez automatiquement
au suivant.  Si vous voulez aller directement a un niveau
particulier, vous pouvez utiliser la
LINK(pSELECTLEVEL, boite de dialogue de choix de niveau) affichee
lorsque vous selectionnez l'element de menu
BOLD(Ouvrir...) sous le menu BOLD(Jeu).


// Help for the select level dialog --------------------------------

HEADER(2, pSELECTLEVEL, Boite de dialogue Ouvrir... niveau)
INDEX(2, Boite de dialogue Ouvrir... niveau)
PARAGRAPH()
Utilisez cette boite de dialogue pour selectionner le niveau que vous
souhaitez jouer.


// Editing levels ----------------------------

HEADER(1, pEDITINGLEVELS, Edition des niveaux)
INDEX(1, Edition des niveaux)
PARAGRAPH()
Selectionnez l'element de menu BOLD(Niveau...) sous le sous-menu BOLD(Editeur de carte) du
menu BOLD(Options) a tout moment pendant que vous jouez a un niveau. La fenetre de BOLD(Ribble) s'etendra
horizontalement, et une palette de tous les objets disponibles du jeu
apparaitra sur le cote droit de la fenetre.
PARAGRAPH()
BOLD(Ribble) sera remplace par un curseur en croix
ARTINLINE('..\bitmaps\edit.bmp', center) qui indique
quelle cellule de la carte vous voulez modifier.  Les touches habituelles
de BOLD(Ribble) restent actives pendant l'edition, et toutes les
creatures sont arretees.
PARAGRAPH()
ITALIC(Ajout d'objets a la zone de jeu)
LMARGIN(3)
PARAGRAPH()
Cliquez sur un objet de la palette pour le selectionner.  L'objet
de palette actuellement selectionne est affiche a cote de la legende
BOLD(Actuel >>) au-dessus de la palette.
PARAGRAPH()
Appuyer sur la touche BOLD(Entree) placera l'objet selectionne
sous le curseur en croix dans la zone de jeu.
PARAGRAPH()
Lorsque vous placez une creature sur la carte, elle ne devient vivante
que lorsque vous quittez le mode edition.
LMARGIN(1)
PARAGRAPH()
ITALIC(Suppression de creatures de la carte)
LMARGIN(3)
PARAGRAPH()
Positionnez le curseur en croix de maniere a ce qu'il chevauche la
creature, et appuyez sur la touche BOLD(Suppr).  La creature sera
supprimee.
PARAGRAPH()
A noter que les objets tels que les esprits et les teleporteurs
que vous placez sur la zone de jeu ne deviennent des creatures
qu'une fois que vous quittez le mode edition.
LMARGIN(1)
PARAGRAPH()
ITALIC(Definition des destinations des teleporteurs)
LMARGIN(3)
PARAGRAPH()
Chaque teleporteur possede une destination associee.
Ces destinations sont marquees d'un numero blanc sur un
fond bleu et se superposent a tout objet se trouvant
a la destination.
PARAGRAPH()
En plus du marqueur d'emplacement, les teleporteurs
portent egalement un numero blanc sur rouge estampille
afin que vous sachiez quel marqueur de destination est associe
a quel teleporteur.
PARAGRAPH()
Pour deplacer un marqueur de destination, positionnez le curseur en
croix dessus et appuyez sur la touche BOLD(Inser).  Si vous deplacez
alors le curseur en croix, le numero suivra.  Appuyez sur la touche
BOLD(Entree) pour deposer le numero a son nouvel emplacement.
LMARGIN(1)
PARAGRAPH()
Voir aussi:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pSAVINGLEVELS, Enregistrement des niveaux)
LMARGIN(1)


// Saving levels ----------------------------

HEADER(1, pSAVINGLEVELS, Enregistrement des niveaux)
INDEXID(1, saving, Enregistrement des niveaux)
PARAGRAPH()
Pendant que vous jouez ou editez un niveau, vous pouvez enregistrer
la zone de jeu actuelle dans un fichier de niveau.
PARAGRAPH()
Utilisez l'element de menu BOLD(Enregistrer...) sous le menu BOLD(Jeu)
pour ouvrir une LINK(pSAVELEVELAS, boite de dialogue) avec laquelle
vous pouvez enregistrer votre niveau.

// Save level dialog ----------------------------

HEADER(2, pSAVELEVELAS, Boite de dialogue d'enregistrement de niveau)
INDEX(2, Boite de dialogue d'enregistrement de niveau)
PARAGRAPH()
Cette boite de dialogue vous permet de renseigner diverses
informations sur le niveau que vous allez enregistrer.
PARAGRAPH()
Cliquez sur le bouton BOLD(OK) pour enregistrer le niveau et les
informations associees, ou sur BOLD(Annuler) pour fermer la boite
de dialogue sans enregistrer le niveau.
PARAGRAPH()
Notez la boite de saisie numerique du numero de niveau en bas de
la boite de dialogue. Ce numero indique la position dans la sequence
de jeu des niveaux. Pour que BOLD(Ribble) utilise vos niveaux,
ils doivent etre numerotes sequentiellement a partir de un (1).  Vous
pouvez utiliser la boite de dialogue de choix de niveau pour connaitre
le niveau numerote le plus eleve, ou regarder dans le repertoire
"levels" contenu dans le repertoire de l'executable de BOLD(Ribble).



// Help for the product information dialog ------------------------

HEADER(1, pPRODUCTINFO, Informations sur le produit)
INDEXID(1, productinfo, Informations sur le produit)
PARAGRAPH()
Ribble est Copyright (c)1993, 1994 par J.R.Shannon et
D.J.Neades.  Tous droits reserves.
PARAGRAPH()
Voir aussi:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pDISCLAIMER, Clause de non-responsabilite)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licence)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contacter les auteurs)
LINEBREAK()
SQBUL() LINK(pGREETINGS, Salutations)
LMARGIN(1)
PARAGRAPH()
Toutes les marques deposees sont reconnues.

// System requirements and notes --------------------------------

HEADER(2, pSYSTEM_REQUIREMENTS, Configuration requise et remarques)
INDEX(2, Configuration requise et remarques)
PARAGRAPH()
BOLD(Ribble) est un jeu intensif en CPU et en graphisme.  La zone
de jeu est mise a jour plusieurs fois par seconde; pour que BOLD(Ribble)
fonctionne convenablement sur votre machine, vous devez
tenir compte des points suivants:
PARAGRAPH()
Plus votre processeur est rapide, mieux c'est.  BOLD(Ribble) a ete ecrit
sur un 486DX33, un 486DX50 et un P60; les performances sur ces
processeurs sont donc satisfaisantes (surtout sur le dernier!).
PARAGRAPH()
Etant donne que la technique de rendu employee par BOLD(Ribble) consiste
a blitter une bitmap assez grande a l'ecran plusieurs fois par seconde,
BOLD(Ribble) fonctionnera nettement mieux sur les systemes equipes de
cartes graphiques de bus local ou PCI que sur ceux equipes de cartes
ISA (meme accelerees).  Les deux 486 utilises pour le developpement de
BOLD(Ribble) avaient des cartes ISA, et le P60 avait
une #9GXE + bus PCI.
PARAGRAPH()
Vous pouvez regler les performances en selectionnant l'element de menu
BOLD(Options...) sous le sous-menu BOLD(Editeur de carte) du menu BOLD(Options)
et en modifiant les parametres contenus dans
la LINK(pOPTIONSDIALOG, boite de dialogue) qui s'affiche.


// Information concerning licencing ----------------------------

HEADER(2, pLICENCE, Licence)
INDEX(2, Licence)
ARTALIGN('..\bitmaps\tribble-normal.bmp', center)
PARAGRAPH()
BOLD(Ribble) est un Tribbleware.  Cela signifie que si vous l'aimez,
et y jouez pendant que votre patron sort fumer une
cigarette, vous devriez vous sentir plus ou moins
oblige de nous envoyer une de ces creatures Tribble
poilues avec des antennes, des yeux qui ballotent et une
devise amusante en guise de queue...  A defaut, une carte postale
serait la bienvenue.
PARAGRAPH()
Les utilisateurs souhaitant concevoir de meilleurs graphismes, niveaux,
ou ajouter d'autres fonctions au jeu sont invites a
nous contacter.  De petites ritournelles .BOLD(MID) agacantes que nous
pourrions lire avec MMPM/2 seraient tres utiles.


// Information concerning contacting the authors  -------------------------

HEADER(2, pCONTAUTHOR, Contacter les auteurs)
INDEX(2, Contacter les auteurs)
PARAGRAPH()
Les auteurs sont joignables sur Internet a:
LMARGIN(5)
PARAGRAPH()
BOLD(jrs@larch.demon.co.uk),
LMARGIN(2)
PARAGRAPH()
ou (pour les Tribbles, etc.),
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
Angleterre
LMARGIN(1)

// Help for Disclaimer -------------------------------

HEADER(2, pDISCLAIMER, Clause de non-responsabilite)
INDEX(2, Clause de non-responsabilite)
PARAGRAPH()
Ce produit est fourni sans aucune garantie, expresse ou implicite.
Les auteurs (Daniel J Neades et Jason R Shannon) declinent
toute responsabilite pour les consequences defavorables pouvant
resulter de l'utilisation ou d'une mauvaise utilisation de BOLD(Ribble)
ou de son programme et de ses fichiers de donnees associes. Ces
consequences defavorables incluent, sans s'y limiter, la perte
de profit et la perte de donnees.
PARAGRAPH()
Les auteurs declinent expressement toutes les garanties, expresses ou
implicites, y compris, sans s'y limiter, toute garantie implicite de
qualite marchande ou d'adequation a un usage particulier.
PARAGRAPH()
Voila, nous l'avons dit!

// Help for Greetings --------------------------------

HEADER(2, pGREETINGS, Salutations)
PARAGRAPH()
Sans ordre particulier, salutations a:
LMARGIN(5)
PARAGRAPH()
Alan Garde, Jarod Nash, Bob Eager, Mark Hanlon, Steve Wooding,
Keith Rundle, Asif Majid, Trevor Davies, et a tous ceux qui ont
participe a OS/2 chez IBM.


// Help for Options dialog --------------------------------

HEADER(1, pOPTIONSDIALOG, Boite de dialogue Options...)
INDEX(1, Boite de dialogue Options...)
PARAGRAPH()
Utilisez les controles de cette boite de dialogue pour:
LMARGIN(5)
PARAGRAPH()
SQBUL() modifier les touches utilisees pour deplacer BOLD(Ribble)
LMARGIN(8)
PARAGRAPH()
Les trois choix possibles sont:
LMARGIN(10)
PARAGRAPH()
SQBUL() ITALIC(Fleches), les touches de curseur.
PARAGRAPH()
SQBUL() ITALIC(Classique), ou Z = gauche, X = droite, ' (apostrophe) = haut et
/ (barre oblique) = bas.
PARAGRAPH()
SQBUL() ITALIC(Autre), ce que vous voulez.
LMARGIN(5)
PARAGRAPH()
SQBUL() modifier divers parametres afin de regler les performances
LMARGIN(8)
PARAGRAPH()
SQBUL() ITALIC(Cadence de rafraichissement), le delai en millisecondes
entre les rafraichissements de la fenetre.
PARAGRAPH()
SQBUL() ITALIC(Dimensions des cellules), la taille de chaque cellule
dans la fenetre. La valeur par defaut est 64x64, soit une cellule de
64 pel par 64 pel.
PARAGRAPH()
SQBUL() ITALIC(Dimensions visibles), la taille de la zone de jeu
affichee dans la fenetre.  La valeur par defaut est 14x14, soit une
vue de 14 cellules par 14 cellules.
LMARGIN(1)


// -- Los endos --

ENDDOC()