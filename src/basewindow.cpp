//
// Created by Filip on 16.10.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_baseWindow.h" resolved

#include "basewindow.h"
#include "ui_basewindow.h"
#include "paymentwindows.h"
#include "coinwindow.h"
#include <QMessageBox>


BaseWindow::BaseWindow(QWidget *parent) : QWidget(parent), ui(new Ui::baseWindow) {
    ui->setupUi(this);
    timer = new QTimer(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

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

void BaseWindow::on_buyButton_clicked()
{
    // 1. Oblicz łączną kwotę do przekazania
    double finalSum = calculateSum();

    if (finalSum <= 0.0) {
        QMessageBox::warning(this, "Błąd", "Wybierz przynajmniej jeden bilet!");
        return;
    }

    // Tworzymy nowe okno, jeśli nie zostało jeszcze stworzone
    PaymentWindows *paymentWindow = new PaymentWindows(nullptr);
    // Użycie "this" jako parenta jest opcjonalne, ale zalecane

    // Opcjonalnie: Ustawienie atrybutu DeleteOnClose, aby okno się usunęło po zamknięciu
    paymentWindow->setAttribute(Qt::WA_DeleteOnClose);


    // 3. PRZEKAZANIE DANYCH: Wywołujemy metodę w oknie płatności (patrz Krok 2)
    paymentWindow->setPaymentAmount(finalSum);

    // 4. Pokaż okno (lub dwa, jeśli masz coinwindow)
    paymentWindow->show();

    CoinWindow *coinWindow = new CoinWindow(nullptr);
    coinWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 4. Ustawienie pozycji CoinWindow obok PaymentWindow
    // Pobierz pozycję i wymiary okna płatności, aby umieścić okno monet obok.
    QPoint currentPos = paymentWindow->pos();

    // Przesuń CoinWindow, aby było 20 pikseli na prawo od PaymentWindow
    coinWindow->move(currentPos.x() + paymentWindow->width() + 20, currentPos.y());

    coinWindow->show();

    connect(paymentWindow, &PaymentWindows::backButtonWasClicked,
            coinWindow, &CoinWindow::close);

    connect(coinWindow, &CoinWindow::coinInserted,
            paymentWindow, &PaymentWindows::processCoin);
}

// --- FUNKCJA SUMUJĄCA (BEZ ZMIAN) ---

void BaseWindow::updateSum()
{
    double totalSum = calculateSum();
    QString sumText = QString::number(totalSum, 'f', 2) + " zł";
    ui->sumValue->setText(sumText);
}


double BaseWindow::calculateSum()
{
    const double normalTicketPrice = 5.00;
    const double reducedTicketPrice = 2.50;

    int normalCount = ui->normalTicketAmount->value();
    int reducedCount = ui->reducedTicketAmount->value();

    double totalSum = (normalCount * normalTicketPrice) +
                      (reducedCount * reducedTicketPrice);

    return totalSum; // Zwracamy czystą wartość!
}