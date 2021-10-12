#include"main_window.h"
#include<ctime>
#include<cstdlib>
#include<QClipboard>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(800, 600);
    setWindowTitle(tr("Remember Words"));
    createControls();
    srand(static_cast<unsigned int>(time(0)));
    num_words = 1;
    mode = 0;
}

void MainWindow::createControls() {
    textView1 = new QTextEdit(tr("You should Paste Text Here to use with the program\n ") + defaultText, this);
    textView1->setGeometry(25, 25, 800-50, 500);
    textView1->setAcceptRichText(false);
    startButton1 = new QPushButton("Start", this);
    startButton1->setGeometry(25, 550, 100, 25);
    connect(startButton1, SIGNAL(clicked()),this, SLOT(startGame()));
    giveupButton2 = new QPushButton("Give up", this);
    giveupButton2->setGeometry(130, 550, 100, 25);
    connect(giveupButton2, SIGNAL(clicked()), this, SLOT(giveup()));
    
    giveupButton2->hide();
    reverseCheck1 = new QCheckBox("Enter in Reverse", this);
    reverseCheck1->setGeometry(240, 550, 200, 25);
    
}

void MainWindow::startGame() {
    if(mode == 0) {
        QString text = textView1->toPlainText();
        QStringList list = text.split(" ");
        if(list.size() < 10) {
            QMessageBox::information(this, tr("Error not enough words"), tr("Text must contain at least 100 words."));
            return;
        }
      
        QStringList lst;
        for(int i = 0; i < num_words; ++i) {
            lst << list.at(rand()%(list.size()-1));
        }
        stored_list = lst;
        QString textOutput;
        for(int i = 0; i < lst.size(); ++i) {
            
            textOutput += lst.at(i) + ((i < lst.size()-1) ? " " : "");
        }
        
        QString inReverse;
        if(reverseCheck1->checkState() == Qt::Checked)
            inReverse = " in Reverse ";
        
        QMessageBox::information(this, tr("Remember this"),"Remember this exact string words " + inReverse + ":<br>" +  textOutput);
        
        textView1->setPlainText("");
        QClipboard *clipboard = QGuiApplication::clipboard();
        QString otext = clipboard->text();
        if(textOutput == otext) {
            clipboard->setText("");
        }
        startButton1->setText("Match");
        mode = 1;
        num_words ++;
        giveupButton2->show();
    } else {
        QString text = textView1->toPlainText();
        QStringList new_list = text.split(" ");
        bool the_same = true;
        if(reverseCheck1->checkState() == Qt::Unchecked) {
            for(int i = 0; i < stored_list.size(); ++i) {
                if(new_list.at(i) != stored_list.at(i)) {
                    the_same = false;
                    break;
                }
            }
        } else {
            for(int i = stored_list.size()-1; i >= 0; --i) {
                if(new_list.at(i) != stored_list.at(stored_list.size()-1-i)) {
                    the_same = false;
                    break;
                }
            }
        }
        if(the_same == true) {
            QMessageBox::information(this, tr("Correct you remembered!"), tr("Yes you are correct try again for increased difficulty"));
            textView1->setPlainText(tr("You should Paste Text Here to use with the program\n ") + defaultText);
            startButton1->setText(tr("Start"));
            mode = 0;
            giveupButton2->hide();
        } else {
            QMessageBox::information(this, tr("You are incorrect"), tr("Incorrect try again"));
        }
    }
}

void MainWindow::giveup() {

    QString correctGuess;
    QTextStream stream(&correctGuess);
    
    stream << "Game Over:\n The Max Amount of words you guessed is: " << num_words-1 << "\n";
    
    QMessageBox::information(this, "Game Over", correctGuess);
    textView1->setPlainText(tr("You should Paste Text Here to use with the program\n ") + defaultText);
    startButton1->setText(tr("Start"));
    giveupButton2->hide();
    mode = 0;
    num_words = 1;
}
