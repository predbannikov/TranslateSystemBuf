#include "keypresseater.h"
#include <QApplication>

KeyPressEater::KeyPressEater(QObject *parent) : QObject(parent)
{
//    this->installEventFilter(this);

    qApp->installEventFilter(this);
    qDebug() << "construct";

}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if(event->spontaneous())
        qDebug() << "this event outside";
    qDebug() << "event";
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
