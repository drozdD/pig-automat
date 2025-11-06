//
// Created by kubor on 06.11.2025.
//

#ifndef AUTOMAT_COINWINDOW_H
#define AUTOMAT_COINWINDOW_H

#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui {
    class CoinWindow;
}

QT_END_NAMESPACE

class CoinWindow : public QWidget {
    Q_OBJECT

public:
    explicit CoinWindow(QWidget *parent = nullptr);
    ~CoinWindow() override;

signals: // <--- DODAJ TĘ SEKCJĘ
    void coinInserted(double value); // Sygnał, który wysyła wartość wrzuconej monety

private slots: // <--- DODAJ TĘ SEKCJĘ
    // Slot dla każdego przycisku - nazwy muszą pasować do tych z Qt Designer
    void on_push_5_clicked();
    void on_push_2_clicked();
    void on_push_1_clicked();
    void on_push_50_clicked();
    void on_push_20_clicked();
    void on_push_10_clicked();

private:
    Ui::CoinWindow *ui;
};


#endif //AUTOMAT_COINWINDOW_H