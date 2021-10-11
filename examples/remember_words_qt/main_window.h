#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include<QApplication>
#include<QMainWindow>
#include<QTextEdit>
#include<QPushButton>
#include<QMessageBox>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void createControls();
private:
    QTextEdit *textView1;
    QPushButton *startButton1;
    int num_words;
    int mode;
    QStringList stored_list;
public slots:
    void startGame();
};


#endif

