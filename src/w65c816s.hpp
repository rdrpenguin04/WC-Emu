#ifndef _W65C816S_2019_08_01_17_43
#define _W65C816S_2019_08_01_17_43
class w65c816s {
public:
    explicit w65c816s(Bus bus);
    uint8_t tick(); // returns number of cycles used
private:
    Bus bus;
};
#endif
