#include "MyCheckBox.h"
#include <QVBoxLayout>

MyWidget::MyWidget(QCheckBox *checkBox1, QCheckBox *checkBox2, QCheckBox *checkBox3, QWidget *parent)
    : QWidget(parent) {
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(checkBox1);
    buttonGroup->addButton(checkBox2);
    buttonGroup->addButton(checkBox3);
    buttonGroup->setExclusive(true);

    // QVBoxLayout *layout = new QVBoxLayout;
    // layout->addWidget(checkBox1);
    // layout->addWidget(checkBox2);
    // layout->addWidget(checkBox3);
    // setLayout(layout);
}

