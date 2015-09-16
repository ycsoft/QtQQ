#ifndef SETSTATE_H
#define SETSTATE_H

#include <QDialog>

namespace Ui {
class setstate;
}

class setstate : public QDialog
{
    Q_OBJECT

public:
    explicit setstate(QWidget *parent = 0);
    ~setstate();

public slots:
    void slotcloseall();
    void slotclosecurrent();

private:
    Ui::setstate *ui;
};

#endif // SETSTATE_H
