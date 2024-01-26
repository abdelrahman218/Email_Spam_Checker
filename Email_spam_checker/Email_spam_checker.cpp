#include "Email_spam_checker.h"
Email_spam_checker::Email_spam_checker(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

Email_spam_checker::~Email_spam_checker()
{}
void Email_spam_checker::spamChecker() {
    string email = ui.mail->toPlainText().toStdString();
	Trie spamWords;
	for (int i = 0; i < email.size(); i++) {
		if (email[i] == '\n')
			email[i] = ' ';
	}
    if (isSpam(email, spamWords)) {
        ui.result->setText("This is a spam\nSpam Words:");
		string word;
		severityLevel sl;
		size_t offset = 0;
		size_t end = 0;
		string SpamList;
		while (end != string::npos) {
			end = email.find(' ', offset);
			word = email.substr(offset, end - offset);
			if (spamWords.search(word, sl)) {
				SpamList += word + " ";
				if (sl == 5) {
					SpamList += "(Low)\n";
				}
				else if (sl == 10) {
					SpamList += "(Medium)\n";
				}
				else if (sl == 15) {
					SpamList += "(High)\n";
				}
			}
			offset = end + 1;
		}
		ui.result->append(QString::fromStdString(SpamList));
    }
    else {
        ui.result->setText("This is not a spam");
    }
}
void Email_spam_checker::clearNodes() {
	ui.mail->clear();
	ui.result->clear();
}