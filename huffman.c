// C program for Huffman Coding
//#include <stdio>
//#include <stdlib>
#include<fstream>
#include<iostream>
#include<string>
//#include<conio>
using namespace std;
// This constant can be avoided by explicitly calculating
//height of Huffman Tree
#define MAX_TREE_HT 100
char codes[26][10];
int cc=-1,cr=-1,ind;
// A Huffman tree node
struct MinHeapNode
{
    char data; // One of the input characters
    unsigned freq; // Frequency of the character
    struct MinHeapNode *left, *right;
    // Left and right child of this node
};
// A Min Heap: Collection of min heap (or Hufmman tree)nodes
struct MinHeap
{
    unsigned size; // Current size of min heap
    unsigned capacity; // capacity of min heap
    struct MinHeapNode **array; // Attay of minheap node pointers
};
// A utility function allocate a new min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp=(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =(struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0; // current size is 0
    minHeap->capacity = capacity;
    minHeap->array =
    (struct MinHeapNode**)malloc(minHeap->capacity *
                                 sizeof(struct MinHeapNode*));
    return minHeap;
}
// A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct
                     MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
        //_____________________________
        ind=idx;
        //____________________________
    }
}
// A utility function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
// A standard function to extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}
// A utility function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct
                   MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/
                                                   2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}
// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
// A utility function to print an array of size n
void printArr(int arr[], int top,int n)
{
    int i;
    cr=n;
    cc=-1;
    for (i = 0; i < top; ++i)
    {
        printf("%d", arr[i]);
        codes[cr][++cc]=arr[i]+'0';
    }
    codes[cr][++cc]='\0';
    printf("\n");
    //clrscr();
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}
// Creates a min heap of capacity equal to size and inserts
//all character ofdata[] in min heap.
//Initially size of min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[],
                                     int size)
{
    struct MinHeapNode *left, *right, *top;
    
    // Step 1: Create a min heap of capacity equal to size.
    //Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data,
                                                    freq, size);
    
    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from
        //min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        
        // Step 3: Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two
        //extracted node as
        // left and right children of this new node. Add this
        //node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    // Step 4: The remaining node is the root node and the
    //tree is complete.
    return extractMin(minHeap);
}
// Prints huffman codes from the root of Huffman Tree. It
//uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top,char b[]) //****
{
    int i,n;
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1,b);
    }
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1,b);
    }
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
        printf("%c: ", root->data);
        for(i=0;i<strlen(b);i++)
        {
            if(b[i]==root->data)
                n=i;
        }
        printArr(arr, top,n);
    }
}

// The main function that builds a Huffman Tree and print
//codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    // Construct Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(data, freq,size);
    
    // Print Huffman codes using the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top,data);
}
// Driver program to test above functions
int main()
{                    /*
                                       char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
                                       int freq[] = {5, 9, 12, 13, 16, 45};
                                       int size = sizeof(arr)/sizeof(arr[0]);
                                       HuffmanCodes(arr, freq, size);   */
    fstream f("file1.txt",ios::in|ios::out|ios::trunc);
    char a[100],b[26],c[100];
    int freq[26];
    int k,i,j;
    cout<<"Enter your text";
    getchar();

    cin>>a;
    b[0]=a[0];
    b[1]='\0';
    for(i=1;i<strlen(a);i++)
    {
        k=0;
        for(j=0;j<strlen(b);j++)
        {
            if(a[i]==b[j])
                k=1;
        }
        if(k==0)
            b[j]=a[i];
        b[j+1]='\0';
    }
    for(i=0;i<strlen(b);i++)
    {
        k=0;
        for(j=0;j<strlen(a);j++)
        {
            if(a[j]==b[i])
                k++;
        }
        freq[i]=k;
    }
    cout<<"Alphabet  Frequecny\n";
    for(i=0;i<strlen(b);i++)
        cout<<"   "<<b[i]<<"\t\t"<<freq[i]<<"\n";
    int size=strlen(b);
    HuffmanCodes(b,freq,size);
    //clrscr();
    string pass;
    cout<<"set password";
    cin>>pass;
    string password;
    cout<<"enter password to open file";
    cin>>password;
    if(pass==password)
     {
    cout<<a<<'\n';
    for(i=0;i<strlen(b);i++)
        cout<<b[i]<<" "<<codes[i]<<"\n";
    for(i=0;i<strlen(a);i++)
    {
        for(j=0;j<strlen(b);j++)
        {
            if(a[i]==b[j])
            {
                //cout<<codes[j]<<" "<<j<<" "<<b[j]<<endl;
                f<<codes[j];
                f<<'\n';
            }
        }
    }
    f.close();

    f.open("file1.txt",ios::in|ios::out|ios::beg);
    f>>c;
    while(!f.eof())
    {
        cout<<"\ncode : "<<c;
        f>>c;
    }
    }
 
    //cout<<size;
    return 0;
}
