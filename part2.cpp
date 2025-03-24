#include <iostream>
#include <mutex>
#include <thread>

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class MyLinkedList { 
private:
    Node* head;
    std::mutex mtx; //   thread safety

public:
    MyLinkedList() : head(nullptr) {}

    // Add at head
    void addAtHead(int val) {
        std::lock_guard<std::mutex> lock(mtx);
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // Delete at head
    void deleteAtHead() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Display the list
    void display() {
        std::lock_guard<std::mutex> lock(mtx);
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }
};

//  multi-threaded operations
void listOperations(MyLinkedList& list) {
    list.addAtHead(10);
    list.addAtHead(20);
    list.deleteAtHead();
    list.display();
}

int main() {
    MyLinkedList list;
    std::thread t1(listOperations, std::ref(list));
    std::thread t2(listOperations, std::ref(list));

    t1.join();
    t2.join();

    return 0;
}
