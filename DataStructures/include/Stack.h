//
// Created by stefan on 13/03/24.
//

#ifndef STACK_H
#define STACK_H

#include "List.h"

namespace data_structures {

    template<typename T>
    class Stack {
    public:
        void push(const T &value) {
            data.pushBack(value);
        }

        void pop() {
            data.popBack();
        }

        const T &top() const {
            return data.back();
        }

        size_t size() const { return data.size(); }

        bool empty() const { return data.empty(); }

        auto begin() const { return data.rbegin(); }

        auto end() const { return data.rend(); }

    private:
        List<T> data;
    };

} // data_structures

#endif //STACK_H
