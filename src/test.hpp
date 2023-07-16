#ifndef TEST_H
#define TEST_H

#include <QDockWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QInputDialog>

#include <plugin-support.h>

#include "browser.hpp"
#include "TwitchClipFetcher.hpp"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE;

class BrowserDialog : public QDockWidget {
    Q_OBJECT

    public:
        explicit BrowserDialog(
            QWidget *parent = nullptr
        );
        ~BrowserDialog();
        const char * getText() const;

    private:
        QWidget *m_parent;
        QWidget *m_widget;
        QBoxLayout *m_layout;
        QLabel *m_text_label;
        QPushButton *m_text_button;

    private slots:
    void setText();

};
#endif
