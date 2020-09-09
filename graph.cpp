#include "graph.h"
#include "ui_graph.h"
#include <iostream>

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    // Добавляем график 1 на полотно
    ui->customPlot_1->addGraph();
    // Инициализируем трассировщик
    tracer_1 = new QCPItemTracer(ui->customPlot_1);
    // Подписываем оси координат
    ui->customPlot_1->xAxis->setLabel("k");
    ui->customPlot_1->yAxis->setLabel("X(k)");
    // Подписываем название графика
    ui->customPlot_1->plotLayout()->insertRow(0);
    ui->customPlot_1->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot_1, "Состояние системы", QFont("Arial", 12, QFont::Bold)));

    // Строим второй график
    ui->customPlot_2->addGraph();
    tracer_2 = new QCPItemTracer(ui->customPlot_2);
    ui->customPlot_2->xAxis->setLabel("k");
    ui->customPlot_2->yAxis->setLabel("e(k)");
    ui->customPlot_2->plotLayout()->insertRow(0);
    ui->customPlot_2->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot_2, "Ошибка оценивания", QFont("Arial", 12, QFont::Bold)));

    // Подключаем сигналы событий мыши от полотна графика к слотам для их обработки
    connect(ui->customPlot_1, &QCustomPlot::mouseMove, this, &Graph::slotMouseMove_1);
    connect(ui->customPlot_2, &QCustomPlot::mouseMove, this, &Graph::slotMouseMove_2);
}

Graph::~Graph()
{
    delete ui;
}

void Graph::PlotXandE(unsigned int N, double A, double B, double Deps, double Dnu, double X0, double ocX0, double D0, double mu)
{
    QVector<double> e(N), X(N);     // Объявляем наши векторы ошибкт и состояния системы
    // Строим модель
    Graph::Optimization(e, X, N, A, B, Deps, Dnu, X0, ocX0, D0, mu);

    // создаём вектора для графика
    QVector<double> k(X.size());
    for (int i=0; i < X.size(); i++)
    {
        k[i] = i;
    }
    // Для графика 1
    ui->customPlot_1->graph(0)->setData(k,X);     // Устанавливаем координаты точек графика
    tracer_1->setGraph(ui->customPlot_1->graph(0));   // Трассировщик будет работать с графиком
    // Устанавливаем максимальные и минимальные значения координат
    ui->customPlot_1->xAxis->setRange(0,0);
    ui->customPlot_1->yAxis->setRange(0,0);
    // Позволяем увеличивать и передвигать график
    ui->customPlot_1->rescaleAxes();
    ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // Отрисовываем содержимое полотна
    ui->customPlot_1->replot();


    ui->customPlot_2->graph(0)->setData(k, e);
    tracer_2->setGraph(ui->customPlot_2->graph(0));   // Трассировщик будет работать с графиком

    ui->customPlot_2->xAxis->setRange(0, 0);
    ui->customPlot_2->yAxis->setRange(0, 0);

    ui->customPlot_2->rescaleAxes();
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // отрисовка графика
    ui->customPlot_2->replot();

    this->show();
}

void Graph::slotMouseMove_1(QMouseEvent *event)
{
    // Определяем координату X на графике, где был произведён клик мышью
    double coordX = ui->customPlot_1->xAxis->pixelToCoord(event->pos().x());

    // По координате X клика мыши определим ближайшие координаты для трассировщика
    tracer_1->setGraphKey(coordX);
    tracer_1->updatePosition();

    // Выводим координаты точки графика, где установился трассировщик, в lineEdit
    ui->lineEdit_1->setText("k: " + QString::number(tracer_1->position->key()) +
                          " X(k): " + QString::number(tracer_1->position->value()));
    ui->customPlot_1->replot(); // Перерисовываем содержимое полотна графика
}

void Graph::slotMouseMove_2(QMouseEvent *event)
{
    // Определяем координату X на графике, где был произведён клик мышью
    double coordX = ui->customPlot_2->xAxis->pixelToCoord(event->pos().x());

    // По координате X клика мыши определим ближайшие координаты для трассировщика
    tracer_2->setGraphKey(coordX);
    tracer_2->updatePosition();

    // Выводим координаты точки графика, где установился трассировщик, в lineEdit
    ui->lineEdit_2->setText("k: " + QString::number(tracer_2->position->key()) +
                          " e(k): " + QString::number(tracer_2->position->value()));
    ui->customPlot_2->replot(); // Перерисовываем содержимое полотна графика
}
