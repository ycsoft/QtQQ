#ifndef ADDFILES_H
#define ADDFILES_H

#include <QDialog>
#define LOCAL(x) QString::fromLocal8Bit(x)
namespace Ui {
class addfiles;
}

class addfiles : public QDialog
{
    Q_OBJECT

public:
    explicit addfiles(QWidget *parent = 0);
    ~addfiles();
    QString getfilename();
public slots:
    void slotselect();
    void slotconfirm();
private:
    Ui::addfiles *ui;
};

#endif // ADDFILES_H
