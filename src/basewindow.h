//
// Created by Filip on 16.10.2025.
//

#ifndef AUTOMAT_BASEWINDOW_H
#define AUTOMAT_BASEWINDOW_H
#include <QTimer>
#include <QDateTime>

#include <QWidget>
#include "paymentwindows.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class baseWindow;
}

QT_END_NAMESPACE

class BaseWindow : public QWidget {
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);

    ~BaseWindow() override;

private slots:
    void updateDateTime();
    // Slot dla przycisku "+" biletu normalnego
    void on_normalTicketAdd_clicked();
    // Slot dla przycisku "-" biletu normalnego
    void on_normalTicketMinus_clicked();

    // Slot dla przycisku "+" biletu ulgowego
    void on_reducedTicketAdd_clicked();
    // Slot dla przycisku "-" biletu ulgowego
    void on_reducedTicketMinus_clicked();

    void on_buyButton_clicked();

private:
    Ui::baseWindow *ui;
    QTimer *timer;
    void updateSum();

    double calculateSum();

    // **Stałe** przechowujące ceny biletów
    const double normalTicketPrice = 5.00;
    const double reducedTicketPrice = 2.50;

    PaymentWindows *paymentWindow = nullptr;
    // CoinWindow *coinWindow = nullptr; // Jeśli byś stworzył
};


#endif //AUTOMAT_BASEWINDOW_H