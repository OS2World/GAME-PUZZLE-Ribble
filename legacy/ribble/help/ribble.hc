//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "document.h"
#include "help.h"


USERDOC()
TITLE(Ribble Information)

// First major heading ---------------------------------------------

HEADER(1, pMAINPANEL, General help)
INDEX(1 sortkey='a', General help)
PARAGRAPH()
ARTALIGN('..\bitmaps\ribblestatic.bmp', center)
PARAGRAPH()
BOLD(Ribble) is a Boulder-dash clone written specifically
for OS/2's Presentation Manager.
PARAGRAPH()
Select one of the following hyperlinks:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pPLOT, The plot)
LINEBREAK()
SQBUL() LINK(pSELECTINGLEVELS, Selecting levels)
LINEBREAK()
SQBUL() LINK(pEDITINGLEVELS, Editing levels)
LINEBREAK()
SQBUL() LINK(pKEYS, Keyboard)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licencing)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contacting the Authors)
LINEBREAK()
SQBUL() LINK(pSYSTEM_REQUIREMENTS, System requirements and notes)
LMARGIN(1)

// Information concerning the plot ----------------------------------

HEADER(1, pPLOT, The plot)
INDEX(1, The plot)
PARAGRAPH()
The aim of the game is to LINK(pKEYS, guide) BOLD(Ribble)
ARTINLINE('..\bitmaps\repr1.bmp', left) around a number
of levels, collecting diamonds, killing monsters, and
solving puzzles.
PARAGRAPH()
The items found on the levels are divided into three groups:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Collectables)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monsters)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Miscellaneous Items)
LINEBREAK()
LMARGIN(1)
PARAGRAPH()
Each level must be completed within a certain time.  The time
remaining is displayed at the top of the playing area along with
your LINK(pSCORING, score), number of lives, and the number of
diamonds remaining on the current level.
PARAGRAPH()
The value for the number of diamonds remaining indicates how
many diamonds, safes, and cages remain to be collected.

// Help for Keys ---------------------------------------------------

HEADER(1, pKEYS, Keys)
INDEXID(1, keyshelp, Keys)
PARAGRAPH()
To move BOLD(Ribble) around, use the following keys:
LMARGIN(5)
PARAGRAPH()
BOLD(Up cursor) key, to move up
LINEBREAK()
LINEBREAK()
BOLD(Down Cursor) key, to move down
LINEBREAK()
LINEBREAK()
BOLD(Left Cursor) key, to move left
LINEBREAK()
LINEBREAK()
BOLD(Right Cursor) key, to move right
LINEBREAK()
LINEBREAK()
//(The above keys can be changed by selecting the on the BOLD(Options) menu-item
//under the BOLD(Edit) menu.)
//LINEBREAK()
//LINEBREAK()
//BOLD(Return) key, for status report
//LINEBREAK()
//LINEBREAK()
BOLD(Escape) key, to kill yourself, and restart the current level
from scratch.
LINEBREAK()
LINEBREAK()
//BOLD(Shift + Escape) key, to abandon the current level
//LINEBREAK()
//LINEBREAK()
BOLD(Space) key, to toggle the map display on/off
LMARGIN(1)
PARAGRAPH()
Other keys are described in the on-line help sections
for the areas where they are applicable.

// Help for F1 pressed on Help Keys menu item ---------------------

HEADER(2, pKEYSMENUITEM, Help for keys menu-item)
PARAGRAPH()
Select the BOLD(Keys) menu-item for help relating
to keys.

// Information concerning map items ----------------------------

HEADER(1, pITEMSHELP, Goodies&comma. Monsters&comma. and other Things)
INDEXID(1, mapitems, Goodies&comma. Monsters&comma. and other Things)
PARAGRAPH()
Items found on the various levels:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Collectables)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monsters)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Miscellaneous Items)
LINEBREAK()
LMARGIN(1)


// Information concerning collectable items ----------------------------

HEADER(2, pITEMS, Collectables)
INDEX(2, Collectables)
PARAGRAPH()
These are the collectable items that can be found scattered around
the levels:
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left)
Earth
LMARGIN(5)
PARAGRAPH()
Earth is found on just about all the levels.  It acts as a support
for boulders and other droppable objects.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left)
Diamond
LMARGIN(5)
PARAGRAPH()
BOLD(Ribble)'s primary goal is to collect all the diamonds on each level.
Diamonds are either found in this form, or are created by spirits
entering cages, or by collecting a key to unlock the safes.  More
on these later.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left)
Key
LMARGIN(5)
PARAGRAPH()
When BOLD(Ribble) picks up a key, all the safes ARTINLINE('..\bitmaps\safe.bmp', left)
on the current level are converted into diamonds which can then be collected.
Beware of boulders or other droppable objects perched on top of safes - they
might slide off if the safe changes into a diamond.
LMARGIN(1)

// Information concerning monsters ----------------------------

HEADER(2, pMONSTERS, Monsters)
INDEX(2, Monsters)
PARAGRAPH()
These are the monsters which you'll be unfortunate enough
to encounter during your wanderings through the various
levels:
PARAGRAPH()
LMARGIN(1)
ARTINLINE('..\bitmaps\egg.bmp', left)
Egg
LMARGIN(5)
PARAGRAPH()
If you dislodge an egg, then it will crack and eventually
a Slither monster will hatch out.
PARAGRAPH()
Eggs are like boulders in that they will slide off curved
surfaces.  They also count as curved objects, so boulders
and other eggs will slide off them.  Eggs don't crack if
something is dropped on them.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\crackedegg.bmp', left)
Cracked egg
LMARGIN(5)
PARAGRAPH()
After an egg has been dislodged, there is a short period
during which the Slither monster breaks out of the egg.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left)
Slither
LMARGIN(5)
PARAGRAPH()
At the end of the hatching period, a fully grown Slither emerges
from its egg, and begins its sole purpose in life - your death.
PARAGRAPH()
A Slither can only be killed by a boulder.  Either by having
one dropped on its head, or having one pushed into it.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left)
Spirit
LMARGIN(5)
PARAGRAPH()
Spirits are small fluffy creatures which wander
sightlessly around the levels.  They are deadly to touch,
and must be carefully shepherded into cages
ARTINLINE('..\bitmaps\cage.bmp', left) where they
will then turn into diamonds.


// Information concerning miscellaneous items ----------------------------

HEADER(2, pMISCITEMS, Miscellaneous items)
INDEX(2, Miscellaneous items)
PARAGRAPH()
These are the miscellaneous items that can be found scattered around
the levels:

PARAGRAPH()
ARTINLINE('..\bitmaps\boulder.bmp', left)
Boulder
LMARGIN(5)
PARAGRAPH()
Boulders can be dropped by removing whatever's supporting them,
or by pushing them. They slide off curved surfaces (including eggs
and diamonds), and can be used to kill some types of monster.
Being hit by a falling boulder is usually fatal.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\teleport.bmp', left)
Teleporter
LMARGIN(5)
PARAGRAPH()
When BOLD(Ribble) walks into a teleporter, he is teleported to a different
location on the current level.  Once used, teleporters vanish.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\cage.bmp', left)
Cage
LMARGIN(5)
PARAGRAPH()
Guide the Spirits into cages, and they will turn into diamonds.  In order
to complete a level, each cage must have been converted into a diamond.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\safe.bmp', left)
Safe
LMARGIN(5)
PARAGRAPH()
When BOLD(Ribble) picks up the key ARTINLINE('..\bitmaps\key.bmp', left), all the
safes on the current level are converted into diamonds.  As with the cages,
you must have collected all the safe diamonds in order to complete a level.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\bomb.bmp', left)
Bomb
LMARGIN(5)
PARAGRAPH()
Bombs become live when they are dropped onto something other than
earth ARTINLINE('..\bitmaps\earth.bmp', left)PERIOD()  Once live
ARTINLINE('..\bitmaps\bombli1.bmp', left), you have about
five seconds get out of the way before a bomb detonates
ARTINLINE('..\bitmaps\flame1.bmp', left)PERIOD()
LMARGIN(1)


// Information concerning scoring items ----------------------------

HEADER(2, pSCORING, Scoring)
INDEX(2, Scoring)
PARAGRAPH()
Points are gained for collecting and killing things on the levels, as follows:
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

HEADER(1, pSELECTINGLEVELS, Selecting levels)
INDEXID(1, selectlevel, Selecting levels)
PARAGRAPH()
When you complete a level, you automatically progress onto the next
one.  If you want go straight to a particular level, then you
can use the LINK(pSELECTLEVEL, level selection dialog) brought up
when you select the
BOLD(Open...) menu-item under the BOLD(Game) menu.


// Help for the select level dialog --------------------------------

HEADER(2, pSELECTLEVEL, Open... level dialog)
INDEX(2, Open... level dialog)
PARAGRAPH()
Use this dialog to select the level you wish to play.


// Editing levels ----------------------------

HEADER(1, pEDITINGLEVELS, Editing levels)
INDEX(1, Editing levels)
PARAGRAPH()
Select the BOLD(Level...) menu-item under the BOLD(Edit) menu at
any time while you are playing a level. The BOLD(Ribble) window will
expand horizontally, and a palette of all the available game items
will appear on the right-hand side of the window.
PARAGRAPH()
The BOLD(Ribble) will be replaced by a cross-hair cursor
ARTINLINE('..\bitmaps\edit.bmp', center) which indicates which
map cell you want to change.  The usual BOLD(Ribble) keys apply
while editing, and all creatures are halted.
PARAGRAPH()
ITALIC(Adding items to the playing area)
LMARGIN(3)
PARAGRAPH()
Click on an item in the palette to select it.  The currently
selected palette item is displayed next to the BOLD(Current >>)
caption above the palette.
PARAGRAPH()
Pressing the BOLD(Enter) key will place the selected item under
the cross-hair in the playing area.
PARAGRAPH()
When you place a creature onto the map, it doesn't become alive
until you leave edit mode.
LMARGIN(1)
PARAGRAPH()
ITALIC(Removing creatures from the map)
LMARGIN(3)
PARAGRAPH()
Position the cross-hair so that it overlaps the creature, and
press the BOLD(Delete) key.  The creature will be removed.
PARAGRAPH()
Note that items such as Spirits and Teleporters which you
place on the playing area don't become creatures as such
until you leave edit mode.
LMARGIN(1)
PARAGRAPH()
ITALIC(Setting teleport destinations)
LMARGIN(3)
PARAGRAPH()
Each teleporter has a destination location associated with it.
These destination locations are marked with a white number on
a blue background, and are overlaid on whatever item is at
the destination.
PARAGRAPH()
In addition to the location marker, teleporters
also have a white on red number stamped on them so that you can
tell which destination marker is associated with which teleporter.
PARAGRAPH()
To move a destination marker, position the cross-hard above it,
and press the BOLD(Insert) key.  If you now move the cross-hair,
the number will follow.  Press the BOLD(Return) key to drop the
number in the new location.
LMARGIN(1)
PARAGRAPH()
See Also:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pSAVINGLEVELS, Saving levels)
LMARGIN(1)


// Saving levels ----------------------------

HEADER(1, pSAVINGLEVELS, Saving levels)
INDEXID(1, saving, Saving levels)
PARAGRAPH()
While playing or editing a level, you can save the current
playing area to a level file.
PARAGRAPH()
Use the BOLD(Save...) menu-item under the BOLD(Game)
menu to bring up a LINK(pSAVELEVELAS, dialog) with which you can save your
level.

// Save level dialog ----------------------------

HEADER(2, pSAVELEVELAS, Save level dialog)
INDEX(2, Save level dialog)
PARAGRAPH()
This dialog allows you fill in various bits of information
about the level you are about to save.
PARAGRAPH()
Click the BOLD(OK) button to save the level and associated
information, or the BOLD(Cancel) to close the dialog without
saving the level.
PARAGRAPH()
Note the level number spin-button at the bottom of the dialog.
This number indicates the position in the level playing sequence.
In order for BOLD(Ribble) to use your levels they
must be numbered sequentially from one (1) upwards.  You
can use the level selection dialog to find out the current
highest numbered level, or look in the "levels" directory
contained in the BOLD(Ribble) executable's directory.



// Help for the product information dialog ------------------------

HEADER(1, pPRODUCTINFO, Product Information)
INDEXID(1, productinfo, Product Information)
PARAGRAPH()
Ribble is Copyright (c)1993, 1994 by J.R.Shannon and
D.J.Neades.  All rights reserved.
PARAGRAPH()
See also:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pDISCLAIMER, Disclaimer)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licencing)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contacting the authors)
LINEBREAK()
SQBUL() LINK(pGREETINGS, Greetings)
LMARGIN(1)
PARAGRAPH()
All trademarks acknowledged.

// System requirements and notes --------------------------------

HEADER(2, pSYSTEM_REQUIREMENTS, System requirements and notes)
INDEX(2, System requirements and notes)
PARAGRAPH()
BOLD(Ribble) is both a CPU and graphics intensive game.  The playing
area is updated many times a second, so, in order for BOLD(Ribble)
to run acceptably on your machine, you should take note of the
following points:
PARAGRAPH()
The faster your processor, the better.  BOLD(Ribble) was written on
a 486DX33, 486DX50, and P60, so performance on these processors
is satisfactory (particularly the last one!).
PARAGRAPH()
Since the rendering technique employed by BOLD(Ribble) involves blitting
a largish bitmap to the screen many times a second, BOLD(Ribble) will
run considerably better on systems with Local Bus or PCI graphics cards
than on those with (even accelerated) ISA cards.  Both 486's used in
BOLD(Ribble)'s development had ISA cards, and the P60 had a #9GXE
thingy + PCI bus.
PARAGRAPH()
You can tune performance by selecting the BOLD(Options...) menu-item
under the BOLD(Edit) menu and altering the settings contained inside
the LINK(pOPTIONSDIALOG, dialog) that is displayed.


// Information concerning licencing ----------------------------

HEADER(2, pLICENCE, Licencing)
INDEX(2, Licencing)
ARTALIGN('..\bitmaps\tribble-normal.bmp', center)
PARAGRAPH()
BOLD(Ribble) is Tribbleware.  This means that if you like it,
and play it while your boss ducks out for a quick
smoke, then you should feel under some kind of
obligation to send us one of those furry Tribble
things with the antennae, wobbly eyes, and an amusing
motto for a tail... Failing that, a postcard would be nice.
PARAGRAPH()
Users interested in designing better graphics, levels,
or adding other features into the game are welcome to
get in touch.  Irritating little .BOLD(MID) ditties which we can
run off MMPM/2 would be most useful.


// Information concerning contacting the authors  -------------------------

HEADER(2, pCONTAUTHOR, Contacting the authors)
INDEX(2, Contacting the authors)
PARAGRAPH()
The authors can be contacted on the Internet as:
LMARGIN(5)
PARAGRAPH()
BOLD(jrs@larch.demon.co.uk),
LMARGIN(2)
PARAGRAPH()
or (for Tribbles etc.),
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

HEADER(2, pDISCLAIMER, Disclaimer)
INDEX(2, Disclaimer)
PARAGRAPH()
This product is supplied with no warranty, either expressed or implied.
The Authors (Daniel J Neades and Jason R Shannon) do not 
accept responsibility for any adverse consequences that may arise 
from the use or misuse of BOLD(Ribble) or its associated program
and data files. Such adverse consequences include, but are not limited
to, loss of profit, and loss of data.
PARAGRAPH()
The Authors specifically disclaim all warranties, expressed or implied,
including but not limited to, any implied warranty of merchantability 
or fitness for a particular purpose.
PARAGRAPH()
There, we said it!

// Help for Greetings --------------------------------

HEADER(2, pGREETINGS, Greetings)
PARAGRAPH()
In no particular order, greetings to:
LMARGIN(5)
PARAGRAPH()
Alan Garde, Jarod Nash, Bob Eager, Mark Hanlon, Steve Wooding,
Keith Rundle, Asif Majid, Trevor Davies, and everyone involved with
OS/2 at IBM.


// Help for Options dialog --------------------------------

HEADER(1, pOPTIONSDIALOG, Options... dialog)
INDEX(1, Options... dialog)
PARAGRAPH()
Use the controls in this dialog to:
LMARGIN(5)
PARAGRAPH()
SQBUL() alter the keys used to move BOLD(Ribble) around
LMARGIN(8)
PARAGRAPH()
The three possible selections are:
LMARGIN(10)
PARAGRAPH()
SQBUL() ITALIC(Arrow), cursor keys.
PARAGRAPH()
SQBUL() ITALIC(Classic), where Z = left, X = right, ' (apostrophe) = up, and
/ (forward slash) = down.
PARAGRAPH()
SQBUL() ITALIC(Other), whatever you like.
LMARGIN(5)
PARAGRAPH()
SQBUL() alter various settings in order to tune performance
LMARGIN(8)
PARAGRAPH()
SQBUL() ITALIC(Refresh rate), the delay in milliseconds between
window refreshes.
PARAGRAPH()
SQBUL() ITALIC(Cell dimensions), the size of each cell in the window.
The default is 32x32, for a 32 pel by 32 pel cell.
PARAGRAPH()
SQBUL() ITALIC(Visible dimensions), the size of the playing area
viewed in the window.  The default is 7x7 for a 7 cell by 7 cell
view.
LMARGIN(1)


// -- Los endos --

ENDDOC()


