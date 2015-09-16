
#include <QRect>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <math.h>
#include <QDebug>

#include "framelesswin.h"

FramelessWin::FramelessWin(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    m_movePoint = QPoint(0,0);
    m_pressed = false;
    setAttribute(Qt::WA_TranslucentBackground);
    m_padding = 5;
    m_direct = UNKOWN;
    setMouseTracking(true);
    setCursor(Qt::ArrowCursor);
}

FramelessWin::~FramelessWin()
{

}

void FramelessWin::GetMoveDirect(QPoint cursorPoint)
{
QRect rect = this->rect();
QPoint tl = mapToGlobal(rect.topLeft());
QPoint rb = mapToGlobal(rect.bottomRight());
int x = cursorPoint.x();
int y = cursorPoint.y();
//左上角
if( x-m_padding <= tl.x() && x >= tl.x() && y - m_padding <= tl.y() && y >= tl.y())
{
    m_direct = FramelessWin::LEFTTOP;
    setCursor(Qt::SizeFDiagCursor);
}
//左下角
else if (x - m_padding <= tl.x() && x > tl.x() && y - m_padding <= rb.y() && y >= rb.y())
{
    m_direct = LEFTDOWN;
    setCursor(Qt::SizeBDiagCursor);
}
//左边
else if (x <= tl.x() + m_padding && x >= tl.x() - m_padding)
{
    m_direct = LEFT;
    setCursor(Qt::SizeHorCursor);
}
//右上角
else if (x <= rb.x() && x + m_padding >= rb.x() && y >= tl.y() && y - m_padding <= tl.y())
{
    m_direct = RIGHTTOP;
    setCursor(Qt::SizeBDiagCursor);
}
//右下角
else if (x <= rb.x() && x + m_padding >= rb.x() && y <= rb.y() && y + m_padding >= rb.y())
{
    m_direct = RIGHTDOWN;
    setCursor(Qt::SizeFDiagCursor);
}
//右边
else if (x <= rb.x() + m_padding && x + m_padding >= rb.x())
{

    m_direct = RIGHT;
    setCursor(Qt::SizeHorCursor);
}
//上
else if (y > tl.y() && y < tl.y()+m_padding)
{
    m_direct = UP;
    setCursor(Qt::SizeVerCursor);
}
else if (y <= rb.y() && y +  m_padding >= rb.y())
{
    m_direct = DOWN;
    setCursor(Qt::SizeVerCursor);
}
else
{
    m_direct = UNKOWN;
    setCursor(Qt::ArrowCursor);
}
}

void FramelessWin::changeSize(QRect &move, QPoint pos)
{
    QRect cur = rect();
    QPoint tl = mapToGlobal(cur.topLeft());
    QPoint rb = mapToGlobal(cur.bottomRight());

    if (m_direct == LEFT)
        move.setX(pos.x());
    else if (m_direct == RIGHT)
        move.setWidth(pos.x() - tl.x());
    else if (m_direct == LEFTTOP){
        move.setX(pos.x());
        move.setY(pos.y());
    }
    else if (m_direct == RIGHTTOP){
        move.setWidth(pos.x() - tl.x());
        move.setY(pos.y());
    }
    else if (m_direct == LEFTDOWN){
        move.setHeight(pos.y()- tl.y());
        move.setX(pos.x());}
    else if (m_direct == RIGHTDOWN){
        move.setWidth(pos.x()-tl.x());
        move.setHeight(pos.y() - tl.y());}
    else if (m_direct == UP)
        move.setY(pos.y());
    else if (m_direct == DOWN)
        move.setHeight(pos.y() - tl.y());

}
void FramelessWin::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() != Qt::LeftButton)
    {
        m_pressed = false;
    }
    else
    {
        m_pressed = true;
        m_movePoint = evt->globalPos()-pos();
    }
}
void FramelessWin::mouseReleaseEvent(QMouseEvent *evt)
{
    m_pressed = false;
    if (evt->button() != Qt::LeftButton)
    {
        m_pressed = true;
    }else
    {
        m_pressed = false;
    }
}
void FramelessWin::mouseMoveEvent(QMouseEvent *evt)
{
    QPoint globalPos = evt->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint tb  = mapToGlobal(rect.bottomRight());
    QRect rmove(tl,tb);
    if ( m_pressed )
    {
        if (m_direct == UNKOWN )
        {
            move(evt->globalPos()-m_movePoint);
        }
        else
        {
            changeSize(rmove,globalPos);
            setGeometry(rmove);
        }
    }
    else
    {

        GetMoveDirect(globalPos);
        if ( m_direct == UNKOWN )
            setCursor(Qt::ArrowCursor);
    }
}
void FramelessWin::paintEvent(QPaintEvent *evt)
{
    /*
    添加阴影效果
    :param args:
    :param kwargs:
    :return:
    */
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    QStyle *style = this->style();
    style->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,width()-20,height()-20);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillPath(path,QBrush(Qt::white));
    QColor color(0,0,0,50);
    int i = 0;
    //for i in xrange(10):
    for (i = 0 ; i < 10; i++)
    {
        QPainterPath path2;
        path2.setFillRule(Qt::WindingFill);
        path2.addRect(10-i,10-i,width()-(10-i)*2,height()-(10-i)*2);
        color.setAlpha(150 - sqrt((float)i)*50);
        painter.setPen(color);
        painter.drawPath(path2);
    }
    QPixmap back("./ui/skin.png");
    i = 0;
    painter.drawPixmap(10-i,10-i,width()-(10-i)*2,height()-(10-i)*2,back);

}
