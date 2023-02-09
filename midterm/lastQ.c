
bool CompareAndSet(int *mem, int oldVal, int newVal);

//Write a function, which atomically multiplies a value at a given memory location and returns the updated value using this instruction.
int atomicMultiply(int *location, int multiplier){

    int ans = 0;
    int curr = 0;

    boolean done = false;
    while(!done){
        curr = *location;
        ans = curr*multiplier
        done = CompareAndSet(location, curr, ans);
    }
    return curr;
}