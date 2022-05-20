#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct subscription
{
    int number;
    string name;
    string address;
};

void input1(vector <subscription>& arr) // Заполнение таблицы с клавиатуры 
{
    int n;
    cout << "N = "; cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Number: "; cin >> arr[i].number;
        cin.ignore();
        cout << "Full name: "; getline(cin, arr[i].name);
        cout << "Address: "; getline(cin, arr[i].address);
    }
}

void output(vector <subscription> arr) // Вывод таблицы с данным о всех студентах
{
    int size = arr.size();
    cout << left << setw(10) << "number" << setw(20) << "full name" << setw(25) << "address" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << left << setw(10) << arr[i].number << setw(20) << arr[i].name << setw(25) << arr[i].address << endl;
    }
}

bool input2(vector <subscription>& arr) // Считывание информации с данными о студентах
{
    ifstream in("task9.txt");
    if (!in.is_open())
    {
        cout << "Error of file reading :(\n";
        in.close();
        return false;
    }
    else
    {
        int n;
        in >> n;
        arr.resize(n);
        for (int i = 0; i < n; i++)
        {
            in >> arr[i].number;
            in.ignore();
            getline(in, arr[i].name);
            getline(in, arr[i].address);
        }
        in.close();
    }
    return true;
}


// Сортировка таблицы слиянием по полю "number"
void merge(vector <subscription>& arr, int l, int r, int m)
{
    int n1 = m - l + 1; // Размер первого подмассива
    int n2 = r - m;
    vector <subscription> L(n1);
    vector <subscription> R(n2);
    // Создаем копии подмассивов
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i, j, k;
    i = j = 0; k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].number <= R[j].number)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Собираем оставшиеся элементы, если один из подмассивов закончился раньше:
    while (i < n1)
    {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++; k++;
    }
}

void table_sort(vector <subscription>& arr, int l, int r)
{
    if (l >= r) return;
    int m = l + (r - l) / 2;
    table_sort(arr, l, m);
    table_sort(arr, m + 1, r);
    merge(arr, l, r, m);
}

int search1(vector <subscription>& arr, int key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].number == key) return i;
    }
    return -1;
}

int search2(vector <subscription> arr, int key)
{
    int mid;
    int left = 0;
    int right = arr.size() - 1;
    while (arr[left].number < key && arr[right].number > key)
    {
        mid = left + (key - arr[left].number) * (right - left) / (arr[right].number - arr[left].number);
        if (arr[mid].number < key) left = mid + 1;
        else if (arr[mid].number > key) right = mid - 1;
        else return mid;
    }
    if (arr[left].number == key) return left;
    if (arr[right].number == key) return right;
    else return -1;
}

int main()
{
    int c;
    vector <subscription> list;
    cout << "Type 1 to enter using the keyboard.\n";
    cout << "Type 2 to read from the file.\n";
    cin >> c;
    if (c == 2)
    {
        if (!input2(list)) return 0;
    }
    else if (c == 1)
    {
        input1(list);
    }
    else
    {
        cout << "ERROR";
        return 0;
    }
    table_sort(list, 0, list.size() - 1);
    output(list);
    int key_number, ans;
    cout << "Please, enter key: "; cin >> key_number;
    ans = search2(list, key_number);
    if (ans != -1) cout << "answer: element #" << ans + 1 << "\nfull name: " << list[ans].name << "\naddress: " << list[ans].address;
    else cout << "Element is not found :(";
    return 0;
}
