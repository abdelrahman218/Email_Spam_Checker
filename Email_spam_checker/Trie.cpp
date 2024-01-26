#include "Trie.h"
Trie::Trie() {
	root = new trieNode(NULL);
}
bool Trie::isNextChar(ElementType test, NodePtr iter) const { return(iter->nextChar[indexOf(test)] != nullptr); }
bool Trie::isEmpty() const { return (!haveNextChar(root)); }
int Trie::indexOf(ElementType character) const {
	int index = -1;
	if (character >= 'a' && character <= 'z')
		index = (int)character - 97;
	else if (character == '%')
		index = 26;
	else if (character == '$')
		index = 27;
	else if (character == '0')
		index = 28;
	else if (character == '1')
		index = 29;
	return index;
}
bool Trie::haveNextChar(NodePtr Ptr) const {
	for (NodePtr iter : Ptr->nextChar)
	{
		if (iter != nullptr) {
			return true;
		}
	}
	return false;
}
void Trie::insert(string input, severityLevel wordSeverity) {
	NodePtr track = root, nextTrack;
	input = formatRegulator(input);
	for (char currentChar : input) {
		if (!isNextChar(currentChar, track)) {
			nextTrack = new trieNode(track);
			track->nextChar[indexOf(currentChar)] = nextTrack;
			track = nextTrack;
		}
		else {
			track = track->nextChar[indexOf(currentChar)];
		}
	}
	track->isWord = true;
	track->spamWordSeverity = wordSeverity;
}
bool Trie::search(string key, severityLevel& wordSeverity) const {
	NodePtr track = root;
	key = formatRegulator(key);
	for (char currentChar : key) {
		if (!isNextChar(currentChar, track))
			return false;

		track = track->nextChar[indexOf(currentChar)];
	}
	wordSeverity = track->spamWordSeverity;
	return (track->isWord);
}

bool Trie::search(string key) const {
	NodePtr track = root;
	key = formatRegulator(key);
	for (char currentChar : key) {
		if (!isNextChar(currentChar, track))
			return false;

		track = track->nextChar[indexOf(currentChar)];
	}
	return (track->isWord);
}
void Trie::erase(string input) {
	input = formatRegulator(input);
	if (isEmpty()) {
		cout << "Trie is Empty." << endl;
		return;
	}
	if (!search(input)) {
		cout << "Item \"" << input << "\" doesn't exist in the trie." << endl;
		return;
	}
	else {
		NodePtr Ptr;
		Ptr = root;
		for (int j = 0; j < input.size(); j++) {
			Ptr = Ptr->nextChar[indexOf(input[j])];
		}
		if (haveNextChar(Ptr)) {
			Ptr->isWord = false;
			Ptr->spamWordSeverity = Low;
			return;
		}
		else {
			for (int j = 0; j < input.size(); j++) {
				NodePtr ter = Ptr;
				Ptr = Ptr->parent;
				Ptr->nextChar[indexOf(input[input.size() - j - 1])] = nullptr;
				delete ter;
				if (haveNextChar(Ptr))
					return;
			}
		}
	}
}
void Trie::clear(NodePtr ptr) {
	if (haveNextChar(ptr)) {
		for (int i = 0; i < charCount; i++) {
			if (ptr->nextChar[i] != nullptr) {
				clear(ptr->nextChar[i]);
				ptr->nextChar[i] = nullptr;
			}
		}
	}
	delete ptr;
}
string Trie::formatRegulator(string trial) const {
	string regulated = "";
	for (int j = 0; j < trial.size(); j++) {
		if ((trial[j] >= 'A') && (trial[j] <= 'Z'))
			regulated += tolower(trial[j]);
		else if (trial[j] >= 'a' && trial[j] <= 'z')
			regulated += trial[j];
	}
	return regulated;
}
void Trie::display(ostream& out) const {
	displayAUX(root, out);
	out << endl;
}
void  Trie::displayAUX(NodePtr ptr, ostream& out) const {
	if (haveNextChar(ptr)) {
		for (int i = 0; i < charCount; i++) {
			if (ptr->nextChar[i] != nullptr) {
				if (ptr->nextChar[i]->isWord) {
					string word;
					NodePtr ptrparent = ptr;
					NodePtr ptrgrand = ptr->parent;
					word += (char)revIndOf(i);
					while (ptrparent != root) {
						for (int i = 0; i < charCount; i++) {
							if (ptrgrand->nextChar[i] == ptrparent)
								word += revIndOf(i);
						}
						ptrparent = ptrgrand;
						ptrgrand = ptrgrand->parent;
					}
					for (int i = word.size() - 1; i >= 0; i--)
						out << word[i];
					out << " , ";
				}
				displayAUX(ptr->nextChar[i], out);
			}
		}
	}
}

char Trie::revIndOf(int x) const { 
	char charAscii = ' ';
	if (x < 26)
		charAscii = (char)x + 97;
	else if (x == 26)
		charAscii = '%';
	else if (x == 27)
		charAscii = '$';
	else if (x == 28)
		charAscii = '0';
	else if (x == 29)
		charAscii = '1';
	return charAscii;
}
Trie::~Trie() {
	clear(root);
}
ostream& operator<<(ostream& out, const Trie& aTrie) {
	aTrie.display(out);
	return out;
}