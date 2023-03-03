#include "DictionaryList.h"

DictionaryList::DictionaryList() {
    head_ = nullptr;
    tail_ = nullptr;
}

DictionaryList::DictionaryList(const DictionaryList& src)
{
    if (src.head_ != nullptr && src.tail_ != nullptr)
    {
        head_ = new Node(src.head_->item_);
        Node* destPtr = head_;
        Node* srcPtr = src.head_->next_;
        while (srcPtr != nullptr)
        {
            destPtr->next_ = new Node(srcPtr->item_, nullptr);
            destPtr = destPtr->next_;
            srcPtr = srcPtr->next_;
        }
    }
    else
    {
        head_ = nullptr;
        tail_ = nullptr;
    }
}

DictionaryList::DictionaryList(DictionaryList&& src) noexcept
{
    head_ = src.head_;
    src.head_ = nullptr;
    tail_ = src.tail_;
    src.tail_ = nullptr;
}

DictionaryList& DictionaryList::operator=(const DictionaryList& src)
{
    if (this == &src)
    {
        return *this;
    }
    DictionaryList temp(src);
    swap(temp);
    return *this;
}

DictionaryList& DictionaryList::operator=(DictionaryList&& src) noexcept
{
    swap(src);
    return *this;
}

DictionaryList::~DictionaryList()
{
    if (head_ != nullptr) {
        Node* next = head_;
        while (next) {
            next = next->next_;
            delete head_;
            head_ = next;
        }
    }
}

DictionaryList::Node* DictionaryList::head() const
{
    return head_;
}

DictionaryList::Node* DictionaryList::tail() const
{
    return tail_;
}

DictionaryList::Node* DictionaryList::search(int item) const
{
    Node* current = head_;
    while (current != nullptr && current->item_ != item)
    {
        current = current->next_;
    }
    return current;
}

void DictionaryList::remove(Node* x)
{
    if (isEmpty()) return;
    Node* prev = head_;
    if (prev == x) {
        head_ = prev->next_;
        prev = prev->next_;
    }
    while (prev->next_ != nullptr) {
        if (prev->next_ == x) {
            if (prev->next_->next_ != nullptr) {
                prev->next_ = prev->next_->next_;
            }
            else {
                prev->next_ = nullptr;
            }
        }
        if (prev->next_ != nullptr) {
            prev = prev->next_;
        }
    }
    tail_ = prev;
}

void DictionaryList::insert(Node* x)
{
    if (this->search(x->item_)) {
        return;
    }
    if (this->isEmpty()) {
        head_ = x;
        tail_ = x;
        return;
    }
    if (x->item_ < head_->item_) {
        x->next_ = head_;
        head_ = x;
    }
    else {
        Node* prev = head_;
        while (prev != tail_) {
            if (prev->next_->item_ > x->item_) {
                break;
            }
            prev = prev->next_;
        }
        if (prev == tail_) {
            x->next_ = nullptr;
            prev->next_ = x;
            tail_ = x;
        }
        else {
            x->next_ = prev->next_;
            prev->next_ = x;
        }
    }
}

bool DictionaryList::isEmpty()
{
    return head_ == nullptr && tail_ == nullptr;
}

bool DictionaryList::searchItem(int item)
{
    return (search(item) != nullptr);
}

void DictionaryList::insert(int item)
{
    Node* newNode = new Node(item);
    this->insert(newNode);
}

void DictionaryList::deleteItem(int item)
{
    if (isEmpty()) return;
    Node* current = head_;
    if (head_->item_ == item) {
        head_ = head_->next_;
        return;
    }

    while (current->next_) {
        if (current->next_->item_ == item) {
            if (current->next_->next_) {
                current->next_ = current->next_->next_;
            }
            else {
                current->next_ = nullptr;
            }
        }
        if (current->next_) {
            current = current->next_;
        }
    }
    tail_ = current;
}

void DictionaryList::merge(DictionaryList* list)
{
    if (this == list)
    {
        throw std::invalid_argument("Trying to merge a list with itself!");
    }
    if (list->isEmpty())
    {
        return;
    }
    if (this->isEmpty())
    {
        swap(*list);
        return;
    }
    
    Node* current = list->head();
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next_;
        if (current == list->head_) {
            if (list->head_->next_ != nullptr) { 
                list->head_ = list->head_->next_; 
            }
            else { 
                list->head_ = nullptr;
                list->tail_ = nullptr;
            }
        }
        this->insert(current);
        if (!list->isEmpty()) {
            list->remove(current);
        }
        if (next != nullptr) {
            current = next;
        }
        else {
            current = nullptr;
        }
    }
}

void DictionaryList::remove(DictionaryList* list)
{
    if (this == list)
    {
        throw std::invalid_argument("Trying to subtract the list itself from the list!");
    }
    if (this->isEmpty()) {
        return;
    }
    Node* head = list->head();

    while (head != nullptr) {
        this->deleteItem(head->item_);
        head = head->next_;
    }
}

DictionaryList* getIntersection(DictionaryList* leftList, DictionaryList* rightList) {
    if (leftList == rightList) {
        throw std::invalid_argument("Trying to get the intersections of the list with itself!");
    }
    DictionaryList* newList = new DictionaryList;
    DictionaryList::Node* head = leftList->head();
    while (head != nullptr) {
        if (rightList->search(head->item_)) {
            newList->insert(head->item_);
        }
        head = head->next_;
    }
    return newList;
}

std::ostream& operator<<(std::ostream& out, const DictionaryList& src)
{
    DictionaryList::Node* current = src.head_;
    while (current != nullptr)
    {
        out << current->item_ << ' ';
        current = current->next_;
    }
    return out;
}

void DictionaryList::swap(DictionaryList& other) noexcept
{
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
}