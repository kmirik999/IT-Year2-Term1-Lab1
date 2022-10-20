#include <fstream>
#include <iostream>
#include <string>

using namespace std;
// Develop your own data structure with memory allocation for strings inside
// one option - finish the implementation with string object, and then to rework all places with string you have

class StringFormatter
{
public:
    int find_string(string str, int pos);
    void safe_text();
    void safe_text_redo();
    void undo_command();
    void redo_command();
    void append_string(string newstr);
    void append_to_end();
    void delete_command();
    void newline();
    void save();
    void load();
    void print();
    void insert_text();
    void cut();
    void copy();
    void paste();
    void search();
    void systempause();

public:
    char* text_1;
    int text_length;
    string safeTextS;
    string safeTextRedo;
    string safeTextPaste;
};

string commands[] =
        {
                "0. End program",
                "1. Append text symbols to the end",
                "2. Start the new line",
                "3. Saving the information",
                "4. Loading the information from file",
                "5. Print the current text to console",
                "6. Insert the text by line and symbol index",
                "7. Search",
                "8. Delete",
                "9. Undo",
                "10. Redo",
                "11. Cut",
                "12. Copy",
                "13. Paste"
        };

int main() {
    int stop = 0;
    StringFormatter strFormatter;
    while (true) {
        system("clear");
        if (stop == 0) {
            cout << "Write -help to see the commands\n";

            string inputST;
            cin >> inputST;

            if (inputST == "-help") {
                for (string f : commands)  //ітератор
                {
                    cout << f << endl;
                }
            }
            stop++;
        }
        int input;
        cout << "Choose the command:\n";
        cin >> input;

        switch (input)
        {
            case 0:
                return 0;
                break;
            case 1:
                strFormatter.safe_text();
                strFormatter.append_to_end();
                strFormatter.safe_text_redo();
                break;
            case 2:
                strFormatter.safe_text();
                strFormatter.newline();
                strFormatter.safe_text_redo();
                break;
            case 3:
                strFormatter.save();
                break;
            case 4:
                strFormatter.load();
                break;
            case 5:
                strFormatter.print();
                break;
            case 6:
                strFormatter.safe_text();
                strFormatter.insert_text();
                strFormatter.safe_text_redo();
                break;
            case 7:
                strFormatter.search();
                break;
            case 8:
                strFormatter.safe_text();
                strFormatter.delete_command();
                strFormatter.safe_text_redo();
                break;
            case 9:
                strFormatter.undo_command();
                break;
            case 10:
                strFormatter.redo_command();
                break;
            case 11:
                strFormatter.cut();
                break;
            case 12:
                strFormatter.copy();
                break;
            case 13:
                strFormatter.paste();
                break;
            default:
                cout << "Unknown command\n";
        }
        strFormatter.systempause();
    }
}


// Знаходить шуканий шматок тексту, повертає індекс позиції початку шуканого тексту. Або повертає -1(не знайшов нічого)
int StringFormatter::find_string(string str, int pos)
{
    for (int i = pos; i <= text_length - str.size(); ++i)
    {
        if (str[0] == text_1[i])
            for (int j = 1; j < str.size(); ++j)
            {
                if (str[j] != text_1[i + j])
                    break;
                else if (j == str.size() - 1)
                    return i;
            }
    }
    return -1;
}

void StringFormatter::safe_text()
{
    for (int i = 0; i < text_length; i++)
    {
        safeTextS += text_1[i];
    }
}

void StringFormatter::safe_text_redo()
{
    for (int i = 0; i < text_length; i++)
    {
        safeTextRedo += text_1[i];
    }
}

void StringFormatter::undo_command()
{
    text_1 = new char[safeTextS.length()];

    for (int i = 0; i < safeTextS.length(); i++)
    {
        text_1[i] = safeTextS[i];
    }

    text_length = safeTextS.length();

}

void StringFormatter::redo_command()
{
    text_1 = new char[safeTextRedo.length()];

    for (int i = 0; i < safeTextRedo.length(); i++)
    {
        text_1[i] = safeTextRedo[i];
    }

    text_length = safeTextRedo.length();
}

void StringFormatter::append_string(string newstr)
{
    char* text_new = new char[text_length + newstr.size()]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < text_length; ++i)
    {
        *(text_new + i) = text_1[i]; // Перебирає послідовно кожну літеру старого стрінга, який збережений комірці пам'яті за вказівником text_1, та зберігає в іншу комірку пам'яті за вказівником text_new
    }
    for (int i = 0; i < newstr.size(); ++i)
    {
        text_new[i + text_length] = newstr[i];  // Перебирає послідовно кожну літеру нового стрінга(тот, що user хоче додати) та зберігає в іншу комірку пам'яті за вказівником text_new
    }
    delete[] text_1; // Чистимо мусорну інформацію

    text_1 = text_new; // Тепер новий текст стає старим
    text_length = text_length + newstr.size(); // Змінюємо довжину text_length, бо додався новий текст(тому стрінг став довшим)
}

void StringFormatter::append_to_end()
{
    string newstr;
    cout << "Enter text to append: ";
    cin >> newstr;

    // Додаємо новий текст до старого тексту
    append_string(newstr);
}

void StringFormatter::delete_command()
{

    int line = 0, index = 0, numSymD = 0;
    cout << "Choose line and index: " << endl;

    cout << "Line: ";
    cin >> line;

    cout << "Index: ";
    cin >> index;

    cin.ignore(); // Чистить поток вводу

    cout << "Enter number of symbols to delete: ";
    cin >> numSymD;


    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text_length; i++)
    {
        //Якщо шуканий рядок знайден, то обчислюємо позіцію в тексті, куди треба додати текст user
        if (cline == line) {
            pos = i + index;
            break;
        }
        //Якщо бачить перехід на новий рядок, то додає cline++ поки не знайде шуканий рядок
        if (text_1[i] == '\n') cline++;
    }

    //Якщо позиція не знайдена - виводимо помилку
    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    char* new_text = new char[text_length]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < pos; i++)
    {
        new_text[i] = text_1[i]; // Перебирає послідовно кожну літеру старого стрінга, який збережений комірці пам'яті за вказівником text_1, та зберігає в іншу комірку пам'яті за вказівником text_new
    }

    for (int i = pos; i < text_length; i++)
    {
        new_text[i] = text_1[i + numSymD]; // Перебирає послідовно кожну літеру тексту, який залишилось додати після видалення старогу
    }

    delete[] text_1;
    text_1 = new_text;

    text_length = text_length - numSymD;
}

// Функція додає новий ENTER до вже створьоного тексту(Новий рядок)
void StringFormatter::newline()
{
    char* text_new = new char[text_length + 1]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < text_length; ++i)
    {
        // Зберігає старий текст у нову комірку пам'яті для того, щоб додати НОВИЙ РЯДОК(ENTER)
        text_new[i] = text_1[i];
    }

    // Видаляє мусорну інформацію з комірки пам'яті
    delete[] text_1;

    text_1 = text_new;
    text_length++;
    //text_new[text_length] = '\n';
    text_1[text_length] = '\n';

    cout << "New line is started\n";
}

void StringFormatter:: save()
{
    string filename;
    cout << "Enter the file name for saving: ";
    cin >> filename;

    ofstream file;
    file.open(filename);

    for (int i = 0; i < text_length; ++i)
    {
        file << text_1[i]; // Зберігає усі літери послідовно у файл
    }

    cout << "Text have been saved successfully\n";
}

void StringFormatter::load()
{
    string filename;
    cout << "Enter the file name for loading: ";
    cin >> filename;

    ifstream file;
    file.open(filename);

    string line;
    if (file) getline(file, line);  // Зберігає в змінну line перший рядок
    append_string(line); // Зберігаємо цей рядок з файлу у комірку пам'яті за адрессою text_1

    // Почергову(кожен рядок) зберігає з файлу текст и передає в комірку пам'яті за адрессою text_1
    while (file.good())
    {
        getline(file, line);
        append_string('\n' + line);
    }
    cout << "Text have been loaded successfully\n";
}

// Виводить весь текст у консоль
void StringFormatter::print()
{
    for (int i = 0; i < text_length; ++i)
    {
        cout << text_1[i];
    }
    cout << '\n';
}

// Додає текст user я якийсь конкретний рядок та позіцію в старому тексті
void StringFormatter::insert_text() {
    int line = 0, index = 0;
    cout << "Choose line and index: " << endl;

    cout << "Line: ";
    cin >> line;

    cout << "Index: ";
    cin >> index;

    cin.ignore(); // Чистить поток вводу

    char newstr[10000];
    cout << "Enter text to insert: ";
    cin.getline(newstr, 10000);



    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text_length; i++)
    {
        // Якщо шуканий рядок знайден, то обчислюємо позіцію в тексті, куди треба додати текст user
        if (cline == line) {
            pos = i + index;
            break;
        }
        // Якщо бачить перехід на новий рядок, то додає cline++ поки не знайде шуканий рядок
        if (text_1[i] == '\n') cline++;
    }

    // Якщо позиція не знайдена - виводимо помилку
    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    char* new_text = new char[text_length + strlen(newstr)]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < pos; i++)
    {
        new_text[i] = text_1[i]; // Перебирає послідовно кожну літеру старого стрінга, який збережений комірці пам'яті за вказівником text_1, та зберігає в іншу комірку пам'яті за вказівником text_new
    }
    for (int i = 0; i < strlen(newstr); i++)
    {
        new_text[i + pos] = newstr[i]; // Перебирає послідовно кожну літеру нового стрінга(тот, що user хоче додати) та зберігає в іншу комірку пам'яті за вказівником text_new
    }
    for (int i = pos; i < text_length; i++)
    {
        new_text[i + strlen(newstr)] = text_1[i]; // Перебирає послідовно кожну літеру тексту, який залишилось додати після нового
    }
    delete[] text_1;
    text_1 = new_text;
    text_length = text_length + strlen(newstr);
}

void StringFormatter::cut()
{


    int line = 0, index = 0, numSymCut = 0;
    cout << "Choose line and index: " << endl;

    cout << "Line: ";
    cin >> line;

    cout << "Index: ";
    cin >> index;

    cin.ignore(); // Чистить поток вводу

    cout << "Enter number of symbols to Cut: ";
    cin >> numSymCut;


    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text_length; i++)
    {
        //Якщо шуканий рядок знайден, то обчислюємо позіцію в тексті, куди треба додати текст user
        if (cline == line) {
            pos = i + index;
            break;
        }
        //Якщо бачить перехід на новий рядок, то додає cline++ поки не знайде шуканий рядок
        if (text_1[i] == '\n') cline++;
    }

    //Якщо позиція не знайдена - виводимо помилку
    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    char* new_text = new char[text_length]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < pos; i++)
    {
        new_text[i] = text_1[i]; // Перебирає послідовно кожну літеру старого стрінга, який збережений комірці пам'яті за вказівником text_1, та зберігає в іншу комірку пам'яті за вказівником text_new
    }

    for (int i = pos; i < pos + numSymCut; i++)
    {
        safeTextPaste += text_1[i];
    }

    for (int i = pos; i < text_length; i++)
    {
        new_text[i] = text_1[i + numSymCut]; // Перебирає послідовно кожну літеру тексту, який залишилось додати після видалення старогу
    }

    delete[] text_1;
    text_1 = new_text;

    text_length = text_length - numSymCut;

}

void StringFormatter::copy()
{

    int line = 0, index = 0, numSymCopy = 0;
    cout << "Choose line and index: " << endl;

    cout << "Line: ";
    cin >> line;

    cout << "Index: ";
    cin >> index;

    cin.ignore(); // Чистить поток вводу

    cout << "Enter number of symbols to Copy: ";
    cin >> numSymCopy;


    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text_length; i++)
    {
        //Якщо шуканий рядок знайден, то обчислюємо позіцію в тексті, куди треба додати текст user
        if (cline == line) {
            pos = i + index;
            break;
        }
        //Якщо бачить перехід на новий рядок, то додає cline++ поки не знайде шуканий рядок
        if (text_1[i] == '\n') cline++;
    }

    //Якщо позиція не знайдена - виводимо помилку
    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    //char* new_text = new char[text_length]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять

    for (int i = pos; i < pos + numSymCopy; i++)
    {
        safeTextPaste += text_1[i];
    }

    //delete[] text_1;
    //text_1 = new_text;

    //text_length = text_length - numSymCopy;
}

void StringFormatter::paste()
{
    int line = 0, index = 0;
    cout << "Choose line and index: " << endl;

    cout << "Line: ";
    cin >> line;

    cout << "Index: ";
    cin >> index;

    int cline = 0;
    int pos = -1;

    for (int i = 0; i < text_length; i++)
    {
        // Якщо шуканий рядок знайден, то обчислюємо позіцію в тексті, куди треба додати текст user
        if (cline == line) {
            pos = i + index;
            break;
        }

        // Якщо бачить перехід на новий рядок, то додає cline++ поки не знайде шуканий рядок
        if (text_1[i] == '\n') cline++;
    }

    // Якщо позиція не знайдена - виводимо помилку
    if (pos == -1) {
        cout << "ERR!\n";
        return;
    }

    char* new_text = new char[text_length + safeTextPaste.length()]; // запитує перегляд пам'яті, і отримує вказівник на її пам'ять
    for (int i = 0; i < pos; i++)
    {
        new_text[i] = text_1[i]; // Перебирає послідовно кожну літеру старого стрінга, який збережений комірці пам'яті за вказівником text_1, та зберігає в іншу комірку пам'яті за вказівником text_new
    }
    for (int i = 0; i < safeTextPaste.length(); i++)
    {
        new_text[i + pos] = safeTextPaste[i]; // Перебирає послідовно кожну літеру нового стрінга(тот, що user хоче додати) та зберігає в іншу комірку пам'яті за вказівником text_new
    }
    for (int i = pos; i < text_length; i++)
    {
        new_text[i + safeTextPaste.length()] = text_1[i]; // Перебирає послідовно кожну літеру тексту, який залишилось додати після нового
    }
    delete[] text_1;
    text_1 = new_text;
    text_length = text_length + safeTextPaste.length();
}

void StringFormatter::search() {
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

void StringFormatter::systempause()
{
    string s;
    cout << "Enter 'e' and press enter to continue...";
    cin >> s;
}
