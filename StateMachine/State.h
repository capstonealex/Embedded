//
// Created by William Campbell on 2019-09-04.
//

#ifndef EMBEDED_STATE_H
#define EMBEDED_STATE_H


class State {
public:
    State();
    virtual void entry(void)  = 0;
    virtual void during(void) = 0;
    virtual void exit(void)  = 0;

};


#endif //EMBEDED_STATE_H
