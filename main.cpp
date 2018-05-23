#include <iostream>
#include <cctype>
#include <cmath>

int kol_znak(char a);
void add_to_exit(char * exit,int  & i_exit , char ch);
void add_to_sign(char * sign, int & i_sig, char ch);
void sign_to_exit(char *exit, int & i_exit, char *sign, int & i_sign);
double licz(char * tab, int d1, int d2);

int main()
{
    using namespace std;

    char tab[100];
    char odp[200];
    int i_odp = 0;
    char znak[100] = { '\0' };
    int i_znak = 0;
    char z = 'k';
    while(z=='k'||z=='K') {
        cout << "Podaj rownanie  w standardowej notacji <bez spacji>,\nznaki operacji matematycznych to: ( ) ^ * / % + -\n";
        cin.getline(tab, 99);
        i_znak=0;
        int i;
        for (i = 0; tab[i] != '\0'; i++) {
            switch (tab[i]) {
                case '(':
                    add_to_sign(znak, i_znak, tab[i]);
                    break;
                case '^':
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                    if (i_znak == 0 || kol_znak(tab[i]) > kol_znak(znak[i_znak - 1]))
                        add_to_sign(znak, i_znak, tab[i]);
                    else {
                        while (kol_znak(tab[i]) <= kol_znak(znak[i_znak - 1]))
                            sign_to_exit(odp, i_odp, znak, i_znak);
                        add_to_sign(znak, i_znak, tab[i]);
                    }
                    break;
                case ')':
                    while (znak[i_znak - 1] != '(')
                        sign_to_exit(odp, i_odp, znak, i_znak);
                    znak[i_znak - 1] = '\0';
                    --i_znak;
                    break;
                default:
                    add_to_exit(odp, i_odp, tab[i]);
                    if (tab[i] == '.' || tab[i] == ',' || isdigit(tab[i + 1]) || tab[i + 1] == ',' ||
                        tab[i + 1] == '.')
                        --i_odp;
                    break;
            }
        }
        while (i_znak != 0)
            sign_to_exit(odp, i_odp, znak, i_znak);
        cout << "W odwroconej notacji polskiej:\n";
        for (int j = 0; j < i_odp; j++)
            cout << odp[j];
        double liczby[100] = { '\0' };
        int i_liczby = 0;
        char znaki[100] = { '\0' };
        int i_znak = 0;
        double wynik = 0;
        int t1, t2;
        t1 = 0;
        t2 = 0;
        for ( i = 0; odp[i] != '\0'; i++) {
            double x1, x2;
            switch (odp[i]) {
                case '+':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby]=0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x1 + x2;
                    i_liczby++;
                    break;
                case '-':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby]=0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x2 - x1;
                    i_liczby++;
                    break;
                case '*':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby]=0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x2 * x1;
                    i_liczby++;
                    break;
                case '/':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby]=0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = x2 / x1;
                    i_liczby++;
                    break;
                case '%':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby]=0;
                    i_liczby--;
                    x2 = liczby[i_liczby];
                    liczby[i_liczby] = (int)x2 % (int)x1;
                    i_liczby++;
                    break;
                case '^':
                    i_liczby--;
                    x1 = liczby[i_liczby];
                    liczby[i_liczby]=0;
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
                    liczby[i_liczby] = licz(odp + i, t1,0);
                    break;
                case ' ':
                    if (isdigit(odp[i - 1])|| odp[i - 1]=='.'|| odp[i - 1] == ',') {
                        liczby[i_liczby] +=licz(odp+i, t1,t2);
                        i_liczby++;
                        t1 = 0;
                        t2 = 0;
                    }
                    break;
            }
        }
        cout << "\nWynik: " << liczby[i_liczby-1] << endl;
        cout <<"\npodaj <k> aby zadac kolejne rownanie: ";
        cin >> z;
        for (int i=0;i<100;i++)
            odp[i] ='\0';
        i_odp = 0;
        for (int i=0;i<200;i++)
            znak[i] ='\0';
        i_znak = 0;
        cin.sync();
    }
    cout << "To bajo...";
    return 0;
}

int kol_znak(char a)
{
    if (a == '^')
        return 3;
    else if (a == '*' || a == '/'||a=='%')
        return 2;
    else if (a == '+' || a == '-'||a==')')
        return 1;
    else
        return 0;
}


void add_to_exit(char * exit, int  & i_exit, char ch)
{
    *(exit+i_exit) = ch;
    *(exit +i_exit+1)=' ';
    i_exit+=2;

}

void add_to_sign(char * sign, int & i_sig, char ch)
{
    *(sign + i_sig) = ch;
    ++i_sig;
}

void sign_to_exit(char *exit, int & i_exit, char *sign, int & i_sign)
{
    i_sign--;
    *(exit + i_exit) = *(sign + i_sign);
    *(sign + i_sign) = '\0';
    *(exit +i_exit+1)=' ';
    i_exit+=2;
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
        for ( int j = 1; j<i ; j++)
        {
            y = *(pc+j) - 48;
            m += y * pow(10, -j);
        }
    }
    return m;
}

