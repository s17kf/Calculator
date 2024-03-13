//
// Created by stefan on 13/03/24.
//

#ifndef CALCULATORAADS_QUEUE_H
#define CALCULATORAADS_QUEUE_H

#include "List.h"

namespace data_structures {

    template<typename T>
    class Queue {
    public:
        void push(const T &value) {
            data.pushBack(value);
        }

        void pop() {
            data.popFront();
        }

        const T &front() const {
            return data.front();
        }

        size_t size() const { return data.size(); }

        bool empty() const { return data.empty(); }

    private:
        List<T> data;
    };

} // data_structures

#endif //CALCULATORAADS_QUEUE_H
