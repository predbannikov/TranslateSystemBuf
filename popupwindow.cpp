#include "popupwindow.h"


PopupWindow::PopupWindow(QObject *parent) : QObject(parent)
{
    clipboard = QApplication::clipboard();

    pxmap = QPixmap(":/translate-ico-64x64.png");

    connect( clipboard, SIGNAL( dataChanged() ), SLOT( onClipboardChanged() ) );
    customButton = new CustomPushButton(pxmap);
    connect(customButton, &QPushButton::clicked, this, &PopupWindow::slotCustomButtonClick);
    customButton->installEventFilter(this);
    customButton->setObjectName("button");
    customButton->setWindowFlag(Qt::FramelessWindowHint);


    notify = new Notify;
    notify->installEventFilter(this);
    notify->setObjectName("notify");
//    slotCustomButtonClick();
//    sendNotification();
//    showPopUpNotify();
}

void PopupWindow::hideFromTaskBar(QWidget* widget)
{

}

bool PopupWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::FocusOut) {
        if(obj->objectName() == "button") {
            timerShow.stop();
            timerShow.start(100);
        } else {
            qDebug() << "focus out" << obj->objectName();
            if(!notify->isActiveWindow()) {
                timerNotify.stop();
                timerNotify.start(waitAfterReleaseFocusNotify);

            }
        }
        return true;
    } else if(event->type() == QEvent::HoverEnter) {
        if(obj->objectName() == "notify") {

        } else if(obj->objectName() == "button") {
            timerShow.stop();
        }
        return true;
    } else if(event->type() == QEvent::HoverLeave) {
        if(obj->objectName() == "notify") {

        } else if(obj->objectName() == "button") {
            timerShow.start(waitShowPopUp);
        }
    }
    return false;
}

void PopupWindow::showPopUpWindow()
{
    if(customButton->isVisible()) {
        customButton->move(QCursor::pos());
        customButton->activateWindow();
    } else {
//        customButton->setFocus();
        customButton->move(QCursor::pos());
        customButton->show();
        timerShow.setSingleShot(true);
        timerShow.start(waitShowPopUp);
        QEventLoop loop;
        QObject::connect(&timerShow, &QTimer::timeout, &loop, &QEventLoop::quit);
        loop.exec();
        customButton->hide();
    }
}

void PopupWindow::showPopUpNotify()
{
    if(notify->isVisible()) {
        notify->setText(resultMsg);
        notify->activateWindow();
    } else {
        notify->setFocus();
        notify->move(QCursor::pos());
        notify->setText(resultMsg);
        notify->show();
        timerNotify.setSingleShot(true);
//        timerNotify.start(waitAfterReleaseFocusNotify);
        QEventLoop loop;
        QObject::connect(&timerNotify, &QTimer::timeout, &loop, &QEventLoop::quit);
        loop.exec();
        notify->hide();
    }
}

void PopupWindow::onClipboardChanged()
{
    copyText = clipboard->text();
    showPopUpWindow();
}

void PopupWindow::parsArray(QJsonArray jarray)
{
    for(int i = 0; i < jarray.size(); i++) {
        if(jarray.isEmpty())
            return;
        if(i == 8)
            continue;
        if(!jarray[i].isArray()) {
            if(!jarray[i].toString().isEmpty()) {
                if(jarray[i].toString() != "en") {
                    resultMsg << jarray[i].toString();
//                    qDebug() << qPrintable(jarray[i].toString()) ;
                }
            }
        }
        else {
            parsArray(jarray[i].toArray());
        }
    }
}

void PopupWindow::sendNotification()
{

}


void PopupWindow::slotCustomButtonClick()
{
    timerShow.stop();
    customButton->hide();


    QNetworkAccessManager man;
    QNetworkRequest req;
    QString sourceLang = "en";
    QString targetLang = "ru";
    QString sourceText = copyText.simplified();
    QString strurl = QString("http://translate.googleapis.com/translate_a/single?client=gtx&sl=%1&tl=%2&dt=t&q=%3")
            .arg(sourceLang)
            .arg(targetLang)
            .arg(sourceText);
    req.setUrl(QUrl(strurl));
    QNetworkReply *reply = man.get(req);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    QByteArray array = reply->readAll();

    QJsonDocument jdoc = QJsonDocument::fromJson(array);
    QJsonArray jarray = jdoc.array();
    resultMsg.clear();
    parsArray(jarray);
    showPopUpNotify();
}
