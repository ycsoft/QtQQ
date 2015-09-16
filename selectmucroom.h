#ifndef SELECTMUCROOM_H
#define SELECTMUCROOM_H

#include <QDialog>

namespace Ui {
class SelectMucroom;
}

class SelectMucroom : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMucroom(QWidget *parent = 0);
    ~SelectMucroom();
    void tranobjectJID(QString);
    void tranobjectname(QString);
public slots:
    void confirmClick();

private:
    Ui::SelectMucroom *ui;
    QString objectJID;
    QString objectname;
    QString roomJID;
};

#endif // SELECTMUCROOM_H

