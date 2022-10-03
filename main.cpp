#include <fstream>
#include <iostream>


using namespace std;

string text("");

void append_to_end() {
    string newstr;
    cout << "Enter text to append: ";
    cin >> newstr;
    text += newstr;
    // Develop your own data structure with memory allocation for strings inside
    // one option - finish the implementation with string object, and then to rework all places with string you have
}
void newline() {
    text += "\n";

    cout << "New line is started\n";
}

void save() {
    string filename;
    cout << "Enter the file name for saving: ";
    cin >> filename;

    ofstream file;
    file.open(filename);

    file << text;

    cout << "Text have been saved successfully\n";
}

void load() {
    string filename;
    cout << "Enter the file name for loading: ";
    cin >> filename;

    ifstream file;
    file.open(filename);

    std::string line;
    if (file) getline(file, text);

    while (file) {
        getline(file, line);
        text += '\n' + line;
    }

    cout << "Text have been loaded successfully\n";
}

void print() { cout << text << '\n'; }

void insert_text() {
    int line, index;
    cout << "Choose line and index: ";
    string newstr;
    cout << "Enter text to insert: ";
    cin >> newstr;

    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text.size(); i++) {
        if (cline == line) {
            pos = i + index;
            break;
        }

        if (text[i] == '\n') cline++;
    }

    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    string newtext("");

    for (int i = 0; i < pos; i++) {
        newtext += text[i];
    }
    newtext += newstr;
    for (int i = pos; i < text.size(); i++) {
        newtext += text[i];
    }

    text = newtext;
}

void search() {
    string text_to_find;
    cout << "Enter text to search: ";
    cin >> text_to_find;

    bool found = false;
    int i = 0;
    while ((i = text.find(text_to_find, i)) != std::string::npos) {
        cout << "Text found in position: " << i << '\n';
        i += text_to_find.length();
        found = true;
    }
    if (!found) {
        cout << "Not found\n";
    }
}

void systempause() {
    string s;
    cout << "Enter 'e' and press enter to continue...";
    cin >> s;
}

int main() {
    while (true) {
        system("clear");
        cout << "Choose the command:\n";
        int input;
        cin >> input;

        switch(input)
        {
            case 0:
                return 0;
            case 1:
                append_to_end();
                break;
            case 2:
                newline();
                break;
            case 3:
                save();
                break;
            case 4:
                load();
                break;
            case 5:
                print();
                break;
            case 6:
                insert_text();
                break;
            case 7:
                search();
                break;
            default:
                cout << "Unknown command\n";
        }
        systempause();
    }
}
