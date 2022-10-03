#include <fstream>
#include <iostream>

using namespace std;
// Develop your own data structure with memory allocation for strings inside
// one option - finish the implementation with string object, and then to rework all places with string you have

char* text_1;
int text_length;
int find_string(string str, int pos)
{
    for (int i = pos; i <= text_length - str.size(); ++i)
    {
        if(str[0] == text_1[i])
            for (int j = 1; j < str.size(); ++j)
            {
                if (str[j] != text_1[i + j])
                    break;
                else if(j == str.size() - 1)
                    return i;
            }
    }
    return - 1;
}


void append_string( string newstr)
{
    char *text_new = new char[text_length + newstr.size()]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < text_length; ++i)
    {
        text_new[i] = text_1[i];
    }
    for (int i = 0; i < newstr.size(); ++i)
    {
        text_new[i + text_length] = newstr[i];
    }
    delete[] text_1;
    text_1 = text_new;
    text_length = text_length + newstr.size();
}

void append_to_end()
{
    string newstr;
    cout << "Enter text to append: ";
    cin >> newstr;
    append_string(newstr);
}



void newline()
{
    char* text_new = new char[text_length + 1];
    for (int i = 0; i < text_length; ++i)
    {
        text_new[i] = text_1[i];
    }
    delete[] text_1;
    text_1 = text_new;
    text_length ++;
    text_new[text_length] = '\n';

    cout << "New line is started\n";
}

void save()
{
    string filename;
    cout << "Enter the file name for saving: ";
    cin >> filename;

    ofstream file;
    file.open(filename);

    for (int i = 0; i < text_length; ++i)
    {
        file << text_1[i];
    }

    cout << "Text have been saved successfully\n";
}

void load()
{
    string filename;
    cout << "Enter the file name for loading: ";
    cin >> filename;

    ifstream file;
    file.open(filename);

    std::string line;
    if (file) getline(file, line);
    append_string(line);

    while (file)
    {
        getline(file, line);
        append_string('\n' + line);
    }
    cout << "Text have been loaded successfully\n";
}

void print()
{
    for (int i = 0; i < text_length; ++i)
    {
        cout << text_1[i];
    }
    cout <<'\n';
}

void insert_text() {
    int line, index;
    cout << "Choose line and index: ";
    string newstr;
    cout << "Enter text to insert: ";
    cin >> newstr;

    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text_length; i++)
    {
        if (cline == line) {
            pos = i + index;
            break;
        }
        if (text_1[i] == '\n') cline++;
    }

    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    char*  new_text = new char[text_length + newstr.size()];
    for (int i = 0; i < pos; i++)
    {
        new_text[i] = text_1[i];
    }
    for (int i = 0; i < newstr.size(); i++)
    {
        new_text[i + pos] = newstr[i];
    }
    for (int i = pos; i < text_length ; i++)
    {
        new_text[i + newstr.size()]= text_1[i];
    }
    delete[] text_1;
    text_1 = new_text;
    text_length = text_length + newstr.size();
}

void search() {
    string text_to_find;
    cout << "Enter text to search: ";
    cin >> text_to_find;

    bool found = false;
    int i = 0;
    while ((i = find_string(text_to_find, i)) != std::string::npos)
    {
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