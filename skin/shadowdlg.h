#ifndef SHADOWDLG_H
#define SHADOWDLG_H

#include <QDialog>
#include <QMouseEvent>
#include <event.h>

class ShadowDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ShadowDlg(QWidget *parent = 0);

    //重载标准组件的鼠标事件
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QPoint          m_movePoint;
    bool            m_pressed;


};

#endif // SHADOWDLG_H
