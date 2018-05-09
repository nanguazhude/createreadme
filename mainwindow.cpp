#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_doButton_clicked()
{
    const auto varDirName = ui->dirName->text().trimmed();
    if( varDirName.isEmpty() ){ return;  }
    QDir varDir{ varDirName };
    QDirIterator varDirIterator{
        varDir.absoluteFilePath(""),
        QDir::NoDotAndDotDot | QDir::Dirs
    };
    const static QString varReadMe = "readme.txt";
    const auto varCodeC = QTextCodec::codecForName("UTF-8")  ;
    while ( varDirIterator.hasNext() ) {
        varDirIterator.next() ;
        const auto varFileInfo = varDirIterator.fileInfo() ;
        const auto varReadMeFileName = QDir( varFileInfo.absoluteFilePath() ).absoluteFilePath(varReadMe) ;
        if( QFileInfo::exists( varReadMeFileName ) ){
            continue;
        }
        QFile varFile{ varReadMeFileName };
        if( false == varFile.open( QIODevice::WriteOnly ) ){
            continue;
        }
        QTextStream varStream{ &varFile };
        varStream.setCodec( varCodeC );
        varStream.setGenerateByteOrderMark(true);
        varStream << endl ;
    }
}
/* ;;;;;;; */

void MainWindow::on_sDir_clicked()
{
    const auto varDir = QFileDialog::getExistingDirectory();
    if( varDir.isEmpty() ){return ;}
    ui->dirName->setText( varDir );
}
/* ;;;;;;; */
