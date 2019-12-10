#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <QWidget>
#include <QtGui>
#include <QLabel>

class KeyPress : public QWidget
{
    Q_OBJECT
public:
    explicit KeyPress(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QLabel *myLabelText;
};

#endif // KEYPRESS_H
