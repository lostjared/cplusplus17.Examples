#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include<QApplication>
#include<QMainWindow>
#include<QTextEdit>
#include<QPushButton>
#include<QMessageBox>
#include<QCheckBox>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void createControls();
private:
    QTextEdit *textView1;
    QPushButton *startButton1, *giveupButton2;
    QCheckBox *reverseCheck1;
    int num_words;
    int mode;
    QStringList stored_list;
    
    QString defaultText = tr("This is where you can input some text to use with the program. It can contain any plain-text and the program will tokenize the string. Once the string is tokenized it will output a new string for you to read and then input again from memory. As you progress the string will get longer and longer. I wrote this to help with my memory. I love programming. This program is written in C++. It is written using the Qt library.");
    
public slots:
    void startGame();
    void giveup();
};


#endif

