//
// Created by Filip on 16.10.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_baseWindow.h" resolved

#include "basewindow.h"
#include "ui_basewindow.h"


BaseWindow::BaseWindow(QWidget *parent) : QWidget(parent), ui(new Ui::baseWindow) {
    ui->setupUi(this);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &BaseWindow::updateDateTime);

    timer->start(1000);

    updateDateTime();

    updateSum(); // Ustawienie początkowej sumy na 0,00 zł
}

BaseWindow::~BaseWindow() {
    delete ui;
}

void BaseWindow::updateDateTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    QString formattedDateTime = currentDateTime.toString("dd.MM.yy hh:mm:ss");

    // Ustaw sformatowany tekst w Labelu, którego objectName to "dateTimeLabel"
    ui->dateTime->setText(formattedDateTime);
}

void BaseWindow::on_normalTicketAdd_clicked()
{
    // Programowe zwiększenie wartości w QSpinBox
    // value() zwraca aktualną wartość, +1, a setValue() ją ustawia.
    int currentCount = ui->normalTicketAmount->value();
    ui->normalTicketAmount->setValue(currentCount + 1);

    // Po zmianie wartości QSpinBox musi być wywołana funkcja sumująca
    updateSum();
}

void BaseWindow::on_normalTicketMinus_clicked()
{
    int currentCount = ui->normalTicketAmount->value();

    // Sprawdzamy, czy nie zejdziemy poniżej 0 (choć QSpinBox powinien to obsługiwać)
    if (currentCount > 0) {
        ui->normalTicketAmount->setValue(currentCount - 1);
        updateSum();
    }
}

// --- BILETY ULGOWE ---

void BaseWindow::on_reducedTicketAdd_clicked()
{
    int currentCount = ui->reducedTicketAmount->value();
    ui->reducedTicketAmount->setValue(currentCount + 1);
    updateSum();
}

void BaseWindow::on_reducedTicketMinus_clicked()
{
    int currentCount = ui->reducedTicketAmount->value();
    if (currentCount > 0) {
        ui->reducedTicketAmount->setValue(currentCount - 1);
        updateSum();
    }
}

// --- FUNKCJA SUMUJĄCA (BEZ ZMIAN) ---

void BaseWindow::updateSum()
{
    // Zmienne stanowe usunięte, wartości pobierane z QSpinBox.
    const double normalTicketPrice = 5.00; // Używamy stałych
    const double reducedTicketPrice = 2.50;

    int normalCount = ui->normalTicketAmount->value();
    int reducedCount = ui->reducedTicketAmount->value();

    double totalSum = (normalCount * normalTicketPrice) +
                      (reducedCount * reducedTicketPrice);

    QString sumText = QString::number(totalSum, 'f', 2) + " zł";
    ui->sumValue->setText(sumText);

}
