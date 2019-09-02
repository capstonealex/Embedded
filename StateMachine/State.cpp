//
// Created by ALEX EXOSKELETON on 2019-09-02.
//
// Abstract class of a a state machines State member.


Class State{

        public:
        virtual void entry(void)  = 0;
        virtual void during(void) = 0;
        virtual void exit(void)  = 0;

};
