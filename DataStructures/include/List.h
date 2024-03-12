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
        struct Iterator {
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

        private:
            Node *node;
        };

        List() : mSize(0) {
            beforeFirst = new Node();
            afterLast = new Node();
            beforeFirst->next = afterLast;
            afterLast->prev = beforeFirst;
        }

        Iterator begin() { return ++Iterator(beforeFirst); }
        Iterator end() { return Iterator(afterLast); }

        const size_t &size() const { return mSize; }

        void pushBack(T &data) {
            if (mSize == 0) {
            }
        }

    private:
        size_t mSize;
        Node *beforeFirst;
        Node *afterLast;
    };
} // data_structures

#endif //LIST_H
