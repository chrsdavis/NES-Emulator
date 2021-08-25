#include "mos6502.h"

mos6502::mos6502()
{
  using a = mos6502;
  //lookup is a std::vector 
  //initializer list of initializer lists
  lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::ILL, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::ILL, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::ILL, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::ILL, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::ILL, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::ILL, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::ILL, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::ILL, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::ILL, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::ILL, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::ILL, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::ILL, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::ILL, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::ILL, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::ILL, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "???", &a::ILL, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::ILL, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::ILL, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::ILL, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::ILL, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::ILL, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::ILL, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::ILL, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::ILL, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::ILL, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::ILL, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::ILL, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::ILL, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::ILL, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::ILL, &a::IMP, 7 },
	};
}

mos6502::~mos6502()
{

}

uint8_t mos6502::read(uint16_t a) /* cpu read */
{
  return bus->read(a,false); /* return bus' read (adr,flag)*/
}

void mos6502::write(uint16_t a, uint8_t d) /*cpu write */
{
  bus->write(a,d); /* bus write (adr,data) */
}

void mos6502::clock()
{
  if(cycles==0)
  {
    opcode = read(pc);
    SetFlag(U, true);
    pc++;

    cycles = lookup[opcode].cycles; /* required number of cycles */
    uint8_t additional_cycle1 (this->*lookup[opcode].addrmode)(); /* calls current address mode */
    uint8_t additional_cycle2 (this->*lookup[opcode].operate)(); /* calls current opcode */

    /* if adr and op need additional cycles, add cycles */
    cycles += (additional_cycle1 & additional_cycle2);
  }
  
  cycles--;
}

/*_______________________________________*/
  /* Addressing Modes */
/*_______________________________________*/

uint8_t mos6502::IMP() //IMPLIED
{
  fetched = a; /* set fetched to contents of accumulator */
  return 0;
}

uint8_t mos6502::IMM() //IMMEDIATE
{
  addr_abs = pc++; /* data is in next byte */
  return 0;
}

uint8_t mos6502::ZP0() //ZERO PAGE ADDRESSING
{
  addr_abs = read(pc);
  pc++;
  addr_abs &= 0x00FF; /* gets first page */
  return 0;
}

uint8_t mos6502::ZPX() //ZERO PAGE ADDRESSING w/ X Register Offset 
{
  addr_abs = (read(pc) + x); /* useful for iteration */
  pc++;
  addr_abs &= 0x00FF; /* gets first page */
  return 0;
}

uint8_t mos6502::ZPY() //ZERO PAGE ADDRESSING w/ Y Register Offset 
{
  addr_abs = (read(pc) + y); /* useful for iteration */
  pc++;
  addr_abs &= 0x00FF; /* gets first page */
  return 0;
}

uint8_t mos6502::ABS() //ABSOLUTE
{
  uint16_t low = read(pc);
  pc++;
  uint16_t high = read(pc);
  pc++;

  addr_abs = (high << 8) | low;

  return 0;
}

uint8_t mos6502::ABX() //ABSOLUTE w/ X Register Offset
{
  uint16_t low = read(pc);
  pc++;
  uint16_t high = read(pc);
  pc++;

  addr_abs = (high << 8) | low;
  addr_abs += x; /* offsets by x */

  if((addr_abs & 0xFF00) != (hi << 8)) /* if offset address is on a different page */
    return 1; /* alert system of page change */
  else
    return 0;
}

uint8_t mos6502::ABY() //ABSOLUTE w/ Y Register Offset
{
  uint16_t low = read(pc);
  pc++;
  uint16_t high = read(pc);
  pc++;

  addr_abs = (high << 8) | low;
  addr_abs += y; /* offsets by y */

  if((addr_abs & 0xFF00) != (hi << 8)) /* if offset address is on a different page */
    return 1; /* alert system of page change */
  else
    return 0;
}

uint8_t mos6502::IND() //INDIRECT (basically 6502's pointers)
{
  uint16_t ptr_low = read(pc);
  pc++;
  uint16_t ptr_high = read(pc);
  pc++;

  uint16_t ptr = (ptr_high << 8) | ptr_low;

  if(ptr_low == 0x00FF) /* page turn hardware bug simulation */
  {
    addr_abs = (read(ptr * 0xFF00) << 8) | read(ptr + 0);
  }else{ /* expected behavior */
    addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
  }

  return 0;
}

uint8_t mos6502::IZX() //Indirect Zero Page w/ X Offset
{
  uint16_t t = read(pc);
  pc++;

  uint16_t low = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
  uint16_t high = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

  addr_abs = (hi << 8) | lo;

  return 0;
}

uint8_t mos6502::IZX() //Indirect Zero Page w/ Y Offset
{
  uint16_t t = read(pc);
  pc++;

  uint16_t low = read(t & 0x00FF);
  uint16_t high = read((t+1) & 0x00FF);

  addr_abs = (hi << 8) | lo;
  addr_abs += y;

  if(addr_abs & 0xFF00) != (high << 8))
  {
    return 1;
  }else{
    return 0;
  }

  return 0;
}

uint8_t mos6502::REL() //Relative
{
  addr_rel = read(pc);
  pc++;
  if(addr_rel & 0x80) /* see if signed by checking 7th bit */
    addr_rel |= 0xFF));
  return 0;
}


/*_______________________________________*/
  /* Instructions */
/*_______________________________________*/

uint8_t mos6502::fetch() //fetch memory
{
  if(!(lookup[opcode].addrmode == &mos6502::IMP)) /* if it's not implied addressing mode */
    fetched = read(addr_abs);
  return fetched;
}

uint8_t mos6502::AND() //bitwise logical AND
{
  fetch(); /* fetch data */

  a = a & fetched;
  SetFlag(Z, a == 0x00); /* zero flag */
  SetFlag(N, a & 0x80);  /* negative flag if bit 7 = 1*/

  return 1; /* candidate for additional clock cycles */
}

uint8_t mos6502::BCS() //Branch if Carry Set 
{
  if(GetFlag(C) == 1) /* if carry bit is 1 */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::BCC() //Branch if Carry Clear
{
  if(GetFlag(C) == 0) /* if carry bit is false */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::BEQ() //Branch if Equal
{
  if(GetFlag(Z) == 1) /* if zero bit = 1 */
  {
    cycles++;
    addr_abs = pc + addr_rel;

    if((addr_abs & 0xFF00) != (pc & 0x00FF))
      cycles++;

    pc = addr_abs; /* pc = pc + offset */
  }
}

uint8_t mos6502::BMI() //Branch if Negative
{
  if(GetFlag(N) == 1) /* if negative bit is false */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::BNE() //Branch if Not Equal
{
  if(GetFlag(Z) == 0) /* if zero is false */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::BPL() //Branch if Positive
{
  if(GetFlag(N) == 0) /* if negative is false */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::BVC() //Branch if Overflow Clear
{
  if(GetFlag(V) == 0) /* if overflow is false */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::BVS() //Branch if Overflow Set
{
  if(GetFlag(V) == 1) /* if overflow is true */
  {
    cycles++;
    addr_abs = pc + addr_rel; /* adr = current + offset */

    if((addr_abs & 0xFF00) != (pc & 0xFF00))
      cycles++; /* if branch crosses page, add a cycle */

    pc = addr_abs; /* real adr = calculated adr */
  }
  return 0;
}

uint8_t mos6502::CLC() // Clear Carry bit
{
  SetFlag(C, false);
  return 0;
}

uint8_t mos6502::CLD() // Clear Decimal Flag
{
  SetFlag(D, false);
  return 0;
}

uint8_t mos6502::CLI() // Clear Interrupt Flag
{
  SetFlag(I, false);
  return 0;
}

uint8_t mos6502::CLV() // Clear Overflow Flag
{
  SetFlag(V, false);
  return 0;
}

uint8_t::ADC() // Addition 
{
  fetch();

  /* casting into 16 bit range */
  temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C); 

  SetFlag(C, temp > 255); /* set carry bit if >255 */
  SetFlag(Z, (temp & 0x00FF) == 0); /* if zero */
  SetFlag(N, temp & 0x80); /* negative = last bit */
  
  /* overflow flag bit math */
  SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080);

  a = temp & 0x00FF; /* put result in accumulator (8 bit) */
  return 1; /* candidate for extra clock cycles */
}

uint8_t mos6502::SBC() // Subtraction
{
  fetch();

  /* invert the data for negative */
  uint16_t val = ((uint16_t)fetched) ^ 0x00FF;

  /* overflow flag bit math, same as addition */
  temp = (uint16_t)a + val + (uint16_t)GetFlag(C);

  SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080);
  SetFlag(C, temp > 255); /* set carry bit if >255 */
  SetFlag(Z, (temp & 0x00FF) == 0); /* if zero */
  SetFlag(N, temp & 0x80); /* negative = last bit */

  a = temp & 0x00FF; /* put result in accumulator (8 bit) */

  return 1; /* can have extra clock cycles */
}

uint8_t mos6502::PHA() // Push Accumulator to Stack
{
  write(0x0100 + stkP, a);
  /* 6502 stack ptr's base location is at 0x0100 */
  /* stack has a reserved segment of mem */ 
  stkP--;
  /* stkP is current top of stack */
  return 0;
}

uint8_t mos6502::PLA() // Pop Accumulator from Stack
{
  stkP++; /* pushing puts stkP one behind */
  a = read(0x0100 + stkP); /* get value from bus */
  SetFlag(Z, a == 0x00); /* set zero flag */
  SetFlag(N, a & 0x80); /* set negative flag */
  return 0; /* no extra clock cycles */
}

void mos6502::reset() // Resets CPU
{
  /* Reset registers */
  a = 0;
  x = 0;
  y = 0;
  stkP = 0xFD;
  status = 0x00 | U; /* (U = unused) */

  addr_abs = 0xFFFC; /* address to set program counter to */
  uint16_t low = read(addr_abs + 0);
  uint16_t high = read(addr_abs + 1);

  pc = (high << 8) | low; /* set program counter */

  /* reset misc variables */
  addr_abs = 0x0000;
  addr_rel = 0x0000;
  fetched = 0x00;

  cycles = 8; /* resets take time */
}

void mos6502::irq() // Interruptable Request Signal
{
  if(GetFlag(I) == 0) /* if no interrupt flag */
  {
    /* write current program counter */
    /* 16 bits, so needs two writes */
    write(0x0100 + stkP, (pc >> 8) & 0x00FF);
    stkP--;
    write(0x0100 + stkP, pc & 0x00FF);
    stkP--;

    /* write status register to stack */
    SetFlag(B, 0);
    SetFlag(U, 1);
    SetFlag(I, 1);
    write(0x0100 + stkP, status);
    stkP--;

    /* set new, known prog counter location */
    addr_abs = 0xFFFE;
    uint16_t low = read(addr_abs + 0);
    uint16_t high = read(addr_abs + 1);
    pc = (high << 8) | low;

    cycles = 7; /* interrupts take time */
  }
}

void mos6502::nmi() // Non-Maskable IRQ
{
  /* [Same as irq, but can't be stopped] */

  /* write current program counter */
  /* 16 bits, so needs two writes */
  write(0x0100 + stkP, (pc >> 8) & 0x00FF);
  stkP--;
  write(0x0100 + stkP, pc & 0x00FF);
  stkP--;

  /* write status register to stack */
  SetFlag(B, 0);
  SetFlag(U, 1);
  SetFlag(I, 1);
  write(0x0100 + stkP, status);
  stkP--;

  /* set new, known prog counter location */
  addr_abs = 0xFFFA; /* new value of pc */
  uint16_t low = read(addr_abs + 0);
  uint16_t high = read(addr_abs + 1);
  pc = (high << 8) | low;

  cycles = 8; /* interrupts take time */
}



uint8_t mos6502::RTI() // Return from Interrupt
{
  /* reverts to pre-interrupt */

  /* reset status register from stack */
  stkP++;
  status = read (0x0100 + stkP);
  status &= ~B;
  status &= ~U;
  
  /* get previous pc from stack */
  /* 16 bit, so two reads */
  stkP++;
  pc = (uint16_t)read(0x0100 + stkP);
  stkP++;
  pc |=. (uint16_t)read(0x0100 + stkP) << 8;

  return 0; /* no additional cycles */
}

uint8_t mos6502::BRK() // Break
{
  pc++;

  SetFlag(I,1);
  write(0x0100 + stkP, (pc >> 8) & 0x00FF);
  stkP--;
  write(0x0100 + stkP, pc & 0x00FF);
  stkP--;

  SetFlag(B,1);
  write(0x0100 + stkP, status);
  stkP--;
  SetFlag(B,0);

  pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) >> 8);
  return 0;
}

uint8_t mos6502::CMP() // Compare Accumulator
{
  fetch();
  temp = (uint16_t)a - (uint16_t)fetched;
  SetFlag(C, a >= fetched;
  SetFlag(Z, (temp & 0x00FF) == 0x0000);
  SetFlag(N, temp & 0x0080);
  return 1; /* ? additional cycles */
}

uint8_t mos6502::CPX() //  Compare X Register
{
  fetch();
  temp = (uint16_t)x - (uint16_t)fetched;
  SetFlag(C, x >= fetched;
  SetFlag(Z, (temp & 0x00FF) == 0x0000);
  SetFlag(N, temp & 0x0080);
  return 0; /* no extra cycles */
}

uint8_t mos6502::CPX() //  Compare Y Register
{
  fetch();
  temp = (uint16_t)y - (uint16_t)fetched;
  SetFlag(C, y >= fetched;
  SetFlag(Z, (temp & 0x00FF) == 0x0000);
  SetFlag(N, temp & 0x0080);
  return 0; /* no extra cycles */
}