// Plik: src/coinwindow.cpp

#include "coinwindow.h"
#include "ui_coinwindow.h"


CoinWindow::CoinWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CoinWindow)
{
    ui->setupUi(this);
    // Tutaj możesz dodać połączenia dla przycisków monet
}

void CoinWindow::on_push_5_clicked()
{
    emit coinInserted(5.00); // 5 zł
}

void CoinWindow::on_push_2_clicked()
{
    emit coinInserted(2.00); // 2 zł
}

void CoinWindow::on_push_1_clicked()
{
    emit coinInserted(1.00); // 1 zł
}

void CoinWindow::on_push_50_clicked()
{
    emit coinInserted(0.50); // 50 gr
}

void CoinWindow::on_push_20_clicked()
{
    emit coinInserted(0.20); // 20 gr
}

void CoinWindow::on_push_10_clicked()
{
    emit coinInserted(0.10); // 10 gr
}

CoinWindow::~CoinWindow()
{
    delete ui;
}

// ... (jeśli masz metody showEvent/hideEvent, zostaw je)