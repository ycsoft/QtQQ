#ifndef FINDFRIEND_H
#define FINDFRIEND_H

#include <QDialog>

namespace Ui {
class FindFriend;
}

class FindFriend : public QDialog
{
    Q_OBJECT

public:
    explicit FindFriend(QWidget *parent = 0);
    ~FindFriend();
public slots:
    void addFriend();//ÃÌº”∫√”—
private:
    Ui::FindFriend *ui;
};

#endif // FINDFRIEND_H
