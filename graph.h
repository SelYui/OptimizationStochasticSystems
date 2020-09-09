#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <qcustomplot.h>

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

public slots:
    void PlotXandE(unsigned int N, double A, double B, double Deps, double Dnu, double X0, double ocX0, double D0, double mu);               // слот построения графиков по кнопке

private:
    Ui::Graph *ui;
    QCPItemTracer *tracer_1;      // Трасировщик по точкам графика
    QCPItemTracer *tracer_2;      // Трасировщик по точкам графика
    //QVector<double> e, X;         // Состояние системы и ошибка оценивания

private slots:
    void slotMouseMove_1(QMouseEvent * event);
    void slotMouseMove_2(QMouseEvent * event);
    void Optimization(QVector<double> &e, QVector<double> &X, unsigned int N, double A, double B, double Deps, double Dnu, double X0, double ocX0, double D0, double mu);
};

#endif // GRAPH_H
