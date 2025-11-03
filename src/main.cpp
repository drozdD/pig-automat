#include <QApplication>
#include <QStackedWidget>
#include "basewindow.h"
#include "paymentwindows.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QStackedWidget stack;
    auto *baseWindow = new BaseWindow();
    auto *paymentWindow = new PaymentWindows();

    stack.addWidget(baseWindow);
    stack.addWidget(paymentWindow);
    stack.setGeometry(baseWindow->geometry());

    stack.show();
    return QApplication::exec();
}
