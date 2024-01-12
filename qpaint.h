#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QPaint; }
QT_END_NAMESPACE

class QPainter;
class QImage;

class QPaint : public QMainWindow
{
    Q_OBJECT

public:
    QPaint(QWidget *parent = nullptr);
    ~QPaint();
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private slots:
    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_actionClear_all_triggered();

private:
    Ui::QPaint *ui;
    QPainter *mPainter;
    QImage *mImage;
    QPoint mBegin;
    QPoint mEnd;
    QColor mColor;
    int mSize;
    bool mEnabled;
};

#endif // MAINWINDOW_H

