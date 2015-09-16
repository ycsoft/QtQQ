#ifndef SET_DIRPATH_H
#define SET_DIRPATH_H

#include <QDialog>
#include "roomchat.h"
namespace Ui {
class Set_dirpath;
}

class Set_dirpath : public QDialog
{
    Q_OBJECT

public:
    explicit Set_dirpath(QWidget *parent = 0);
    ~Set_dirpath();
public slots:
    void slot_select();
    void slot_setpath();
    void slot_close();

private:
    QString path;
    Ui::Set_dirpath *ui;
};

#endif // SET_DIRPATH_H
