#ifndef TRANSFORM_H
#define TRANSFORM_H

class TransformComponent : public Component
{
private:
    float xpos, ypos;
    float dir;

public:

    float x() { return xpos; }
    float y() { return ypos; }

    void init() override {
        dir = 1.f;    
        xpos = 0.f;
        ypos = 0.f;
    }

    void setPosition(float x, float y) {
        
        xpos = x;
        ypos = y;
    }


    void update(float dt) override {
        xpos += dir * dt;

        if (xpos > 800)
            dir = -1.f;

        if (xpos < 0) 
            dir = 1.f;
        
    }
};


#endif