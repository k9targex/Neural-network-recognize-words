#include "qpaint.h"
#include "ui_qpaint.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
QPaint::QPaint(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QPaint)
{
    ui->setupUi(this);
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QSize screenSize = primaryScreen->size;
    setFixedSize(1080, 340);
    QPalette pal = palette();

    // Устанавливаем цвет фона в белый
    pal.setColor(QPalette::Window, Qt::white);

    // Устанавливаем созданную палитру
    setPalette(pal);

    mImage = new QImage(screenSize,
                        QImage::Format_ARGB32_Premultiplied);
    mPainter = new QPainter(mImage);
    mEnabled = false;
    mSize = 12;
    mColor = QColor(Qt::black);
}

QPaint::~QPaint()
{
    delete ui;
    delete mImage;
    delete mPainter;
}
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawImage(0,0,*mImage);
    e->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mEnabled = true;
    mBegin = e->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!mEnabled){
        e->accept();
        return;
    }
    QPen pen(mColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    //    QBrush brush;
    //    brush.setColor(Qt::black);
    //    brush.setStyle(Qt::SolidPattern);
    //    pen.setBrush(brush);
    mEnd = e->pos();
    mPainter->setPen(pen);
    //    mPainter->setBrush(brush);

    mPainter ->drawLine(mBegin,mEnd);
    mBegin = mEnd;
    update();
    e->accept();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    mEnabled = false;
    e->accept();
}

void MainWindow::on_action_3_triggered()
{
    mColor = (Qt::white);
    mSize = 30;


}


void MainWindow::on_action_4_triggered()
{
    mColor = (Qt::black);
    mSize = 12;
}

void MainWindow::on_actionClear_all_triggered()
{
    // Очищаем изображение
    mImage->fill(Qt::white);
    on_action_4_triggered();
}

