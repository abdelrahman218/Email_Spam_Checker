#pragma once

#include <QtWidgets/QMainWindow>
#include<iostream>
#include<string>
#include "ui_Email_spam_checker.h"
#include"Trie.h"
#include"spam filter.h"
using namespace std;
class Email_spam_checker : public QMainWindow
{
    Q_OBJECT

public:
    Email_spam_checker(QWidget *parent = nullptr);
    ~Email_spam_checker();
private:
    Ui::Email_spam_checkerClass ui;
private slots:
    void spamChecker();
    void clearNodes();
};
