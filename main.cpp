// onp z.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <cctype>
#include <cmath>


double licz(char * tab, int d1, int d2);

int main() {
    double liczby[100] = { '\0' };
    int i_liczby = 0;
    char tab[100];
    int t1, t2;
    t1 = t2 = 0;
    char ch ='n';
    while (ch=='n'||ch=='N') {
        std::cout << "Podaj rownanie w odwroconej notacji polskiej (oddzielajac spacjami liczby i znaki): " << std::endl;
        std::cin.getline(tab, 100);
        for (int i = 0; tab[i] != '\0'; i++) {
            double x1, x2;
            switch (tab[i]) {
                case '+':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby] = 0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x1 + x2;
                    i_liczby++;
                    break;
                case '-':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby] = 0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x2 - x1;
                    i_liczby++;
                    break;
                case '*':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby] = 0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x2 * x1;
                    i_liczby++;
                    break;
                case '/':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby] = 0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x2 / x1;
                    i_liczby++;
                    break;
                case '%':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby] = 0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = (int) x2 % (int) x1;
                    i_liczby++;
                    break;
                case '^':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby] = 0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = pow(x2, x1);
                    i_liczby++;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    t1++;
                    break;
                case '.':
                case ',':
                    t2 = 1;
                    liczby[i_liczby] = licz(tab + i, t1, 0);
                    break;
                case ' ':
                    if (isdigit(tab[i - 1]) || tab[i - 1] == '.' || tab[i - 1] == ',') {
                        liczby[i_liczby] += licz(tab + i, t1, t2);
                        i_liczby++;
                        t1 = 0;
                        t2 = 0;
                    }
                    break;
            }
        }
        std::cout << "Wynik: " << liczby[i_liczby - 1] << std::endl;
        std::cout << "Wpisz <n> aby dodac nastepne rownanie.";
        std::cin >> ch;
        std::cin.sync();
    }
    std::cout << "Do widzenia!";
    return 0;
}

double licz(char * tab, int d1,int d2)
{
    double m = 0;
    double y;
    int i;
    if (d2 == 0)
    {
        for (int i = 1; i <= d1; i++)
        {
            y = *(tab - i) - 48;
            m += y * pow(10, i - 1);
        }
    }
    else if (d2 == 1)
    {
        int k = 1;
        char * pc;
        for (i = 1; *(tab - i) != '.' && *(tab - i) != ','; i++) {}
        pc = (tab - i);
        std::cout<< "i = " << i << "  *pc^- = " << *pc  << std::endl;
        for ( int j = 1; j<i ; j++)
        {
            y = *(pc+j) - 48;
            m += y * pow(10, -j);
        }
    }
    return m;
}