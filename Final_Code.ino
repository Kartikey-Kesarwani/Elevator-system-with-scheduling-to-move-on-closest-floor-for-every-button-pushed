#include <Stepper.h>

int stepsPerRevolution = 64;  

// initialize the stepper library om pins
Stepper myStepper(stepsPerRevolution, 8,10,9,11);

//defining constants

int a;
int current = 1;
int floor[4]={0,0,0,0};
int front=-1,rear=-1;


void setup() {
  myStepper.setSpeed(5);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
}


// to add the floor no. in a queue 
void enque(int item)
{
    if (rear==3)
    {
        rear=-1;
    }
  
    rear++;
    floor[rear]=item;

    
}

// to remove the floor already reached
void deque()
{
    if (front==3)
    {
        front=-1;
    }
    front++;
    floor[front]=0;
}
// loop
void loop()
{

    if (digitalRead(2)==HIGH)        // taking inputs from pin no. 2
    {
        a=1;
        if(check(a))
        {
            enque(1);
        }
    }
    else if (digitalRead(3)==HIGH){   // taking inputs from pin no. 3
        a=2;
        if(check(a))
        {
            enque(2);
        }
    }
    else if (digitalRead(4)==HIGH){     // taking inputs from pin no. 4
       a=3;
        if(check(a))
        {
            enque(3);
        }
    }
    else if(digitalRead(5)==HIGH){       // taking inputs from pin no. 5
       a=4;
        if(check(a))
        {
            enque(4);
        }
    }
    for(int i=0;i<4;i++)
    {   if (floor[i]!=0)
        {
            myStepper.step(stepsPerRevolution*(current-floor[i]));    // moving the elevator to its desiered floor
            current=floor[i];
            deque();
        }
    }

}
boolean check(int n)                 // to  check whether the floor enterd is already in the queue or not 
{
    if (floor.empty())
    {
        return true;
    }
    else{
        for(int i=0;i<4;i++)
        {
            if (n==floor[i]){
                return false;
            }
            else {
                return true;
            }
        }

    }
}
