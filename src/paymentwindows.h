//
// Created by Filip on 19.10.2025.
//

#ifndef AUTOMAT_PAYMENTWINDOWS_H
#define AUTOMAT_PAYMENTWINDOWS_H
#include <QTimer>
#include <QDateTime>

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class PaymentWindows;
}

QT_END_NAMESPACE

class PaymentWindows : public QWidget {
    Q_OBJECT

public:
    explicit PaymentWindows(QWidget *parent = nullptr);

    ~PaymentWindows() override;
    void setPaymentAmount(double amount);

    void on_backButton_clicked();

signals: // <--- DODAJ TĘ SEKCJĘ
    void backButtonWasClicked(); // <--- DODAJ TĘ LINIĘ

public slots: // <--- DODAJ TĘ SEKCJĘ (lub dodaj do istniejącej, jeśli masz)
    void processCoin(double value);

protected:
    void showEvent(QShowEvent *event) override;

    void hideEvent(QHideEvent *event) override;

private slots: // 3. Zadeklaruj slot, który będzie aktualizował czas
    void updateDateTime();

private:
    Ui::PaymentWindows *ui;
    QTimer *timer; // 4. Dodaj prywatny wskaźnik na QTimer
    double amountToPay = 0.0;
    double amountPaid = 0.0;
};


#endif //AUTOMAT_PAYMENTWINDOWS_H