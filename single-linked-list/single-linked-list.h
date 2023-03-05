#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>


template <typename Type>
class SingleLinkedList {
    // Узел списка
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };
    
    
    
    template <typename ValueType>
    class BasicIterator {
    
        friend class SingleLinkedList;

    
        explicit BasicIterator(Node* node) {
           node_ = node;
        }

    public:
        
        using iterator_category = std::forward_iterator_tag;
        
        using value_type = Type;

        using difference_type = std::ptrdiff_t;
 
        using pointer = ValueType*;
 
        using reference = ValueType&;

        BasicIterator() = default;

        
        BasicIterator(const BasicIterator<Type>& other) noexcept {
            node_ = other.node_;
        }

        
        BasicIterator& operator=(const BasicIterator& rhs) = default;

       
        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            if(this->node_ == rhs.node_ ){
            return true;
            }
            return false;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            if(this->node_ != rhs.node_ ){
            return true;
            }
            return false;
        }
        
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            if(this->node_ == rhs.node_ ){
            return true;
            }
            return false;
        }
        
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            if(this->node_ != rhs.node_ ){
            return true;
            }
            return false;
        }
        
        BasicIterator& operator++() noexcept {
        if(this->node_->next_node != nullptr && this->node_ != nullptr){
           this->node_ = this->node_->next_node;}
           else{
           this->node_ = nullptr;
           }
           return *this;
        }

        BasicIterator operator++(int) noexcept {
        
        BasicIterator m = *this;
        
            if(this->node_->next_node != nullptr && this->node_ != nullptr){
            
           this->node_ = this->node_->next_node;}
           return m;
        }
        
        [[nodiscard]] reference operator*() const noexcept {
           return node_->value;
        }

        [[nodiscard]] pointer operator->() const noexcept {
             return &(*node_).value;
        }

    private:
        Node* node_ = nullptr;
    };


public:

    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Итератор, допускающий изменение элементов списка
    using Iterator = BasicIterator<Type>;
    // Константный итератор, предоставляющий доступ для чтения к элементам списка
    using ConstIterator = BasicIterator<const Type>;

    // Возвращает итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    [[nodiscard]] Iterator begin() noexcept {
        return Iterator(head_.next_node);
    }

    // Возвращает итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator end() noexcept {
        return Iterator(nullptr);
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    // Результат вызова эквивалентен вызову метода cbegin()
    [[nodiscard]] ConstIterator begin() const noexcept {
        return ConstIterator(head_.next_node);
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    // Результат вызова эквивалентен вызову метода cend()
    [[nodiscard]] ConstIterator end() const noexcept {
        
      return ConstIterator(nullptr);
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен cend()
    [[nodiscard]] ConstIterator cbegin() const noexcept {
         return ConstIterator(head_.next_node);
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cend() const noexcept {
        return ConstIterator(nullptr);
    }
public:


SingleLinkedList(std::initializer_list<Type> values) {
        auto it = values.end();
        SingleLinkedList tmp;
        while (it != values.begin()){
            --it;
            tmp.PushFront(*it);}
    swap(tmp);
    }

    SingleLinkedList(const SingleLinkedList& other) {
     if (!other.IsEmpty() || this != &other) {
        SingleLinkedList copy;
        std::vector<Type> copy_v;
        for(auto i = other.begin(); i != other.end(); ++i){
        copy_v.push_back(*i);
        }
        for(int i = copy_v.size()-1; i >= 0; --i){
        copy.PushFront(copy_v[i]);
        } 
        swap(copy);
     }
     }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
     if (!rhs.IsEmpty() || &rhs != this) {
          SingleLinkedList copy(rhs);
          swap(copy);
         }
         return *this;
    }

    // Обменивает содержимое списков за время O(1)
    void swap(SingleLinkedList& other) noexcept {
     std::swap(this->head_.next_node, other.head_.next_node);
     std::swap(this->size_, other.size_);
    }


    void PushFront(const Type& value){
    Node* new_node = new Node(value, head_.next_node);
    head_.next_node = new_node;
    ++size_;
    }
    
   void PopFront(){
   if(size_ > 0){
   Node* del = head_.next_node;
   head_.next_node = head_.next_node->next_node;
   delete del;
   --size_;}
   }
   
   Iterator InsertAfter( ConstIterator after, const Type& value) {
   Node* new_node = new Node(value, after.node_->next_node);
  after.node_->next_node = new_node;
        ++size_;
        return Iterator{after.node_->next_node};
  }
  
 Iterator EraseAfter(ConstIterator after)  {
    if(after.node_->next_node == nullptr && after.node_ == nullptr){
return Iterator(nullptr);}
else{
Node* node = after.node_->next_node->next_node;
Node* del = after.node_->next_node;
after.node_->next_node = node;
delete del;
--size_;
return Iterator(after.node_->next_node);
}
 }
 
 [[nodiscard]] Iterator before_begin() noexcept {
  return Iterator{&head_};
    }
 
  [[nodiscard]] ConstIterator cbefore_begin() const noexcept{
  return ConstIterator{const_cast<Node*>(&head_)};
    }
 
    void Clear(){
    Node* tmp = head_.next_node;
    Node* del;
        while(!IsEmpty()){
        del = tmp;
        tmp = tmp->next_node;
        delete del;
        --size_;
        }
    }
    
   SingleLinkedList() = default;
    
    // Возвращает количество элементов в списке за время O(1)
   size_t GetSize() const noexcept {
        return size_;
    }

    // Сообщает, пустой ли список за время O(1)
    bool IsEmpty() const noexcept {
         bool is_empty = false;
        if (size_ == 0){
        is_empty = true;
        }
        return is_empty;
    }
    
    ~SingleLinkedList(){
    Clear();
    
    }

private:
    // Фиктивный узел, используется для вставки "перед первым элементом"
    Node head_;
    size_t size_ = 0;
};

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
      if (lhs.GetSize() == rhs.GetSize() && std::equal(lhs.cbegin(),lhs.cend(),rhs.cbegin(),rhs.cend())){
    return true;
    }
    return false;
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (lhs.GetSize() == rhs.GetSize() && std::equal(lhs.cbegin(),lhs.cend(),rhs.cbegin(),rhs.cend())){
    return false;
    }
    return true;
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (std::lexicographical_compare(lhs.cbegin(),lhs.cend(),rhs.cbegin(),rhs.cend())){
    return true;
    }
    return false;
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
      if (std::lexicographical_compare(lhs.cbegin(),lhs.cend(),rhs.cbegin(),rhs.cend()) || lhs == rhs){
    return true;
    }
    return false;
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
if (std::lexicographical_compare(lhs.cbegin(),lhs.cend(),rhs.cbegin(),rhs.cend())){
    return false;
    }
    return true;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
          if (std::lexicographical_compare(lhs.cbegin(),lhs.cend(),rhs.cbegin(),rhs.cend()) || lhs == rhs){
    return true;
    }
    return false;
} 



