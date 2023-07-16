#include "test.hpp"

BrowserDialog::BrowserDialog(
    QWidget *parent
) : QDockWidget("CodeJam Test Plugin", parent) {
    this->m_parent = parent;

    this->m_widget= new QWidget();

    int frameStyle = QFrame::Sunken;

    m_text_label = new QLabel;
    m_text_label->setFrameStyle(frameStyle);
    m_text_button = new QPushButton(tr("Set browser source"));

    m_layout = new QHBoxLayout();

    m_layout->addWidget(m_text_label);
    m_layout->addWidget(m_text_button);
    m_widget->setLayout(m_layout);

    setWidget(m_widget);

    setVisible(false);
    setFloating(true);
    resize(300, 300);

    QObject::connect(m_text_button, &QAbstractButton::clicked, this, &BrowserDialog::setText);
}

BrowserDialog::~BrowserDialog() {
    delete m_text_label;
    delete m_text_button;
    delete m_layout;
    delete m_widget;
}

void BrowserDialog::setText() {
    bool ok;
    QString text = QInputDialog::getText(
        this,
        tr("QInputDialog::getText()"),
        tr("Browser source for random clip"),
        QLineEdit::Normal,
        QString("Browser"),
        &ok
    );

    if (ok && !text.isEmpty()) {
        m_text_label->setText(text);
    }
}

const char * BrowserDialog::getText() const {
    QByteArray ba = m_text_label->text().toLocal8Bit();
    const char *s = ba.data();

    return s;
}
