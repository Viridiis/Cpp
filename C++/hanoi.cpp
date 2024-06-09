#include <iostream>
#include <time.h>
using namespace std;

// Structure of elements inside list.
struct stackElement
{
    string key;
    int keyChain;
    stackElement* nextElement; // Pointer to next pair in the list.
};

// Generate string of random characters.
string generateRNGString(int length)
{
    string s = string(length, '\0');
    for (int i = 0; i < length; i++) {
        unsigned char x = 'a' + (unsigned char)rand() % 26;
        s[i] = x;
    }
    return s;
}

stackElement* top(stackElement* stack)
{
    if (!stack) return nullptr;
    stackElement* current = stack; 
    while (current->nextElement != nullptr)
    {
        current = current->nextElement;
    }
    return current;
}

// Function to insert a new pair at the beginning of list.
void push(stackElement*& stack, const string& newKey, int keychain)
{
    if (stack == nullptr) {
        stack = new stackElement();
        stack->key = newKey;
        stack->keyChain = keychain;
        stack->nextElement = nullptr;
        return;
    }
    stackElement* newElement = new stackElement(); // Create new pair.
    newElement->key = newKey; // Set a key.
    newElement->keyChain = keychain; // Set a randomly generated keychain in range <0:100>
    newElement->nextElement = nullptr; //
    stackElement* current = stack;
    while (current->nextElement != nullptr)
    {
        current = current->nextElement;
    }
    current->nextElement = newElement;
    return;
}

void push(stackElement*& stack, int keychain)
{
    push(stack, generateRNGString(10), keychain);
}

void push(stackElement*& stack)
{
    push(stack, generateRNGString(10), rand() % 101);
}

void push(stackElement*& stack, stackElement* element)
{
    if (stack == nullptr) {
        stack = element;

        return;
    }   
    stackElement* current = stack;  
    while (current->nextElement != nullptr) 
    {
        current = current->nextElement; 
    }  
    current->nextElement = element; 
    return;
}

int size(stackElement* stack)
{
    int count = 0;
    stackElement* current = stack;
    while (current)
    {
        current = current->nextElement;
        count++;
    }
    return count;
}

// Function to delete pair.
stackElement* pop(stackElement*& stack)
{
    stackElement* result = stack;
    if (size(stack) == 1)
    {
        stack = nullptr;
        return result;
    }
    stackElement* preLast = stack;
    while (preLast->nextElement->nextElement != nullptr)
    {
        preLast = preLast->nextElement;
    }
    result = preLast->nextElement;
    preLast->nextElement = nullptr;
    return result;
}

bool empty(stackElement* stack)
{
    return stack == nullptr;
}

bool full(stackElement* stack)
{
    int count = 0;
    stackElement* current = stack;   
    while (current)
    {
        current = current->nextElement;
        count++;
    }
    return count >= 10;
}

void printStack1(stackElement* stack)
{
    if (empty(stack))
    {
        cout << "empty";
        return;
    }
    stackElement* current = stack;
    while (current != nullptr)
    {
        cout << current->keyChain << ' ';
        current = current->nextElement;
    }
    return;
}

void printStacks(stackElement* stack1, stackElement* stack2, stackElement* stack3)
{
    cout << "Stack 1: " << size(stack1) << ": ";
    printStack1(stack1);
    cout << endl;
    cout << "Stack 2: " << size(stack2) << ": ";
    printStack1(stack2);
    cout << endl;
    cout << "Stack 3: " << size(stack3) << ": ";
    printStack1(stack3);
    cout << endl;
}

enum primary
{
    primaryLeft,
    primaryMid,
    primaryRight
};

void hanoi(stackElement* left, stackElement* mid, stackElement* right)
{
    primary currentTower = primaryLeft; 
    int steps = 0;
  
    while(!(empty(left) && empty(mid)))
    {
        //some space :podcaster:

        switch (currentTower) {
        case primaryLeft:
        {
            //if left is empty
            if (empty(left))
            {
                //Largest disc is correct
                //switch logic
                currentTower = primaryMid; //switch to middle
                continue;
            }

            //odd move right
            if (size(left) % 2 != 0) {

                stackElement* topRight = top(right);
                stackElement* topLeft = top(left);
                if (empty(right))
                {
                    push(right, pop(left));
                    break;
                }
                if (topRight->keyChain > topLeft->keyChain)
                    push(right, pop(left));
                else {
                    currentTower = primaryRight;
                    continue;
                }
                break;
            }

            //even move middle

            stackElement* topMid = top(mid);
            stackElement* topLeft = top(left);
            if (empty(mid))
            {
                push(mid, pop(left));
                break;
            }
            if (topMid->keyChain > topLeft->keyChain)
                push(mid, pop(left));
            else {
                currentTower = primaryMid;
                continue;
            }
            break;
        }
        case primaryMid:
            {
                //if left is empty
                if (empty(mid))
                {
                    //Largest disc is correct
                    //switch logic
                    currentTower = primaryLeft; //switch to left
                    continue;
                    break;
                }

                //odd move right
                if (size(mid) % 2 != 0) {

                    stackElement* topRight = top(right);
                    stackElement* topMid = top(mid);
                    if (empty(right))
                    {
                        push(right, pop(mid));
                        break;
                    }
                    if (topRight->keyChain > topMid->keyChain)
                        push(right, pop(mid));
                    else {
                        currentTower = primaryRight;
                        continue;
                    }
                    break;
                }

                //even move left
                stackElement* topLeft = top(left);
                stackElement* topMid = top(mid);
                if (empty(left))
                {
                    push(left, pop(mid));
                    break;
                }
                if (topLeft->keyChain > topMid->keyChain)
                    push(left, pop(mid));
                else {
                    currentTower = primaryLeft;
                    continue;
                }
                break;
            }
        case primaryRight:
            {
              
                    //if left is empty
                    if (empty(right))
                    {
                        //Largest disc is correct
                        //switch logic
                        currentTower = primaryLeft; //switch to left
                        continue;
                        break;
                    }

                    //odd move middle
                    if (size(right) % 2 != 0) {

                        stackElement* topMid = top(mid);
                        stackElement* topRight = top(right);
                        if (empty(mid))
                        {
                            push(mid, pop(right));
                            break;
                        }
                        if (topMid->keyChain > topRight->keyChain)
                            push(mid, pop(right));
                        else {
                            currentTower = primaryMid;
                            continue;
                        }
                        break;
                    }

                    //even move left
                    stackElement* topLeft = top(left);
                    stackElement* topRight = top(right);
                    if (empty(left))
                    {
                        push(left, pop(right));
                        break;
                    }
                    if (topLeft->keyChain > topRight->keyChain)
                        push(left, pop(right));
                    else { // cannot move left
                        currentTower = primaryLeft;
                        continue;
                    }
                    break;
            }
        }
        steps++;
        cout << "Steps: " << steps << endl;
        printStacks(left, mid, right);
        cout << endl;
    }
}
 

int main()
{
    srand(time(nullptr)); // Time seed.
    
    stackElement* stack1 = nullptr;
    stackElement* stack2 = nullptr;
    stackElement* stack3 = nullptr;

    int discCount = 0;

    cout << "How many discs in hanoi tower? ";
    cin >> discCount;

    for(int i = discCount; i >= 0; i--)
        push(stack1, i);

    hanoi(stack1, stack2, stack3);
    
}