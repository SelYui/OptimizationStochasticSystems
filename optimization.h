#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <QVector>

#include <math.h>
#include <random>
#include <vector>
#include <iostream>

extern QVector<double> e, X;   // ошибка оценивание и состояние системы
//extern double A, B, Deps, Dnu, X0, ocX0, D0, mu;
//extern unsigned int N;

// Объявление функции моделирования оптимального фильтра и регулятора
void Optimization(unsigned int N, double A, double B, double Deps, double Dnu, double X0, double ocX0, double D0, double mu);

#endif // OPTIMIZATION_H
