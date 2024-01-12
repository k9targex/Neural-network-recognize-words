#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "Source.h"
//#include "Network.h"
#include <QString>
//#include <string>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    checkBox1(nullptr),
    checkBox2(nullptr),
    checkBox3(nullptr),
    myWidget(nullptr)
{
    ui->setupUi(this);
    checkBox1 = ui->checkBox;
    checkBox2 = ui->checkBox_2;
    checkBox3 = ui->checkBox_3;
    myWidget = new MyWidget(checkBox1, checkBox2, checkBox3, this);
    setFixedSize(280, 230);
    connect(&paint, &PaintWidget::saveSignal, this, &MainWindow::slot);
    conf = 0;
     currentDirectory = "C://";
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::load_file(Network T800)
{
    QString str;
    str=QFileDialog::getOpenFileName(this,"Выбрать файл",currentDirectory,"BMP File (*.bmp)");
    if (!str.isEmpty()) {
        QFileInfo fileInfo(str);
        currentDirectory = fileInfo.path();
    }
//  ]\  ui->label->setText(str);

    return str;
}


void MainWindow::on_pushButton_2_clicked()
{

    int fl = 1;
    if(ui->checkBox->isChecked())
    {
        conf=1;
    }
    else if(ui->checkBox_2->isChecked())
    {
        conf=2;
    }
    else if(ui->checkBox_3->isChecked())
    {
        conf=3;
    }
    if(conf)
    {
        T800.NetworkInit(conf);
        if(!T800.ReadWeight(conf))
            QMessageBox::critical(this, "Error", "Произошла ошибка2324!");
        else
            QMessageBox::information(this, "Поздравляю", "Вам повезло и все веса загрузились!");
    }
    else
    QMessageBox::critical(this, "Error", "Произошла ошибка!");

}

//void MainWindow::on_pushButton_clicked()
//{

//}

void MainWindow::on_pushButton_3_clicked()
{
    if(conf)
    {
        paint.show();
    }
    else
        QMessageBox::critical(this, "Error", "Произошла ошибка!");

}


void MainWindow::slot(QString filepath)
{
    std::string str2 = filepath.toStdString();
    std::string finalstr = ReadWord(T800,str2);
    //QMessageBox::information(this,"Word",filepath);
    QMessageBox::information(this, "Word",  QString::fromStdString(finalstr));
}

void MainWindow::on_pushButton_4_clicked()
{

    int fl = 1;
    if(ui->checkBox->isChecked())
    {
        conf=1;
    }
    else if(ui->checkBox_2->isChecked())
    {
        conf=2;
    }
    else if(ui->checkBox_3->isChecked())
    {
        conf=3;
    }
    if(conf)
    {
        QMessageBox::information(this, "Wait....","Это может занять довольно долгий период времени");
        data_picture* mas = NULL;
        T800.NetworkInit(conf);
        mas = ReadPicture();
        QString final = Study(T800,mas);

        QMessageBox::information(this, "Stats",  final);
    }
    else
        QMessageBox::critical(this, "Error", "Произошла ошибка!");
}


void MainWindow::on_pushButton_5_clicked()
{
    if(conf)
    {
        //        QMessageBox::critical(this, "Ошибка", "Произошла ошибка!");
        QString str = load_file(T800);
        if (str!="")
        {
            std::string str2 = str.toStdString();
            std::string finalstr = ReadWord(T800,str2);
            QMessageBox::information(this, "Recognized",  QString::fromStdString(finalstr));
        }
    }
    else
        QMessageBox::critical(this, "Error", "Произошла ошибка!");
}

