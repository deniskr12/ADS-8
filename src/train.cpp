// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = new Cage;
    first->prev = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    if (first->prev == nullptr) {
        first->light = light;
        first->prev = first;
        first->next = first;
    } else {
        Cage *temp = first->next;
        first->next = new Cage;
        first->next->prev = first;
        first = first->next;
        temp->prev = first;
        first->next = temp;
        first->light = light;
    }
}

int Train::getLength() {
    int count1 = 0;
    int count2 = 0;
    int total = 0;
    Cage *current = first;

    if (!current) {
        return 0;
    }

    if (!current->light) {
        current->light = true;
        count1++;
        current = current->next;
        while (!current->light) {
            count1++;
            current = current->next;
        }
        count2 = 0;
        Cage *reverse = current->prev;
        count2++;
        while (!reverse->light) {
            count2++;
            reverse = reverse->prev;
        }
        if (count2 == count1) {
            total = count1 * 2;
            countOp = total;
            return count1;
        }
    } else {
        int count = 0;
        total = 0;
        while (true) {
            current = current->next;
            count++;
            total++;
            if (current->light) {
                current->light = false;
                for (int i = 0; i < count; i++) {
                    current = current->prev;
                    total++;
                }
                if (!current->light) {
                    countOp = total;
                    return count;
                } else {
                    count = 0;
                }
            }
        }
    }
    return 0;
}

int Train::getOpCount() {
    return countOp;
}
