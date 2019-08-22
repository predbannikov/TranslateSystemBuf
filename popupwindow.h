#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QMouseEvent>
#include <QNetworkReply>
#include <QTimer>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPropertyAnimation>
#include <QNetworkAccessManager>
#include <QGraphicsOpacityEffect>
#include <QApplication>
#include <QClipboard>
#include <QCursor>
#include "notify.h"

class CustomPushButton;

class PopupWindow : public QObject
{
    Q_OBJECT
public:
    explicit PopupWindow(QObject *parent = nullptr);
//    ~PopupWindow() override;
protected:
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void showPopUpWindow();
    void showPopUpNotify();

    QStringList resultMsg;
    QClipboard* clipboard;
    QPixmap pxmap;
    QString copyText;
    CustomPushButton *customButton;
    QTimer timerNotify;
    QTimer timerShow;
    const int waitShowPopUp = 5000;
    const int waitAfterReleaseFocus = 1000;
//    const int waitShowPopUpNotify = 15000;
    const int waitAfterReleaseFocusNotify = 1000;
    void hideFromTaskBar(QWidget *widget);
    void parsArray(QJsonArray jarray);
    void sendNotification();
    Notify  *notify;
signals:
    void closeButton();

public slots:
    void onClipboardChanged();
    void slotCustomButtonClick();
};

class CustomPushButton : public QPushButton
{
Q_OBJECT
public:
    explicit CustomPushButton(QPixmap pixmap, QWidget* parent=nullptr ) : QPushButton(parent) {

        QIcon ico = QIcon(pixmap);
        setIcon(ico);
        setIconSize(QSize(24, 24));
        setGeometry(QRect(QPoint(0,0),QSize(24, 24)));
    }
signals:
    void clicked();
protected:
//    void focusInEvent(QFocusEvent* event)  {
//        qDebug() << "hit the target";
//    }
//    void focusOutEvent(QFocusEvent* event)  {
//        qDebug() << "hit the target";
//    }

};

#endif // POPUPWINDOW_H
