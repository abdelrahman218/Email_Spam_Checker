#include"spam filter.h"
#include"Trie.h"
#include<fstream>
bool isSpam(string& emailMessage,Trie& words) {
	static Trie spamList;
	if (spamList.isEmpty()) {
		ifstream file;
		file.open("Trie.txt");
        readfromfile(spamList,file);
	}
	const int spamScore = 80;
	string word;
	severityLevel sl;
	size_t offset = 0;
	size_t end = 0;
	int score = 0;
	while (end != string::npos) {
		end = emailMessage.find(' ', offset);
		word = emailMessage.substr(offset, end - offset);
		if (spamList.search(word, sl)) {
			score += sl;
			words.insert(word, sl);
		}
		offset = end + 1;
	}
	if (score >= spamScore)
		return true;
	else return false;
}
void readfromfile(Trie &test, ifstream& file) {
	while (!file.eof()) {
		string wor,word, c;
		getline(file, wor);
		getline(file, c);
		if (c == "High") {
			test.insert(wor, High);
		}
		else if (c == "Medium") {
			test.insert(wor, Medium);
		}
		else if (c == "Low") {
			test.insert(wor, Low);
		}
	}
	
}
