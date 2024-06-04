#ifndef DECK_HPP_
#define DECK_HPP_

#include <cstddef>
#include <stdexcept>

namespace card {
    template <class T>
    class Deck {
        public:
            struct Node {
                T data;
                struct Node* _next = nullptr;
            };

        class DeckConstIterator {
            public:
                explicit DeckConstIterator(const Node* node) : _current(node) {}

                const T& operator*() const { return _current->data; }

                DeckConstIterator& operator++() {
                    _current = _current->_next;
                    return *this;
                }

                DeckConstIterator operator++(int) {
                    DeckConstIterator temp_iter = *this;
                    ++(*this);
                    return temp_iter;
                }

                bool operator==(const DeckConstIterator& other) const {
                    return _current == other._current;
                }

                bool operator!=(const DeckConstIterator& other) const {
                    return !(*this == other);
                }

            private:
                const Node* _current;
        };

        class DeckIterator {
            public:
                explicit DeckIterator(Node* node) : _current(node) {}

                T& operator*() { return _current->data; }

                DeckIterator& operator++() {
                    _current = _current->_next;
                    return *this;
                }

                DeckIterator operator++(int) {
                    DeckIterator temp_iter = *this;
                    ++(*this);
                    return temp_iter;
                }

                bool operator==(const DeckIterator& other) const {
                    return _current == other._current;
                }

                bool operator!=(const DeckIterator& other) const {
                    return !(*this == other);
                }

            private:
                Node* _current;
        };

        using iterator = card::Deck<T>::DeckIterator;
        using const_iterator = card::Deck<T>::DeckConstIterator;

        Deck() = default;
        Deck(const Deck& other) : Deck() { copy(other); }
        Deck(Deck&& other) noexcept : Deck() { swap(other); }

        ~Deck() { clear(); }

        Deck<T>& operator=(const Deck& other) {
            if (this != &other) {
                clear();
                Copy(other);
            }
            return *this;
        }

        iterator begin() { return iterator(_head); }
        iterator end() { return iterator(nullptr); }

        DeckConstIterator begin() const { return DeckConstIterator(_head); }
        DeckConstIterator end() const { return DeckConstIterator(nullptr); }
        DeckConstIterator cbegin() const { return DeckConstIterator(_head); }
        DeckConstIterator cend() const { return DeckConstIterator(nullptr); }

        bool empty() const { return _size == 0; }
        size_t size() const { return _size; }

        const T& top() const {
            if (empty()) {
                throw std::out_of_range("Error: Empty deck");
            }
            return _head->data;
        }

        void add(const T& value) {
            Node* node = new Node{value};
            node->_next = _head;
            _head = node;
            _size++;
        }

        void draw() {
            // Check if deck has contents
            if (empty()) {
                throw std::out_of_range("Error: Empty deck");
            }

            // Remove top card
            Node* node = _head->_next;
            delete _head;
            _head = node;
            _size--;
        }

        void shuffle(Deck& other) {
            /*using std::swap;
            swap(_head, other._head);
            swap(_size, other._size);*/
        }

        /*
        template <class... Args>
        void Emplace(Args&&... args) {
            Push(T(std::forward<Args>(args)...));
        }
        */

        void clear() {
            while (!empty()) {
                draw();
            }
        }

        void copy(const Deck& other) {
            clear();
            Node* node = other._head;
            
            Deck temp_deck;

            while (node) {
                temp_deck.add(node->data);
                node = node->_next;
            }

            while (!temp_deck.empty()) {
                add(temp_deck.top());
                temp_deck.draw();
            }
        }

        private:
            Node* _head = nullptr;
            size_t _size = 0;
    };

}

#endif 
