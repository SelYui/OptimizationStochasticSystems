#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customvalidator.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // выставляем проверку вводимых значений
    ui->lineEdit_A->setValidator(new CustomValidator());
    ui->lineEdit_B->setValidator(new CustomValidator());
    ui->lineEdit_Deps->setValidator(new CustomValidator());
    ui->lineEdit_Dnu->setValidator(new CustomValidator());
    ui->lineEdit_X0->setValidator(new CustomValidator());
    ui->lineEdit_ocX0->setValidator(new CustomValidator());
    ui->lineEdit_D0->setValidator(new CustomValidator());
    ui->lineEdit_mu->setValidator(new CustomValidator());
    ui->lineEdit_N->setValidator(new QIntValidator(ui->lineEdit_N));

    graphs = new Graph();// Инициализируем второе кно с графиком
    connect(this, &MainWindow::plotGraph, graphs, &Graph::PlotXandE);   // По кнопке строим график и рисуем его в классе второго окна
}

void MainWindow::on_pushButton_clicked()
{
    // Читаем значения из формы и проверяем их корректность
    if(ui->lineEdit_A->text().isEmpty()){
        A = 0.999;
        ui->lineEdit_A->setText("0.999");}
    else
        A = ui->lineEdit_A->text().toDouble();
    if(ui->lineEdit_B->text().isEmpty()){
        B = 1;
        ui->lineEdit_B->setText("1");}
    else
        B = ui->lineEdit_B->text().toDouble();
    if(ui->lineEdit_Deps->text().isEmpty()){
        Deps = 0.01;
        ui->lineEdit_Deps->setText("0.01");}
    else
        Deps = ui->lineEdit_Deps->text().toDouble();
    if(ui->lineEdit_Dnu->text().isEmpty()){
        Dnu = 0.0025;
        ui->lineEdit_Dnu->setText("0.0025");}
    else
        Dnu = ui->lineEdit_Dnu->text().toDouble();
    if(ui->lineEdit_X0->text().isEmpty()){
        X0 = 10;
        ui->lineEdit_X0->setText("10");}
    else
        X0 = ui->lineEdit_X0->text().toDouble();
    if(ui->lineEdit_ocX0->text().isEmpty()){
        ocX0 = 9.5;
        ui->lineEdit_ocX0->setText("9.5");}
    else
        ocX0 = ui->lineEdit_ocX0->text().toDouble();
    if(ui->lineEdit_D0->text().isEmpty()){
        D0 = 0.5;
        ui->lineEdit_D0->setText("0.5");}
    else
        D0 = ui->lineEdit_D0->text().toDouble();
    if(ui->lineEdit_mu->text().isEmpty()){
        mu = 10;
        ui->lineEdit_mu->setText("10");}
    else
        mu = ui->lineEdit_mu->text().toDouble();
    if(ui->lineEdit_N->text().isEmpty()){
        N = 100;
        ui->lineEdit_N->setText("100");}
    else {
        N = ui->lineEdit_N->text().toUInt();
        if (N <= 0){
            N = 100;
            ui->lineEdit_N->setText("100");}}

    emit plotGraph(N, A, B, Deps, Dnu, X0, ocX0, D0, mu);   // посылаем сигнал во второе окно для начала постройки графиков
}

MainWindow::~MainWindow()
{
    delete ui;
}
