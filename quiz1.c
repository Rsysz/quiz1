#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

/* origin
node_t *swap_pair(node_t *head)
{
    for (node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}
*/

void swap_pair(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

node_t *rev_recursive(node_t *cursor, node_t *head)
{
    if(!head)
        return cursor;
    node_t *next = head->next;
    head->next = cursor;
    return rev_recursive(head, next);
}

void reverse(node_t **head)
{
    if(!(*head))
        return;
    *head = rev_recursive(NULL, *head);
}

void shuffle(node_t **head)
{
    srand(time(NULL));
    int size = 0;
    node_t *tmp = *head;
    while(tmp){
        size++;
        tmp = tmp->next;
    }
    while(size != 0)
    {
        node_t *tail, *prev_tmp = NULL, *prev_tail = NULL;
        int rad = rand() % size;
        tmp = tail = *head;
        for(int i = 0; i < rad; i++){
            prev_tmp = tmp;
            tmp = tmp->next;
        }
        for(int j = 0; j < size - 1; j++){
            prev_tail = tail;
            tail = tail->next;
        }
        /*prev_swap & head*/
        if(prev_tmp != NULL)
            prev_tmp->next = tail;
        else
            *head = tail;
        if(prev_tail != NULL)
            prev_tail->next = tmp;
        else
            *head = tmp;
        /*swap*/
        node_t *next = tmp->next;
        tmp->next = tail->next;
        tail->next = next;
        size--;
    }
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    swap_pair(&head);
    print_list(head);

    reverse(&head);
    print_list(head);

    shuffle(&head);
    print_list(head);

    return 0;
}
