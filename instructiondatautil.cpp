#include "internal8085.h"
void Internal8085::instructionTypeMapping(){

    //no operand
    instructionType[tr("CMA")] = 1;
    instructionType[tr("CMC")] = 1;
    instructionType[tr("DAA")] = 1;
    instructionType[tr("HLT")] = 1;
    instructionType[tr("NOP")] = 1;
    instructionType[tr("PCHL")] = 1;
    instructionType[tr("RAL")] = 1;
    instructionType[tr("RAR")] = 1;
    instructionType[tr("RET")] = 1;
    instructionType[tr("RC")] = 1;
    instructionType[tr("RLC")] = 1;
    instructionType[tr("RM")] = 1;
    instructionType[tr("RNC")] = 1;
    instructionType[tr("RNZ")] = 1;
    instructionType[tr("RP")] = 1;
    instructionType[tr("RPE")] = 1;
    instructionType[tr("RPO")] = 1;
    instructionType[tr("RRC")] = 1;
    instructionType[tr("RZ")] = 1;
    instructionType[tr("SPHL")] = 1;
    instructionType[tr("STC")] = 1;
    instructionType[tr("XCHG")] = 1;
    instructionType[tr("XTHL")] = 1;

    //data operand
   instructionType[tr("ACI")] = 2;
   instructionType[tr("ADI")] = 2;
   instructionType[tr("ANI")] = 2;
   instructionType[tr("CPI")] = 2;
   instructionType[tr("ORI")] = 2;
   instructionType[tr("SBI")] = 2;
   instructionType[tr("SUI")] = 2;
   instructionType[tr("XRI")] = 2;

   //reg oprand
   //single register operand [A, B, C, D, E, H, L, M]
   instructionType[tr("ADC")] = 3;
   instructionType[tr("ADD")] = 3;
   instructionType[tr("ANA")] = 3;
   instructionType[tr("CMP")] = 3;
   instructionType[tr("DCR")] = 3;
   instructionType[tr("INR")] = 3;
   instructionType[tr("ORA")] = 3;
   instructionType[tr("SBB")] = 3;
   instructionType[tr("SUB")] = 3;
   instructionType[tr("XRA")] = 3;

   //address
    instructionType[tr("CALL")] = 4;
    instructionType[tr("CC")] = 4;
    instructionType[tr("CM")] = 4;
    instructionType[tr("CNC")] = 4;
    instructionType[tr("CNZ")] = 4;
    instructionType[tr("CP")] = 4;
    instructionType[tr("CPE")] = 4;
    instructionType[tr("CPO")] = 4;
    instructionType[tr("CZ")] = 4;
    instructionType[tr("JC")] = 4;
    instructionType[tr("JM")] = 4;
    instructionType[tr("JMP")] = 4;
    instructionType[tr("JNC")] = 4;
    instructionType[tr("JNZ")] = 4;
    instructionType[tr("JP")] = 4;
    instructionType[tr("JPE")] = 4;
    instructionType[tr("JPO")] = 4;
    instructionType[tr("JZ")] = 4;

    instructionType[tr("LDA")] = 4;
    instructionType[tr("LHLD")] = 4;
    instructionType[tr("SHLD")] = 4;
    instructionType[tr("STA")] = 4;

    //Rpair4 {BC, DE, HL, SP}
    instructionType[tr("DAD")] = 5;
    instructionType[tr("DCX")] = 5;
    instructionType[tr("INX")] = 5;

    //Rp2 {BC, DE}
    instructionType[tr("LDAX")] = 6;
    instructionType[tr("STAX")] = 6;

    //Rpw4 {BC, DE, HL, PSW}
    instructionType[tr("PUSH")] = 7;
    instructionType[tr("POP")] = 7;

    //reg, reg
    instructionType[tr("MOV")] = 8;

    //reg, data
    instructionType[tr("MVI")] = 9;

    //reg, address
    instructionType[tr("LXI")] = 10;

    //not supported
    instructionType[tr("DI")] = 11;
    instructionType[tr("EI")] = 11;
    instructionType[tr("IN")] = 11;
    instructionType[tr("OUT")] = 11;
    instructionType[tr("RIM")] = 11;
    instructionType[tr("SIM")] = 11;
    instructionType[tr("RST")] = 11;

}
void Internal8085::byteCntMapping(){
    byteCnt[tr("ADC")] = 1;
    byteCnt[tr("ADD")] = 1;
    byteCnt[tr("ANA")] = 1;
    byteCnt[tr("CMA")] = 1;
    byteCnt[tr("CMC")] = 1;
    byteCnt[tr("CMP")] = 1;
    byteCnt[tr("DAA")] = 1;
    byteCnt[tr("DAD")] = 1;
    byteCnt[tr("DCR")] = 1;
    byteCnt[tr("DCX")] = 1;
    byteCnt[tr("HLT")] = 1;
    byteCnt[tr("INR")] = 1;
    byteCnt[tr("INX")] = 1;
    byteCnt[tr("LDAX")] = 1;
    byteCnt[tr("MOV")] = 1;
    byteCnt[tr("NOP")] = 1;
    byteCnt[tr("ORA")] = 1;
    byteCnt[tr("PCHL")] = 1;
    byteCnt[tr("POP")] = 1;
    byteCnt[tr("PUSH")] = 1;
    byteCnt[tr("RAL")] = 1;
    byteCnt[tr("RAR")] = 1;
    byteCnt[tr("RC")] = 1;
    byteCnt[tr("RET")] = 1;
    byteCnt[tr("RLC")] = 1;
    byteCnt[tr("RM")] = 1;
    byteCnt[tr("RNC")] = 1;
    byteCnt[tr("RNZ")] = 1;
    byteCnt[tr("RP")] = 1;
    byteCnt[tr("RPE")] = 1;
    byteCnt[tr("RPO")] = 1;
    byteCnt[tr("RRC")] = 1;
    byteCnt[tr("RZ")] = 1;
    byteCnt[tr("SBB")] = 1;
    byteCnt[tr("SPHL")] = 1;
    byteCnt[tr("STAX")] = 1;
    byteCnt[tr("STC")] = 1;
    byteCnt[tr("SUB")] = 1;
    byteCnt[tr("XCHG")] = 1;
    byteCnt[tr("XRA")] = 1;
    byteCnt[tr("XTHL")] = 1;
    byteCnt[tr("ACI")] = 2;
    byteCnt[tr("ADI")] = 2;
    byteCnt[tr("ANI")] = 2;
    byteCnt[tr("CPI")] = 2;
    byteCnt[tr("MVI")] = 2;
    byteCnt[tr("ORI")] = 2;
    byteCnt[tr("SBI")] = 2;
    byteCnt[tr("SUI")] = 2;
    byteCnt[tr("XRI")] = 2;
    byteCnt[tr("CALL")] = 3;
    byteCnt[tr("CC")] = 3;
    byteCnt[tr("CM")] = 3;
    byteCnt[tr("CNC")] = 3;
    byteCnt[tr("CNZ")] = 3;
    byteCnt[tr("CP")] = 3;
    byteCnt[tr("CPE")] = 3;
    byteCnt[tr("CPO")] = 3;
    byteCnt[tr("CZ")] = 3;
    byteCnt[tr("JC")] = 3;
    byteCnt[tr("JM")] = 3;
    byteCnt[tr("JMP")] = 3;
    byteCnt[tr("JNC")] = 3;
    byteCnt[tr("JNZ")] = 3;
    byteCnt[tr("JP")] = 3;
    byteCnt[tr("JPE")] = 3;
    byteCnt[tr("JPO")] = 3;
    byteCnt[tr("JZ")] = 3;
    byteCnt[tr("LDA")] = 3;
    byteCnt[tr("LHLD")] = 3;
    byteCnt[tr("LXI")] = 3;
    byteCnt[tr("SHLD")] = 3;
    byteCnt[tr("STA")] = 3;

}
