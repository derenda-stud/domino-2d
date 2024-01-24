/*
Inserisci la tessera più frequente / i cui valori compaiono più volte?

[5|1] [5|6] [4|6] [6|3] [1|6] [6|2] [3|2] [2|4] -> [6|3]
  0     1     2     3     4     5     6     7
  4     7     7     9     7     8     7     5

1 2 3 4 5 6
2 3 2 2 2 5
				posso collegarci:
se posizionata in hor:	[6|3]	2 hor, 2 ver
se posizionata in ver:	{3	    4 hor, 4 ver (2 tessere uguali) -> inserimento iniziale: orientamento = 0
			            6}                                      -> rotazione dipende dall'estremo piu' frequenze

[5|1] [5|6] [4|6] [1|6] [6|2] [3|2] [2|4] -> [6|2]
  0     1     2     3     4     5     6
  2     5     5     5     6     3     3

1 2 3 4 5 6
1 2 1 1 1 4

se posizionata in hor: [2|6][6|3]   /  [2|6]{6   /  {6 [6|2] -> preferibile dato che si accosta al numero in alto
					                        3}      3}
se posizionata in ver: 	{6 [6|3]    /   {6 XX avrebbe funzionato se accostata al numero in basso
			            2}              {3

verticale:
{3
6}

-> sx va bene il 6 (estremo dx)
-> dx va bene il 6 (estremo dx)

-> e' lo stesso? -> continua
-> era diverso -> non va bene

orizzontale:
[6|2]

-> sx va bene il 6 (estremo sx)
-> dx va bene il 2 (estremo dx)

va bene se sono OPPOSTI

estremo = piano[posizione di inserimento]
precedente = estremo - 1;
successivo = estremo + orientamento + 1;

controllo_sx = 0;

if(precedente.cardine) {
    if(precedente.valore == sinistro)       controllo_sx = 1;
    else if(precedente.valore == destro)    controllo_sx = 2;
}

controllo_dx = 0;

if(successivo.cardine) {
    if(successivo.valore == destro)         controllo_dx = 1 + !orientamento;
    else if(successivo.valore == sinistro)  controllo_dx = 1 + orientamento;
}



// sx = 0,  dx = 0   --> nessuna corrispondenza
// sx = 0,  dx = 1/2 --> va bene
// sx = 1/2 dx = 0   --> va bene
// sx = 1/2 dx = 1/2 -->  (stesso valore)   --> va bene
// sx = 1/2 dx = 2/1 --> (se sono opposti)  --> no

[6|3] -> sx X, dx 1
[3|6] -> sx X, dx 2

Se ho come estremo 0, metti un valore arbitrario che vada SEMPRE bene alla OR/XOR

      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
  0  --  --  --  --  --  --  --  --  --  --  --  --  --  {5  [5  1]  [1  6]  {6  --  --  --  --  --  --  --  --  --  --  --
  1  --  --  --  --  --  --  --  --  --  --  {4  [4  6]  6}  --  [3  3]  {3  2}  {2  --  --  --  --  --  --  --  --  --  --
  2  --  --  --  --  --  --  --  --  --  --  4}  --  --  --  --  --  --  [1  4]  4}  --  --  --  --  --  --  --  --  --  --

      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
  0  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

if(!sx && !dx) return false;
if(!sx) return dx;
if(!dx) return sx;

sx & dx
sx | dx

sx dx ^ ris
00 00   00 => 0
00 01   01 => 1
01 00   01 => 1
00 10   10 => 2
10 00   10 => 2
01 01   01 => 1
10 10   10 => 2
01 10   11 => 3
10 01   11 => 3

ris = sx ^ dx;
if(ris == 3) false;
else return ris;

GRANDE TABELLA XOR

bitwise operator:
AND &
OR |
XOR ^
COMPLEMENT ~
SHIFT LEFT <<
SHIFT RIGHT >>



GRANDE TABELLA BHO
XX XX | XX -> return;

return ris;

sx dx | ris
 0  0 |  0 nessuna corrispondenza
 0  1 |  1 unico estremo
 0  2 |  2 unico estremo
 1  0 |  1 unico estremo
 1  1 |  1 stesso valore
 1  2 |  0 
 2  0 |  2 unico estremo
 2  1 |  0 
 2  2 |  2 stesso valore

***Posizione valida mi assicura che abbia almeno un estremo collegato***

Occorre sistemare mossa legale / estremi corrispondono?

Una tessera va bene in orizzontale se:
	- sx esiste? -> sx corrisponde?
    - dx esiste? -> dx corrisponde? [pos + 2] (ci aggiungo l'orientamento)

Una tessera va bene in verticale se:
    - sx esiste? -> sx corrisponde?
    - dx esiste? -> dx corrisponde? [pos + 1]
    - esiste una riga sotto? -> no = true
    - sottostante sx esiste? -> sottostante sx corrisponde?
    - sottostante dx esiste? -> sottostante dx corrisponde?

if(orizzontale) {
    return estremi_corrispondono([riga, colonna], tessera, orientamento);
}
if(verticale) {
    int superiore = estremi_corrispondono([riga, colonna], tessera, orientamento);
    if(non esiste riga inferiore) va bene così
    int inferiore = estremi_corrispondono([riga + 1, colonna], tessera, orientamento);
    // confronta superiore ed inferiore
}

*/