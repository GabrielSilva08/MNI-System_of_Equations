#include "linear_system_solver.hpp"

// =======================
// Substituições
// =======================

std::vector<double> LinearSystemSolver::forwardSubstitution(
    const Matrix& L, const std::vector<double>& b) {

    int n = b.size();
    std::vector<double> y(n, 0.0);

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += L(i, j) * y[j];
        y[i] = b[i] - sum;
    }
    return y;
}

std::vector<double> LinearSystemSolver::backwardSubstitution(
    const Matrix& U, const std::vector<double>& y) {

    int n = y.size();
    std::vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += U(i, j) * x[j];
        x[i] = (y[i] - sum) / U(i, i);
    }
    return x;
}

// =======================
// Fatoração LU
// =======================

void LinearSystemSolver::decomposeLU(const Matrix& A, Matrix& L, Matrix& U) {
    int n = A.getRows();

    L = Matrix::identity(n);
    U = Matrix(n, n);

    for (int k = 0; k < n; k++) {
        for (int j = k; j < n; j++) {
            double sum = 0.0;
            for (int s = 0; s < k; s++)
                sum += L(k, s) * U(s, j);
            U(k, j) = A(k, j) - sum;
        }

        for (int i = k + 1; i < n; i++) {
            double sum = 0.0;
            for (int s = 0; s < k; s++)
                sum += L(i, s) * U(s, k);
            L(i, k) = (A(i, k) - sum) / U(k, k);
        }
    }
}

std::vector<double> LinearSystemSolver::solveLU(
    const Matrix& L, const Matrix& U, const std::vector<double>& f) {

    std::vector<double> y = forwardSubstitution(L, f);
    return backwardSubstitution(U, y);
}

// =======================
// Fatoração LDP
// =======================

void LinearSystemSolver::decomposeLDP(
    const Matrix& A, Matrix& L, Matrix& D, Matrix& P) {

    int n = A.getRows();
    Matrix U(n, n);
    decomposeLU(A, L, U);

    std::vector<double> diag(n);
    for (int i = 0; i < n; i++)
        diag[i] = U(i, i);

    D = Matrix::diagonal(diag);
    P = Matrix::identity(n);

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (diag[i] != 0.0)
                P(i, j) = U(i, j) / diag[i];
}

std::vector<double> LinearSystemSolver::solveLDP(
    const Matrix& L, const Matrix& D,
    const Matrix& P, const std::vector<double>& f) {

    std::vector<double> y = forwardSubstitution(L, f);

    int n = y.size();
    std::vector<double> z(n);
    for (int i = 0; i < n; i++)
        z[i] = y[i] / D(i, i);

    return backwardSubstitution(P, z);
}
