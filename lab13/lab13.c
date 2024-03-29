#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
    struct node *next;
    int          data;
};

int count(int value, struct node *list);
struct node *get_nth(int n, struct node *head);
struct node *insert_nth(int n, struct node *new_node, struct node *head);
struct node *delete_nth(int n, struct node *head);
struct node *delete_odd(struct node *head);

void print_list(struct node *head);
struct node *reverse(struct node *list);
struct node *create_node(int data, struct node *next);
struct node *last(struct node *head);
struct node *append(struct node *head, int value);
void free_list(struct node *head);

#define MAX_LINE 4096

// simple main function to test count, get_nth, insert_nth, delete_nth, delete_odd

int
main(int argc, char *argv[]) {
    char line[MAX_LINE];
    struct node *list_head = NULL;

    while (1) {
        printf("list = ");
        print_list(list_head);
        printf("\n");

        printf("> ");
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            // free memory even though program is exiting
            // so we can check for memory not freed by other functions
            // by running dcc --leak-check
            free_list(list_head);
            return 0;
        }

        int i = 0;
        while (isalpha(line[i]) || line[i] == '_') {
            i++;
        }
        int argument = atoi(&line[i]);
        line[i] = '\0';

        if (strcmp(line, "append") == 0) {
            list_head = append(list_head, argument);
        } else if (strcmp(line, "count") == 0) {
            printf("count(%d) returns %d\n", argument, count(argument, list_head));
        } else if (strcmp(line, "get_nth") == 0) {
            struct node *n = get_nth(argument, list_head);
            if (n == NULL) {
                printf("get_nth(%d) returned NULL\n", argument);
            } else {
                printf("get_nth(%d) returned a pointer to a node containing %d\n", argument, n->data);
            }
        } else if (strcmp(line, "delete_nth") == 0) {
            list_head = delete_nth(argument, list_head);
        } else if (strcmp(line, "insert_nth") == 0) {
            // insert a node containing 42
            struct node *new_node = create_node(42, NULL);
            list_head = insert_nth(argument, new_node, list_head);
        } else if (strcmp(line, "delete_odd") == 0) {
            list_head = delete_odd(list_head);
        } else if (strcmp(line, "") != 0) {
            printf("Unknown command: '%s'\n", line);
        }
    }
}

// Return number of nodes in the list containing value.

int count(int value, struct node *head) {
    // REPLACE THIS LINE WITH YOUR CODE
	struct node *tracker = head;
	int counter = 0;
	while (tracker != NULL) {
		if (tracker->data == value) {
			counter++;
		}
		tracker = tracker->next;
	}

    	return counter;
}

// Return a pointer to the node in  position n in the list.
// Position 0 is the first node in the list.
// Return NULL if the list has no n-th node.

struct node *get_nth(int n, struct node *head) {
    // REPLACE THIS LINE WITH YOUR CODE
    	int counter = 0;
	struct node *tracker = head;
	
	if (n < 0) {
		return NULL;
	}

	while (tracker != NULL && counter < n) {
		tracker = tracker->next;
		counter++;
	}

	return tracker;
}

// Delete the node in  position  n in the list.
// The deleted nodes is freed.
// The first node in the list is in position 0.
// Do nothing if there is no position n in the list.
// The head of the list is returned.

struct node *delete_nth(int n, struct node *head) {
    // REPLACE THIS LINE WITH YOUR CODE
	if (head == NULL) return head;

	int counter = 0;
	struct node *tracker = head;

	if (n < 0) return head;
	if (n == 0) {
		struct node *next = head->next;
		free(head);
		return next;
	}

	struct node *length_tracker = head;
	int length = 0;
	while (length_tracker != NULL) {
		length++;
		length_tracker = length_tracker->next;
	}

	if (n > length) return head;

	while (tracker != NULL && counter < n - 1) {
		tracker = tracker->next;
		counter++;
	}
	
	struct node *prev = tracker;
	
	if (prev->next != NULL) {
		struct node *nth = tracker->next;
		struct node *after = tracker->next->next;
		free(nth);
		prev->next = after;
	}

	return head;
}


// Delete all nodes in the list containing odd numbers.
// Any deleted nodes are freed.
// The head of the list is returned.

struct node *delete_odd(struct node *head) {
    // REPLACE THIS LINE WITH YOUR CODE
    	
	struct node *new_head = head;
	struct node *tracker = head;
	struct node *prev = NULL;

	while (tracker != NULL) {
		// Odd
		if (tracker->data % 2 != 0) {
			if (prev == NULL) {
				new_head = tracker->next;
				free(tracker);
				tracker = new_head;
			} else {
				prev->next = tracker->next;
				free(tracker);
				tracker = prev->next;
			}
		} else {
			if (prev == NULL) {
				prev = tracker;
			} else {
				prev = prev->next;
			}
			tracker = tracker->next;
		}
	}
	
	return new_head;
}

// Insert new_node before position n in the list.
// The first node in the list is in position 0.
// If n == length of the list, new_node is appended to list.
// Otherwise do nothing if there is no position n in the list.
// The head of the list is returned.

struct node *insert_nth(int n, struct node *new_node, struct node *head) {
    // REPLACE THIS LINE WITH YOUR CODE
    	
	if (n < 0) return head;
	
	if (head == NULL && n > 0) return head;
	if (head == NULL) return new_node;
	if (new_node == NULL) return head;
	if (n == 0) {
		new_node->next = head;
		return new_node;
	}

    	struct node *tracker = head;
	int counter = 1;
	while (tracker->next != NULL && counter < n) {
		tracker = tracker->next;
		counter++;
	}
	
	if (tracker->next == NULL && counter + 1 < n) {
		return head;
	}

	new_node->next = tracker->next;
	tracker->next = new_node;

	return head;
}

// print contents of list in Python syntax

void print_list(struct node *head) {
    printf("[");
    for (struct node *n = head; n != NULL; n = n->next) {
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]");
}

// return pointer to last node in list
// NULL is returned if list is empty

struct node *last(struct node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    return last(head->next);
}

// create a new list node containing value
// and append it to end of list

struct node *append(struct node *head, int value) {
    // new node will be last in list, so next field is NULL
    struct node *n =  create_node(value, NULL);
    if (head == NULL) {
        // new node is now  head of the list
        return n;
    } else {
        // change next field of last list node
        // from NULL to new node
        last(head)->next = n;  /* append node to list */
        return head;
    }
}

// Create a new struct node containing the specified data,
// and next fields, return a pointer to the new struct node.

struct node *create_node(int data, struct node *next) {
    struct node *n;

    n = malloc(sizeof (struct node));
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->data = data;
    n->next = next;
    return n;
}

void free_list(struct node *head) {
    if (head != NULL) {
        free_list(head->next);
        free(head);
    }
}

