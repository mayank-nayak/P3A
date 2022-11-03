/*
    main: 
        determine number of threads
            check if n/2 is less than number of processors
            if true: do normal recursive merge sort
            else: make threads
        
        split until we get #arrays = #processors

    Figuring out what level stop at:
        stop = floor(log(nproc))

    thread(sub_arr):
        create thread
        return merge_sort(sub_arr)

    merge_sort(arr, level, stop): <- call until level == stop
        if level == stop:
            thread(arr)
            return arr
        normal merge stuff
        

    merge_sort(init_arr)
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/sysinfo.h>


#define KEY_SIZE 4
#define RECORD_SIZE 100

int determineLevel(int numProcessors);

void merge(char *arr[], int start, int mid, int end)
{
    int left_len = mid - start + 1;
    int right_len = end - mid;

    char* left[left_len];
    char* right[right_len];

    for (int i = 0; i < left_len; i++) {
        left[i] = arr[start + i];
    }
    for (int i = 0; i < right_len; i++) {
        right[i] = arr[mid + 1 + i];
    }

    int lp = 0; // left array pointer
    int rp = 0; // right array pointer
    int mp = start; // start index of subarray we split
                    // and are now merging

    while (lp < left_len && rp < right_len) {
        if (left[lp] <= right[rp]) {
            arr[mp++] = left[lp++];
        } else arr[mp++] = right[rp++];
    }

    while (lp < left_len) {
        arr[mp++] = left[lp++];
    }

    while (rp < right_len) {
        arr[mp++] = right[rp++];
    }

}

void merge_sort_threaded(char* arr[], int level, int thread_level, int start, int end)
{
    // create thread and run merge sort on sub-array
}

void merge_sort(char* arr[], int level, int thread_level, int start, int end)
{
    if (start < end) {
        int mid = start + (end - start) / 2;

        if (level == thread_level) {
            merge_sort_threaded(arr, level, thread_level, start, mid);
            merge_sort_threaded(arr, level, thread_level, mid + 1, end);
        } else {
            merge_sort(arr, level, thread_level, start, mid);
            merge_sort(arr, level, thread_level, mid + 1, end);
        }
        level++;               
    }
}




int determineLevel(int numProcessers) {
    int numArrays = 1;
    int level = 0;
    while (2 * numArrays < numProcessers) {
        numArrays *= 2;
        level++;
    }
    return level;
}



int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        printf("Incorrect number of arguments\n");
        exit(1);
    }
    int fd;
    if ( (fd = open(argv[1], O_RDONLY)) < 0) {
        exit(1);
    }
    struct stat st;
    stat(argv[1], &st);
    int size = st.st_size / 8;

    void *start;
    start = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

    int *init_arr[size/4];
   // printf("size = %d\n", size);
    int *p;
    int i = 0;
    for (p = start; (void *)p < start + size; p+=1) {
        printf("p = %p\n", p);
        init_arr[i] = p;

        // move this later
        int key = *init_arr[i];
        i++;
        printf("the key is %d\n", key);
        hhhh
    }



    // calculating the level at which to stop
    //double availableProcessors = get_nprocs();
    
    //int thread_level = determineLevel(availableProcessors);
    //printf("init arr: %s, %s\n", init_arr[0], init_arr[1]);
    //merge_sort(init_arr, 0, thread_level, 0, size/100);
    //printf("%s, %s\n", init_arr[0], init_arr[1]);   
}




