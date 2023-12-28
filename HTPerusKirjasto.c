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
/* Tehtävä Harjoitustyö, tiedoston nimi HTPerusKirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"

int valikko()   {
    int iValinta = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return (iValinta);
}

void kysyNimi(char *pNimi)  {
    printf("Anna tiedoston nimi: ");
    scanf("%s", pNimi);
    return;
}

TIEDOT *lisaaListaan(TIEDOT *pAlku, char *pSana, char *pLuokka)   {
    TIEDOT *pUusi = NULL, *ptr = NULL;
    
    if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL)  {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    pUusi->pSeuraava = NULL;
    strcpy(pUusi->aSana, pSana);
    pUusi->iLuokka = atoi(pLuokka);

    if (pAlku == NULL) {
        pAlku = pUusi;
    } else {
        ptr = pAlku;
        while(ptr->pSeuraava != NULL)   {
            ptr = ptr->pSeuraava;
        }
        ptr->pSeuraava = pUusi;
    }
    return(pAlku);
}

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi)   {
    char aRivi[RIVI], *pSana, *pLuokka;
    FILE *tiedosto;

    if ((tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fgets(aRivi, RIVI, tiedosto); /*otsikko*/
    while((fgets(aRivi, RIVI, tiedosto)) != NULL)   {
        if ((pSana = strtok(aRivi, ";")) == NULL)  {
            perror("Merkkijonon pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }
        if ((pLuokka = strtok(NULL, ";")) == NULL)  {
            perror("Merkkijonon pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }
        pAlku = lisaaListaan(pAlku, pSana, pLuokka); /*varataan ja lisätään uusi struct-alkio listaan*/
    }
    fclose(tiedosto);
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return (pAlku);
}

TILASTO *tilastoAnalyysi(TILASTO *pTilasto, TIEDOT *pAlku)    {
    TIEDOT *ptr = NULL;
    /*muistin varaus tilastotiedoille*/
    if ((pTilasto = (TILASTO*)malloc(sizeof(TILASTO))) == NULL)  {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    pTilasto->iMaara = 1;
    pTilasto->fPituus = strlen(pAlku->aSana);
    strcpy(pTilasto->aPisin, pAlku->aSana);    /*lisätään listan ensimmäiset arvot*/
    strcpy(pTilasto->aLyhyin, pAlku->aSana);
    strcpy(pTilasto->aEnsimmainen, pAlku->aSana);
    strcpy(pTilasto->aViimeinen, pAlku->aSana);

    ptr = pAlku->pSeuraava; /*Looppi alkaa linkitetyn listan toisesta alkiosta, jotta voidaan vertailla*/
    while(ptr != NULL)  {
        pTilasto->iMaara += 1;
        pTilasto->fPituus += strlen(ptr->aSana);
        if (strlen(pTilasto->aPisin) < strlen(ptr->aSana))  {
            strcpy(pTilasto->aPisin, ptr->aSana);
        }
        if (strlen(pTilasto->aLyhyin) > strlen(ptr->aSana))  {
            strcpy(pTilasto->aLyhyin, ptr->aSana);
        }
        if (strcmp(pTilasto->aEnsimmainen, ptr->aSana) > 0)     {
            strcpy(pTilasto->aEnsimmainen, ptr->aSana);
        }
        if (strcmp(pTilasto->aViimeinen, ptr->aSana) < 0)     {
            strcpy(pTilasto->aViimeinen, ptr->aSana);
        }
        ptr = ptr->pSeuraava;
    }
    pTilasto->fPituus = (float)(pTilasto->fPituus/pTilasto->iMaara); /*keskiarvon lasku*/
    printf("Analysoitu %d sanaa.\n", pTilasto->iMaara);
    return(pTilasto);
}

LUOKKA *luokkaAnalyysi(LUOKKA *pLuokka, TIEDOT *pAlku)    {
    TIEDOT *ptr = NULL;
    int i;
    /*muistin varaus kymmenelle alkiolle*/
    if ((pLuokka = (LUOKKA*)malloc(sizeof(LUOKKA)*TAULUKKO)) == NULL)  {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    /*taulukon alustus*/
    for (i = 0; i < 10; i++)    {
        pLuokka[i].iMaara = 0;
        pLuokka[i].iLuokka = (i+1);
    }
    ptr = pAlku;
    while (ptr != NULL) {
        pLuokka[ptr->iLuokka - 1].iMaara += 1;
        ptr = ptr->pSeuraava;
    }
    printf("Sanaluokittaiset lukumäärät analysoitu.\n");
    return(pLuokka);
}

void tietojenTulostus(TILASTO *pTilasto, LUOKKA *pLuokka, FILE *tiedosto)   {
    int i;

    fprintf(tiedosto, "Tilastotiedot %d sanasta:\n", pTilasto->iMaara);
    fprintf(tiedosto, "Keskimääräinen sanan pituus on %.1f merkkiä.\n", pTilasto->fPituus);
    fprintf(tiedosto, "Pisin sana '%s' on %ld merkkiä pitkä.\n", pTilasto->aPisin, strlen(pTilasto->aPisin));
    fprintf(tiedosto, "Lyhyin sana '%s' on %ld merkkiä pitkä.\n", pTilasto->aLyhyin, strlen(pTilasto->aLyhyin));
    fprintf(tiedosto, "Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", pTilasto->aEnsimmainen);
    fprintf(tiedosto, "Aakkosjärjestyksessä viimeinen sana on '%s'.\n", pTilasto->aViimeinen);
    fprintf(tiedosto, "\n");
    fprintf(tiedosto, "Sanaluokka;Lkm\n");
    for (i = 0; i < 10; i++)    {
        fprintf(tiedosto, "Luokka %d;%d\n", pLuokka[i].iLuokka, pLuokka[i].iMaara);
    }
    return;
}

void kirjoitaTiedosto(TILASTO *pTilasto, LUOKKA *pLuokka, char *pNimi)  {
    FILE *tiedosto;

    tietojenTulostus(pTilasto, pLuokka, stdout); /*tulostus standarditulostevirtaan*/

    if ((tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    tietojenTulostus(pTilasto, pLuokka, tiedosto);
    fclose(tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

TIEDOT *muistinVapautus(TIEDOT *pAlku)    {
    TIEDOT *ptr = pAlku;

    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    pAlku = NULL;
    return (pAlku);
}
/* eof */