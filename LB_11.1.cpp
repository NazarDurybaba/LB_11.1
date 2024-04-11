#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void CreateBIN(const char* fname);
void PrintBIN(const char* fname);
void ProcessBIN1(const char* fname, const char* gname);
void SortBIN(const char* fname, const char* gname);
void SortBIN(const char* fname);
char fRead(fstream& f, const int i);
void fWrite(fstream& f, const int i, const char val);
void fChange(fstream& f, const int i, const int j);

void CreateBIN(const char* fname) {
    ofstream fout(fname, ios::binary);
    char ch;
    string s;
    do {
        cin.ignore();
        cout << "enter line: ";
        getline(cin, s);
        for (size_t i = 0; i < s.length(); i++) {
            char c = s[i];
            fout.write(reinterpret_cast<char*>(&c), sizeof(char));
        }
        cout << "continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;
}

void PrintBIN(const char* fname) {
    ifstream fin(fname, ios::binary);
    char c;
    while (fin.read(reinterpret_cast<char*>(&c), sizeof(char))) {
        cout << c;
    }
    cout << endl;
}

void ProcessBIN1(const char* fname, const char* gname) {
    ifstream f(fname, ios::binary);
    ofstream g(gname, ios::binary);
    char c;
    while (f.read(reinterpret_cast<char*>(&c), sizeof(char))) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            g.write(reinterpret_cast<char*>(&c), sizeof(char));
        }
    }
}

void SortBIN(const char* fname, const char* gname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    fstream g(gname, ios::binary | ios::in | ios::out);
    f.seekg(0, ios::end);
    int size = f.tellg();
    f.seekg(0, ios::beg);
    for (int i0 = 1; i0 < size; i0++)
        for (int i1 = 0; i1 < size - i0; i1++) {
            char a = fRead(f, i1);
            char b = fRead(f, i1 + 1);
            if (a > b)
                fChange(f, i1, i1 + 1);
        }
    f.seekp(0, ios::end);
}

char fRead(fstream& f, const int i) {
    f.seekg(i, ios::beg);
    char val;
    f.read(reinterpret_cast<char*>(&val), sizeof(char));
    return val;
}

void fWrite(fstream& f, const int i, const char val) {
    f.seekp(i, ios::beg);
    f.write(reinterpret_cast<const char*>(&val), sizeof(char));
}

void fChange(fstream& f, const int i, const int j) {
    char x = fRead(f, i);
    char y = fRead(f, j);
    fWrite(f, i, y);
    fWrite(f, j, x);
}

void SortBIN(const char* fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    f.seekg(0, ios::end);
    int size = f.tellg();
    f.seekg(0, ios::beg);
    for (int i0 = 1; i0 < size; i0++)
        for (int i1 = 0; i1 < size - i0; i1++) {
            char a = fRead(f, i1);
            char b = fRead(f, i1 + 1);
            if (a > b)
                fChange(f, i1, i1 + 1);
        }
    f.seekp(0, ios::end);
}

int main() {
    char fname[100];
    cout << "enter file name 1: ";
    cin >> fname;
    CreateBIN(fname);
    PrintBIN(fname);

    char gname[100];
    cout << "enter file name 2: ";
    cin >> gname;
    ProcessBIN1(fname, gname);

    SortBIN(gname);
    PrintBIN(gname);

    return 0;
}
