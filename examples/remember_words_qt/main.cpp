#include "main_window.h"
#include<QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window1;
    window1.show();
    return app.exec();
}
