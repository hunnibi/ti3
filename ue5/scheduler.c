#include <stdlib.h>
#include <stdio.h>

#include "scheduler.h"

// Evghenii Orenciuc, Jonathan Rex

struct Process* rr(struct Process* head, struct Process* current) {
    if (head == NULL) {
        fprintf(stderr, "RR: head == NULL\n");
        exit(1);
    }
    if (head->next == head) { // process queue is empty
        return NULL;
    }
    if (current == NULL) {
        return head->next;
    }

    struct Process *next = current->next;

    while (next != current) {
        if (next->cycles_todo)
            return next;
        next = next->next;
    }

    return current->cycles_todo ? current : NULL;
}

struct Process* fcfs(struct Process* head, struct Process* current) {
    if (head == NULL) {
        fprintf(stderr, "RR: head == NULL\n");
        exit(1);
    }
    if (head->next == head) { // process queue is empty
        return NULL;
    }
    if (current == NULL) {
        return head->next;
    }

    return current->cycles_todo ? current : current->next;
}

struct Process* spn(struct Process* head, struct Process* current) {
    if (head == NULL) {
        fprintf(stderr, "RR: head == NULL\n");
        exit(1);
    }
    if (head->next == head) { // process queue is empty
        return NULL;
    }
    if (current == NULL) {
        return head->next;
    }
    if (current->cycles_todo) {
        return current;
    }

    struct Process *shortest = head->next;
    struct Process *next = head->next;
    while (next != head) {
        if (next->cycles_todo < shortest->cycles_todo)
            shortest = next;
        next = next->next;
    }

    return shortest;
}

struct Process* srt(struct Process* head, struct Process* current) {
	return NULL;
}

struct Process* hrrnPreemptive(struct Process* head, struct Process* current) {
	return NULL;
}

struct Process* hrrnNonPreemptive(struct Process* head, struct Process* current) {
	return NULL;
}
