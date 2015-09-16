#ifndef RESETNICKNAME_H
#define RESETNICKNAME_H

#include <QDialog>

namespace Ui {
class ResetNickname;
}

class ResetNickname : public QDialog
{
    Q_OBJECT

public:
    explicit ResetNickname(QWidget *parent = 0);
    ~ResetNickname();
    QString getNickname();

public slots:
    void confirmClick();

private:
    Ui::ResetNickname *ui;
    QString Nickname;
};

#endif // RESETNICKNAME_H
