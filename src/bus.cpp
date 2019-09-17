#include "bus.hpp"

uint8_t ExtBus::read(uint32_t loc) {
    bool valSet = 0;
    for(Component* comp : m_components) {
        if(comp->respondToRead(loc)) {
            if(valSet)
                m_status &= comp->read(loc);
            else {
                m_status  = comp->read(loc);
                valSet = 1;
            }
        }
    }
    return m_status; // Normal value if one response, AND of multiple if multiple responses, previous value if Open Bus
}

void ExtBus::write(uint32_t loc, uint8_t val) {
    for(Component* comp : m_components)
        comp->write(loc, val);
}
