//#pragma once
#include <cstdint>

/* abstract base class */
class Mapper
{
  public:
    Mapper(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper();

  public:
    /* transfroms ppu/cpu addresses */
    /* if sucessfully mapped, returns true */
    virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;

  protected:
    uint8_t nPRGBanks = 0; /* # of banks */
    uint8_t nCHRBanks = 0;
}