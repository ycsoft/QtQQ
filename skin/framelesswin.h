#ifndef FRAMELESSWIN_H
#define FRAMELESSWIN_H

#include <QDialog>
#include <QPoint>

class FramelessWin : public QDialog
{
    Q_OBJECT
public:
    enum Direct {
                 UP,DOWN,LEFT,
                 RIGHT,LEFTTOP,
                 LEFTDOWN,RIGHTTOP,
                 RIGHTDOWN,UNKOWN
                };
    explicit FramelessWin(QWidget *parent = 0);
    virtual ~FramelessWin();

    //UI界面设计
    virtual void SetupUI() = 0;


    void GetMoveDirect(QPoint cursorPoint);
    void changeSize(QRect &move,QPoint pos);
    //重载事件
    void mousePressEvent(QMouseEvent *evt);
    void mouseReleaseEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void paintEvent(QPaintEvent *evt);
signals:

public slots:
private:
    int         m_direct;
    int         m_padding;
    bool        m_pressed;
    QPoint      m_movePoint;

};

#endif // FRAMELESSWIN_H
