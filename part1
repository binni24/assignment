class Node {
    public:
        int data;
        Node* next;
        
        Node(int val) {
            data = val;
            next = nullptr;
        }
    };
    
    class MyLinkedList {
    private:
        Node* head; // Pointer to the first node
    
    public:
        MyLinkedList() {
            head = nullptr;
        }
        
        // put value at a specific index
        int get(int index) {
            int count = 0;
            Node* temp = head;
            
            while (temp != nullptr) {
                if (count == index) return temp->data;
                temp = temp->next;
                count++;
            }
            return -1; // Index out of range
        }
        
        // Add at head
        void addAtHead(int val) {
            Node* newNode = new Node(val);
            newNode->next = head;
            head = newNode;
        }
        
        // Add at tail
        void addAtTail(int val) {
            Node* newNode = new Node(val);
            if (head == nullptr) {
                head = newNode;
                return;
            }
            
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        
        // Add 
        void addAtIndex(int index, int val) {
            if (index == 0) {
                addAtHead(val);
                return;
            }
    
            int count = 0;
            Node* temp = head;
            
            while (temp != nullptr && count < index - 1) {
                temp = temp->next;
                count++;
            }
            
            if (temp == nullptr) return; // Invalid index
            
            Node* newNode = new Node(val);
            newNode->next = temp->next;
            temp->next = newNode;
        }
        
        // Delete 
        void deleteAtIndex(int index) {
            if (head == nullptr) return; 
            
            if (index == 0) {
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }
            
            int count = 0;
            Node* temp = head;
            
            while (temp != nullptr && count < index - 1) {
                temp = temp->next;
                count++;
            }
            
            if (temp == nullptr || temp->next == nullptr) return; // Invalid index
            
            Node* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;
        }
    };
