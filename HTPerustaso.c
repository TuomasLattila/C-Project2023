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
/* Tehtävä Harjoitustyö, tiedoston nimi HTPerustaso.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"

int main()  {
    int iValinta = 0;
    char aNimi[TIEDOSTO];
    TIEDOT *pAlku = NULL;
    TILASTO *pTilasto = NULL;
    LUOKKA *pLuokka = NULL;

    do  {
        iValinta = valikko();

        if (iValinta == 1)  {
            if (pAlku != NULL)  {
                pAlku = muistinVapautus(pAlku); /*muistin vapautus ennen uuden lukemista*/
            }
            kysyNimi(aNimi);
            pAlku = lueTiedosto(pAlku, aNimi);
        } else if (iValinta == 2)   {
            if (pAlku != NULL)  {
                free(pTilasto);
                pTilasto = NULL;
                pTilasto = tilastoAnalyysi(pTilasto, pAlku);
                free(pLuokka);
                pLuokka = NULL;
                pLuokka = luokkaAnalyysi(pLuokka, pAlku);
            } else {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
        } else if (iValinta == 3)   {
            if (pTilasto != NULL || pLuokka != NULL)   {
                kysyNimi(aNimi);
                kirjoitaTiedosto(pTilasto, pLuokka, aNimi);
            } else {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
        } else if (iValinta == 0)   {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta !=0);
    
    pAlku = muistinVapautus(pAlku); /*muistin vapautus*/
    free(pTilasto);
    pTilasto = NULL;
    free(pLuokka);
    pLuokka = NULL;
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}
/* eof */