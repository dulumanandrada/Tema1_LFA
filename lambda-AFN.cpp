#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>
#include <unordered_map>
 
using namespace std;
 
ifstream fin ("afn.in");
ofstream fout("afn.out");
 
int n, m;                       ///nr de noduri, respectiv nr de muchii
int nr_finale, F[1001];         ///starile finale
int viz[1001];                  ///vectorul de vizitare
int q0;                         ///starea initiala
int drum[1001];
bool OK;
char s[1001];                    ///cuvantul primit spre verificare
unordered_map<char, vector<int>> M[1001];
queue<int> Q1;                  ///vom retine starile in care putem ajunge cu lambda

queue<int> Q2;                  ///vom retine starile in care putem ajunge din
                                ///Q1 folosindu-ne de caracterul curent
 
void Parcurgere(int q, int iq, int l);
void Parcurgere_lambda(int q, int iq, int l);
 
///reinitializare
void Reinitializare()
{
    for(int i = 0; i < n; i++)
        viz[i] = 0;
    while(Q1.empty() == 0)
        Q1.pop();
    while(Q2.empty() == 0)
        Q2.pop();
    int i = 1;
    while(drum[i] != 0)
    {
        drum[i] = 0;
        i++;
    }
 
}
 
///verificare daca un cuvant este acceptat sau nu de limbaj
bool Evaluare(char s[])
{
    int i, j, x, y;
    int lungime = strlen(s);
    Q1.push(q0);            ///incarcam Q1 cu starea initiala
    viz[q0] = 1;            ///marcam starea initiala ca fiind prima vizitata
    for(i = 0; i < lungime; i++)
    {
        j = i + 1;
        if(Q1.empty())
            return 0;       ///nu s-a putut ajunge in nicio stare
        if(i == 0)
            Q2.push(Q1.front());
        while(!Q1.empty())  ///punem in Q2 starile in care putem ajunge cu lambda
        {
            x = Q1.front();
            Q1.pop();
            Q2.push(x);
            for(int y : M[x]['#'])
                if(viz[y] != j)
                {
                    viz[y] = j;
                    Q2.push(y); 
                }
        }
 
        while(!Q2.empty())  ///punem in Q1 starile in care putem ajunge cu caracterul curent
        {
            x = Q2.front();
            Q2.pop();
            for(int y : M[x][s[i]])
                if(viz[y] != j + 1)
                {
                    viz[y] = j + 1;
                    Q1.push(y);
                }
        }
    }
 
    while(!Q1.empty())      ///chiar daca s-a terminat cuvantul,
    {                       ///inca mai putem parcurge graful cu lambda
        x = Q1.front();
        Q1.pop();
        Q2.push(x);
 
        for(int y : M[x]['#'])
            if(viz[y] != lungime + 1)
            {
                viz[y] = lungime + 1;
                Q2.push(y);
            }
    }
 
    while(!Q2.empty())
    {
        x = Q2.front();
        Q2.pop();
        for(i = 1; i <= nr_finale; i++)
            if(F[i] == x)
                return 1;
    }
    return 0;
}
 
 
///test de stare finala
bool SolutieFinala(int q, int l)
{
    if(l == strlen(s))
    {
        for(int i = 1; i <= nr_finale; i++)
            if(F[i] == q)
                return 1;
    }
    return 0;
}
 
void Afisare(int z)
{
    for(int i = 0; i <= z; i++)
        fout << drum[i] << " ";
    fout << "\n";
}
 
void Parcurgere(int q, int iq, int l)
{
    if(!OK)                 ///inca nu am gasit un drum 
    {
        drum[iq] = q;
        if(SolutieFinala(q, l))
        {
            Afisare(iq);
            OK = 1;         ///am gasit drum valid, iesim.
        }
        else
        {
            for(auto L : M[q])
            {
                for(int x : M[q][L.first])
                    if(L.first == '#')                                         ///daca gasim o muchie cu lambda
                        Parcurgere(x, iq + 1, l);                              ///mergem in continuare, insa ramanand la litera curenta
                    else if(L.first == s[l]) Parcurgere(x, iq + 1, ++l);       ///daca gasim mucie cu litera curenta
            }                                                                  ///mergem in continuare, cu urmatoarea litera
        }
    }
}
 
int main()
{
    int i;
    bool ok;
    int nr_cuv;
 
    ///citim graful aferent limbajului
    fin >> n >> m;
    for(i = 1; i <= m; i++)
    {
        int st, dr;
        char e;
        fin >> st >> dr >> e;
        M[st][e].push_back(dr);
    }
 
    ///citim starea initiala si starile finale
    fin >> q0;
    fin >> nr_finale;
    for(i = 1; i <= nr_finale; i++)
        fin >> F[i];
 
    ///citim cuvintele date spre verificare
    fin >> nr_cuv;
    for(i = 1; i <= nr_cuv; i++)
    {
        fin >> s;
        ok = Evaluare(s);
        if(ok == 1)
        {
            fout << "DA \n";
            Reinitializare();
            fout << "Traseu: ";
            OK = 0;
            Parcurgere(q0, 0, 0);
        }
        else
        {
            fout << "NU \n";
        }
        Reinitializare();
    }
 
}