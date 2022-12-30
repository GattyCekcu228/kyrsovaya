#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;
ofstream fout("answer.txt");
class Graph {
private:

    bool** G; // матрица смежности
    int numVertices; // количество вершин
    bool* used; // посещенные вершины
    vector<int> comp; //содержит список вершин в текущей компоненте связности

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        G = new bool* [numVertices];
        used = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            G[i] = new bool[numVertices];
            used[i] = false;
            for (int j = 0; j < numVertices; j++)
                G[i][j] = false;
        }
    } // конструктор
    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] G[i];
        delete[] G;
        delete[] used;
    }// деструктор

    //функция добавления ребра
    void addEdge(int i, int j, int u) {
        u == 0 ? G[i][j] = true : u == 1 ? G[j][i] = true : G[i][j] = G[j][i] = true;
    }
    //функция вывода
    void toString() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++) {
                cout << G[i][j] << " ";
                fout << G[i][j] << " ";
            }
            cout << endl;
            fout << endl;
        }
    }
    //обнуление для повторной работы
    void Memset() {
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                G[i][j] = false, used[i] = false;

    }
    //обход в глубину
    void DFS(int v);
    //поиск компонентов связи
    void find_comps();
};

void Graph::DFS(int v) {
    used[v] = true;
    comp.push_back(v); // добавление элемента в компонент 
    for (int i = 0; i < numVertices; ++i) {
        if ((G[v][i] != 0 || G[i][v] != 0) && (!used[i]))
            DFS(i);
    }
}

void Graph::find_comps() {
    for (int i = 0; i < numVertices; ++i)
        if (!used[i]) {
            comp.clear();
            DFS(i);

            cout << "Компоненты:";
            fout << "Компоненты:";

            for (auto it = comp.begin(); it != comp.end(); it++) {
                cout << " " << *it, fout << " " << *it;
            }

            //for (int j : comp)
               // cout << " " << j, fout << " " << j;

            cout << endl; fout << endl;
        }
}


int main()
{
    srand(time(NULL));
    setlocale(0, "");

    int z;
l:
    system("cls");
    cout << "Введите кол-во вершин графа: "; cin >> z;
    Graph c(z);

    string s;
    while (true) {
        system("cls");
        cout << "Количество вершин: " << z
            << "\n Выберете способ построения графа: \n 1) Случайное заполнение \n"
            << " 2) Заполнить самому \n 3) Изменить кол-во вершин \n 4) Выход\n Введите: ";
        cin >> s;
        switch (atoi(s.c_str()))
        {
        case 1:
            system("cls");

            int r;
            cout << "Введите вероятность присутствия ребра(чем больше, тем выше вероятность): ";
            cin >> r;
            for (int i = 0; i < z; i++)
            {
                for (int j = i + 1; j < z; j++)
                {
                    if (2 <= (rand() % r)) {
                        c.addEdge(i, j, rand() % 3);
                    }
                }
            }
            cout << "-----------------" << endl << "Матрица смежности: \n";
            fout << endl << "-----------------" << endl << "Матрица смежности: \n";
            c.toString();
            cout << endl << "-----------------" << endl << "Ответ: \n";
            fout << endl << "-----------------" << endl << "Ответ: \n";

            c.find_comps();
            c.Memset();

            system("pause");
            break;
        case 2:
            system("cls");

            cout << "Вводите по две вершины через пробел" << endl
                << "Для выхода введите *" << endl
                << "Пример: \n 0 1\n 0 2\n ....\nВведите:\n";
            while (true) {
                string a, b;
                cin >> a >> b;
                if (a == "*" || b == "*")
                    break;
                if (atoi(a.c_str()) < z && atoi(b.c_str()) < z) {
                    c.addEdge(atoi(a.c_str()), atoi(b.c_str()), 0);
                }
                else {
                    cout << "Такой вершины не существует" << endl;
                }
            }
            cout << "-----------------" << endl << "Матрица смежности: \n";
            fout << endl << "-----------------" << endl << "Матрица смежности: \n";
            c.toString();
            cout << endl << "-----------------" << endl << "Ответ: \n";
            fout << endl << "-----------------" << endl << "Ответ: \n";

            c.find_comps();
            c.Memset();
            system("pause");
            break;
        case 3:
            goto l;
            break;
        case 4:
            exit(0);
            break;
        }
        system("cls");
    }

    fout.close();
    c.~Graph();
    return 0;
}