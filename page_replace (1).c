#include <stdio.h>
#include <limits.h>

void printPages(int pages[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (pages[i] == -1)
            printf("- ");
        else
            printf("%d ", pages[i]);
    }
    printf("\n");
}

// FIFO Page Replacement Algorithm
int FIFO(int pages[], int n, int frames) {
    int frame[frames];
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int page_faults = 0;
    int index = 0;
    
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            page_faults++;
        }

        printPages(frame, frames);
    }

    return page_faults;
}

// LRU Page Replacement Algorithm
int LRU(int pages[], int n, int frames) {
    int frame[frames];
    int time[frames];
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    int page_faults = 0;
    int t = 0;

    for (int i = 0; i < n; i++) {
        int flag = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                time[j] = ++t;
                flag = 1;
                break;
            }
        }

        if (!flag) {
            int min = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[min])
                    min = j;
            }

            frame[min] = pages[i];
            time[min] = ++t;
            page_faults++;
        }

        printPages(frame, frames);
    }

    return page_faults;
}

// Optimal Page Replacement Algorithm
int optimal(int pages[], int n, int frames) {
    int frame[frames];
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int flag = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            int replaceIndex = -1;
            int farthest = i + 1;

            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k])
                        break;
                }

                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            if (replaceIndex == -1) {
                for (int j = 0; j < frames; j++) {
                    if (frame[j] == -1) {
                        replaceIndex = j;
                        break;
                    }
                }
            }

            frame[replaceIndex] = pages[i];
            page_faults++;
        }

        printPages(frame, frames);
    }

    return page_faults;
}

int main() {
    int n, frames;

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("\nFIFO Page Replacement\n");
    int fifo_faults = FIFO(pages, n, frames);
    printf("Total Page Faults (FIFO): %d\n", fifo_faults);

    printf("\nLRU Page Replacement\n");
    int lru_faults = LRU(pages, n, frames);
    printf("Total Page Faults (LRU): %d\n", lru_faults);

    printf("\nOptimal Page Replacement\n");
    int opt_faults = optimal(pages, n, frames);
    printf("Total Page Faults (Optimal): %d\n", opt_faults);

    return 0;
}

