#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QFileDialog>
#include <QString>
#include"MyCheckBox.h"
#include "Source.h"
#include "Network.h"
#include"paintwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    int conf;
public:
    QCheckBox *checkBox1;
    QCheckBox *checkBox2;
    QCheckBox *checkBox3;
    MyWidget *myWidget;
    QString Finalstr;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_2_clicked();
//    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    QString currentDirectory;
    PaintWidget paint;
    data_picture* mas = NULL;
    Network T800;
    data_picture* our;
    Ui::MainWindow *ui;
    QString load_file(Network T800);
public slots:
    void slot(QString filepath);
};
#endif // MAINWINDOW_H
