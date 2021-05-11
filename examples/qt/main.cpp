#include<QApplication>
#include<QMainWindow>

class Window1 : QMainWindow {
  Q_OBJECT
public:
    MainWindow(QWidget *parent = 0) : QMainWindow(parent) {
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Window1 win;
    win.show();
    app.exec();
    return 0;
}
