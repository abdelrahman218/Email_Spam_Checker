#include "Email_spam_checker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Email_spam_checker w;
    w.show();
    return a.exec();
}