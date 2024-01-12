#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QMainWindow>

namespace Ui {
class PaintWidget;}
class PaintWidget : public QMainWindow
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private slots:

    void on_actionPencil_triggered();

    void on_actionErase_triggered();

    void on_actionClear_triggered();

    void on_actionSave_triggered();

private:
    QString pathway;
    Ui::PaintWidget *ui;
    QPainter *mPainter;
    QImage *mImage;
    QPoint mBegin;
    QPoint mEnd;
    QColor mColor;
    int mSize;
    bool mEnabled;
protected:
    void closeEvent(QCloseEvent *event) override
    {
        mImage->fill(Qt::white);
        update();
        QWidget::closeEvent(event);
    }
signals:
    void saveSignal(QString filePath);
};

#endif // PAINTWIDGET_H
