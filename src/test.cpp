#include "test.hpp"

TestWidget::TestWidget(QWidget *parent) : QDockWidget("CodeJam Test Plugin", parent) {
    this->m_parent = parent;

    QWidget *widget = new QWidget();
    this->m_button->setText("Press me!");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(this->m_button);

    widget->setLayout(layout);
    setWidget(widget);

    setVisible(false);
    setFloating(true);
    resize(300, 300);

    QObject::connect(this->m_button, SIGNAL(clicked()), SLOT(ButtonClicked()));
}

TestWidget::~TestWidget() {
}

void TestWidget::ButtonClicked() {
    QMessageBox::information(this, "Infor", "you clicked on a box!");
}