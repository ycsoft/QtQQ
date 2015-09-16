
#include <QHBoxLayout>

#include "tabbutton.h"
#include "skin/iconbutton.h"


TabButton::TabButton(QWidget *parent) :
    QWidget(parent)
{

    QHBoxLayout *mainlay = new QHBoxLayout(this);
    setMaximumHeight(40);
    QWidget *center = new QWidget(this);
    QHBoxLayout *centerlay = new QHBoxLayout(center);
    centerlay->setSpacing(0);
    centerlay->setContentsMargins(0,0,0,0);

    m_closebtn = new IconButton(this,":/ui/close_nofocus.png",":/ui/close_high2.png",":/ui/close_normal2.png");
            //new IconButton(this,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");

    m_btn = new IconButton(this,":/ui/switch.png",":/ui/switch-high.png",":/ui/switch-down.png");

    m_btn->SetMode( IconButton::DOWNUP);
    centerlay->addWidget(m_btn);
    centerlay->addWidget(m_closebtn);
    center->setLayout(centerlay);

    mainlay->setContentsMargins(0,0,0,0);
    mainlay->addWidget(center);
    setAttribute(Qt::WA_TranslucentBackground);
    connect(m_btn,SIGNAL(textClick(QString)),this,SLOT(tabButtonClick_slot(QString)));
    connect(m_closebtn,SIGNAL(clicked()),this,SLOT(tabCloseClick()));
    //m_closebtn->setVisible(false);
}

void TabButton::tabButtonClick_slot(QString txt)
{
    emit tabButtonClick_sig(txt);
}

void TabButton::setButtonDown(bool b)
{

    m_btn->setButtonDown(b);
    if ( b )
    {
        SetFocus();
    }else
    {
        NoFocus();
    }
    update();
}

void TabButton::enterEvent(QEvent *evt)
{
    m_closebtn->SetStatus(IconButton::BUTTON_ENTER);
    update();

}

void TabButton::leaveEvent(QEvent *evt)
{
    //m_closebtn->setVisible(false);
    m_closebtn->SetStatus(IconButton::BUTTON_LEAVE);
    update();
}

void TabButton::SetCloseIcon(QString icon)
{
    m_closebtn->SetButtonIcon(icon);
}

void TabButton::SetFocus()
{
    m_closebtn->m_icon_list[0] = QPixmap(":/ui/close_nofocushigh.png");
    m_closebtn->m_icon_list[1] = QPixmap(":/ui/close_focus.png");
    m_closebtn->SetStatus(IconButton::BUTTON_LEAVE);
    m_closebtn->update();
}
void TabButton::NoFocus()
{
    m_closebtn->m_icon_list[0] = QPixmap(":/ui/close_nofocus.png");
    m_closebtn->m_icon_list[1] = QPixmap(":/ui/close_high2.png");
    m_closebtn->SetStatus(IconButton::BUTTON_LEAVE);
    m_closebtn->update();
}

void TabButton::tabCloseClick()
{
    emit tabCloseClick_sig(m_btn->GetButtonText());
}

void TabButton::SetButtonText(QString txt)
{

    m_btn->SetButtonText(txt);
}
