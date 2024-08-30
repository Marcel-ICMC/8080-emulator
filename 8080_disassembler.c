#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *GetCondition(unsigned char condition) {
    switch (condition) {
        case 0x00:
            return "NZ";
        case 0x01:
            return "Z";
        case 0x02:
            return "NC";
        case 0x03:
            return "C";
        case 0x04:
            return "PO";
        case 0x05:
            return "PE";
        case 0x06:
            return "P";
        case 0x07:
            return "M";
    }

    return "\0";
}

char GetRegister(unsigned char reg) {
    switch (reg) {
        case 0x00:
            return 'B';
        case 0x01:
            return 'C';
        case 0x02:
            return 'D';
        case 0x03:
            return 'E';
        case 0x04:
            return 'H';
        case 0x05:
            return 'L';
        case 0x06:
            return 'M';
        case 0x07:
            return 'A';
    }
    return '\0';
}

char *GetRegisterPair(unsigned char reg) {
    switch (reg) {
        case 0x00:
            return "B-C";
        case 0x01:
            return "D-E";
        case 0x02:
            return "H-L";
        case 0x03:
            return "PSW";
    }

    return "\0";
}

int Disassemble8080Op(unsigned char *codebuffer, int pc) {
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;

    // printf("%04x ", pc);

    if ((*code & 0xc0) == 0x40) {
        char dest_reg = GetRegister((*code & 0x38) >> 3);
        char source_reg = GetRegister(*code & 0x07);

        printf("MOV    %c,%c", dest_reg, source_reg);

        if (dest_reg == 'M' || source_reg == 'M') {
            return 2;
        }
        return 1;
    }

    char reg = GetRegister(*code & 0x07);

    bool f8_exp = false;
    switch (*code & 0xf8) {
        case 0x80:
            printf("ADD    %c", reg);
            f8_exp = true;
            break;
        case 0x90:
            printf("SUB    %c", reg);
            f8_exp = true;
            break;
        case 0x98:
            printf("SBB    %c", reg);
            f8_exp = true;
            break;
        case 0xa0:
            printf("ANA    %c", reg);
            f8_exp = true;
            break;
        case 0xa8:
            printf("XRA    %c", reg);
            f8_exp = true;
            break;
        case 0xb0:
            printf("ORA    %c", reg);
            f8_exp = true;
            break;
        case 0xb8:
            printf("CMP    %c", reg);
            f8_exp = true;
            break;
    }

    if (f8_exp) {
        if (reg == 'M')
            return 2;
        return 1;
    }
    char *condition = GetCondition(*code & 0x38);
    switch (*code & 0xc7) {
        case 0xc2:
            printf("J%s", condition);
            return 3;
        case 0x84:
            printf("C%s", condition);
            return 3;
    }

    char *reg_pair = GetRegisterPair((*code & 0x30) >> 4);
    switch (*code & 0xCF) {
        case 0xC1:
            printf("POP %s", reg_pair);
            return opbytes;
        case 0xC5:
            printf("PUSH %s", reg_pair);
            return opbytes;
    }

    switch (*code) {
        case 0x00:
            printf("NOP");
            break;
        case 0x01:
            printf("LXI    B,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x02:
            printf("STAX   B");
            break;
        case 0x03:
            printf("INX    B");
            break;
        case 0x04:
            printf("INR    B");
            break;
        case 0x05:
            printf("DCR    B");
            break;
        case 0x06:
            printf("MVI    B,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x07:
            printf("RLC");
            break;
        case 0x08:
            printf("NOP");
            break;
        case 0x09:
            printf("DAD    B");
            break;
        case 0x0a:
            printf("LDAX   B");
            break;
        case 0x0b:
            printf("DCX    B");
            break;
        case 0x0c:
            printf("INR    C");
            break;
        case 0x0d:
            printf("DCR    C");
            break;
        case 0x0e:
            printf("MVI    C,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x0f:
            printf("RRC");
            break;
        case 0x10:
            printf("NOP");
            break;
        case 0x11:
            printf("LXI    D,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x12:
            printf("STAX   D");
            break;
        case 0x13:
            printf("INX    D");
            break;
        case 0x14:
            printf("INR    D");
            break;
        case 0x15:
            printf("DCR    D");
            break;
        case 0x16:
            printf("MVI    D,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x17:
            printf("RAL");
            break;
        case 0x18:
            printf("NOP");
            break;
        case 0x19:
            printf("DAD    D");
            break;
        case 0x1a:
            printf("LDAX   D");
            break;
        case 0x1b:
            printf("DCX    D");
            break;
        case 0x1c:
            printf("INR    E");
            break;
        case 0x1d:
            printf("DCR    E");
            break;
        case 0x1e:
            printf("MVI    E,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x1f:
            printf("RAR");
            break;
        case 0x20:
            printf("NOP");
            break;
        case 0x21:
            printf("LXI    H,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x22:
            printf("SHLD   H,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x23:
            printf("INX    H");
            break;
        case 0x24:
            printf("INR    H");
            break;
        case 0x25:
            printf("DCR    H");
            break;
        case 0x26:
            printf("MVI    H,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x27:
            printf("DAA");
            break;
        case 0x28:
            printf("NOP");
            break;
        case 0x29:
            printf("DAD    H");
            break;
        case 0x2a:
            printf("LHLD adr,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x2b:
            printf("DCX    H");
            break;
        case 0x2c:
            printf("INR    L");
            break;
        case 0x2d:
            printf("DCR    L");
            break;
        case 0x2e:
            printf("MVI    L,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x2f:
            printf("CMA");
            break;
        case 0x30:
            printf("NOP");
            break;
        case 0x31:
            printf("LXI   SP,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x32:
            printf("STA addr,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x33:
            printf("INX   SP");
            break;
        case 0x34:
            printf("INR    M");
            break;
        case 0x35:
            printf("DCR    M");
            break;
        case 0x36:
            printf("MVI    M,#$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x37:
            printf("STC");
            break;
        case 0x38:
            printf("NOP");
            break;
        case 0x39:
            printf("DAD   SP");
            break;
        case 0x3a:
            printf("LDA  adr,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x3b:
            printf("DCX   SP");
            break;
        case 0x3c:
            printf("INR    A");
            break;
        case 0x3d:
            printf("DCR    A");
            break;
        case 0x3e:
            printf("MVI    A,#0x%02x", code[1]);
            opbytes = 2;
            break;
        case 0x3f:
            printf("CMC");
            break;
        case 0xc0:
            printf("RNZ");
            break;
        case 0xc3:
            printf("JMP    $%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x76:
            printf("HTL");
            break;
            /* ........ */
    }

    return opbytes;
}

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        printf("error: Couldn't open %s\n", argv[1]);
        exit(1);
    }
    // Get the file size and read it into a memory buffer
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    unsigned char *buffer = malloc(fsize);

    fread(buffer, 1, fsize, f);
    fclose(f);

    int pc = 0;
    while (pc < fsize) {
        pc += Disassemble8080Op(buffer, pc);
        printf("\n");
    }
    return 0;
}
