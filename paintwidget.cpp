#include "paintwidget.h"
#include "ui_paintwidget.h"
#include <QInputDevice>
#include <QColorDialog>
#include <QScreen>
#include <QBrush>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QImageWriter>
#include <QFileDialog>
PaintWidget::PaintWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaintWidget)
{

    ui->setupUi(this);
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QSize screenSize = primaryScreen->size();
    setFixedSize(1080, 340);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);

    mImage = new QImage(screenSize,
                        QImage::Format_ARGB32_Premultiplied);
    mPainter = new QPainter(mImage);
    mEnabled = false;
    mSize = 12;
    mColor = QColor(Qt::black);
//    on_actionClear_triggered();
}
PaintWidget::~PaintWidget()
{
    delete ui;
    delete mImage;
    delete mPainter;
}
void PaintWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawImage(0,0,*mImage);
    e->accept();
}

void PaintWidget::mousePressEvent(QMouseEvent *e)
{
    mEnabled = true;
    mBegin = e->pos();
}
void PaintWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(!mEnabled){
        e->accept();
        return;
    }
    QPen pen(mColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    mEnd = e->pos();
    mPainter->setPen(pen);
    mPainter ->drawLine(mBegin,mEnd);
    mBegin = mEnd;
    update();
    e->accept();
}
void PaintWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mEnabled = false;
    e->accept();
}

void PaintWidget::on_actionPencil_triggered()
{
    mColor = (Qt::black);
    mSize = 12;
}


void PaintWidget::on_actionErase_triggered()
{
    mColor = (Qt::white);
    mSize = 30;
}


void PaintWidget::on_actionClear_triggered()
{
    mImage->fill(Qt::white);
    update();
    on_actionPencil_triggered();
}


void PaintWidget::on_actionSave_triggered()
{

    QPixmap pixmap = this->grab();
    int menuBarHeight = this->menuBar()->height();
    QRect targetRect(0, -menuBarHeight, pixmap.width(), pixmap.height() + menuBarHeight);

    QPixmap croppedPixmap = QPixmap(targetRect.size());
    croppedPixmap.fill(Qt::white);

    QPainter painter(&croppedPixmap);
    painter.drawPixmap(targetRect, pixmap, pixmap.rect());


    QString fileName = "save.bmp";
    QString currentDir = QDir::currentPath();
    QString filePath = currentDir + "/" + fileName;


    QImage image = croppedPixmap.toImage();

    QImageWriter writer(filePath);
    writer.setFormat("BMP");

    if (writer.write(image)) {
        qDebug() << "Изображение успешно сохранено в" << filePath;
    } else {
        qDebug() << "Ошибка при сохранении изображения.";
    }
    emit saveSignal(filePath);
}

