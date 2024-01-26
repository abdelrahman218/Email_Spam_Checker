#pragma once
#include<iostream>
#include"Trie.h"
#include<fstream>
using namespace std;

bool isSpam(string& ,Trie& );
void readfromfile(Trie& test,ifstream& file);