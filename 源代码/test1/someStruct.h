#ifndef SOMESTRUCT_H
#define SOMESTRUCT_H

struct HitEffect{
    int x;
    int y;
    int index;
    int type;
    HitEffect(int x, int y, int index, int type){
        this->x = x;
        this->y = y;
        this->index = index;
        this->type = type;
    }
};

struct UpgradeEffect{
    int x;
    int y;
    bool beShowed;
    UpgradeEffect(int x, int y){
        this->x = x;
        this->y = y;
        beShowed = false;
    }
};

#endif // SOMESTRUCT_H
