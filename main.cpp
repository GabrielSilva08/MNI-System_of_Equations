#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "src/matrix.hpp"
#include "src/linear_system_solver.hpp"

// TODO: 
// 1. MOSTRAR QUAIS CONEXÕES ROMPERAM
// 2. TRATAR CASOS EM QUE Determinante = 0 OU QUANDO TEMOS INFINITAS SOLUÇÕES

using namespace std;

// Utilitários de interface

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForUser() {
    cout << "\nPressione ENTER para voltar ao menu...";
    cin.get();
}

void printVector(const vector<double>& v, const string& name) {
    cout << name << " = [ ";
    for (double x : v)
        cout << fixed << setprecision(4) << x << " ";
    cout << "]\n";
}

// Programa principal

int n = 0, option;
Matrix A(1, 1);
vector<double> f;
bool dataLoaded = false;


void insertMatrixAandVectorf(){
    clearScreen();
    cout << "=========== INSERCAO DE DADOS ===========\n\n";
    cout << "Digite o numero de deslocamentos n (d1, d2, ..., dn): ";
    cin >> n;

    A = Matrix(n, n);
    f.resize(n);

    do{
    cout << "\nDigite os elementos da matriz A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A(i, j);
    
    if(A.determinant() == 0){
        cout<< "\nO determinante da matriz de parametros nao pode ser igual a 0, por favor insira outra matriz.";
    }
    } while(A.determinant() == 0);

    cout << "\nDigite os elementos do vetor f:\n";
    for (int i = 0; i < n; i++)
        cin >> f[i];

    dataLoaded = true;
    waitForUser();
}

void viewMatrixA(){
    clearScreen();
    if (!dataLoaded) {
        cout << "Nenhuma matriz carregada! Inicialize seus elementos.\n";
    } else {
        cout << "=========== MATRIZ A ===========\n\n";
        A.print();
    }
    waitForUser();
}

void viewVectorf(){
    clearScreen();
    if (!dataLoaded) {
        cout << "Nenhum vetor carregado! Inicialize seus elementos.\n";
    } else {
        cout << "=========== VETOR f ===========\n\n";
        printVector(f, "f^T");
    }
    waitForUser();
}



void showLUDecomposition(){
    clearScreen();
    if (!dataLoaded) {
        cout << "Nenhuma matriz carregada! Inicialize seus elementos.\n";
    } else {
        Matrix L(n, n), U(n, n);
        decomposeLU(A, L, U);

        cout << "========== DECOMPOSICAO LU ==========\n\n";
        cout << "Matriz L:\n";
        L.print();
        cout << "\nMatriz U:\n";
        U.print();
    }
    waitForUser();
}

void showLDPDecomposition(){
    clearScreen();
    if (!dataLoaded) {
        cout << "Nenhuma matriz carregada! Inicialize seus elementos.\n";
    } else {
        Matrix L(n, n), D(n, n), P(n, n);
        decomposeLDP(A, L, D, P);

        cout << "========== DECOMPOSICAO LDP ==========\n\n";
        cout << "Matriz L:\n";
        L.print();
        cout << "\nMatriz D:\n";
        D.print();
        cout << "\nMatriz P:\n";
        P.print();
    }
    waitForUser();
}

void solveSystem(){
    clearScreen();
    if (!dataLoaded){
        cout << "\n>>> Nenhuma matriz carregada! Inicialize seus elementos.\n";
    }else{
        cout << "========== ANALISE DO JATO ==========\n\n";
        Matrix Lr(n, n), Ur(n, n);
        decomposeLU(A, Lr, Ur);
        vector<double> dLU = solveLU(Lr, Ur, f);

        Matrix Lr2(n, n), Dr(n, n), Pr(n, n);
        decomposeLDP(A, Lr2, Dr, Pr);
        vector<double> dLDP = solveLDP(Lr2, Dr, Pr, f);

        cout << "\n====== SOLUCAO PELO METODO LU =====\n";
        bool explodeLU = false;
        for (int i = 0; i < n; i++){
            cout << "d" << i + 1 << " = " << dLU[i] << " |d| = " << abs(dLU[i]);
            if (abs(dLU[i]) > 2.0){
                explodeLU = true;
                cout << " -> Deslocamento " << i+1 << " passou do limite maximo!";
            }
            cout <<  "\n";
        }
        cout << (explodeLU ? ">>> JATO EXPLODE (LU)\n" : ">>> JATO ESTAVEL (LU)\n");

        cout << "\n===== SOLUCAO PELO METODO LDP =====\n";
        bool explodeLDP = false;
        for (int i = 0; i < n; i++) {
            cout << "d" << i + 1 << " = " << dLDP[i] << " |d| = " << abs(dLDP[i]);
            if (abs(dLDP[i]) > 2.0){
                explodeLDP = true;
                cout << " -> Deslocamento " << i+1 << " passou do limite maximo!";
            }
            cout <<  "\n";
        }
        cout << (explodeLDP ? ">>> JATO EXPLODE (LDP)\n" : ">>> JATO ESTAVEL (LDP)\n");
    }
    waitForUser();
}

int main() {
    cout << fixed << setprecision(4);
    // Main loop
    do {
        clearScreen();
        cout << "====================================\n";
        cout << "   SISTEMA DE ANALISE DO JATO\n";
        cout << "====================================\n";
        cout << "1 - Inserir / Atualizar matriz A e vetor f\n";
        cout << "2 - Visualizar matriz A\n";
        cout << "3 - Visualizar vetor f\n";
        cout << "4 - Mostrar decomposicao LU\n";
        cout << "5 - Mostrar decomposicao LDP\n";
        cout << "6 - Resolver sistema e analisar jato\n";
        cout << "0 - Sair\n";
        cout << "====================================\n";
        cout << "Opcao: ";
        cin >> option;
        cin.ignore(); // limpa buffer

        switch (option){
            case 1: 
                insertMatrixAandVectorf();
                break;

            case 2:
                viewMatrixA();
                break;

            case 3:
                viewVectorf();
                break;

            case 4:
                showLUDecomposition();
                break;

            case 5:
                showLDPDecomposition();
                break;

            case 6:
                solveSystem();
                break;

            case 0:
                clearScreen();
                cout << "Encerrando o sistema...\n";
                break;

            default:
                clearScreen();
                cout << "Opcao invalida! Tente novamente.\n";
                waitForUser();
                break;
        }
    } while (option != 0);
    return 0;
}
