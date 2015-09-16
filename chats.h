#ifndef CHATS_H
#define CHATS_H

#include <QDialog>
#define LOCAL(x) QString::fromLocal8Bit(x)

namespace Ui {
class chats;
}

class chats : public QDialog
{
    Q_OBJECT

public:
    explicit chats(QWidget *parent = 0);
    ~chats();
    void setchatsedit(QString);
    void clear();
    void scrollToBottom();

private:
    Ui::chats *ui;
};

#endif // CHATS_H
