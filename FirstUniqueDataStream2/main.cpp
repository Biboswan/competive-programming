class Node {
    public:
        int val;
        Node* prev,*next;
        Node(int val) {
            this->val = val;
            prev=nullptr;
            next=nullptr;
        }
};

class DLL {
    public:
        Node* head,*tail;
        DLL() {
            head=nullptr;
            tail=nullptr;
        }
        
        Node* addEnd(int val) {
            Node* n = new Node(val);
            if (head == nullptr) {
                head=n;
                tail=n;
            } else {
                n->prev = tail;
                tail->next=n;
                tail=n;
            }
            
            return n;
        }
        
        void delNode(Node* n) {
            if (n->prev==nullptr && n->next==nullptr) {
                head=nullptr;
                tail=nullptr;
            }else if(head == n) {
                head=n->next;
                n->next->prev = nullptr;
            } else if(tail==n) {
                tail = n->prev;
                n->prev->next == nullptr;
            } else {
                n->next->prev = n->prev;
                n->prev->next = n->next;
            }
        }
        
        int getBeg() {
            if (head !=nullptr) {
                return head->val;
            }
        }
};

class DataStream {
public:
    DLL* LL;
    unordered_map<int,Node*> mp;
    DataStream(){
        // do intialization if necessary
        LL = new DLL();
    }
    
    /**
     * @param num: next number in stream
     * @return: nothing
     */
    void add(int num) {
        // write your code here
        if (mp.find(num) == mp.end()) {
            mp[num] = LL->addEnd(num);
        } else {
            if (mp[num] != nullptr) {
                LL->delNode(mp[num]);
                mp[num]=nullptr;
            }
        }
    }

    /**
     * @return: the first unique number in stream
     */
    int firstUnique() {
        // write your code here
        return LL->getBeg();
    }
};
