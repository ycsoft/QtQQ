#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QWidget>


class IconButton;

class TabButton : public QWidget
{
    Q_OBJECT
public:
    explicit TabButton(QWidget *parent = 0);

    void    SetButtonText( QString txt );


    void setButtonDown(bool b);

    void enterEvent(QEvent *evt);
    void leaveEvent(QEvent *evt);

    void SetCloseIcon( QString icon );
    void NoFocus();
    void SetFocus();

signals:
    void    tabButtonClick_sig(QString);
    void    tabCloseClick_sig(QString);


public slots:
    void    tabButtonClick_slot(QString);
    void    tabCloseClick();

private:
    IconButton  *m_btn;
    IconButton  *m_closebtn;

};

#endif // TABBUTTON_H
