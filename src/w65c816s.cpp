#include <cstdio>

#include "w65c816s.hpp"

w65c816s::w65c816s(ExtBus& bus): m_bus(&bus) {
    reset();
}

void setTop8(uint16_t &reg, uint8_t val) {
    uint16_t oldPart = reg & 0x00FF;
    reg = oldPart | (uint16_t(val) << 8);
}

void w65c816s::reset() {
    m_regD = 0;
    m_regDBR = 0;
    m_regPBR = 0;
    setTop8(m_regS, 1);
    setTop8(m_regX, 0);
    setTop8(m_regY, 0);
    m_regPC = m_bus->read(0xFFFC) + (uint16_t(m_bus->read(0xFFFD)) << 8);
    m_regP &= 0xF7; // 11110111
    m_regP |= 0x34; // 00110100
    m_flagE = 1;
    m_flagRDY = 0;
    m_flagIRQ = 0;
}

uint8_t w65c816s::tick() {
    uint8_t numCycles = 0;
    m_regIR = m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)); numCycles++;

    if(m_flagRDY && !m_flagIRQ) {
        printf("Waiting for IRQ...");
        return numCycles;
    }

    switch(m_regIR) {
    case 0x18: // CLC
        m_regP &= 0xFE; numCycles++;
        m_regPC++;
        break;
    case 0x58: // CLI
        m_regP &= 0xFB; numCycles++;
        m_regPC++;
        break;
    case 0x78: // SEI
        m_regP |= 0x04; numCycles++;
        m_regPC++;
        break;
    case 0x80: // BRA
    {
        int8_t offset = m_bus->read((m_regPBR << 16) | ((m_regPC + 1) & 0xFFFF)); numCycles++;
        numCycles++; // Branch taken
        uint16_t oldPage = m_regPC & 0xFF00;
        m_regPC += offset + 2;
        if(m_flagE && (m_regPC & 0xFF00) != oldPage) numCycles++; // Page boundary
        break;
    }
    case 0xCB: // WAI
    {
        m_flagRDY = 1;
        break;
    }
    case 0xE2: // SEP
    {
        int8_t newP = m_bus->read((m_regPBR << 16) | ((m_regPC + 1) & 0xFFFF)); numCycles++;
        numCycles++; // Well...
        m_regP |= newP;
        m_regPC += 2;
        break;
    }
    case 0xEA: // NOP
        numCycles++;
        m_regPC++;
        break;
    case 0xFB: // XCE
    {
        bool oldC = m_regP & 0x1;
        m_regP &= 0xFE; // Clear carry
        m_regP |= m_flagE ? 1 : 0;
        m_flagE = oldC;
        numCycles++;
        m_regPC++;
        break;
    }
    default:
        printf("Opcode 0x%02X not supported! Skipping instruction...\n", m_regIR);
    }

    return numCycles;
}
