/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Tekijä: Tuomas Lättilä
 * Opiskelijanumero: 000437136
 * Päivämäärä: 28.2.2023
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
 * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:

 * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
 * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
 * vaikuttaneet siihen yllä mainituilla tavoilla.
 */
/*************************************************************************/
/* Tehtävä Harjoitustyö, tiedoston nimi HTPerusKirjasto.h */

#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H
#define TIEDOSTO 30
#define SANA 255
#define RIVI 300
#define TAULUKKO 10

typedef struct tiedot   {
    char aSana[SANA];
    int iLuokka;
    struct tiedot *pSeuraava;
} TIEDOT;

typedef struct tilasto    {
    int iMaara;
    float fPituus;
    char aPisin[SANA];
    char aLyhyin[SANA];
    char aEnsimmainen[SANA];
    char aViimeinen[SANA];
} TILASTO;

typedef struct luokka   {
    int iLuokka;
    int iMaara;
} LUOKKA;

int valikko();
void kysyNimi(char *pNimi);
TIEDOT *lisaaListaan(TIEDOT *pAlku, char *pSana, char *pLuokka);
TIEDOT *lueTiedosto(TIEDOT *pA, char *pNimi);
TILASTO *tilastoAnalyysi(TILASTO *pTilasto, TIEDOT *pA);
LUOKKA *luokkaAnalyysi(LUOKKA *pLuokka, TIEDOT *pA);
void tietojenTulostus(TILASTO *pTilasto, LUOKKA *pLuokka, FILE *tiedosto);
void kirjoitaTiedosto(TILASTO *pTilasto, LUOKKA *pLuokka, char *pNimi);
TIEDOT *muistinVapautus(TIEDOT *pA);

#endif
/* eof */