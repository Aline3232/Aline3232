#include <stdio.h>

// Função para calcular o polinômio interpolador de Lagrange
double lagrange_interpolation(int x, double *x_values, double *y_values, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = y_values[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    int n = 3;// Número de pontos
    int x = 3;
    double x_values[] = {2, 4, 7}; // Valores de x
    double y_values[] = {5, -5, 10}; // Valores de f(x)

    printf("Polinômio interpolador de Lagrange:\n");
    printf("P(x) = ");
    for (int i = 0; i < n; i++) {
        printf("(%+.2f)", y_values[i]);
        for (int j = 0; j < n; j++) {
            if (j != i) {
                printf(" * (x - %.2f) / (%.2f - %.2f)", x_values[j], x_values[i], x_values[j]);
            }
        }
        if (i < n - 1) {
            printf(" + ");
        }
    }
    printf("\n");
    printf("\n");
    printf("De acordo com calculos feitos previamente o Polinômio de Lagrange é : 2x^2-17x+31");

    printf("\n");
    printf("\n");
    printf("O valor interpolado em P(3) = %.2f", lagrange_interpolation(x,x_values,y_values,n));
   
    
    // Abrir um arquivo para salvar os dados
    FILE *file = fopen("interpolation_data.dat", "w");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    for (double x = 1; x <= 8; x += 0.1) {
        double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = y_values[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        result += term;
    }
        fprintf(file, "%lf %lf\n", x, result);
    }

    fclose(file);
    printf("\n");
    printf("\n");
    printf("Pontos x e y do grafico calculos com sucesso.\n");
    
    
    FILE *gnuplotScript = fopen("plot_script.plt", "w");
    if (gnuplotScript == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo do script Gnuplot\n");
        return 1;
    }

    fprintf(gnuplotScript, "set term png\n");
    fprintf(gnuplotScript, "set output 'polynomial_interpolation.png'\n");
    fprintf(gnuplotScript, "set title 'Polinômio Interpolador de Lagrange'\n");
    fprintf(gnuplotScript, "set xlabel 'x'\n");
    fprintf(gnuplotScript, "set ylabel 'P(x)'\n");
    fprintf(gnuplotScript, "plot %f*x**2 - %f*x + %f title 'Polinômio de Lagrange', ", 2.0, 17.0, 31.0);
    fprintf(gnuplotScript, "'-' with points title 'Pontos do Conjunto'\n");

    for (int i = 0; i < 3; i++) {
        fprintf(gnuplotScript, "%f %f\n", x_values[i], y_values[i]);
    }
    fprintf(gnuplotScript, "e\n");

    fclose(gnuplotScript);

    printf("Script Gnuplot gerado com sucesso.\n");
    
    
    return 0;
}
