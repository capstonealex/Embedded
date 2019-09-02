
# State machine of state machines task management
The task manager runs as a supervisor of the entire system, isolating different
tasks from each other and running safety features and machine clean up.
Tasks are manged by a taskManager object, which loads and unloads them
and manages the transition between tasks.
The base task class of the manager consists of:
``` cpp
task.cpp
virtual void init(void);
virtual void activate(void);
virtual void update(void);
virtual void deactivate(void);
virtual void uninit(void);

```

init and unit are occur when a task is loaded or unloaded by the task manager, their
primary roll is to initialize and clean up the task data structure, making sure
all internal representations of the system are clean.a


The activate and deactivate methods are called when a task is activated or deactivate.
The tasks here would activating and deactivate other modules needed in hardware
to begin opperation (e.g. homing or mode setting for the specific algorithm)

Update runs the actual state machine.