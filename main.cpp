#include <QApplication>
#include "popupwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PopupWindow *popup;
    popup = new PopupWindow(qobject_cast<PopupWindow* >(&a));
//    popup = new PopupWindow(&a);
//    popup->show();




    return a.exec();
//    return 0;
}
