#include <iostream>
#include <vector>
#include <cmath>

#include "src/matrix.hpp"
#include "src/linear_system_solver.hpp"

int main() {
    int n;
    // 1. Leitura dos elementos de entrada
    std::cout << "Digite o numero de deslocamentos n: ";
    std::cin >> n;

    Matrix A(n, n);
    std::vector<double> f(n);

    std::cout << "\nDigite os elementos da matriz A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> A(i, j);

    std::cout << "\nDigite os elementos do vetor f:\n";
    for (int i = 0; i < n; i++)
        std::cin >> f[i];

    // 2. Resolução via método LU
    Matrix L(n, n), U(n, n);
    LinearSystemSolver::decomposeLU(A, L, U);
    std::vector<double> dLU = LinearSystemSolver::solveLU(L, U, f);

    // 3. Resolução via método LDP
    Matrix L2(n, n), D(n, n), P(n, n);
    LinearSystemSolver::decomposeLDP(A, L2, D, P);
    std::vector<double> dLDP = LinearSystemSolver::solveLDP(L2, D, P, f);

    // 4. Impressão dos resultados de saída
    std::cout << "\n=== Solucao pelo metodo LU ===\n";
    bool explodeLU = false;
    for (int i = 0; i < n; i++) {
        std::cout << "d" << i + 1 << " = " << dLU[i]
                  << " |d| = " << std::abs(dLU[i]) << "\n";
        if (std::abs(dLU[i]) > 2.0)
            explodeLU = true;
    }

    std::cout << (explodeLU ? ">>> JATO EXPLODE (LU)\n" : ">>> JATO ESTAVEL (LU)\n");

    std::cout << "\n=== Solucao pelo metodo LDP ===\n";
    bool explodeLDP = false;
    for (int i = 0; i < n; i++) {
        std::cout << "d" << i + 1 << " = " << dLDP[i]
                  << " |d| = " << std::abs(dLDP[i]) << "\n";
        if (std::abs(dLDP[i]) > 2.0)
            explodeLDP = true;
    }

    std::cout << (explodeLDP ?
        ">>> JATO EXPLODE (LDP)\n" :
        ">>> JATO ESTAVEL (LDP)\n");
    return 0;
}
