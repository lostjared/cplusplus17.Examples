#include"main_window.h"
#include<ctime>
#include<cstdlib>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(800, 600);
    setWindowTitle(tr("Remember Words"));
    createControls();
    srand(static_cast<unsigned int>(time(0)));
    num_words = 5;
    mode = 0;
}

void MainWindow::createControls() {
    textView1 = new QTextEdit(tr("Paste Text Here"), this);
    textView1->setGeometry(25, 25, 800-50, 500);
    startButton1 = new QPushButton("Start", this);
    startButton1->setGeometry(25, 550, 100, 25);
    connect(startButton1, SIGNAL(clicked()),this, SLOT(startGame()));
}

void MainWindow::startGame() {
    
    if(mode == 0) {
        QString text = textView1->toPlainText();
        QStringList list = text.split(" ");
        if(list.size() < 100) {
            QMessageBox::information(this, tr("Error not enough words"), tr("Text must contain at least 100 words."));
            return;
        }
      
        QStringList lst;
        for(int i = 0; i < num_words; ++i) {
            lst << list.at(rand()%list.size()-1);
        }
        stored_list = lst;
        QString textOutput;
        for(int i = 0; i < lst.size(); ++i) {
            
            textOutput += lst.at(i) + ((i < lst.size()-1) ? " " : "");
        }
        
        QMessageBox::information(this, tr("Remember this string"), textOutput);
        
        textView1->setPlainText("");
        startButton1->setText("Match");
        mode = 1;
        num_words += 5;
        
    } else {
        QString text = textView1->toPlainText();
        QStringList new_list = text.split(" ");
        bool the_same = true;
        for(int i = 0; i < stored_list.size(); ++i) {
            if(new_list.at(i) != stored_list.at(i)) {
                the_same = false;
                break;
            }
        }
        if(the_same == true) {
            QMessageBox::information(this, tr("Correct you remembered!"), tr("Yes you are correct try again for increased difficulty"));
            textView1->setPlainText(tr("Paste text here"));
            startButton1->setText(tr("Start"));
            mode = 0;
        } else {
            QMessageBox::information(this, tr("You are incorrect"), tr("Incorrect try again"));
        }
    }
}
