#include "widget.h"
Window1::Window1(QWidget *parent)
    : QWidget(parent)
{
       QHBoxLayout *hbox = new QHBoxLayout;
       QVBoxLayout *vbox = new QVBoxLayout;
       vbox->addWidget(createClickIntervalGroup());
       hbox->addWidget(createClickOptionsGroup());
       hbox->addWidget(createClickRepeat());
       vbox->addLayout(hbox);
       vbox->addWidget(createBottomButtons());
       setLayout(vbox);
       setWindowTitle("Auto_Clicker_v2");
       this->layout()->setSizeConstraint(QLayout::SetFixedSize);

}


QGroupBox *Window1::createClickIntervalGroup()
{
    QGroupBox *groupBox = new QGroupBox("Click Interval");
    QHBoxLayout *hbox = new QHBoxLayout;
    QLabel *Lh = new QLabel("hours");
    QLineEdit *QLh = new QLineEdit();
    QLabel *Lm = new QLabel("minutes");
    QLineEdit *QLm = new QLineEdit();
    QLabel *Ls = new QLabel("seconds");
    QLineEdit *QLs = new QLineEdit();
    QLabel *Lmi = new QLabel("miliseconds");
    QLineEdit *QLmi = new QLineEdit("100");
    QLh->setValidator(new QRegExpValidator(QRegExp("^[1-9][0-9]{0,3}$")));
    QLm->setValidator(new QRegExpValidator(QRegExp("^[1-9][0-9]{0,3}$")));
    QLs->setValidator(new QRegExpValidator(QRegExp("^[1-9][0-9]{0,3}$")));
    QLmi->setValidator(new QRegExpValidator(QRegExp("^[1-9][0-9]{0,3}$")));
    QLh->setFixedWidth(45);
    QLm->setFixedWidth(45);
    QLs->setFixedWidth(45);
    QLmi->setFixedWidth(45);
    hbox->addWidget(QLh);
    hbox->addWidget(Lh);
    hbox->addWidget(QLm);
    hbox->addWidget(Lm);
    hbox->addWidget(QLs);
    hbox->addWidget(Ls);
    hbox->addWidget(QLmi);
    hbox->addWidget(Lmi);
    groupBox->setLayout(hbox);
    hbox->addStretch(0);

    connect(QLh, SIGNAL(textChanged(QString)), this, SLOT(set_interval_h(QString)));
    connect(QLm, SIGNAL(textChanged(QString)), this, SLOT(set_interval_m(QString)));
    connect(QLs, SIGNAL(textChanged(QString)), this, SLOT(set_interval_s(QString)));
    connect(QLmi, SIGNAL(textChanged(QString)), this, SLOT(set_interval_mi(QString)));

    return groupBox;
}

QGroupBox *Window1::createClickOptionsGroup()
{
    QGroupBox *groupBox = new QGroupBox("Click Options");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox1 = new QHBoxLayout;
    QHBoxLayout *hbox2 = new QHBoxLayout;
    QComboBox *Cb1 = new QComboBox;
    QComboBox *Cb2 = new QComboBox;
    QLabel *L1 = new QLabel("mouse button");
    QLabel *L2 = new QLabel("click type");
    Cb1->addItem("Left");
    Cb1->addItem("Right");
    Cb2->addItem("Single");
    Cb2->addItem("Double");
    hbox1->addWidget(L1);
    hbox1->addWidget(Cb1);
    vbox->addLayout(hbox1);
    hbox2->addWidget(L2);
    hbox2->addWidget(Cb2);
    vbox->addLayout(hbox2);
    groupBox->setLayout(vbox);
    QSignalMapper *sm= new QSignalMapper();
    sm->setMapping(Cb1, Cb1->currentText());
    connect(Cb1, SIGNAL(textActivated(QString)), this, SLOT(changebutton(QString)));
    QSignalMapper *sm2= new QSignalMapper();
    sm2->setMapping(Cb2, Cb2->currentText());
    connect(Cb2, SIGNAL(textActivated(QString)), this, SLOT(changeclicktype(QString)));
    return groupBox;
}
QGroupBox *Window1::createClickRepeat()
{
    QGroupBox *groupBox = new QGroupBox("Click Repeat");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;
    QRadioButton *R1 = new QRadioButton("Infinite (Until stopped)");
    QRadioButton *R2 = new QRadioButton("Repeat");
    QLineEdit *QLr = new QLineEdit("0");  
    QLabel *L = new QLabel("times");
    QLr->setValidator(new QRegExpValidator(QRegExp("^[1-9][0-9]{0,3}$")));
    QLr->setFixedWidth(55);
    R2->setFixedWidth(65);
    R1->setChecked(true);
    QLr->setDisabled(true);
    groupBox->setFixedWidth(225);
    vbox->addWidget(R1);
    hbox->addWidget(R2);
    hbox->addWidget(QLr);
    hbox->addWidget(L);
    vbox->addLayout(hbox);
    groupBox->setLayout(vbox);
    connect(R1, SIGNAL(toggled(bool)),QLr,SLOT(setDisabled(bool)));
    connect(R1, SIGNAL(toggled(bool)), this, SLOT(changetozero()));
    connect(R2, SIGNAL(toggled(bool)), this, SLOT(changetovar()));
    connect(QLr, SIGNAL(textChanged(QString)), this, SLOT(changevalue(QString)));
    return groupBox;
}

QGroupBox *Window1::createBottomButtons()
{
    QGroupBox *groupBox = new QGroupBox();
    groupBox->setFlat(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    Stop->setText("Stop (F9)");
    Start->setText("Start (F8)");
    Debug->setText("Debug (F10)");
    QShortcut *shortcut = new QShortcut(QKeySequence("F8"),Start);
    QShortcut *shortcut2 = new QShortcut(QKeySequence("F9"),Stop);
    QShortcut *shortcut3 = new QShortcut(QKeySequence("F10"),Debug);
    connect(shortcut, SIGNAL(activated()), this, SLOT(startWorkInAThread()));
    connect(shortcut2, SIGNAL(activated()), this, SLOT(stup()));
    connect(shortcut3, SIGNAL(activated()), this, SLOT(startWorkInAThread()));

    hbox->addWidget(Start);
    hbox->addWidget(Stop);
    hbox->addWidget(Debug);
    groupBox->setLayout(hbox);
    connect(Start, SIGNAL(clicked()), this, SLOT(startWorkInAThread()));
    connect(Stop, SIGNAL(clicked()), this, SLOT(stup()));
    connect(Debug, SIGNAL(clicked()), this, SLOT(debug()));
    return groupBox;
}


