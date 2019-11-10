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
        printf("Waiting for IRQ...\n");
        return numCycles;
    }

    if(m_flagIRQ && !(m_regP & 0x04)) {
        printf("IRQ\n");
        numCycles++; // Internal Operation..?
        if(!m_flagE) { m_bus->write(m_regS--, m_regPBR); numCycles++; }
        m_bus->write(m_regS--, m_regPC>>8); numCycles++;
        m_bus->write(m_regS--, m_regPC&0xFF); numCycles++;
        m_bus->write(m_regS--, m_regP); numCycles++;
        m_regP |= 0x04;
        m_regP &= 0xF7;
        m_regPBR = 0;
        if(m_flagE)
            m_regPC = m_bus->read(0xFFFE) + (uint16_t(m_bus->read(0xFFFF)) << 8);
        else
            m_regPC = m_bus->read(0xFFEE) + (uint16_t(m_bus->read(0xFFEF)) << 8);
        numCycles += 2;
        m_flagRDY = 0;
        m_flagIRQ = 0;
        return numCycles; // GET OUT OF HERE
    }

    m_flagIRQ = 0; // IRQ has been processed, continuing...

    switch(m_regIR) {
    case 0x18: // CLC
        m_regP &= 0xFE; numCycles++;
        m_regPC++;
        break;
    case 0x1A: // INC
        // TODO: Set status flags
        m_regC++;
        m_regPC++;
        break;
    case 0x40: // RTI
        numCycles += 2; // Internal Operation
        m_regP = m_bus->read(++m_regS); numCycles++;
        m_regPC = m_bus->read(++m_regS); numCycles++;
        m_regPC |= m_bus->read(++m_regS) << 8; numCycles++;
        if(!m_flagE) { m_regPBR = m_bus->read(++m_regS); }
        break;
    case 0x4C: // JMP
    {
        m_regPC++;
        int16_t location = m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)); m_regPC++; numCycles++;
        location |= m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)) << 8; m_regPC++; numCycles++;
        m_regPC = location;
        break;
    }
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
        if(m_flagE) numCycles++; // Branch taken
        uint16_t oldPage = m_regPC & 0xFF00;
        m_regPC += offset + 2;
        if(m_flagE && (m_regPC & 0xFF00) != oldPage) numCycles++; // Page boundary
        break;
    }
    case 0x89: // BIT
    {
        m_regPC++;
        int16_t test = m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)); m_regPC++; numCycles++;
        if(!(m_regP & 0x20)) { test |= m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)) << 8; m_regPC++; numCycles++; }
        test &= m_regC;
        if(test == 0) m_regP |= 0x02; else m_regP &= ~0x02;
        // TODO: Do the other flags
        break;
    }
    case 0x8E: // STX
    {
        m_regPC++;
        int16_t location = m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)); m_regPC++; numCycles++;
        location |= m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)) << 8; m_regPC++; numCycles++;
        m_bus->write((m_regDBR << 16) | location, m_regX & 0xFF); numCycles++;
        if(!(m_regP & 0x10)) { m_bus->write((m_regDBR << 16) | (location + 1), m_regX >> 8); }
        break;
    }
    case 0xA2: // LDX
    {
        m_regPC++;
        int16_t newVal = m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)); m_regPC++; numCycles++;
        if(!(m_regP & 0x10)) { newVal |= m_bus->read((m_regPBR << 16) | (m_regPC & 0xFFFF)) << 8; m_regPC++; numCycles++; }
        m_regX = newVal;
        break;
    }
    case 0xCB: // WAI
    {
        m_flagRDY = 1;
        m_regPC++; // Get ready to run next instruction
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
    case 0xF0: // BEQ
    {
        if(m_regP & 0x02) {
            int8_t offset = m_bus->read((m_regPBR << 16) | ((m_regPC + 1) & 0xFFFF)); numCycles++;
            if(m_flagE) numCycles++;
            uint16_t oldPage = m_regPC & 0xFF00;
            m_regPC += offset + 2;
            if(m_flagE && (m_regPC & 0xFF00) != oldPage) numCycles++; // Page boundary
        } else {
            m_regPC += 2;
        }
        break;
    }
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
