# Exoskeleton: State Machine
Robots must be able to undertake both low level (read sensors, timing, a/d IO) and high level (behavioral) tasks (data log, trajectory gen, motor cal, sensor filtering, etc). We require most of these tasks to be managed to support experimental controllers and supervisory machines that activate and deactivate behaviors based on user input. We have implemented a modular State Machine library to develop event-driven controllers for specific tasks and a method to safely switch between tasks. Bellow, we describe the architecture of the State Machine class. The explnation is meant to be non exhaustive and only gives a brief intro to the mechanics of the software. For full details, run through the source code, example ExoStateMachine project and try to develop your own event driven State Machine to meet your needs.

driven state Machine.
## State  Machine.
- StateMachine class is a base class, it is from this class that states are run and switched between. The class must have the following methods.
```
void StateMachine::init(void)
void StateMachine::acttuvate(void)
void StateMachine::update(void)
void StateMachine::deactivate(void)
void StateMachine::initialize(State *i)
void StateMachine::getCurState(void)
```
## Events
---
Abstract base class to represent **Events** which trigger a transition between two states. Using the check method.
    `virtual Boolean method: check()`
    - the derived class must implement the check method to return t/f based on some world condition. e.g. event (doneMove) -> returns true or false if a motion has been completed (90 deg for example).
    
## State
---
ABSTRACT base class w/ 3 methods which must be defined
```
        virtual void entry(void); 
            -> 1 time set ups
        virtual void durring(void); 
            -> essentially the update method of the state machine
            -> *CONTINUOUS UPDATE AND CONTROL LIVES HERE*
                *MOTOR CONTROL*
        virtual void exit(void);
            -> transition out of the state triggers this, release resources.
```
When a state becomes active: STATE_MACHINE OWNER of it calls its entry method 1 time.

## Transitions
---
- list of outgoing transitions (class Transitions) 
Transitions: events (who trigger the transition) and the target state.
note: events have a check method which returns true or false if they have occurred

## State machine transitions
---
- Pointer to a currently active state and continuously checks outgoing Transitions of that state (their check())
- When a Transition becomes active (check method returns true), the current state is set to the target state of that transition.
## State machine implementation.
---
Specific State machines are classes derived from StateMachine class base class.
- Must implements init, deactivate, and uninitiated as empty functions
- StateMachines have a pointer to initial STATE object of the machine, set up in the constructor using the initialize method.
Activate and update methods are as bellow.
```
void StateMachine::update()
{

    Transition *t = currentState->getActiveArc();

    if (t != NULL)
    {

        currentState->exit();
        currentState = t->target;
        currentState->entry();
    }

    currentState->during();
}

```
---
### To design your own state machine programatically follow these four steps:
1) Define the event objects with the statemachine
2) Define the state classes and objects within the statemachine
3) Add desired transitions to the states 
4) Set the initial state of the state machine 
