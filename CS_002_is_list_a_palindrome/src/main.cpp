// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
struct ListNode
{
    ListNode(const T& v) : value(v), next(nullptr) {}
    T value;
    ListNode* next;
};

bool solution(ListNode<int> * l) {
    ListNode<int>* list_node_cursor(l);
    // Count list size
    int list_size(0);
    while(list_node_cursor != nullptr) {
        ++list_size;
        list_node_cursor = list_node_cursor->next;
    }
    if (list_size < 2)
        return true;
    if (list_size == 2)
        return (l->value == l->next->value);
    // Set cursor to the initial position
    list_node_cursor = l;

    // Reverse second half of the list
    // At first find the middle (one step to middle actually) element
    ListNode<int>* l_rev_init(nullptr);
    int index(0);
    int rev_init_index(list_size / 2 - 1);

    while(list_node_cursor != nullptr && index < rev_init_index) {
        list_node_cursor = list_node_cursor->next;
        ++index;
    }
    l_rev_init = list_node_cursor;
    if (l_rev_init == nullptr)
        return true;

    ListNode<int> *ln1(nullptr), *ln2(nullptr), *ln3(nullptr);
    // reverse start
    ln1 = l_rev_init->next;
    ln2 = ln1->next;
    ln3 = ln2->next;
    ln1->next = nullptr;
    ln2->next = ln1;

    while (ln3 != nullptr)
    {
        ln1 = ln2;
        ln2 = ln3;
        ln3 = ln3->next;
        ln2->next = ln1;
    }

    l_rev_init->next = ln2;
    // reverse finished
    list_node_cursor = l;
    ListNode<int> *list_node_cursor_2(l_rev_init->next);
    bool list_is_palindrome(true);
    while (list_node_cursor != nullptr && list_node_cursor_2 != nullptr)
    {
        if ((list_size % 2 == 1) && list_node_cursor_2->next == nullptr)
        {
            break;
        }
        if (list_node_cursor->value != list_node_cursor_2->value)
        {
            list_is_palindrome = false;
            break;
        }
        list_node_cursor = list_node_cursor->next;
        list_node_cursor_2 = list_node_cursor_2->next;
    }

    // reverse start
    ln1 = l_rev_init->next;
    ln2 = ln1->next;
    ln3 = ln2->next;
    ln1->next = nullptr;
    ln2->next = ln1;

    while (ln3 != nullptr)
    {
        ln1 = ln2;
        ln2 = ln3;
        ln3 = ln3->next;
        ln2->next = ln1;
    }

    l_rev_init->next = ln2;
    // reverse finished

    return list_is_palindrome;
}


int main()
{
    ListNode<int> node5(1);
    node5.next = nullptr;
    ListNode<int> node4(2);
    node4.next = &node5;
    ListNode<int> node3(3);
    node3.next = &node4;
    ListNode<int> node2(2);
    node2.next = &node3;
    ListNode<int> node1(1);
    node1.next = &node2;

    bool result = solution(&node1);

    cout << result << '\n';

    return 0;
}
