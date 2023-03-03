#pragma once

#include <iostream>

class DictionaryList
{
private:
    struct Node
    {
        int item_;
        Node* next_;
        Node(int item, Node* next = nullptr) {
            item_ = item;
            next_ = next;
        }
    };
    Node* head_;
    Node* tail_;

    Node* head() const; 
    Node* tail() const;
    Node* search (int item) const;
    void remove (Node* x);
    void insert(Node* x);
    void swap(DictionaryList&) noexcept;
    friend std::ostream& operator<<(std::ostream& out, const DictionaryList&);
            
public:
    DictionaryList();
    DictionaryList(const DictionaryList&);
    DictionaryList(DictionaryList&&) noexcept;
    DictionaryList& operator=(const DictionaryList&);
    DictionaryList& operator=(DictionaryList&&) noexcept;
    ~DictionaryList();

    bool isEmpty();
    bool searchItem(int);
    void insert(int);
    void deleteItem(int);

    void merge(DictionaryList* subList);
    void remove(DictionaryList* subList);
    friend DictionaryList* getIntersection(DictionaryList* leftList, DictionaryList* rightList);
};