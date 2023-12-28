#/*************************************************************************/
#/* CT60A2500 C-ohjelmoinnin perusteet
# * Tekijä: Tuomas Lättilä
# * Opiskelijanumero:
# * Päivämäärä: 28.2.2023
# * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
# * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
#
# * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
# * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
# * vaikuttaneet siihen yllä mainituilla tavoilla.
# */
#/*************************************************************************/
#/* Tehtävä Harjoitustyö, tiedoston nimi Makefile */

HT: HTPerustaso.o HTPerusKirjasto.o
	gcc -o HT HTPerustaso.o HTPerusKirjasto.o
HTPerustaso.o: HTPerustaso.c HTPerusKirjasto.h
	gcc -c HTPerustaso.c -std=c99 -pedantic -Wall
HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc -c HTPerusKirjasto.c -std=c99 -pedantic -Wall
