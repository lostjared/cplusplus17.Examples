#include<QApplication>
#include<QMainWindow>

class Window1 : public QMainWindow {
  Q_OBJECT
public:
    Window1(QWidget *parent = nullptr) : QMainWindow(parent) {
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Window1 win;
    win.show();
    app.exec();
    return 0;
}

  #include "main.moc"
