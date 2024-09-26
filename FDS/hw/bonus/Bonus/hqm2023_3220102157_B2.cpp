/* Author: 张祎迪;  ID:3220102157;  No.02 */
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main(){
    int flag = 1, n, capacity, data;
    
    // Priority queue for sorted output, input queue, and wait queue
    priority_queue<int, vector<int>, greater<int> >  OUTPUT;
    queue<int> INPUT, WAIT;
    // Input the number of elements and the capacity
    cin >> n;
    cin >> capacity;
    
    // Input data into the input queue
    while(n--){
        cin >> data;
        INPUT.push(data);
    }
    // Initialize the output queue with the first 'capacity' elements
    for(int i = 0; i < capacity; i++){
        OUTPUT.push(INPUT.front());
        INPUT.pop();
    }
    // Process and output the elements
    while(!OUTPUT.empty()){
        data = OUTPUT.top();
        // Output the element with proper formatting
        if(flag){
            flag = 0;
            cout << data;// The first element has no space before it
        }
        else{
            cout << " " << data;
        }
        // Remove the processed element from the output queue
        OUTPUT.pop();
        // Move elements from the input queue to the wait queue based on the comparison with the processed element
        if(!INPUT.empty()){
            int data1 = INPUT.front();
            if(data1 < data){
                WAIT.push(data1);// Move to the wait queue
            }
            else{
                OUTPUT.push(data1);// Move to the output queue
            }
            INPUT.pop();
        }
        // If the output queue is empty, print a newline and update the output queue
        if(OUTPUT.empty()){
            cout << endl;
            flag = 1;// Reset the flag
            int count = 0;
            // Move elements from the wait queue to the output queue
            while(!WAIT.empty() && count < capacity){
                data = WAIT.front();// Get the element
                OUTPUT.push(data);// Move to the output queue
                WAIT.pop();// Remove from the wait queue
                count ++;// Update the count
            }
            // Fill the output queue with elements from the input queue
            while(count < capacity && !INPUT.empty()){
                OUTPUT.push(INPUT.front());// Move to the output queue
                INPUT.pop();// Remove from the input queue
            }
        }
    }
    return 0;
}
