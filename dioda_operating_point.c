#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ITER 100
#define TOL 1e-6

// Fungsi f(Vd)
double diode_function(double Vd, double Vin, double R, double Is, double n, double Vt) {
    return Is * (exp(Vd / (n * Vt)) - 1.0) - (Vin - Vd) / R;
}

// Turunan f'(Vd)
double diode_derivative(double Vd, double R, double Is, double n, double Vt) {
    return (Is / (n * Vt)) * exp(Vd / (n * Vt)) + 1.0 / R;
}

int main() {
    double Vin, R, Is, n, Vt;
    double Vd = 0.7; // Initial guess
    double Vd_next, error;
    int iter = 0;

    // Input
    printf("Masukkan nilai Vin (V): ");
    scanf("%lf", &Vin);
    printf("Masukkan nilai R (Ohm): ");
    scanf("%lf", &R);
    printf("Masukkan nilai Is (A): ");
    scanf("%lf", &Is);
    printf("Masukkan nilai n (faktor idealitas): ");
    scanf("%lf", &n);
    printf("Masukkan nilai Vt (tegangan termal): ");
    scanf("%lf", &Vt);

    // Newton-Raphson
    FILE *fp = fopen("dioda_output.txt", "w");
    if (!fp) {
        printf("Gagal membuka file output.\n");
        return 1;
    }

    fprintf(fp, "=== Hasil Analisis Operating Point Dioda ===\n");
    fprintf(fp, "Vin = %.6f V\nR = %.2f Ohm\nIs = %.2e A\nn = %.2f\nVt = %.6f V\n\n", Vin, R, Is, n, Vt);
    fprintf(fp, "Iterasi Newton-Raphson:\n");
    fprintf(fp, "%-10s %-15s %-15s\n", "Iterasi", "Vd (V)", "Error");

    printf("\n=== Iterasi Newton-Raphson ===\n");
    printf("%-10s %-15s %-15s\n", "Iterasi", "Vd (V)", "Error");

    do {
        double f = diode_function(Vd, Vin, R, Is, n, Vt);
        double f_prime = diode_derivative(Vd, R, Is, n, Vt);

        if (fabs(f_prime) < 1e-12) {
            printf("Turunan terlalu kecil, metode gagal.\n");
            fprintf(fp, "Metode gagal: turunan mendekati nol.\n");
            fclose(fp);
            return 1;
        }

        Vd_next = Vd - f / f_prime;
        error = fabs(Vd_next - Vd);
        Vd = Vd_next;

        printf("%-10d %-15.6f %-15.6f\n", iter + 1, Vd, error);
        fprintf(fp, "%-10d %-15.6f %-15.6f\n", iter + 1, Vd, error);

        iter++;
    } while (error > TOL && iter < MAX_ITER);

    double Id = Is * (exp(Vd / (n * Vt)) - 1.0);

    printf("\n=== Hasil Akhir ===\n");
    printf("Tegangan Dioda (Vd)  = %.6f V\n", Vd);
    printf("Arus Dioda (Id)      = %.6e A\n", Id);

    fprintf(fp, "\n=== Hasil Akhir ===\n");
    fprintf(fp, "Tegangan Dioda (Vd)  = %.6f V\n", Vd);
    fprintf(fp, "Arus Dioda (Id)      = %.6e A\n", Id);

    fclose(fp);
    printf("\nHasil telah disimpan ke file 'dioda_output.txt'\n");
    return 0;
}
