#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QButtonGroup>

class MyWidget : public QWidget {
    Q_OBJECT

public:
    MyWidget(QCheckBox *checkBox1, QCheckBox *checkBox2, QCheckBox *checkBox3, QWidget *parent = nullptr);

private:
    QButtonGroup *buttonGroup;
};

#endif // MYWIDGET_H
