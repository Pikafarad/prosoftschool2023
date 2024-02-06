#ifndef SERIALIZ_H
#define SERIALIZ_H


class Messag{

    virtual ~Messag() = default;

    virtual void serialize() = 0;
};

#endif // SERIALIZ_H
