#include "bus.hpp"

uint8_t ExtBus::read(uint32_t loc) {
    bool valSet = 0;
    for(std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); it++) {
        if((**it).respondToRead(loc)) {
            if(valSet)
                m_status &= (**it).read(loc);
            else {
                m_status  = (**it).read(loc);
                valSet = 1;
            }
        }
    }
    return m_status; // Normal value if one response, AND of multiple if multiple responses, previous value if Open Bus
}
