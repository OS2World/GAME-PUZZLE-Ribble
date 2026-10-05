//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//
// Spanish translation
//

#include "document.h"
#include "help.h"


USERDOC()
TITLE(Ribble Information)

// First major heading ---------------------------------------------

HEADER(1, pMAINPANEL, Ayuda general)
INDEX(1 sortkey='a', Ayuda general)
PARAGRAPH()
ARTALIGN('..\bitmaps\ribblestatic.bmp', center)
PARAGRAPH()
BOLD(Ribble) es un clon de Boulder Dash escrito especificamente
para el PM (Presentation Manager) de OS/2.
PARAGRAPH()
Seleccione uno de los siguientes hiperenlaces:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pPLOT, El argumento)
LINEBREAK()
SQBUL() LINK(pSELECTINGLEVELS, Seleccionar niveles)
LINEBREAK()
SQBUL() LINK(pEDITINGLEVELS, Editar niveles)
LINEBREAK()
SQBUL() LINK(pKEYS, Teclado)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licencia)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contacto con los autores)
LINEBREAK()
SQBUL() LINK(pSYSTEM_REQUIREMENTS, Requisitos del sistema y notas)
LMARGIN(1)

// Information concerning the plot ----------------------------------

HEADER(1, pPLOT, El argumento)
INDEX(1, El argumento)
PARAGRAPH()
El objetivo del juego es LINK(pKEYS, guiar) a BOLD(Ribble)
ARTINLINE('..\bitmaps\repr1.bmp', left) por varios
niveles, recogiendo diamantes, matando monstruos y
resolviendo puzles.
PARAGRAPH()
Los objetos que se encuentran en los niveles se dividen en tres grupos:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Coleccionables)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monstruos)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Objetos diversos)
LINEBREAK()
LMARGIN(1)
PARAGRAPH()
Cada nivel debe completarse dentro de un tiempo determinado.  El tiempo
restante se muestra en la parte superior de la zona de juego junto con
su LINK(pSCORING, puntuacion), numero de vidas, y el numero de
diamantes que quedan por recoger en el nivel actual.
PARAGRAPH()
El valor del numero de diamantes restantes indica
cuantos diamantes, cajas fuertes y jaulas quedan por recoger.

// Help for Keys ---------------------------------------------------

HEADER(1, pKEYS, Teclas)
INDEXID(1, keyshelp, Teclas)
PARAGRAPH()
Para mover a BOLD(Ribble), use las siguientes teclas:
LMARGIN(5)
PARAGRAPH()
BOLD(Tecla de cursor Arriba), para moverse hacia arriba
LINEBREAK()
LINEBREAK()
BOLD(Tecla de cursor Abajo), para moverse hacia abajo
LINEBREAK()
LINEBREAK()
BOLD(Tecla de cursor Izquierda), para moverse hacia la izquierda
LINEBREAK()
LINEBREAK()
BOLD(Tecla de cursor Derecha), para moverse hacia la derecha
LINEBREAK()
LINEBREAK()
//(The above keys can be changed by selecting the on the BOLD(Options) menu-item
//under the BOLD(Edit) menu.)
//LINEBREAK()
//LINEBREAK()
//BOLD(Return) key, for status report
//LINEBREAK()
//LINEBREAK()
BOLD(Tecla Escape), para suicidarse y reiniciar el nivel actual
desde el principio.
LINEBREAK()
LINEBREAK()
//BOLD(Shift + Escape) key, to abandon the current level
//LINEBREAK()
//LINEBREAK()
BOLD(Tecla Espacio), para mostrar u ocultar el mapa
LMARGIN(1)
PARAGRAPH()
El resto de teclas se describen en las secciones de ayuda en linea
de las zonas en las que se utilizan.

// Help for F1 pressed on Help Keys menu item ---------------------

HEADER(2, pKEYSMENUITEM, Ayuda para el elemento de menu Teclas)
PARAGRAPH()
Seleccione el elemento de menu BOLD(Teclas) para obtener ayuda
relacionada con las teclas.

// Information concerning map items ----------------------------

HEADER(1, pITEMSHELP, Objetos&comma. monstruos y otras cosas)
INDEXID(1, mapitems, Objetos&comma. monstruos y otras cosas)
PARAGRAPH()
Objetos que se encuentran en los distintos niveles:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pITEMS, Coleccionables)
LINEBREAK()
SQBUL() LINK(pMONSTERS, Monstruos)
LINEBREAK()
SQBUL() LINK(pMISCITEMS, Objetos diversos)
LINEBREAK()
LMARGIN(1)


// Information concerning collectable items ----------------------------

HEADER(2, pITEMS, Coleccionables)
INDEX(2, Coleccionables)
PARAGRAPH()
Estos son los objetos coleccionables que se pueden encontrar
repartidos por los niveles:
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left)
Tierra
LMARGIN(5)
PARAGRAPH()
La tierra se encuentra en casi todos los niveles.  Sirve de soporte
para las rocas y otros objetos que pueden caer.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left)
Diamante
LMARGIN(5)
PARAGRAPH()
El objetivo principal de BOLD(Ribble) es recoger todos los diamantes
de cada nivel. Los diamantes o bien se encuentran en esta forma,
o bien se crean cuando los espiritus entran en las jaulas, o al
recoger una llave para abrir las cajas fuertes.  Mas
informacion mas adelante.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left)
Llave
LMARGIN(5)
PARAGRAPH()
Cuando BOLD(Ribble) recoge una llave, todas las cajas fuertes ARTINLINE('..\bitmaps\safe.bmp', left)
del nivel actual se convierten en diamantes que luego se pueden recoger.
Cuidado con las rocas u otros objetos que puedan caer sobre las cajas
fuertes - pueden deslizarse si la caja fuerte se convierte en un diamante.
LMARGIN(1)

// Information concerning monsters ----------------------------

HEADER(2, pMONSTERS, Monstruos)
INDEX(2, Monstruos)
PARAGRAPH()
Estos son los monstruos con los que tendra la mala suerte de
encontrarse durante sus paseos por los distintos
niveles:
PARAGRAPH()
LMARGIN(1)
ARTINLINE('..\bitmaps\egg.bmp', left)
Huevo
LMARGIN(5)
PARAGRAPH()
Si desaloja un huevo, se agrietara y, finalmente,
un monstruo Slither nace de el.
PARAGRAPH()
Los huevos son como las rocas: se deslizan por las superficies
curvas. Tambien cuentan como objetos curvos, de modo que las rocas
y otros huevos se deslizaran sobre ellos. Los huevos no se agrietan
si se les cae algo encima.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\crackedegg.bmp', left)
Huevo agrietado
LMARGIN(5)
PARAGRAPH()
Despues de desalojar un huevo, hay un breve periodo
durante el cual el monstruo Slither sale del huevo.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left)
Slither
LMARGIN(5)
PARAGRAPH()
Al final del periodo de eclosion, un Slither completamente
crecido emerge de su huevo y comienza a cumplir
su unico proposito en la vida - su muerte.
PARAGRAPH()
Un Slither solo puede ser matado por una roca:  ya sea
dejandola caer sobre su cabeza, o empujandola contra el.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left)
Espiritu
LMARGIN(5)
PARAGRAPH()
Los espiritus son pequenas criaturas esponjosas que deambulan
sin vista por los niveles.  Son mortales al tocarlos,
y deben ser conducidos con cuidado hacia las jaulas
ARTINLINE('..\bitmaps\cage.bmp', left) donde
se convertiran en diamantes.


// Information concerning miscellaneous items ----------------------------

HEADER(2, pMISCITEMS, Objetos diversos)
INDEX(2, Objetos diversos)
PARAGRAPH()
Estos son los objetos diversos que se pueden encontrar
repartidos por los niveles:

PARAGRAPH()
ARTINLINE('..\bitmaps\boulder.bmp', left)
Roca
LMARGIN(5)
PARAGRAPH()
Las rocas se pueden hacer caer quitando lo que las sostiene,
o empujandolas. Se deslizan por las superficies curvas (incluidos
los huevos y los diamantes), y pueden usarse para matar a
algunos tipos de monstruo.
Que le golpee una roca que cae suele ser fatal.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\teleport.bmp', left)
Teletransportador
LMARGIN(5)
PARAGRAPH()
Cuando BOLD(Ribble) entra en un teletransportador, es trasladado a
otro lugar del nivel actual.  Una vez usado, los teletransportadores
desaparecen.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\cage.bmp', left)
Jaula
LMARGIN(5)
PARAGRAPH()
Conduzca a los espiritus hasta las jaulas y se convertiran en
diamantes.  Para completar un nivel, cada jaula debe haberse
convertido en un diamante.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\safe.bmp', left)
Caja fuerte
LMARGIN(5)
PARAGRAPH()
Cuando BOLD(Ribble) recoge la llave ARTINLINE('..\bitmaps\key.bmp', left), todas las
cajas fuertes del nivel actual se convierten en diamantes.  Igual que con las jaulas,
debe haber recogido todos los diamantes de las cajas fuertes para
completar el nivel.
LMARGIN(1)
PARAGRAPH()
ARTINLINE('..\bitmaps\bomb.bmp', left)
Bomba
LMARGIN(5)
PARAGRAPH()
Las bombas se activan cuando caen sobre algo que no sea
tierra ARTINLINE('..\bitmaps\earth.bmp', left).  Una vez activadas
ARTINLINE('..\bitmaps\bombli1.bmp', left), tiene unos
cinco segundos para apartarse antes de que la bomba
detone
ARTINLINE('..\bitmaps\flame1.bmp', left).
LMARGIN(1)


// Information concerning scoring items ----------------------------

HEADER(2, pSCORING, Puntuacion)
INDEX(2, Puntuacion)
PARAGRAPH()
Se ganan puntos por recoger y matar cosas en los niveles, de la
siguiente manera:
PARAGRAPH()
ARTINLINE('..\bitmaps\earth.bmp', left) 1 punto
PARAGRAPH()
ARTINLINE('..\bitmaps\diamond.bmp', left) 10 puntos
PARAGRAPH()
ARTINLINE('..\bitmaps\key.bmp', left) 10 puntos
PARAGRAPH()
ARTINLINE('..\bitmaps\spirit.bmp', left) + ARTINLINE('..\bitmaps\cage.bmp', left) 25 puntos
PARAGRAPH()
ARTINLINE('..\bitmaps\slither.bmp', left) + ARTINLINE('..\bitmaps\boulder.bmp', left)  50 puntos


// Information selecting levels ----------------------------

HEADER(1, pSELECTINGLEVELS, Seleccionar niveles)
INDEXID(1, selectlevel, Seleccionar niveles)
PARAGRAPH()
Cuando complete un nivel, pasara automaticamente al siguiente.
Si quiere ir directamente a un nivel en particular, entonces
puede usar el LINK(pSELECTLEVEL, dialogo de seleccion de nivel)
que aparece al seleccionar el
elemento de menu
BOLD(Abrir...) bajo el menu BOLD(Juego).


// Help for the select level dialog --------------------------------

HEADER(2, pSELECTLEVEL, Dialogo de nivel Abrir...)
INDEX(2, Dialogo de nivel Abrir...)
PARAGRAPH()
Use este dialogo para seleccionar el nivel que desea jugar.


// Editing levels ----------------------------

HEADER(1, pEDITINGLEVELS, Editar niveles)
INDEX(1, Editar niveles)
PARAGRAPH()
Seleccione el elemento de menu BOLD(Nivel...) bajo el submenu BOLD(Editor de mapa) del
menu BOLD(Opciones) en cualquier momento mientras juega a un nivel. La ventana de BOLD(Ribble) se
expandira horizontalmente y aparecera una paleta con todos los objetos
disponibles del juego en el lado derecho de la ventana.
PARAGRAPH()
BOLD(Ribble) sera sustituido por un cursor en cruz
ARTINLINE('..\bitmaps\edit.bmp', center) que indica
que celda del mapa desea cambiar.  Se aplican las teclas habituales
de BOLD(Ribble) mientras se edita, y todas las criaturas se detienen.
PARAGRAPH()
ITALIC(Anadir objetos a la zona de juego)
LMARGIN(3)
PARAGRAPH()
Haga clic en un objeto de la paleta para seleccionarlo.  El objeto
seleccionado actualmente se muestra junto al rotulo BOLD(Actual >>)
en la parte superior de la paleta.
PARAGRAPH()
Pulsar la tecla BOLD(Intro) colocara el objeto seleccionado
bajo el cursor en cruz en la zona de juego.
PARAGRAPH()
Cuando coloque una criatura en el mapa, no cobrara vida
hasta que salga del modo edicion.
LMARGIN(1)
PARAGRAPH()
ITALIC(Quitar criaturas del mapa)
LMARGIN(3)
PARAGRAPH()
Coloque el cursor en cruz de modo que se superponga a la criatura,
y pulse la tecla BOLD(Supr).  La criatura sera eliminada.
PARAGRAPH()
Tenga en cuenta que los objetos como los espiritus y los
teletransportadores que coloque en la zona de juego no
se convierten en criaturas como tales
hasta que sale del modo edicion.
LMARGIN(1)
PARAGRAPH()
ITALIC(Establecer destinos de teletransporte)
LMARGIN(3)
PARAGRAPH()
Cada teletransportador tiene asociada una ubicacion de destino.
Estas ubicaciones se marcan con un numero blanco sobre
un fondo azul, y se superponen a cualquier objeto que haya
en el destino.
PARAGRAPH()
Ademas del marcador de ubicacion, los teletransportadores
tambien llevan estampado un numero blanco sobre rojo
para que sepa que marcador de destino esta asociado
a cada teletransportador.
PARAGRAPH()
Para mover un marcador de destino, coloque el cursor en cruz encima,
y pulse la tecla BOLD(Insert).  Si ahora mueve el cursor en cruz,
el numero le seguira.  Pulse la tecla BOLD(Intro) para soltar
el numero en la nueva ubicacion.
LMARGIN(1)
PARAGRAPH()
Ver tambien:
LMARGIN(5)
PARAGRAPH()
SQBUL() LINK(pSAVINGLEVELS, Guardar niveles)
LMARGIN(1)


// Saving levels ----------------------------

HEADER(1, pSAVINGLEVELS, Guardar niveles)
INDEXID(1, saving, Guardar niveles)
PARAGRAPH()
Mientras juega o edita un nivel, puede guardar la zona
de juego actual en un archivo de nivel.
PARAGRAPH()
Use el elemento de menu BOLD(Guardar...) bajo el menu BOLD(Juego)
para mostrar un LINK(pSAVELEVELAS, dialogo) con el que puede
guardar su nivel.

// Save level dialog ----------------------------

HEADER(2, pSAVELEVELAS, Dialogo de guardado de nivel)
INDEX(2, Dialogo de guardado de nivel)
PARAGRAPH()
Este dialogo le permite rellenar diversos datos
sobre el nivel que va a guardar.
PARAGRAPH()
Haga clic en el boton BOLD(Aceptar) para guardar el nivel y la
informacion asociada, o en BOLD(Cancelar) para cerrar el dialogo
sin guardar el nivel.
PARAGRAPH()
Observe el boton de giro del numero de nivel en la parte inferior
del dialogo. Este numero indica la posicion en la secuencia de
juego de niveles. Para que BOLD(Ribble) use sus niveles,
deben estar numerados secuencialmente desde uno (1) en adelante.  Puede
usar el dialogo de seleccion de nivel para averiguar el nivel
mas alto numerado, o mirar en el directorio "levels"
contenido en el directorio del ejecutable de BOLD(Ribble).



// Help for the product information dialog ------------------------

HEADER(1, pPRODUCTINFO, Informacion del producto)
INDEXID(1, productinfo, Informacion del producto)
PARAGRAPH()
Ribble tiene los derechos de autor (c)1993, 1994 de J.R.Shannon y
D.J.Neades.  Todos los derechos reservados.
PARAGRAPH()
Ver tambien:
PARAGRAPH()
LMARGIN(5)
SQBUL() LINK(pDISCLAIMER, Exencion de responsabilidad)
LINEBREAK()
SQBUL() LINK(pLICENCE, Licencia)
LINEBREAK()
SQBUL() LINK(pCONTAUTHOR, Contacto con los autores)
LINEBREAK()
SQBUL() LINK(pGREETINGS, Saludos)
LMARGIN(1)
PARAGRAPH()
Se reconocen todas las marcas comerciales.

// System requirements and notes --------------------------------

HEADER(2, pSYSTEM_REQUIREMENTS, Requisitos del sistema y notas)
INDEX(2, Requisitos del sistema y notas)
PARAGRAPH()
BOLD(Ribble) es un juego intensivo en CPU y graficos.  La zona
de juego se actualiza muchas veces por segundo, por lo tanto, para que BOLD(Ribble)
funcione correctamente en su maquina, tenga en cuenta
los siguientes puntos:
PARAGRAPH()
Cuanto mas rapido sea su procesador, mejor.  BOLD(Ribble) se escribio
en un 486DX33, un 486DX50 y un P60, por lo que el rendimiento
en estos procesadores es satisfactorio (sobre todo en el ultimo!).
PARAGRAPH()
Dado que la tecnica de renderizado que emplea BOLD(Ribble) consiste
en copiar un mapa de bits bastante grande a la pantalla muchas veces
por segundo, BOLD(Ribble) funcionara considerablemente mejor en
sistemas con tarjetas graficas de bus local o PCI
que en aquellos con tarjetas ISA (incluso aceleradas).  Los dos 486 usados
en el desarrollo de BOLD(Ribble) tenian tarjetas ISA, y el P60 tenia
una #9GXE
+ bus PCI.
PARAGRAPH()
Puede ajustar el rendimiento seleccionando el elemento de menu BOLD(Opciones...)
bajo el submenu BOLD(Editor de mapa) del menu BOLD(Opciones) y modificando
los ajustes contenidos dentro
del LINK(pOPTIONSDIALOG, dialogo) que se muestra.


// Information concerning licencing ----------------------------

HEADER(2, pLICENCE, Licencia)
INDEX(2, Licencia)
ARTALIGN('..\bitmaps\tribble-normal.bmp', center)
PARAGRAPH()
BOLD(Ribble) es Tribbleware.  Esto significa que si le gusta,
y juega mientras su jefe sale a fumarse un cigarrillo,
entonces deberia sentirse en cierto modo
obligado a enviarnos una de esas criaturas Tribble
peludas con antenas, ojos temblorosos y un
lema divertido a modo de cola...  Si no, una postal estaria bien.
PARAGRAPH()
Los usuarios interesados en disenar mejores graficos, niveles,
o en anadir otras funciones al juego son bienvenidos a
ponerse en contacto.  Serian muy utiles esas melodias
.BOLD(MID) irritantes que podamos ejecutar con MMPM/2.


// Information concerning contacting the authors  -------------------------

HEADER(2, pCONTAUTHOR, Contacto con los autores)
INDEX(2, Contacto con los autores)
PARAGRAPH()
Puede ponerse en contacto con los autores por Internet en:
LMARGIN(5)
PARAGRAPH()
BOLD(jrs@larch.demon.co.uk),
LMARGIN(2)
PARAGRAPH()
o (para los Tribbles, etc.),
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

HEADER(2, pDISCLAIMER, Exencion de responsabilidad)
INDEX(2, Exencion de responsabilidad)
PARAGRAPH()
Este producto se suministra sin garantia, ya sea expresa o implicita.
Los autores (Daniel J Neades y Jason R Shannon) no
aceptan ninguna responsabilidad por las consecuencias adversas que
puedan derivarse del uso o mal uso de BOLD(Ribble) o de su
programa y archivos de datos asociados. Tales consecuencias adversas
incluyen, entre otras, la perdida de beneficios y la perdida de
datos.
PARAGRAPH()
Los autores renuncian expresamente a todas las garantias, expresas o
implicitas, incluidas, entre otras, cualquier garantia implicita de
comerciabilidad o idoneidad para un fin particular.
PARAGRAPH()
Ah, ya lo hemos dicho!

// Help for Greetings --------------------------------

HEADER(2, pGREETINGS, Saludos)
PARAGRAPH()
Sin ningun orden particular, saludos para:
LMARGIN(5)
PARAGRAPH()
Alan Garde, Jarod Nash, Bob Eager, Mark Hanlon, Steve Wooding,
Keith Rundle, Asif Majid, Trevor Davies, y todos los implicados con
OS/2 en IBM.


// Help for Options dialog --------------------------------

HEADER(1, pOPTIONSDIALOG, Dialogo Opciones...)
INDEX(1, Dialogo Opciones...)
PARAGRAPH()
Use los controles de este dialogo para:
LMARGIN(5)
PARAGRAPH()
SQBUL() modificar las teclas utilizadas para mover a BOLD(Ribble)
LMARGIN(8)
PARAGRAPH()
Las tres opciones posibles son:
LMARGIN(10)
PARAGRAPH()
SQBUL() ITALIC(Flechas), teclas de cursor.
PARAGRAPH()
SQBUL() ITALIC(Clasico), donde Z = izquierda, X = derecha, ' (apostrofo) = arriba y
/ (barra) = abajo.
PARAGRAPH()
SQBUL() ITALIC(Otro), lo que usted quiera.
LMARGIN(5)
PARAGRAPH()
SQBUL() modificar varios ajustes para ajustar el rendimiento
LMARGIN(8)
PARAGRAPH()
SQBUL() ITALIC(Frecuencia de refresco), el retardo en milisegundos
entre los refrescos de la ventana.
PARAGRAPH()
SQBUL() ITALIC(Dimensiones de celda), el tamano de cada celda en la
ventana. El valor predeterminado es 64x64, es decir, una celda de
64 por 64 pixels.
PARAGRAPH()
SQBUL() ITALIC(Dimensiones visibles), el tamano de la zona de juego
vista en la ventana.  El valor predeterminado es 14x14, es decir, una
vista de 14 por 14 celdas.
LMARGIN(1)


// -- Los endos --

ENDDOC()