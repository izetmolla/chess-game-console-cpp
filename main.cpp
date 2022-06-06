// C++ program for Knight Tour problem
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

#define N 8

// Krijimi i listes se Lidhur
class Node
{
public:
    int data;
    Node *next;
};
// Shtimi i nje elementi te ri ne liste
void push(Node **head_ref, int new_data)
{
    /* 1. allocate node */
    Node *new_node = new Node();
    /* 2. put in the data */
    new_node->data = new_data;
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);
    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}
// Afishimi i elementeve te listes
void printList(Node *node)
{
    cout << "Ushtrimi 3 - ELEMMENTET E LISTES SE LIDHUR" << endl;
    while (node != NULL)
    {
        cout << " " << node->data;
        node = node->next;
    }
}
// Popullimi i listes nga tabela e shahut
void populloListen(int sol[N][N])
{
    Node *head = NULL;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            push(&head, sol[x][y]);
        }
    }
    printList(head);
}

// Fundi metodave te listes
int solveKTUtil(int x, int y, int movei, int sol[N][N], int xMove[], int yMove[]);

/* Një funksion i dobishëm për të kontrolluar nëse i,j janë
indekse të vlefshme për tabelën e shahut N*N */
int isSafe(int x, int y, int sol[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}
/* Një funksion i dobishëm për printim
matrica e zgjidhjes sol[N][N] */
void printSolution(int sol[N][N])
{
    cout << "Ushrimi 1 - AFISHIMI I Tabeles se SHAHUT" << endl;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
            cout << " " << setw(2) << sol[x][y] << " ";
        cout << endl;
    }
}

// Kalimi i 64 adresave te levizjes ne nje skedar te quajtur shah.txt
void storeToTxt(int sol[N][N])
{
    cout << "Ushrimi 2 - 64 adresat e levizjes u ruajten nse skedarin shah.txt" << endl;
    ofstream MyFile("shah.txt");
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            MyFile << " " << setw(2) << sol[x][y] << " ";
        }
        MyFile << endl;
    }
}

/* Ky funksion zgjidh problemin e Knight Tour duke përdorur
Tërheqja prapa. Ky funksion përdor kryesisht solveKTUtil()
për të zgjidhur problemin. Ai kthehet false nëse nuk është i plotë
turne është e mundur, përndryshe kthimi i vërtetë printon
turne. */
int solveKT()
{
    int sol[N][N];
    /* Inicializimi i matricës së zgjidhjes */
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;

    /* xMove[] dhe yMove[] përcaktojnë lëvizjen tjetër të Knight.
      xMove[] është për vlerën tjetër të koordinatës x
      yMove[] është për vlerën tjetër të koordinatës y */
    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    // Meqenëse Kalorësi është fillimisht në bllokun e parë
    sol[0][0] = 0;

    /* Filloni nga 0,0 dhe eksploroni të gjitha turnet duke përdorur
     ZgjidhKTUtil() */
    if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0)
    {
        cout << "Solution does not exist";
        return 0;
    }
    else
    {
        printSolution(sol); // afishon tabelen e shahut
        storeToTxt(sol);    // ruan tabelen e shahut ne Txt file
        populloListen(sol); // Popullo listen me elementet e tabelse se shahut
        return 1;
    }
}
/* Një funksion rekurziv i ndihmës për të zgjidhur Knight Tour
problem */
int solveKTUtil(int x, int y, int movei, int sol[N][N], int xMove[8], int yMove[8])
{
    int k, next_x, next_y;
    if (movei == N * N)
        return 1;

    /* Provoni të gjitha lëvizjet e ardhshme nga
     koordinata aktuale x, y */
    for (k = 0; k < 8; k++)
    {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol))
        {
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove) == 1)
            {
                return 1;
            }
            else
            {
                // backtracking
                sol[next_x][next_y] = -1;
            }
        }
    }
    return 0;
}

// Driver Code
int main()
{

    solveKT();

    return 0;
}