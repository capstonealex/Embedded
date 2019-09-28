# Alex Exoskeleton: StaeMachines
## STATE MACHINES.
- StateMachine class is a base which all state machines are created from, it is from this class that states are run and switched between. The class must has the following mandatory methods.
```
void StateMachine::init(void)
void StateMachine::acttuvate(void)
void StateMachine::update(void)
void StateMachine::deactivate(void)
void StateMachine::initialize(State *i)
void StateMachine::getCurState(void)
```
### Events
---
Abstract base class to represent **Events** which trigger a transition between two states. Done through the check method.
	`virtual Boolean method: check()`
	- derived class must implement the check method to return t/f based on some world condition.
	e.g. event (doneMove) -> returns true or false if a motion has been completed (90 deg for example)
---
### State
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
When a state becomes active.
---STATE_MACHINE OWENER of it calls its entry method 1 time.
### Transitions
---
- list of outgoing transitions (class Transitions) 
Transitions: events (whom trigger the transition) and the target state.
note: events have a check method which returns true or false if they have occurred

### State machine transitions
---
- Pointer to a currently active state and continuously checks outgoing Transitions of that state (their check())
- When a Transition becomes active (check method returns true), current state is set to the target state of that transition.
### State machine implementation.
---
Specific State machines are classes derived from StateMachine class base class.
- Must implements init, deactivate and uninitiated as empty functions.

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

### The other difference between the basic task and a stateMachine task is that stateMachine tasks have:
---
- pointer to initial STATE object of the machine, set up in the constructor using the initialize method.

To set up a state machine as a programmer do the following:
1) Define the event objects 
2) Define the state objects 
3) Add trsitionsan to the states 
4) Set the initial state of the state machine 

### Useful programming tools.
---
MACROS for easily creating scaffolding code for STATE,EVENT, and TRANSITIONS
e.g. typing StateObject(nameOfStateClass) creates a a new state class called nameOfStateClass as well as a pointer to an object of that state.
To use: StateObject ( MyState ) * myState;
```cpp
/*Definition of Macro:*/
#define StateObject(_name_)                                                  \
    class _name_;                                                            \
    friend class _name_;                                                     \
    class _name_ : public State                                              \
    {                                                                        \
                                                                             \
    public:                                                                  \
        _name_(StateMachine *m, const char *name = NULL) : State(m, name){}; \
        void entry(void);                                                    \
        void during(void);                                                   \
        void exit(void);                                                     \
    };                                                                       \
    _name_
		
```
