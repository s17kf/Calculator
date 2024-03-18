//
// Created by stefan on 12/03/24.
//

#ifndef LIST_H
#define LIST_H

namespace data_structures {
    template<typename T>
    class List {
        struct Node {
            T data;
            Node *prev;
            Node *next;
        };

    public:
        class Iterator {
        public:
            Iterator &operator++() {
                node = node->next;
                return *this;
            }

            Iterator &operator++(int) {
                Node *tmp = node;
                node = node->next;
                return *tmp;
            }

            bool operator==(const Iterator &other) const {
                return node == other.node;
            }

            bool operator!=(const Iterator &other) const {
                return !(*this == other);
            }

            T &operator*() const {
                return node->data;
            }

            explicit Iterator(Node *node) : node(node) {
            }

        protected:
            Node *node;
        };

        class ReverseIterator : public Iterator {
        public:
            ReverseIterator &operator++() {
                this->node = this->node->prev;
                return *this;
            }

            ReverseIterator &operator++(int) {
                Node *tmp = this->node;
                this->node = this->node->prev;
                return *tmp;
            }

            explicit ReverseIterator(Node *node) : Iterator(node) {
            }
        };

        List() : mSize(0) {
            beforeFirst = new Node();
            afterLast = new Node();
            beforeFirst->next = afterLast;
            afterLast->prev = beforeFirst;
        }

        ~List() {
            Node *node = beforeFirst;
            while (node != nullptr) {
                const Node *toDelete = node;
                node = node->next;
                delete toDelete;
            }
        }

        Iterator begin() { return ++Iterator(beforeFirst); }

        Iterator end() { return Iterator(afterLast); }

        ReverseIterator rbegin() { return ++ReverseIterator(afterLast); }

        ReverseIterator rend() { return ReverseIterator(beforeFirst); }

        const size_t &size() const { return mSize; }

        bool empty() const { return mSize == 0; }

        void pushBack(const T &data) {
            Node *newNode = new Node{
                    .data = data,
                    .prev = afterLast->prev,
                    .next = afterLast
            };
            afterLast->prev->next = newNode;
            afterLast->prev = newNode;
            ++mSize;
        }

        void pushFront(const T &data) {
            Node *newNode = new Node{
                    .data = data,
                    .prev = beforeFirst,
                    .next = beforeFirst->next
            };
            beforeFirst->next->prev = newNode;
            beforeFirst->next = newNode;
            ++mSize;
        }

        const T &front() const {
            if (mSize == 0) {
                throw std::out_of_range("Read (first) element from empty list!");
            }
            return beforeFirst->next->data;
        }

        const T &back() const {
            if (mSize == 0) {
                throw std::out_of_range("Read (last) element from empty list!");
            }
            return afterLast->prev->data;
        }

        void popFront() {
            if (mSize == 0) {
                throw std::out_of_range("Try to remove (last) element from empty list!");
            }
            Node *firstNode = beforeFirst->next;
            beforeFirst->next = firstNode->next;
            firstNode->next->prev = beforeFirst;
            delete firstNode;
            --mSize;
        }

        void popBack() {
            if (mSize == 0) {
                throw std::out_of_range("Try to remove (last) element from empty list!");
            }
            Node *lastNode = afterLast->prev;
            afterLast->prev = lastNode->prev;
            lastNode->prev->next = afterLast;
            delete lastNode;
            --mSize;
        }

    private:
        size_t mSize;
        Node *beforeFirst;
        Node *afterLast;
    };
} // data_structures

#endif //LIST_H