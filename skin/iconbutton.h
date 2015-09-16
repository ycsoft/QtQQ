#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QVector>


class QMouseEvent;
class QEvent;
class QPaintEvent;
class QPixmap;
class QLabel;


class IconButton : public QPushButton
{
    Q_OBJECT
public:

    enum Status{
                BUTTON_FIRST,
                BUTTON_SCALED,
                BUTTON_ENTER,
                BUTTON_LEAVE,
                BUTTON_PRESSED,
                BUTTON_DISABLE
                };
    enum Mode{ COMMON,DOWNUP };

    explicit IconButton(QWidget *parent = 0,
                        QString iconnormal="",QString iconHigh="",QString icondown="");

    void SetButtonText(QString txt);

    void setText( QString txt ) { SetButtonText(txt);}

    void SetMode( Mode mode )            { m_mode = mode;}

    void SetTextStyle(QString style);

    void SetButtonIcon(QString iconpath);

    void AddTxtLabel();

    void SetStatus(int status);

    void enterEvent(QEvent *evt);

    void leaveEvent(QEvent *evt);

    void mousePressEvent(QMouseEvent *evt);

    void mouseReleaseEvent(QMouseEvent *evt);

    void paintEvent(QPaintEvent *evt);

    void setButtonDown(bool b);

    void setButtonDown();
    void setButtonUP();
    QString GetButtonText() { return m_txt;}


    QVector<QPixmap>            m_icon_list;
    QPixmap                     m_cur_icon;

signals:
    void  textClick(QString txt);

public slots:

private:


    QString                     m_txt;
    QLabel                      *m_txt_lb;
    int                         m_status;
    int                         m_mode;
    bool                        m_isDown;

};

#endif // ICONBUTTON_H
