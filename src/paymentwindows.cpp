//
// Created by Filip on 19.10.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PaymentWindows.h" resolved

#include "paymentwindows.h"

#include <QPushButton>

#include "ui_paymentwindows.h"


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

    // Formatowanie kwoty i wyświetlanie w labelu
    QString amountText = QString::number(amount, 'f', 2) + " PLN";
    // Upewnij się, że masz QLabel o nazwie finalAmountLabel w pliku paymentwindows.ui
    ui->toPayValue->setText(amountText);
}

void PaymentWindows::on_backButton_clicked()
{
    // Zamknij okno płatności
    this->close();
}