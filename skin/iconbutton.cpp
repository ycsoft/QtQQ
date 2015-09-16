
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QPainter>


#include "iconbutton.h"



IconButton::IconButton(QWidget *parent,QString iconnormal,QString iconHigh,QString icondown)
{
    QPixmap pix_0(iconnormal);
    QPixmap pix_1(iconHigh);
    QPixmap pix_2(icondown);

    m_icon_list.append(pix_0);
    m_icon_list.append(pix_1);
    m_icon_list.append(pix_2);

    if (!iconnormal.isEmpty())
    {
        m_cur_icon = pix_0;
        setFixedSize(m_cur_icon.size());
    }

    setAttribute(Qt::WA_TranslucentBackground);
    m_txt_lb = NULL;
    m_mode = COMMON;
    m_isDown = false;

}

//设置按钮文本
void IconButton::SetButtonText(QString txt)
{
    m_txt = txt;

    if ( m_txt_lb )
    {
        m_txt_lb->setText(txt);
    }

}

//设置文本风格
void IconButton::SetTextStyle(QString style)
{
    m_txt_lb->setStyleSheet(style);
}

//添加文本标签
void IconButton::AddTxtLabel()
{
    m_txt_lb = new QLabel(this);
    m_txt_lb->setAlignment(Qt::AlignHCenter);
    m_txt_lb->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(m_txt_lb,0,Qt::AlignHCenter | Qt::AlignVCenter);
    this->setLayout(lay);
}

//设置按钮图标
void IconButton::SetButtonIcon(QString iconpath)
{
    if ( !iconpath.isEmpty())
        m_cur_icon = QPixmap(iconpath);
}

//设置按钮状态
void IconButton::SetStatus(int status)
{
    if ( m_mode == DOWNUP )
        return;
    m_status = status;
    switch(status)
    {
        case BUTTON_ENTER:
        {
            m_cur_icon = m_icon_list[1];
            break;
        }
        case BUTTON_PRESSED:
        {
            m_cur_icon = m_icon_list[2];
            break;
        }
        case BUTTON_LEAVE:
        {
            m_cur_icon = m_icon_list[0];
            break;
        }
    }
}

void IconButton::enterEvent(QEvent *evt)
{
    SetStatus(BUTTON_ENTER);
}

void IconButton::leaveEvent(QEvent *evt)
{
    SetStatus(BUTTON_LEAVE);
}

void IconButton::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),m_cur_icon);
    if ( NULL == m_txt_lb )
    painter.drawText(QRectF(rect()),m_txt,QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}

void IconButton::setButtonDown()
{
    m_cur_icon = m_icon_list[1];
    update();
}

void IconButton::setButtonDown(bool b)
{
    if ( b )
    {
        setButtonDown();
        m_isDown = true;
    }
    else
    {
        m_isDown = false;
        setButtonUP();
    }
    update();
}


void IconButton::setButtonUP()
{
    m_cur_icon = m_icon_list[0];
    update();
}

void IconButton::mousePressEvent(QMouseEvent *evt)
{
    if ( evt->button() == Qt::LeftButton )
    {
        SetStatus(BUTTON_PRESSED);
        emit clicked();
        emit textClick( m_txt );
        setButtonDown(m_isDown);

        m_isDown = !m_isDown;
        update();
    }
}
void IconButton::mouseReleaseEvent(QMouseEvent *evt)
{
    SetStatus(BUTTON_LEAVE);
}
