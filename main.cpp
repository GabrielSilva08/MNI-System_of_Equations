#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "src/matrix.hpp"
#include "src/linear_system_solver.hpp"

// Utilitários de interface

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForUser() {
    std::cout << "\nPressione ENTER para voltar ao menu...";
    std::cin.ignore();
    std::cin.get();
}

void printVector(const std::vector<double>& v, const std::string& name) {
    std::cout << name << " = [ ";
    for (double x : v)
        std::cout << std::fixed << std::setprecision(4) << x << " ";
    std::cout << "]\n";
}

// Programa principal

int main() {
    int n = 0, option;
    Matrix A(1, 1);
    std::vector<double> f;
    bool dataLoaded = false;
    // Main loop
    do {
        clearScreen();
        std::cout << "====================================\n";
        std::cout << "   SISTEMA DE ANALISE DO JATO\n";
        std::cout << "====================================\n";
        std::cout << "1 - Inserir / Atualizar matriz A e vetor f\n";
        std::cout << "2 - Visualizar matriz A\n";
        std::cout << "3 - Visualizar vetor f\n";
        std::cout << "4 - Mostrar decomposicao LU\n";
        std::cout << "5 - Mostrar decomposicao LDP\n";
        std::cout << "6 - Resolver sistema e analisar jato\n";
        std::cout << "0 - Sair\n";
        std::cout << "====================================\n";
        std::cout << "Opcao: ";
        std::cin >> option;
        std::cin.ignore(); // limpa buffer

        switch (option){
            case 1: {
                clearScreen();
                std::cout << "INSERCAO DE DADOS\n\n";
                std::cout << "Digite o numero de deslocamentos n: ";
                std::cin >> n;

                A = Matrix(n, n);
                f.resize(n);

                std::cout << "\nDigite os elementos da matriz A:\n";
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        std::cin >> A(i, j);

                std::cout << "\nDigite os elementos do vetor f:\n";
                for (int i = 0; i < n; i++)
                    std::cin >> f[i];

                dataLoaded = true;
                waitForUser();
                break;
            }

            case 2: {
                clearScreen();
                if (!dataLoaded) {
                    std::cout << "Nenhuma matriz carregada.\n";
                } else {
                    std::cout << "MATRIZ A\n\n";
                    A.print();
                }
                waitForUser();
                break;
            }

            case 3: {
                clearScreen();
                if (!dataLoaded) {
                    std::cout << "Nenhum vetor carregado.\n";
                } else {
                    std::cout << "VETOR f\n\n";
                    printVector(f, "f");
                }
                waitForUser();
                break;
            }

            case 4: {
                clearScreen();
                if (!dataLoaded) {
                    std::cout << "Dados nao carregados.\n";
                } else {
                    Matrix L(n, n), U(n, n);
                    decomposeLU(A, L, U);

                    std::cout << "DECOMPOSICAO LU\n\n";
                    std::cout << "Matriz L:\n";
                    L.print();
                    std::cout << "\nMatriz U:\n";
                    U.print();
                }
                waitForUser();
                break;
            }

            case 5: {
                clearScreen();
                if (!dataLoaded) {
                    std::cout << "Dados nao carregados.\n";
                } else {
                    Matrix L(n, n), D(n, n), P(n, n);
                    decomposeLDP(A, L, D, P);

                    std::cout << "DECOMPOSICAO LDP\n\n";
                    std::cout << "Matriz L:\n";
                    L.print();
                    std::cout << "\nMatriz D:\n";
                    D.print();
                    std::cout << "\nMatriz P:\n";
                    P.print();
                }
                waitForUser();
                break;
            }

            case 6: {
                clearScreen();
                if (!dataLoaded) {
                    std::cout << "Dados nao carregados.\n";
                } else {
                    Matrix L(n, n), U(n, n);
                    decomposeLU(A, L, U);
                    std::vector<double> dLU =
                        solveLU(L, U, f);

                    Matrix L2(n, n), D(n, n), P(n, n);
                    decomposeLDP(A, L2, D, P);
                    std::vector<double> dLDP =
                        solveLDP(L2, D, P, f);

                    std::cout << "ANALISE DO JATO\n\n";

                    bool explode = false;
                    for (int i = 0; i < n; i++) {
                        std::cout << "d" << i + 1 << " = "
                                  << dLU[i]
                                  << " |d| = " << std::abs(dLU[i]) << "\n";
                        if (std::abs(dLU[i]) > 2.0)
                            explode = true;
                    }

                    std::cout << "\nRESULTADO: ";
                    std::cout << (explode ?
                        "JATO EXPLODE\n" :
                        "JATO ESTAVEL\n");
            }
            waitForUser();
            break;
        }

        case 0:
            clearScreen();
            std::cout << "Encerrando o sistema...\n";
            break;

        default:
            clearScreen();
            std::cout << "Opcao invalida.\n";
            waitForUser();
        }

    } while (option != 0);

    return 0;
}
