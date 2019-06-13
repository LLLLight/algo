/*
 * Joe/algo.c
 *
 * This file is for algo.
 *
 * Copyright (C) 2019-2020 Joe
 *
 * 1996-12-23 Modified by Dave Grothe to fix bugs in semaphores  and
 *            make semaphores SMP safe
 * 1998-11-19 Implemented schedule_timeout() and related stuff
 *            by Andrea Arcangeli
 * 2002-01-04 New ultra-scalable O(1) scheduler by Ingo Molnar:
 *            hybrid priority-list and round-robin design with
 *            an array-switch method of distributing timeslices
 *            and per-CPU runqueues. Cleanups and useful suggestions
 *            by Davide Libenzi, preemptible kernel bits by Robert Love.
 * 2003-09-03 Interactivity tuning by Con Kolivas.
 * 2004-04-02 Scheduler domains code by Nick Piggin
 */

#include <stdio.h>

typedef enum sort_type {
    e_insertion_sort = 0,
    e_bubble_sort,
    e_selection_sort,
    e_quick_sort
} e_sort_type_t;

e_sort_type_t choice = e_quick_sort; // FIXME:TODO: /* 选择排序方式 */

void print_array(int *array, int length)
{
    for (int i=0; i<length; i++)
        printf("[%d] \t", array[i]);
    printf("\n");
}

void insertion_sort(int array[], int length)
{
    printf("******************\n");
    printf("*[Insertion Sort]*\n");
    printf("******************\n");

    int i;

    for (i=1; i<length; i++) {

        int tmp = array[i]; /* 将数组[0]当作有序数组，从数组[1]开始与有序数组进行比较 */

        while (i>0 && tmp<array[i-1]) { /* 比较数组位与其前一位的数字进行比较 */
            array[i] = array[i-1]; /* 比较数组位与前一位的数字进行位置交换 */
            i--;
        }

        array[i] = tmp;
    }
}

void bubble_sort(int *array, int length)
{
    printf("******************\n");
    printf("**[Bubble  Sort]**\n");
    printf("******************\n");

    int i, j, tmp, isChange;

    for (i=0; i<length-1; i++) { /* 两两比较，比较次数比数组数-1 */

        isChange = 0;

        for (j=0; j<length-i-1; j++) { /* 每次比较完，最大数已经排在数组末，因此每次比较的位数-1 */

            if (array[j] > array[j+1]) { /* 两两比较，位置交换 */
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                isChange = 1;
            }
        }

        if (!isChange) /* 如果一趟下来没有交换，说明数组已经有序 */
            break;
    }

}

void selection_sort(int *array, int length)
{
    printf("******************\n");
    printf("*[Selection Sort]*\n");
    printf("******************\n");

    int pos; /* 记录当前循环最大数的角标 */
    int i, j, tmp;

    for (i=0; i<length-1; i++) {

        pos = 0;

        for (j=0; j<length-i; j++) { /* pos角标的数循环与剩下的数进行比较 */
            if (array[j] > array[pos]) /* 记录pos角标 */
                pos = j;
        }

        tmp = array[length-i-1]; /* 将已记录pos角标的数与当前未排序的倒一数字进行位置交换 */
        array[length-i-1] = array[pos];
        array[pos] = tmp;
    }
}

void quick_sort(int array[], int left, int right)
{
    printf("******************\n");
    printf("***[Quick Sort]***\n");
    printf("******************\n");

    int pivot; // 支点
    int i = left; // 指向数组左边的第一个元素
    int j = right; // 指向数组右边的最后一个元素

    pivot = array[(left+right)/2];

    while (i <= j) { /* 左右两端进行扫描。只要两端还没有交替，就一直扫描 */

        while (pivot > array[i]) /* 寻找直到比支点大的数 */
            i++;

        while (pivot < array[j]) /* 寻找直到比支点小的数 */
            j--;

        if (i <= j) { /* 此时已经分别找到了比支点小的数和比支点大的数，它们进行交换 */
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    } /* while保证了第一趟排序支点得左边比支点小，支点得右边比支点大 */

    /* 左边再做排序，直到左边剩下一个数（递归出口） */
    if (left < j)
        quick_sort(array, left, j);
    /* 右边再做排序，直到右边剩下一个数（递归出口） */
    if (i < right)
        quick_sort(array, i, right);
}

void main()
{
    int i ;
    int array[10] = {8, 1, 3, 7, 2, 5, 9, 0, 6, 4};

    print_array(array, 10);

    switch (choice) {
        case e_insertion_sort:
            insertion_sort(array, 10);
            break;
        case e_bubble_sort:
            bubble_sort(array, 10);
            break;
        case e_selection_sort:
            selection_sort(array, 10);
            break;
        case e_quick_sort:
            quick_sort(array, 0, 9);
        default:
            break;
    }

    print_array(array, 10);

}