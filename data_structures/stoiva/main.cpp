#include <iostream>

using namespace std;
#include "../../rect/rect.h"


template <class T>
class my_stack{
    private:
        //oριζω κλαση κομβου μέσα στην stack για να χω προσβαση μονο από δω
        class node{
            public:
            T data;
            node *next;
            //
            //ουσιαστικα διπλα συνδεδεμενη λιστα για να διευκολυνθω στο pop(push γινεται μονο αν εχω τον top)
        };
        //ενθυλάκωση
        int count;
        node *top;//head η κεφαλη που αλλαζει οταν μπαινει η βγαινει στοιχειο απο την στιβα

    public:
    //setters getters δεν εχω εδω, ουτε να μπορει να αλλαξει καποιο node ουτε να μπορει να εχει προσβαση σε κάποιο αλλο node
        //constructor
        my_stack();
        my_stack(T data);
        //copy constructor
        my_stack(const my_stack &s1);
        //deconstructor
        ~my_stack();
        bool push(T data);
        void pop();
        T get_top();
        bool is_empty();
        int get_size();
        //προσθεση μιας στιβας σε μια αλλη
        my_stack operator+(my_stack &s2);
        void rec_print(node* t);
        void print();
       // friend ostream<<();

};



int main(void){

    rect r1(1,1);
    rect r2(2,2);
    rect r3(3,3);
    rect r4(4,4);
    rect r35(35,35);

    my_stack<rect> s1(r1);
    s1.push(r2);
    s1.push(r3);
    s1.push(r4);


    my_stack<rect> s3;
    s3.push(r35);

    my_stack<rect>s2(s1);

    cout << "After 3 push s1:\n";;
    s1.print();
    s1.pop();   
    cout <<"After 1 pop s1:\n";
    s1.print();
    cout <<"size of s1 is: "<<s1.get_size()<<endl<<endl;

    

    cout <<"size of copy s2 is: "<<s2.get_size()<<endl;
    cout <<"top of copy s2 is:\n" <<s2.get_top()<<endl;
    s2.pop();
    s2.pop();
    cout <<"after 2 pops s2:\n" <<s2.get_top()<<endl;
    cout <<"size of copy s2 is: "<<s2.get_size()<<endl;

   // my_stack<rect> sum;
   // sum = s3 + s2;
    return 0;
}

//In C++, when you are defining member functions of a template class outside of the class definition,
//you need to specify the template parameter <T> to indicate that you are providing the implementation 
//for a specific instantiation of the template.
template <class T>
my_stack<T>::my_stack() {
    top = NULL;
    count = 0;
}



template <class T>
my_stack<T>::my_stack(T data) {
    count = 1;
    top = new node;
    top->data = data;
    top->next = NULL;
}

//copy
template <class T>
my_stack<T>::my_stack(const my_stack &s1){
    
    top = NULL;//το θέλω και στην δεύτερη περ΄ιπτωση για να βάλω τον π΄ρωτο κόμβο
    if(s1.top == NULL){
        count = 0;
    }
    else{

        node *temp = s1.top;
        while(temp != NULL){
            node *temp2 = new node;
            node *prev;
            temp2->data = temp->data;
            if(top == NULL){//αν ειναι ο π΄ρωτος κόμβος που βάζω
                top = temp2;
                prev = temp2;
                count = 0;//to ++ ειναι στο τελος εξω απο το if
            }
            else{//το top δεν θελουμε να αλλαζει (να μπουν με την ιδια σειρα)
                prev->next = temp2;
                prev = temp2;

            }

            temp = temp->next;//στην λιστα απο την οποι αντιγραφουμε
            count++;
        }

    }
}



template <class T>
my_stack<T>::~my_stack() {
    while(top != NULL){
        node *temp = top;
        top = top->next;
        delete temp;
    }

}

template <class T>
bool my_stack<T>:: push(T data) {

    node* new_node  = new node;
    if (new_node == NULL){
        return false;
    }
    new_node->data  = data;
    new_node->next = top;
    top = new_node;
    count++ ;
    return true;
}

template <class T>
void my_stack<T>:: pop(void) {
    if (!is_empty()){
        node* temp = top;
        top = top->next;
        delete temp;
        count--;
    }
}

template <class T>
T my_stack<T>::get_top(){
    return top->data;
}

template <class T>
bool my_stack<T>::is_empty() {
    return (count == 0);
}

template <class T>
int my_stack<T>::get_size(){
    return count;
}

template <class T>
my_stack<T> my_stack<T>::operator+( my_stack &s){
    my_stack new_st;
    while(!s.is_empty()){
        T data = s.get_top();
        new_st.push(data);
    }
    node* temp = top;
    while(temp!=NULL){
        T data = s.get_top();
        new_st.push(data);
        temp = temp->next;
    }
    return new_st;
}

template <class T>
void my_stack<T>::rec_print(node* t){
    if(t != NULL){
        rec_print(t->next);
        cout << t->data;
    }
}

template <class T>

void my_stack<T>::print(){
    cout <<"Nodes of stack are(from bottom to top) : \n";
    rec_print(top);
    cout <<endl;
}