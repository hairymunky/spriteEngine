#ifndef DISPLAY_H
#define DISPLAY_H

/*{{{ Display
        Basic Display class. 
}}}*/
class Display  {

    public:

    virtual ~Display() {}
    Display() {}

    virtual void refresh() = 0;
    virtual bool init(int w, int h) = 0;
    virtual void uninit() = 0;
    virtual void handleEvents() = 0;
};
#endif