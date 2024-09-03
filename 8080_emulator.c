#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ConditionCodes {
    uint8_t z : 1;
    uint8_t s : 1;
    uint8_t p : 1;
    uint8_t cy : 1;
    uint8_t ac : 1;
    uint8_t pad : 3;
} ConditionCodes;

typedef struct State8080 {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    struct ConditionCodes cc;
    uint8_t int_enable;
} State8080;

void UnimplementedInstruction(State8080 *state) {
    printf("\n[Error]: Unimplemented instruction\n");
    printf("state = {\n");
    printf("\ta: %u\n", state->a);
    printf("\tb: %u\n", state->b);
    printf("\tc: %u\n", state->c);
    printf("\td: %u\n", state->d);
    printf("\te: %u\n", state->e);
    printf("\th: %u\n", state->h);
    printf("\tl: %u\n", state->l);
    printf("\tpc: %u\n", state->pc);
    printf("\tsp: %u\n", state->sp);
    printf("}\n");

    exit(1);
}

void ExecuteNextInstruction8080(State8080 *state) {
    unsigned char *opcode = &state->memory[state->pc];

    printf("%02x ", (uint8_t) *opcode);
    switch (*opcode) {
        case 0x00: // NOP	1
            break;
        case 0x01: // LXI B,D16	3		B <- byte 3, C <- byte 2
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2; // Advance 2 more bytes
            break;
        case 0x02: // STAX B	1		(BC) <- A
            UnimplementedInstruction(state);
        case 0x03: // INX B	1		BC <- BC+1
            UnimplementedInstruction(state);
        case 0x04: // INR B	1	Z, S, P, AC	B <- B+1
            UnimplementedInstruction(state);
        case 0x05: // DCR B	1	Z, S, P, AC	B <- B-1
            UnimplementedInstruction(state);
        case 0x06: // MVI B, D8	2		B <- byte 2
            UnimplementedInstruction(state);
        case 0x07: // RLC	1	CY	A = A << 1; bit 0 = prev bit 7;
                   // CY = prev bit 7
            UnimplementedInstruction(state);
        case 0x08: // -
            UnimplementedInstruction(state);
        case 0x09: // DAD B	1	CY	HL = HL + BC
            UnimplementedInstruction(state);
        case 0x0a: // LDAX B	1		A <- (BC)
            UnimplementedInstruction(state);
        case 0x0b: // DCX B	1		BC = BC-1
            UnimplementedInstruction(state);
        case 0x0c: // INR C	1	Z, S, P, AC	C <- C+1
            UnimplementedInstruction(state);
        case 0x0d: // DCR C	1	Z, S, P, AC	C <-C-1
            UnimplementedInstruction(state);
        case 0x0e: // MVI C,D8	2		C <- byte 2
            UnimplementedInstruction(state);
        case 0x0f: // RRC	1	CY	A = A >> 1; bit 7 = prev bit 0;
                   // CY = prev bit 0
            UnimplementedInstruction(state);
        case 0x10: // -
            UnimplementedInstruction(state);
        case 0x11: // LXI D,D16	3		D <- byte 3, E <- byte 2
            UnimplementedInstruction(state);
        case 0x12: // STAX D	1		(DE) <- A
            UnimplementedInstruction(state);
        case 0x13: // INX D	1		DE <- DE + 1
            UnimplementedInstruction(state);
        case 0x14: // INR D	1	Z, S, P, AC	D <- D+1
            UnimplementedInstruction(state);
        case 0x15: // DCR D	1	Z, S, P, AC	D <- D-1
            UnimplementedInstruction(state);
        case 0x16: // MVI D, D8	2		D <- byte 2
            UnimplementedInstruction(state);
        case 0x17: // RAL	1	CY	A = A << 1; bit 0 = prev CY; CY
                   // = prev bit 7
            UnimplementedInstruction(state);
        case 0x18: // -
            UnimplementedInstruction(state);
        case 0x19: // DAD D	1	CY	HL = HL + DE
            UnimplementedInstruction(state);
        case 0x1a: // LDAX D	1		A <- (DE)
            UnimplementedInstruction(state);
        case 0x1b: // DCX D	1		DE = DE-1
            UnimplementedInstruction(state);
        case 0x1c: // INR E	1	Z, S, P, AC	E <-E+1
            UnimplementedInstruction(state);
        case 0x1d: // DCR E	1	Z, S, P, AC	E <- E-1
            UnimplementedInstruction(state);
        case 0x1e: // MVI E,D8	2		E <- byte 2
            UnimplementedInstruction(state);
        case 0x1f: // RAR	1	CY	A = A >> 1; bit 7 = prev bit 7;
                   // CY = prev bit 0
            UnimplementedInstruction(state);
        case 0x20: // -
            UnimplementedInstruction(state);
        case 0x21: // LXI H,D16	3		H <- byte 3, L <- byte 2
            UnimplementedInstruction(state);
        case 0x22: // SHLD adr	3		(adr) <-L; (adr+1)<-H
            UnimplementedInstruction(state);
        case 0x23: // INX H	1		HL <- HL + 1
            UnimplementedInstruction(state);
        case 0x24: // INR H	1	Z, S, P, AC	H <- H+1
            UnimplementedInstruction(state);
        case 0x25: // DCR H	1	Z, S, P, AC	H <- H-1
            UnimplementedInstruction(state);
        case 0x26: // MVI H,D8	2		H <- byte 2
            UnimplementedInstruction(state);
        case 0x27: // DAA	1		special
            UnimplementedInstruction(state);
        case 0x28: // -
            UnimplementedInstruction(state);
        case 0x29: // DAD H	1	CY	HL = HL + HI
            UnimplementedInstruction(state);
        case 0x2a: // LHLD adr	3		L <- (adr); H<-(adr+1)
            UnimplementedInstruction(state);
        case 0x2b: // DCX H	1		HL = HL-1
            UnimplementedInstruction(state);
        case 0x2c: // INR L	1	Z, S, P, AC	L <- L+1
            UnimplementedInstruction(state);
        case 0x2d: // DCR L	1	Z, S, P, AC	L <- L-1
            UnimplementedInstruction(state);
        case 0x2e: // MVI L, D8	2		L <- byte 2
            UnimplementedInstruction(state);
        case 0x2f: // CMA	1		A <- !A
            UnimplementedInstruction(state);
        case 0x30: // -
            UnimplementedInstruction(state);
        case 0x31: // LXI SP, D16	3		SP.hi <- byte 3, SP.lo
                   // <- byte 2
            UnimplementedInstruction(state);
        case 0x32: // STA adr	3		(adr) <- A
            UnimplementedInstruction(state);
        case 0x33: // INX SP	1		SP = SP + 1
            UnimplementedInstruction(state);
        case 0x34: // INR M	1	Z, S, P, AC	(HL) <- (HL)+1
            UnimplementedInstruction(state);
        case 0x35: // DCR M	1	Z, S, P, AC	(HL) <- (HL)-1
            UnimplementedInstruction(state);
        case 0x36: // MVI M,D8	2		(HL) <- byte 2
            UnimplementedInstruction(state);
        case 0x37: // STC	1	CY	CY = 1
            UnimplementedInstruction(state);
        case 0x38: // -
            UnimplementedInstruction(state);
        case 0x39: // DAD SP	1	CY	HL = HL + SP
            UnimplementedInstruction(state);
        case 0x3a: // LDA adr	3		A <- (adr)
            UnimplementedInstruction(state);
        case 0x3b: // DCX SP	1		SP = SP-1
            UnimplementedInstruction(state);
        case 0x3c: // INR A	1	Z, S, P, AC	A <- A+1
            UnimplementedInstruction(state);
        case 0x3d: // DCR A	1	Z, S, P, AC	A <- A-1
            UnimplementedInstruction(state);
        case 0x3e: // MVI A,D8	2		A <- byte 2
            UnimplementedInstruction(state);
        case 0x3f: // CMC	1	CY	CY=!CY
            UnimplementedInstruction(state);
        case 0x40: // MOV B,B	1		B <- B
            UnimplementedInstruction(state);
        case 0x41: // MOV B,C	1		B <- C
            UnimplementedInstruction(state);
        case 0x42: // MOV B,D	1		B <- D
            UnimplementedInstruction(state);
        case 0x43: // MOV B,E	1		B <- E
            UnimplementedInstruction(state);
        case 0x44: // MOV B,H	1		B <- H
            UnimplementedInstruction(state);
        case 0x45: // MOV B,L	1		B <- L
            UnimplementedInstruction(state);
        case 0x46: // MOV B,M	1		B <- (HL)
            UnimplementedInstruction(state);
        case 0x47: // MOV B,A	1		B <- A
            UnimplementedInstruction(state);
        case 0x48: // MOV C,B	1		C <- B
            UnimplementedInstruction(state);
        case 0x49: // MOV C,C	1		C <- C
            UnimplementedInstruction(state);
        case 0x4a: // MOV C,D	1		C <- D
            UnimplementedInstruction(state);
        case 0x4b: // MOV C,E	1		C <- E
            UnimplementedInstruction(state);
        case 0x4c: // MOV C,H	1		C <- H
            UnimplementedInstruction(state);
        case 0x4d: // MOV C,L	1		C <- L
            UnimplementedInstruction(state);
        case 0x4e: // MOV C,M	1		C <- (HL)
            UnimplementedInstruction(state);
        case 0x4f: // MOV C,A	1		C <- A
            UnimplementedInstruction(state);
        case 0x50: // MOV D,B	1		D <- B
            UnimplementedInstruction(state);
        case 0x51: // MOV D,C	1		D <- C
            UnimplementedInstruction(state);
        case 0x52: // MOV D,D	1		D <- D
            UnimplementedInstruction(state);
        case 0x53: // MOV D,E	1		D <- E
            UnimplementedInstruction(state);
        case 0x54: // MOV D,H	1		D <- H
            UnimplementedInstruction(state);
        case 0x55: // MOV D,L	1		D <- L
            UnimplementedInstruction(state);
        case 0x56: // MOV D,M	1		D <- (HL)
            UnimplementedInstruction(state);
        case 0x57: // MOV D,A	1		D <- A
            UnimplementedInstruction(state);
        case 0x58: // MOV E,B	1		E <- B
            UnimplementedInstruction(state);
        case 0x59: // MOV E,C	1		E <- C
            UnimplementedInstruction(state);
        case 0x5a: // MOV E,D	1		E <- D
            UnimplementedInstruction(state);
        case 0x5b: // MOV E,E	1		E <- E
            UnimplementedInstruction(state);
        case 0x5c: // MOV E,H	1		E <- H
            UnimplementedInstruction(state);
        case 0x5d: // MOV E,L	1		E <- L
            UnimplementedInstruction(state);
        case 0x5e: // MOV E,M	1		E <- (HL)
            UnimplementedInstruction(state);
        case 0x5f: // MOV E,A	1		E <- A
            UnimplementedInstruction(state);
        case 0x60: // MOV H,B	1		H <- B
            UnimplementedInstruction(state);
        case 0x61: // MOV H,C	1		H <- C
            UnimplementedInstruction(state);
        case 0x62: // MOV H,D	1		H <- D
            UnimplementedInstruction(state);
        case 0x63: // MOV H,E	1		H <- E
            UnimplementedInstruction(state);
        case 0x64: // MOV H,H	1		H <- H
            UnimplementedInstruction(state);
        case 0x65: // MOV H,L	1		H <- L
            UnimplementedInstruction(state);
        case 0x66: // MOV H,M	1		H <- (HL)
            UnimplementedInstruction(state);
        case 0x67: // MOV H,A	1		H <- A
            UnimplementedInstruction(state);
        case 0x68: // MOV L,B	1		L <- B
            UnimplementedInstruction(state);
        case 0x69: // MOV L,C	1		L <- C
            UnimplementedInstruction(state);
        case 0x6a: // MOV L,D	1		L <- D
            UnimplementedInstruction(state);
        case 0x6b: // MOV L,E	1		L <- E
            UnimplementedInstruction(state);
        case 0x6c: // MOV L,H	1		L <- H
            UnimplementedInstruction(state);
        case 0x6d: // MOV L,L	1		L <- L
            UnimplementedInstruction(state);
        case 0x6e: // MOV L,M	1		L <- (HL)
            UnimplementedInstruction(state);
        case 0x6f: // MOV L,A	1		L <- A
            UnimplementedInstruction(state);
        case 0x70: // MOV M,B	1		(HL) <- B
            UnimplementedInstruction(state);
        case 0x71: // MOV M,C	1		(HL) <- C
            UnimplementedInstruction(state);
        case 0x72: // MOV M,D	1		(HL) <- D
            UnimplementedInstruction(state);
        case 0x73: // MOV M,E	1		(HL) <- E
            UnimplementedInstruction(state);
        case 0x74: // MOV M,H	1		(HL) <- H
            UnimplementedInstruction(state);
        case 0x75: // MOV M,L	1		(HL) <- L
            UnimplementedInstruction(state);
        case 0x76: // HLT	1		special
            UnimplementedInstruction(state);
        case 0x77: // MOV M,A	1		(HL) <- A
            UnimplementedInstruction(state);
        case 0x78: // MOV A,B	1		A <- B
            UnimplementedInstruction(state);
        case 0x79: // MOV A,C	1		A <- C
            UnimplementedInstruction(state);
        case 0x7a: // MOV A,D	1		A <- D
            UnimplementedInstruction(state);
        case 0x7b: // MOV A,E	1		A <- E
            UnimplementedInstruction(state);
        case 0x7c: // MOV A,H	1		A <- H
            UnimplementedInstruction(state);
        case 0x7d: // MOV A,L	1		A <- L
            UnimplementedInstruction(state);
        case 0x7e: // MOV A,M	1		A <- (HL)
            UnimplementedInstruction(state);
        case 0x7f: // MOV A,A	1		A <- A
            UnimplementedInstruction(state);
        case 0x80: // ADD B	1	Z, S, P, CY, AC	A <- A + B
            UnimplementedInstruction(state);
        case 0x81: // ADD C	1	Z, S, P, CY, AC	A <- A + C
            UnimplementedInstruction(state);
        case 0x82: // ADD D	1	Z, S, P, CY, AC	A <- A + D
            UnimplementedInstruction(state);
        case 0x83: // ADD E	1	Z, S, P, CY, AC	A <- A + E
            UnimplementedInstruction(state);
        case 0x84: // ADD H	1	Z, S, P, CY, AC	A <- A + H
            UnimplementedInstruction(state);
        case 0x85: // ADD L	1	Z, S, P, CY, AC	A <- A + L
            UnimplementedInstruction(state);
        case 0x86: // ADD M	1	Z, S, P, CY, AC	A <- A + (HL)
            UnimplementedInstruction(state);
        case 0x87: // ADD A	1	Z, S, P, CY, AC	A <- A + A
            UnimplementedInstruction(state);
        case 0x88: // ADC B	1	Z, S, P, CY, AC	A <- A + B + CY
            UnimplementedInstruction(state);
        case 0x89: // ADC C	1	Z, S, P, CY, AC	A <- A + C + CY
            UnimplementedInstruction(state);
        case 0x8a: // ADC D	1	Z, S, P, CY, AC	A <- A + D + CY
            UnimplementedInstruction(state);
        case 0x8b: // ADC E	1	Z, S, P, CY, AC	A <- A + E + CY
            UnimplementedInstruction(state);
        case 0x8c: // ADC H	1	Z, S, P, CY, AC	A <- A + H + CY
            UnimplementedInstruction(state);
        case 0x8d: // ADC L	1	Z, S, P, CY, AC	A <- A + L + CY
            UnimplementedInstruction(state);
        case 0x8e: // ADC M	1	Z, S, P, CY, AC	A <- A + (HL) + CY
            UnimplementedInstruction(state);
        case 0x8f: // ADC A	1	Z, S, P, CY, AC	A <- A + A + CY
            UnimplementedInstruction(state);
        case 0x90: // SUB B	1	Z, S, P, CY, AC	A <- A - B
            UnimplementedInstruction(state);
        case 0x91: // SUB C	1	Z, S, P, CY, AC	A <- A - C
            UnimplementedInstruction(state);
        case 0x92: // SUB D	1	Z, S, P, CY, AC	A <- A + D
            UnimplementedInstruction(state);
        case 0x93: // SUB E	1	Z, S, P, CY, AC	A <- A - E
            UnimplementedInstruction(state);
        case 0x94: // SUB H	1	Z, S, P, CY, AC	A <- A + H
            UnimplementedInstruction(state);
        case 0x95: // SUB L	1	Z, S, P, CY, AC	A <- A - L
            UnimplementedInstruction(state);
        case 0x96: // SUB M	1	Z, S, P, CY, AC	A <- A + (HL)
            UnimplementedInstruction(state);
        case 0x97: // SUB A	1	Z, S, P, CY, AC	A <- A - A
            UnimplementedInstruction(state);
        case 0x98: // SBB B	1	Z, S, P, CY, AC	A <- A - B - CY
            UnimplementedInstruction(state);
        case 0x99: // SBB C	1	Z, S, P, CY, AC	A <- A - C - CY
            UnimplementedInstruction(state);
        case 0x9a: // SBB D	1	Z, S, P, CY, AC	A <- A - D - CY
            UnimplementedInstruction(state);
        case 0x9b: // SBB E	1	Z, S, P, CY, AC	A <- A - E - CY
            UnimplementedInstruction(state);
        case 0x9c: // SBB H	1	Z, S, P, CY, AC	A <- A - H - CY
            UnimplementedInstruction(state);
        case 0x9d: // SBB L	1	Z, S, P, CY, AC	A <- A - L - CY
            UnimplementedInstruction(state);
        case 0x9e: // SBB M	1	Z, S, P, CY, AC	A <- A - (HL) - CY
            UnimplementedInstruction(state);
        case 0x9f: // SBB A	1	Z, S, P, CY, AC	A <- A - A - CY
            UnimplementedInstruction(state);
        case 0xa0: // ANA B	1	Z, S, P, CY, AC	A <- A & B
            UnimplementedInstruction(state);
        case 0xa1: // ANA C	1	Z, S, P, CY, AC	A <- A & C
            UnimplementedInstruction(state);
        case 0xa2: // ANA D	1	Z, S, P, CY, AC	A <- A & D
            UnimplementedInstruction(state);
        case 0xa3: // ANA E	1	Z, S, P, CY, AC	A <- A & E
            UnimplementedInstruction(state);
        case 0xa4: // ANA H	1	Z, S, P, CY, AC	A <- A & H
            UnimplementedInstruction(state);
        case 0xa5: // ANA L	1	Z, S, P, CY, AC	A <- A & L
            UnimplementedInstruction(state);
        case 0xa6: // ANA M	1	Z, S, P, CY, AC	A <- A & (HL)
            UnimplementedInstruction(state);
        case 0xa7: // ANA A	1	Z, S, P, CY, AC	A <- A & A
            UnimplementedInstruction(state);
        case 0xa8: // XRA B	1	Z, S, P, CY, AC	A <- A ^ B
            UnimplementedInstruction(state);
        case 0xa9: // XRA C	1	Z, S, P, CY, AC	A <- A ^ C
            UnimplementedInstruction(state);
        case 0xaa: // XRA D	1	Z, S, P, CY, AC	A <- A ^ D
            UnimplementedInstruction(state);
        case 0xab: // XRA E	1	Z, S, P, CY, AC	A <- A ^ E
            UnimplementedInstruction(state);
        case 0xac: // XRA H	1	Z, S, P, CY, AC	A <- A ^ H
            UnimplementedInstruction(state);
        case 0xad: // XRA L	1	Z, S, P, CY, AC	A <- A ^ L
            UnimplementedInstruction(state);
        case 0xae: // XRA M	1	Z, S, P, CY, AC	A <- A ^ (HL)
            UnimplementedInstruction(state);
        case 0xaf: // XRA A	1	Z, S, P, CY, AC	A <- A ^ A
            UnimplementedInstruction(state);
        case 0xb0: // ORA B	1	Z, S, P, CY, AC	A <- A | B
            UnimplementedInstruction(state);
        case 0xb1: // ORA C	1	Z, S, P, CY, AC	A <- A | C
            UnimplementedInstruction(state);
        case 0xb2: // ORA D	1	Z, S, P, CY, AC	A <- A | D
            UnimplementedInstruction(state);
        case 0xb3: // ORA E	1	Z, S, P, CY, AC	A <- A | E
            UnimplementedInstruction(state);
        case 0xb4: // ORA H	1	Z, S, P, CY, AC	A <- A | H
            UnimplementedInstruction(state);
        case 0xb5: // ORA L	1	Z, S, P, CY, AC	A <- A | L
            UnimplementedInstruction(state);
        case 0xb6: // ORA M	1	Z, S, P, CY, AC	A <- A | (HL)
            UnimplementedInstruction(state);
        case 0xb7: // ORA A	1	Z, S, P, CY, AC	A <- A | A
            UnimplementedInstruction(state);
        case 0xb8: // CMP B	1	Z, S, P, CY, AC	A - B
            UnimplementedInstruction(state);
        case 0xb9: // CMP C	1	Z, S, P, CY, AC	A - C
            UnimplementedInstruction(state);
        case 0xba: // CMP D	1	Z, S, P, CY, AC	A - D
            UnimplementedInstruction(state);
        case 0xbb: // CMP E	1	Z, S, P, CY, AC	A - E
            UnimplementedInstruction(state);
        case 0xbc: // CMP H	1	Z, S, P, CY, AC	A - H
            UnimplementedInstruction(state);
        case 0xbd: // CMP L	1	Z, S, P, CY, AC	A - L
            UnimplementedInstruction(state);
        case 0xbe: // CMP M	1	Z, S, P, CY, AC	A - (HL)
            UnimplementedInstruction(state);
        case 0xbf: // CMP A	1	Z, S, P, CY, AC	A - A
            UnimplementedInstruction(state);
        case 0xc0: // RNZ	1		if NZ, RET
            UnimplementedInstruction(state);
        case 0xc1: // POP B	1		C <- (sp); B <- (sp+1); sp <-
                   // sp+2
            UnimplementedInstruction(state);
        case 0xc2: // JNZ adr	3		if NZ, PC <- adr
            UnimplementedInstruction(state);
        case 0xc3: // JMP adr	3		PC <= adr
            UnimplementedInstruction(state);
        case 0xc4: // CNZ adr	3		if NZ, CALL adr
            UnimplementedInstruction(state);
        case 0xc5: // PUSH B	1		(sp-2)<-C; (sp-1)<-B; sp <- sp -
                   // 2
            UnimplementedInstruction(state);
        case 0xc6: // ADI D8	2	Z, S, P, CY, AC	A <- A + byte
            UnimplementedInstruction(state);
        case 0xc7: // RST 0	1		CALL $0
            UnimplementedInstruction(state);
        case 0xc8: // RZ	1		if Z, RET
            UnimplementedInstruction(state);
        case 0xc9: // RET	1		PC.lo <- (sp); PC.hi<-(sp+1); SP
                   // <- SP+2
            UnimplementedInstruction(state);
        case 0xca: // JZ adr	3		if Z, PC <- adr
            UnimplementedInstruction(state);
        case 0xcb: // -
            UnimplementedInstruction(state);
        case 0xcc: // CZ adr	3		if Z, CALL adr
            UnimplementedInstruction(state);
        case 0xcd: // CALL adr	3
                   // (SP-1)<-PC.hi;(SP-2)<-PC.lo;SP<-SP-2;PC=adr
            UnimplementedInstruction(state);
        case 0xce: // ACI D8	2	Z, S, P, CY, AC	A <- A + data + CY
            UnimplementedInstruction(state);
        case 0xcf: // RST 1	1		CALL $8
            UnimplementedInstruction(state);
        case 0xd0: // RNC	1		if NCY, RET
            UnimplementedInstruction(state);
        case 0xd1: // POP D	1		E <- (sp); D <- (sp+1); sp <-
                   // sp+2
            UnimplementedInstruction(state);
        case 0xd2: // JNC adr	3		if NCY, PC<-adr
            UnimplementedInstruction(state);
        case 0xd3: // OUT D8	2		special
            UnimplementedInstruction(state);
        case 0xd4: // CNC adr	3		if NCY, CALL adr
            UnimplementedInstruction(state);
        case 0xd5: // PUSH D	1		(sp-2)<-E; (sp-1)<-D; sp <- sp -
                   // 2
            UnimplementedInstruction(state);
        case 0xd6: // SUI D8	2	Z, S, P, CY, AC	A <- A - data
            UnimplementedInstruction(state);
        case 0xd7: // RST 2	1		CALL $10
            UnimplementedInstruction(state);
        case 0xd8: // RC	1		if CY, RET
            UnimplementedInstruction(state);
        case 0xd9: // -
            UnimplementedInstruction(state);
        case 0xda: // JC adr	3		if CY, PC<-adr
            UnimplementedInstruction(state);
        case 0xdb: // IN D8	2		special
            UnimplementedInstruction(state);
        case 0xdc: // CC adr	3		if CY, CALL adr
            UnimplementedInstruction(state);
        case 0xdd: // -
            UnimplementedInstruction(state);
        case 0xde: // SBI D8	2	Z, S, P, CY, AC	A <- A - data - CY
            UnimplementedInstruction(state);
        case 0xdf: // RST 3	1		CALL $18
            UnimplementedInstruction(state);
        case 0xe0: // RPO	1		if PO, RET
            UnimplementedInstruction(state);
        case 0xe1: // POP H	1		L <- (sp); H <- (sp+1); sp <-
                   // sp+2
            UnimplementedInstruction(state);
        case 0xe2: // JPO adr	3		if PO, PC <- adr
            UnimplementedInstruction(state);
        case 0xe3: // XTHL	1		L <-> (SP); H <-> (SP+1)
            UnimplementedInstruction(state);
        case 0xe4: // CPO adr	3		if PO, CALL adr
            UnimplementedInstruction(state);
        case 0xe5: // PUSH H	1		(sp-2)<-L; (sp-1)<-H; sp <- sp -
                   // 2
            UnimplementedInstruction(state);
        case 0xe6: // ANI D8	2	Z, S, P, CY, AC	A <- A & data
            UnimplementedInstruction(state);
        case 0xe7: // RST 4	1		CALL $20
            UnimplementedInstruction(state);
        case 0xe8: // RPE	1		if PE, RET
            UnimplementedInstruction(state);
        case 0xe9: // PCHL	1		PC.hi <- H; PC.lo <- L
            UnimplementedInstruction(state);
        case 0xea: // JPE adr	3		if PE, PC <- adr
            UnimplementedInstruction(state);
        case 0xeb: // XCHG	1		H <-> D; L <-> E
            UnimplementedInstruction(state);
        case 0xec: // CPE adr	3		if PE, CALL adr
            UnimplementedInstruction(state);
        case 0xed: // -
            UnimplementedInstruction(state);
        case 0xee: // XRI D8	2	Z, S, P, CY, AC	A <- A ^ data
            UnimplementedInstruction(state);
        case 0xef: // RST 5	1		CALL $28
            UnimplementedInstruction(state);
        case 0xf0: // RP	1		if P, RET
            UnimplementedInstruction(state);
        case 0xf1: // POP PSW	1		flags <- (sp); A <- (sp+1); sp
                   // <- sp+2
            UnimplementedInstruction(state);
        case 0xf2: // JP adr	3		if P=1 PC <- adr
            UnimplementedInstruction(state);
        case 0xf3: // DI	1		special
            UnimplementedInstruction(state);
        case 0xf4: // CP adr	3		if P, PC <- adr
            UnimplementedInstruction(state);
        case 0xf5: // PUSH PSW	1		(sp-2)<-flags; (sp-1)<-A; sp <-
                   // sp - 2
            UnimplementedInstruction(state);
        case 0xf6: // ORI D8	2	Z, S, P, CY, AC	A <- A | data
            UnimplementedInstruction(state);
        case 0xf7: // RST 6	1		CALL $30
            UnimplementedInstruction(state);
        case 0xf8: // RM	1		if M, RET
            UnimplementedInstruction(state);
        case 0xf9: // SPHL	1		SP=HL
            UnimplementedInstruction(state);
        case 0xfa: // JM adr	3		if M, PC <- adr
            UnimplementedInstruction(state);
        case 0xfb: // EI	1		special
            UnimplementedInstruction(state);
        case 0xfc: // CM adr	3		if M, CALL adr
            UnimplementedInstruction(state);
        case 0xfd: // -
            UnimplementedInstruction(state);
        case 0xfe: // CPI D8	2	Z, S, P, CY, AC	A - data
            UnimplementedInstruction(state);
        case 0xff: // RST 7	1		CALL $38
            UnimplementedInstruction(state);
    }
    state->pc += 1;
}

void Emulate(State8080 *state) {
    while (true) {
        ExecuteNextInstruction8080(state);
    }
}

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        printf("error: Couldn't open %s\n", argv[1]);
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    struct State8080 *state = (State8080 *) malloc(sizeof(State8080));
    state->memory = malloc(fsize);

    fread(state->memory, 1, fsize, f);
    fclose(f);

    Emulate(state);

    return 0;
}
