#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class Node {
private:
    string data;
    int value;
    Node* next;
    public:
    explicit Node(string d, int v) {
        data = d;
        value = v;
        next = nullptr;
    }
    void setData(string s) {
        data = s;
    }
    string getData() const{
        return data;
    }
    Node* getNext() const {
        return next;
    }
    void setNext(Node* n) {
        next = n;
    }
    void increaseValue() {
        value++;
    }
    int getValue() const {
        return value;
    }
};

class LinkedList {
    private:
    Node* head;
    bool insertHelper(string s) {
        Node* temp = head;
        if (head != nullptr) {
            if (head->getData() == s) {
                return true;
            }
        }
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
            if (temp->getData() == s) {
                return true;
            }
        }
        return false;

    }
    public:
    LinkedList() {
        head = nullptr;
    }
    void insertNode(string s) {
        if (head == nullptr) {
            head = new Node(s, 1);
            return;
        }
        Node* existingNode = search(s);
        if (existingNode) { // Se já existe, incrementa o contador
            existingNode->increaseValue();
            return;
        } else {
            Node* newNode = new Node(s, 1);
            // Se não existir, adiciona ao final da lista
            Node* temp = head;
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();
            }
            temp->setNext(new Node(s, 1));
        }
    }

    Node* search(string s) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->getData() == s) {
                return temp;
            }
            temp = temp->getNext();
        }
        return nullptr;
    }

    void show() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->getData() << ": " << temp->getValue() << endl;
            temp = temp->getNext();
        }
    }

    void writeFile(ofstream &outFile) {
        Node* temp = head;
        while (temp != nullptr) {
            outFile << temp->getData() << " " << temp->getValue() << endl;
            temp = temp->getNext();
        }
    }
};

class HashTable {
    vector <LinkedList> table;
    int hash(string s) {
        int hash = 0;
        char c;
        for (int i = 0; i < s.length(); i++) {
            c = s[i];
            hash = hash + int (c);
        }
        return hash % table.size();
    }
    public:
    HashTable() {
        table.resize(60);
    }
    void insert(string s) {
        int pos = hash(s);
        table[pos].insertNode(s);
    }

    void printSequences (ofstream& outFile) {
        for (auto lists : table) {
            lists.show();
            lists.writeFile(outFile);
        }
    }
};

int main() {
    string sequence;
    ifstream file("C:/Users/ebber/CLionProjects/RevisaoEdoo/genome.txt");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!\n";
        return 1;
    }

    HashTable hashTable;
    LinkedList list;
    list.insertNode("ab");
    list.insertNode("ab");
    while (getline(file, sequence)) {
        for (int i = 0; i < 60; i += 6) {
            hashTable.insert(sequence.substr(i, 6));
        }
    }
    ofstream outFile("C:/Users/ebber/CLionProjects/RevisaoEdoo/output.txt");
    hashTable.printSequences(outFile);
    file.close();
    outFile.close();





}