#ifndef TEST_H
#define TEST_H

#include <QDockWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

class TestWidget : public QDockWidget {
    Q_OBJECT

    public:
        explicit TestWidget(QWidget *parent = nullptr);
        ~TestWidget();

    private:
        void buttonClicked();
        QWidget *m_parent;
        QPushButton *m_button = new QPushButton();

    private slots:
    void ButtonClicked();

};
#endif
