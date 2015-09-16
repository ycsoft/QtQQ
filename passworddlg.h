#ifndef PASSWORDDLG_H
#define PASSWORDDLG_H

#include <QDialog>

namespace Ui {
class passworddlg;
}

class passworddlg : public QDialog
{
    Q_OBJECT

public:
    explicit passworddlg(QWidget *parent = 0);
    ~passworddlg();

public slots:
    void modify();
    void cancle();

private:
    Ui::passworddlg *ui;
};

#endif // PASSWORDDLG_H
