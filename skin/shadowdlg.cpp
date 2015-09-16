
#include <QStyleOption>
#include <QPainter>
#include <QColor>
#include <math.h>


#include "shadowdlg.h"



ShadowDlg::ShadowDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    m_movePoint = QPoint(0,0);
    m_pressed = false;
    setAttribute(Qt::WA_TranslucentBackground);
}

//鼠标按下
void ShadowDlg::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        m_pressed = true;
        m_movePoint = event->globalPos()-pos();
    }
    else
    {
        m_pressed = false;
    }
}
//鼠标移动
void ShadowDlg::mouseMoveEvent(QMouseEvent *event)
{
    if ( m_pressed)
    {
        move(event->globalPos() - m_movePoint);
    }
}
//鼠标释放
void ShadowDlg::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        m_pressed = false;
    }else
    {
        m_pressed = true;
    }
}
//窗口重绘
void ShadowDlg::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    QStyle *style = this->style();
    style->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,this->width()-20,this->height()-20);
    painter.fillPath(path,QBrush(Qt::white));
    QColor color(0,0,0,50);
    for ( int i = 0; i< 10; ++i)
    {
        QPainterPath path2;
        path2.setFillRule(Qt::WindingFill);
        path2.addRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2);
        color.setAlpha(150-sqrt((float)i)*50);
        painter.setPen(color);
        painter.drawPath(path2);
    }
}
