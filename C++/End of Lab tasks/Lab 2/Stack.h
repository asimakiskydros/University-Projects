class Stack{
    private:
        int size;
        int pos;
        int *data;
        bool more_memory(int);
    public:
        Stack();
        Stack(int);
        Stack(const Stack &);
        ~Stack();
        bool isEmpty();
        bool pop(int &);
        bool push(int);
};