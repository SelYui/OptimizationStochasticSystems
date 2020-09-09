#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>
#include <qcustomplot.h>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString         str;
    Graph         *graphs;      // второе окно с графиками
    // переменные из формы
    double A, B, Deps, Dnu, X0, ocX0, D0, mu;
    unsigned int N;

private slots:
    void on_pushButton_clicked();

signals:
    void plotGraph(unsigned int N, double A, double B, double Deps, double Dnu, double X0, double ocX0, double D0, double mu);            // Сигнал для начала построения графика
};
#endif // MAINWINDOW_H
