typedef struct _dynamicArray{
    void* buffer;
    int size;
    int capacity;
    int elementSize;
} DynamicArray;

void initDynamicArray(DynamicArray* arr, int elementSize, int capacity);
void destroyDynamicArray(DynamicArray* arr);
void addToDynamicArray(DynamicArray* arr, void* element);
void getDynamicArray(DynamicArray* arr, int idx, void* element);
void clearDynamicArray(DynamicArray* arr);
void copyDynamicArray(DynamicArray* dest, DynamicArray* source);