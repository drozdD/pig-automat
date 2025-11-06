//
// Created by Filip on 19.10.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PaymentWindows.h" resolved

#include "paymentwindows.h"

#include <QPushButton>
#include <ui_paymentwindows.h>

#include "coinwindow.h"


PaymentWindows::PaymentWindows(QWidget *parent) : QWidget(parent), ui(new Ui::PaymentWindows) {
    ui->setupUi(this);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &PaymentWindows::updateDateTime);
    connect(ui->backButton, &QPushButton::clicked, this, &PaymentWindows::on_backButton_clicked);

    timer->start(1000);

    updateDateTime();
}

PaymentWindows::~PaymentWindows() {
    delete ui;
}

void PaymentWindows::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    qDebug() << "showEvent";
}

void PaymentWindows::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
    qDebug() << "hideEvent";
}

void PaymentWindows::updateDateTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    QString formattedDateTime = currentDateTime.toString("dd.MM.yy hh:mm:ss");

    // Ustaw sformatowany tekst w Labelu, którego objectName to "dateTimeLabel"
    ui->dateTime->setText(formattedDateTime);
}

void PaymentWindows::setPaymentAmount(double amount)
{
    amountToPay = amount; // Zapisz kwotę wewnętrznie
    amountPaid = 0.0;

    // Formatowanie kwoty i wyświetlanie w labelu
    QString amountText = QString::number(amount, 'f', 2) + " PLN";
    // Upewnij się, że masz QLabel o nazwie finalAmountLabel w pliku paymentwindows.ui
    ui->toPayValue->setText(amountText);

    if (ui->paidValue) { // Sprawdzenie, czy label istnieje
        ui->paidValue->setText("0.00 PLN");
    }
}

void PaymentWindows::processCoin(double value)
{
    amountPaid += value; // Dodaj wartość monety do sumy wpłat

    double remainingToPay = amountToPay - amountPaid;

    // Aktualizuj etykietę 'paidValue' (wpłacono)
    // UPEWNIJ SIĘ, ŻE DODAŁEŚ LABEL 'paidValue' w pliku .ui
    if (ui->paidValue) {
        ui->paidValue->setText(QString::number(amountPaid, 'f', 2) + " PLN");
    }

    // Aktualizuj etykietę 'toPayValue' (pozostało)
    if (remainingToPay <= 0) {
        ui->toPayValue->setText("0.00 PLN");
        // Tutaj możesz dodać logikę zakończenia płatności,
        // np. zamknięcie okien lub pokazanie komunikatu "Dziękujemy"
    } else {
        ui->toPayValue->setText(QString::number(remainingToPay, 'f', 2) + " PLN");
    }
}

void PaymentWindows::on_backButton_clicked()
{
    // Zamknij okno płatności
    emit backButtonWasClicked();
    this->close();
}