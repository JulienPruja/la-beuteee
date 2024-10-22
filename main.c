#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int racine(int nb)
{
    int i;

    i = 0;
    while (i * i <= nb)
        i++;
    if (i * i > nb)
        return (i - 1);
    return (i);
}

void write_couleur(char *str, char *color)
{
    char colorstr[12] = {0};

    strcat(colorstr, "\x1B[");
    strcat(colorstr, color);
    strcat(colorstr, "m");
    write(1, colorstr, strlen(colorstr));
    write(1, str, strlen(str));
}

void dessiner_couille(int taille, char *couleur)
{
    int i = 0;
    int j = 0;
    int centerX = taille / 2;
    int centerY = taille / 2;

    while (i < taille) {
        j = 0;
        while (j < taille) {
            if (racine((centerX - j) * (centerX - j) + (centerY - i) * (centerY - i)) < taille / 2)
                write_couleur("*", couleur);
            else
                write(1, " ", 1);
            j++;
        }
        write(1, "  ", 2);
        j = 0;
        while (j < taille) {
            if (racine((centerX - j) * (centerX - j) + (centerY - i) * (centerY - i)) < taille / 2)
                write_couleur("*", couleur);
            else
                write(1, " ", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

void dessiner_suite(int taille, char *couleur)
{
    int milieu = taille + 1;
    int i = 0;
    int j = 0;
    while (i < taille * 2 + 2)
    {
        j = 0;
        while (j < (taille * 2) + 2)
        {
            if (j == taille/2 + 1 || j == taille * 2 - taille / 2 + 1)
                write_couleur("*", couleur);
            else
                write(1, " ", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
    j = 0;
    while (j < (taille * 2) + 2)
    {
        if (j >= taille/2 + 1 && j <= taille * 2 - taille / 2 + 1)
            write_couleur("*", couleur);
        else
            write(1, " ", 1);
        j++;
    }
    write(1, "\n", 1);
}

void arc_de_cercles(int taille, char *couleur)
{
    int i = taille / 2;
    int j = 0;
    int centerX = taille / 2;
    int centerY = taille / 2;

    while (i < taille) {
        j = 0;
        while (j < taille/2 + 1)
        {
            write(1, " ", 1);
            j++;
        }
        j = 0;
        while (j < taille + 2) {
            if (racine((centerX - j) * (centerX - j) + (centerY - i) * (centerY - i)) < taille / 2 + 1 && !(i > 2 * taille / 3 && j == taille/2))
                write_couleur("*", couleur);
            else
                write(1, " ", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char *argv[])
{
    int taille;

    if (argc != 3) {
        write_couleur("Preciser une couleur\n", "31");
        return (0);
    }
    if ((taille = atoi(argv[1])) < 2) {
        write_couleur("Taille trop petite\n", "31");
        return 0;
    }
    dessiner_couille(taille, argv[2]);
    dessiner_suite(taille, argv[2]);
    arc_de_cercles(taille, argv[2]);
}
