/* Функция моделирования оптимального фильтра и регулятора
 * фходные параметры:
 * постоянные коэффициенты A и B, дисперсия гаусова белого шума - Deps, дисперсия ошибки - Dnu, начальное значение - X0, начальное оценочное движение - ocX0
 * начальное значение дисперсии ошибки оценивания - D, условное мат. ожидание x от y - mu, количество точек для построения - N
 * */

#include "graph.h"
#include "ui_graph.h"
#include <random>
#include <iostream>

void Graph::Optimization(QVector<double> &e, QVector<double> &X, unsigned int N, double A, double B, double Deps, double Dnu, double X0, double ocX0, double D0, double mu)
{
    // Объявление некоторых второстепенных переменных
    unsigned int k;
    std::vector<double> Y(N), L(N), u(N), eps(N), I(N), nu(N), G(N), arrayXoc(N), arrayD(N);

    // Обнуление массивов

    // Установка начальных значений
    X[0] = X0;
    arrayXoc[0] = ocX0;
    arrayD[0] = D0;

    e[0] = arrayXoc[0] - X[0];
    L[0] = pow(B,2)/(mu+pow(B,2));
    u[0] = -L[0]*arrayXoc[0];

    // Формирование гаусовского белого шума
    std::random_device rd_eps;
    std::mt19937 gen_eps(rd_eps());
    std::normal_distribution<> temp_eps(0, sqrt(Deps));
    for (double &var_eps : eps)
        var_eps = temp_eps(gen_eps);

    // Формирование случайной ошибки шума
    std::random_device rd_nu;
    std::mt19937 gen_nu(rd_nu());
    std::normal_distribution<> temp_nu(0, sqrt(Dnu));
    for (double &var_nu : nu)
        var_nu = temp_nu(gen_nu);

    // Далее все вычисления в цикле (получаем X(k) и e(k)) для построения N точек
    for (k = 0;k < N-1;k++)
    {
        I[N-k-1] = (A*mu*L[k])/B;

        L[k+1] = (A*B*(1+I[N-k-1]))/(mu+pow(B,2)*(1+I[N-k-1]));
        // уравнение объекта
        X[k+1] = (A*X[k]+B*u[k]+eps[k]);
        // канал наблюдения
        Y[k+1] = X[k+1] + nu[k+1];
        // коэффициент усиления и дисперсия ошибки оценивания
        G[k+1] = (pow(A,2)*arrayD[k]+Deps)/(pow(A,2)*arrayD[k]+Deps+Dnu);
        arrayD[k+1] = G[k+1]*Dnu;
        e[k+1] = A*(1-G[k+1])*e[k]-(1-G[k+1])*eps[k]+G[k+1]*nu[k+1];
        // фильтр калмана
        arrayXoc[k+1] = A*arrayXoc[k]+B*u[k]+G[k+1]*(Y[k+1]-A*arrayXoc[k]-B*u[k]);
        // управляющее воздействие
        u[k+1] = -L[k+1]*arrayXoc[k+1];
    }
}

