#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// voi genera un numar aleator pana in 100 si ii voi afla restul la 4
// voi face asta de doua ori pentru linie si coloana (libera)
// apoi pe pozitia respectiva voi genera un numar aleator pana in 100
// si ii voi afla restul impartirii la 2
// daca este 0 se pune 2 daca este 1 se pune 4

void print(int tabla[4][4])
{
    int i, j;
    printw("Pentru o mutare in sus foloseste sageata in sus\n");
    printw("Pentru o mutare in jos foloseste sageata in jos\n");
    printw("Pentru o mutare in stanga foloseste sageata in stanga\n");
    printw("Pentru o mutare in dreapta foloseste sageata in dreapta\n\n");

    // initializam 11 culori, una pentru fiecare numar
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(9, COLOR_BLACK, COLOR_GREEN);
    init_pair(10, COLOR_BLACK, COLOR_YELLOW);
    init_pair(11, COLOR_BLACK, COLOR_MAGENTA);

    time_t timpActual;
    struct tm *infoTimp;
    time(&timpActual);
    infoTimp = localtime(&timpActual);

    // data
    printw("Data: %02d-%02d-%d\n", infoTimp->tm_mday, infoTimp->tm_mon + 1, infoTimp->tm_year + 1900);
    // +1900 deoarece structura afiseaza numarul de ani incepand cu 1900

    // ora
    printw("Ora: %02d:%02d:%02d\n", infoTimp->tm_hour, infoTimp->tm_min, infoTimp->tm_sec);
    // se adauga un 0 in faca numarului
    printw("+-------------------------------+\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (tabla[i][j] == 0)
            {
                printw("|       ");
            }
            else if (tabla[i][j] > 9)
            {
                printw("|");
                if (tabla[i][j] == 16)
                    attron(COLOR_PAIR(4));
                if (tabla[i][j] == 32)
                    attron(COLOR_PAIR(5));
                if (tabla[i][j] == 64)
                    attron(COLOR_PAIR(6));
                if (tabla[i][j] == 128)
                    attron(COLOR_PAIR(7));
                if (tabla[i][j] == 256)
                    attron(COLOR_PAIR(8));
                if (tabla[i][j] == 512)
                    attron(COLOR_PAIR(9));
                if (tabla[i][j] == 1024)
                    attron(COLOR_PAIR(10));
                if (tabla[i][j] == 2048)
                    attron(COLOR_PAIR(11));
                printw("  %3d  ", tabla[i][j]);
                attroff(COLOR_PAIR(4));
                attroff(COLOR_PAIR(5));
                attroff(COLOR_PAIR(6));
                attroff(COLOR_PAIR(7));
                attroff(COLOR_PAIR(8));
                attroff(COLOR_PAIR(9));
                attroff(COLOR_PAIR(10));
                attroff(COLOR_PAIR(11));
            }
            else
            {
                printw("|");
                if (tabla[i][j] == 2)
                    attron(COLOR_PAIR(1));
                if (tabla[i][j] == 4)
                    attron(COLOR_PAIR(2));
                if (tabla[i][j] == 8)
                    attron(COLOR_PAIR(3));
                printw("   %d   ", tabla[i][j]);
                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(2));
                attroff(COLOR_PAIR(3));
            }
        }
        printw("|\n");
        printw("+-------------------------------+\n");
    } // afisam matricea iar numerele sunt despartite de niste caractere speciale
      // pentru a fi mai usor de urmarit jocul
}

void newGame(int tabla[4][4])
{
    clear();
    refresh();
    int linie, coloana, nrRandom;
    srand(time(NULL));
    // bool playing = true;
    //  plasam doua numere random pe pozitii aleatoare pe noua tabla
    linie = rand() % 4;
    coloana = rand() % 4;
    int ok = 1;
    // punem doua numere random din multimea {2,4} pe pozitii random
    do
    {
        if (tabla[linie][coloana] == 0)
        {
            nrRandom = rand() % 2;
            if (nrRandom == 0)
                tabla[linie][coloana] = 2;
            else if (nrRandom == 1)
                tabla[linie][coloana] = 4;
            ok = 0;
        }
        linie = rand() % 4;
        coloana = rand() % 4;
    } while (ok == 1);
    linie = rand() % 4;
    coloana = rand() % 4;
    ok = 1;
    do
    {
        if (tabla[linie][coloana] == 0)
        {
            nrRandom = rand() % 2;
            if (nrRandom == 0)
                tabla[linie][coloana] = 2;
            else if (nrRandom == 1)
                tabla[linie][coloana] = 4;
            ok = 0;
        }
        linie = rand() % 4;
        coloana = rand() % 4;
    } while (ok == 1);
    print(tabla);
    refresh();
}

int lose(int tabla[4][4])
{
    int i, j;
    // verificare pentru perechi adiacente care pot fi combinate
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (tabla[i][j] == 0)
                return 1;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            // verificare pentru perechi adiacente care pot fi combinate
            if ((i < 3 && tabla[i][j] == tabla[i + 1][j]) ||
                (j < 3 && tabla[i][j] == tabla[i][j + 1]))
            {
                return 1; // se mai poate face o mutare (exista celule adiacente ce pot fi combinate)
            }
        }
    }

    return 0; // nu se mai poate face o mutare
}

void logic(int tabla[4][4], int punctaj)
{
    // fisier in care stocam istoricul punctajelor
    FILE *fisier = fopen("punctaj.txt", "a");
    FILE *undoW = fopen("undo.txt", "w");
    FILE *undoR = fopen("undo.txt", "r");
    // fisier in care stocam ultima versiune a tablei de joc
    FILE *resume = fopen("resume.txt", "w");
    int aux[4][4];
    int esteLoc = 1;
    srand(time(NULL)); // ca in exemplu
    int sageata;       // asta este tasta pe care o vom apasa
    int i, j, contor;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            aux[i][j] = tabla[i][j];
        }
    bool inGame = true, won = false, lost = false;
    while (inGame)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                fprintf(undoW, "%d ", tabla[i][j]);
                aux[i][j] = tabla[i][j];
            }
            fprintf(undoW, "\n");
        }
        fprintf(undoW, "%d", punctaj);
        clear();
        print(tabla); // de fiecare data cand se intra in bucla se reafiseaza tabla
        printw("\npunctajul tau este: %d", punctaj);
        refresh();
        sageata = getch();
        switch (sageata)
        {
        case KEY_UP:
            for (i = 0; i < 4; i++)
            {
                for (contor = 0; contor < 3; contor++)
                {

                    for (j = 1; j < 4; j++)
                    {
                        if (tabla[j - 1][i] == 0)
                        { // daca exista spatiu liber in sus copiem in casetuta libera valoare de jos
                            // iar casetuta punem 0
                            tabla[j - 1][i] = tabla[j][i];
                            tabla[j][i] = 0;
                        }
                        else if (tabla[j - 1][i] == tabla[j][i])
                        {
                            // daca cele doua valori sunt egale
                            // pe cea de mai sus o dublam
                            tabla[j - 1][i] = tabla[j - 1][i] * 2;
                            // in casetuta de jos punem 0
                            tabla[j][i] = 0;
                            contor = 3;
                            // marim punctajul
                            punctaj += tabla[j - 1][i];
                            break;
                        }
                    }
                }
            }
            int ok = 1, nrRandom, linie, coloana;
            esteLoc = 0;
            // aici punem pe o valoare random un numar random din multimea {2,4}
            do
            {
                // verificam daca este loc pentru o noua valoare
                for (i = 0; i < 4; i++)
                    for (j = 0; j < 4; j++)
                        if (tabla[i][j] == 0)
                            esteLoc = 1;
                if (esteLoc == 0)
                    break;
                // luam o linie random
                linie = rand() % 4;
                // luam o coloana random
                coloana = rand() % 4;
                // daca este liber spatiul respectiv
                if (tabla[linie][coloana] == 0)
                {
                    // facem o valoare random si o punem pe pozitia respectiva
                    nrRandom = rand() % 2;
                    if (nrRandom == 0)
                        tabla[linie][coloana] = 2;
                    else if (nrRandom == 1)
                        tabla[linie][coloana] = 4;
                    ok = 0;
                }

            } while (ok == 1);
            clear();
            print(tabla);
            refresh();
            break;
            // ANALOG PENTRU RESTUL SAGETILOR
        case KEY_DOWN:
            for (i = 0; i < 4; i++)
            {
                for (contor = 0; contor < 3; contor++)
                {
                    for (j = 2; j >= 0; j--)
                    {
                        if (tabla[j + 1][i] == 0)
                        {
                            tabla[j + 1][i] = tabla[j][i];
                            tabla[j][i] = 0;
                        }
                        else if (tabla[j + 1][i] == tabla[j][i])
                        {
                            tabla[j + 1][i] = tabla[j + 1][i] * 2;
                            tabla[j][i] = 0;
                            contor = 3;
                            punctaj += tabla[j + 1][i];
                            break;
                        }
                    }
                }
            }
            ok = 1;
            esteLoc = 0;
            do
            {
                for (i = 0; i < 4; i++)
                    for (j = 0; j < 4; j++)
                        if (tabla[i][j] == 0)
                            esteLoc = 1;
                if (esteLoc == 0)
                    break;
                linie = rand() % 4;
                coloana = rand() % 4;
                if (tabla[linie][coloana] == 0)
                {
                    nrRandom = rand() % 2;
                    if (nrRandom == 0)
                        tabla[linie][coloana] = 2;
                    else if (nrRandom == 1)
                        tabla[linie][coloana] = 4;
                    ok = 0;
                }

            } while (ok == 1);
            clear();
            print(tabla);
            refresh();
            break;
        case KEY_LEFT:
            for (i = 0; i < 4; i++)
            {
                for (contor = 0; contor < 3; contor++)
                {
                    for (j = 1; j < 4; j++)
                    {
                        if (tabla[i][j - 1] == 0)
                        {
                            tabla[i][j - 1] = tabla[i][j];
                            tabla[i][j] = 0;
                        }
                        else if (tabla[i][j - 1] == tabla[i][j])
                        {
                            tabla[i][j - 1] = tabla[i][j - 1] * 2;
                            tabla[i][j] = 0;
                            contor = 3;
                            punctaj += tabla[i][j - 1];
                            break;
                        }
                    }
                }
            }
            ok = 1;
            esteLoc = 0;
            do
            {
                for (i = 0; i < 4; i++)
                    for (j = 0; j < 4; j++)
                        if (tabla[i][j] == 0)
                            esteLoc = 1;
                if (esteLoc == 0)
                    break;
                linie = rand() % 4;
                coloana = rand() % 4;
                if (tabla[linie][coloana] == 0)
                {
                    nrRandom = rand() % 2;
                    if (nrRandom == 0)
                        tabla[linie][coloana] = 2;
                    else if (nrRandom == 1)
                        tabla[linie][coloana] = 4;
                    ok = 0;
                }

            } while (ok == 1);
            clear();
            print(tabla);
            refresh();
            break;
        case KEY_RIGHT:
            for (i = 0; i < 4; i++)
            {
                for (contor = 0; contor < 3; contor++)
                {
                    for (j = 2; j >= 0; j--)
                    {
                        if (tabla[i][j + 1] == 0)
                        {
                            tabla[i][j + 1] = tabla[i][j];
                            tabla[i][j] = 0;
                        }
                        else if (tabla[i][j + 1] == tabla[i][j])
                        {
                            tabla[i][j + 1] = tabla[i][j + 1] * 2;
                            tabla[i][j] = 0;
                            contor = 3;
                            punctaj += tabla[i][j + 1];
                            break;
                        }
                    }
                }
            }
            ok = 1;
            esteLoc = 0;
            do
            {
                for (i = 0; i < 4; i++)
                    for (j = 0; j < 4; j++)
                        if (tabla[i][j] == 0)
                            esteLoc = 1;
                if (esteLoc == 0)
                    break;
                linie = rand() % 4;
                coloana = rand() % 4;
                if (tabla[linie][coloana] == 0)
                {
                    nrRandom = rand() % 2;
                    if (nrRandom == 0)
                        tabla[linie][coloana] = 2;
                    else if (nrRandom == 1)
                        tabla[linie][coloana] = 4;
                    ok = 0;
                }

            } while (ok == 1);
            clear();
            print(tabla);
            refresh();
            break;
            // butonul de UNDO
        case 'u':
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    fscanf(undoR, "%d", &tabla[i][j]);
            fscanf(undoR, "%d", &punctaj);
            break;
        // butonul de QUIT
        case 'q':
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    fprintf(resume, "%d ", tabla[i][j]);
                }
                fprintf(resume, "\n");
            }
            fprintf(resume, "%d", punctaj);
            fprintf(fisier, "%d\n", punctaj);
            clear();
            // afisam un mesaj de final folosind culoarea galbena
            start_color();
            init_pair(13, COLOR_YELLOW, COLOR_BLACK);
            attron(COLOR_PAIR(13) | A_BOLD);
            printw("La revedere!");
            attroff(COLOR_PAIR(13) | A_BOLD);
            refresh();
            getch();
            return;
        default:
            break;
        }
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                if (tabla[i][j] == 2048)
                {
                    inGame = false;
                    won = true;
                }
        if (lose(tabla) == 0)
        {
            inGame = false;
            lost = true;
        }
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                aux[i][j] = tabla[i][j];
    }
    if (lost == true)
    {
        getch();
        clear();
        start_color();
        // afisam un mesaj de final folosind culoarea rosie
        init_pair(12, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(12) | A_BOLD);
        printw("AI PIERDUT");
        attroff(COLOR_PAIR(12) | A_BOLD);
        refresh();
        fprintf(fisier, "%d\n", punctaj);
        getch();
    }
    if (won == true)
    {
        clear();
        start_color();
        // afisam un mesaj de final folosind culoarea verde
        init_pair(14, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(14));
        printw("AI CASTIGAT!");
        attroff(COLOR_PAIR(14));
        refresh();
        fprintf(fisier, "%d\n", punctaj);
        getch();
    }
    fclose(fisier);
    fclose(resume);
    fclose(undoW);
}

void resume(int tabla[4][4], int points)
{
    logic(tabla, points);
}

int resumePoints(int tabla[4][4])
{
    // am creat aceasta functie pentru a citi punctajul din sesiunea precedenta
    // pentru a il folosi cand se apasa resume
    int punctaj, i, j;
    FILE *resume = fopen("resume.txt", "r");
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            fscanf(resume, "%d", &tabla[i][j]);
    fscanf(resume, "%d", &punctaj);
    return punctaj;
}

void start(int tabla[4][4])
{
    FILE *resumeFile = fopen("resume.txt", "r");
    // initializam un fisier pentru a pastra in el ulti varianta a tablei de joc
    // astfel can vom volosi resume vom porni jocul de la ultima versiune a tablei de joc
    keypad(stdscr, true); // pentru a folosi sagetile
    curs_set(0);          // ascunderea cursorului
    char *menu[] = {"New Game", "Resume", "Quit"};
    int tablaResume[4][4];
    int punctaj = 0, marime = 3, points, i, selectat = 0, coloana = (COLS - 20) / 2, ales;
    bool merge = true;
    while (merge)
    {
        clear();
        for (i = 0; i < marime; i++)
        {
            if (selectat == i)
                attron(A_REVERSE);
            mvprintw(LINES / 2 + i, coloana, "%s", menu[i]);
            attroff(A_REVERSE);
        }
        ales = getch(); // citim un caracter(sagetile)
        switch (ales)
        {
        case KEY_UP:
            if (selectat >= 0)
            // daca butonul selectat este pe pozitia 1 sau 2 si apasam sageata in sus
            //  pozitia va scadea cu o unitate
            {
                selectat--;
                // daca pozitia era 0 si apasam pe sageata in sus atunci pozitia
                // va deveni 2
                if (selectat == -1)
                    selectat = 2;
            }
            break;
            // analog pentru restul sagetilor
        case KEY_DOWN:
            if (selectat <= 2)
            {
                selectat++;
                if (selectat == 3)
                    selectat = 0;
            }
            break;
        default:
            break;
        }
        // 10 este codul ASCII al lui enter
        // deci cand se apasa enter este selectat butonul de la pozitia respectiva
        if (ales == 10)
        {
            switch (selectat)
            {
                // new game
            case 0:
                merge = false;
                newGame(tabla);
                logic(tabla, punctaj);
                break;
                // resume
            case 1:
                points = resumePoints(tablaResume);
                merge = false;
                resume(tablaResume, points);
                break;
                // quit
            case 2:
                return;
            default:
                break;
            }
        }
    }
    fclose(resumeFile);
}

int main()
{
    int tabla[4][4] = {0};
    initscr(); // inceput

    start(tabla);

    endwin(); // final
    return 0;
}