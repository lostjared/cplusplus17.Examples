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
    
    QString defaultText = tr("Acid Cam is a project I started developing in 2011 as an augmented reality hallucination simulator. The project grew and had various iterations over the years including the v1 series, v2 series, Qt app, command-line tool, and OpenGL visualization instrument. Different variations of the project run on Windows, Linux, and macOS. The most popular version of the project is the v2 OSX video editor version with over 2,000 CPU-based filters. Acid Cam filters are puzzle pieces of a visible language to bend and alter data to create abstract visualizations through mixing them together in different orders. It’s a gift. Available also is a collection of free stock footage I have created on my google drive that you can download for free and use in any   of your projects or videos and evolve and expand. No credit or payment is needed. I want to share my love with you all.");
    
public slots:
    void startGame();
};


#endif

