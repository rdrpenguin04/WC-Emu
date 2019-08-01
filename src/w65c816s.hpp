#pragma once

class w65c816s {
public:
    explicit w65c816s(Bus bus);
    uint8_t tick(); // returns number of cycles used
private:
    Bus bus;
};
