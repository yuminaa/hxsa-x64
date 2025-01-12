# HybridX ISA - Complete Instruction & Register Specification

## 1. Register Definitions

### 1.1 General Purpose Registers (64-bit)

- x0: Zero register (hardwired to 0, writes ignored)
- x1: First return value
- x2: Second return value
- x3-x7: Parameter passing registers
- x8-x15: Caller-saved registers
- x16-x17: Intra-procedure-call registers
- x18: Platform register (reserved)
- x19-x27: Callee-saved registers
- x28: Global pointer
- x29: Frame pointer
- x30: Link register
- x31: Stack pointer

### 1.2 Vector/SIMD Registers (512-bit)

- v0-v7: Parameter passing and return values
- v8-v15: Caller-saved
- v16-v31: Callee-saved

### 1.3 System Registers

- CPSR: Current Program Status Register
    - N: Negative flag [31]
    - Z: Zero flag [30]
    - C: Carry flag [29]
    - V: Overflow flag [28]
    - Q: Saturation flag [27]
    - IT[7:0]: If-Then execution state [15:8]
    - E: Endianness state [7]
    - M[4:0]: Processor mode [4:0]

## 2. Instruction Formats

### 2.1 Base Instruction Format

```
63                  52 51    47 46    42 41    37 36   34 33                     0
+---------------------+--------+--------+--------+-------+------------------------+
|       OpCode        |   Rd   |   Rn   |   Rm   | Mode  |       Extended        |
+---------------------+--------+--------+--------+-------+------------------------+
```

### 2.2 Format Types

1. R-Type (Register)

```
OpCode[12] | Rd[5] | Rn[5] | Rm[5] | Mode[3] | ShiftType[2] | ShiftAmount[6] | Reserved[26]
```

2. I-Type (Immediate)

```
OpCode[12] | Rd[5] | Rn[5] | Immediate[42]
```

3. B-Type (Branch)

```
OpCode[12] | Cond[4] | Offset[48]
```

4. M-Type (Memory)

```
OpCode[12] | Rd[5] | Rn[5] | Offset[16] | Mode[3] | Scale[2] | Reserved[21]
```

5. V-Type (Vector)

```
OpCode[12] | Vd[5] | Vn[5] | Vm[5] | Mode[3] | VectorOp[8] | Reserved[26]
```

## 3. Instruction Set

### 3.1 Data Movement Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
MOV         0x100   R/I     Move register or immediate
MOVZ        0x101   I       Move immediate zero-extended
MOVK        0x102   I       Move immediate keeping bits
MOVS        0x103   R/I     Move and set flags
MVN         0x104   R       Move negative register
```

### 3.2 Arithmetic Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
ADD         0x200   R/I     Add
SUB         0x201   R/I     Subtract
MUL         0x202   R       Multiply
DIV         0x203   R       Divide
SDIV        0x204   R       Signed divide
UDIV        0x205   R       Unsigned divide
ADC         0x206   R       Add with carry
SBC         0x207   R       Subtract with carry
MADD        0x208   R       Multiply-add
MSUB        0x209   R       Multiply-subtract
```

### 3.3 Logical Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
AND         0x300   R/I     Logical AND
ORR         0x301   R/I     Logical OR
EOR         0x302   R/I     Logical XOR
LSL         0x303   R/I     Logical shift left
LSR         0x304   R/I     Logical shift right
ASR         0x305   R/I     Arithmetic shift right
ROR         0x306   R/I     Rotate right
BICS        0x307   R       Bit clear and set flags
```

### 3.4 Comparison Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
CMP         0x400   R/I     Compare
CMN         0x401   R/I     Compare negative
TST         0x402   R/I     Test bits
```

### 3.5 Branch Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
B           0x500   B       Branch
BL          0x501   B       Branch and link
BLR         0x502   R       Branch and link to register
RET         0x503   R       Return
B.cond      0x504   B       Conditional branch
CBZ         0x505   B       Compare and branch if zero
CBNZ        0x506   B       Compare and branch if not zero
TBZ         0x507   B       Test bit and branch if zero
TBNZ        0x508   B       Test bit and branch if not zero
```

### 3.6 Memory Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
LDR         0x600   M       Load register
STR         0x601   M       Store register
LDUR        0x602   M       Load unscaled
STUR        0x603   M       Store unscaled
LDP         0x604   M       Load pair
STP         0x605   M       Store pair
LDXR        0x606   M       Load exclusive
STXR        0x607   M       Store exclusive
```

### 3.7 Vector/SIMD Instructions

```
Mnemonic    OpCode  Format  Description
--------------------------------------------
VADD        0x700   V       Vector add
VSUB        0x701   V       Vector subtract
VMUL        0x702   V       Vector multiply
VDIV        0x703   V       Vector divide
VAND        0x704   V       Vector AND
VORR        0x705   V       Vector OR
VEOR        0x706   V       Vector XOR
VFMA        0x707   V       Vector fused multiply-add
```

## 4. Addressing Modes

### 4.1 Memory Addressing Modes

1. Base Register: [Rn]
2. Base + Immediate: [Rn, #imm]
3. Base + Register: [Rn, Rm]
4. Base + Scaled Register: [Rn, Rm, LSL #shift]
5. Pre-indexed: [Rn, #imm]!
6. Post-indexed: [Rn], #imm
7. PC-relative: [PC, #imm]

### 4.2 Vector Element Addressing

1. Full vector: Vn
2. Element: Vn[index]
3. Element range: Vn[start:end]

## 5. Instruction Encoding Examples

### 5.1 Register Add

```
ADD x1, x2, x3

63      52 51  47 46  42 41  37 36 34 33                  0
+--------+------+------+------+-----+---------------------+
| 0x200  | 0x01 | 0x02 | 0x03 | 000 |         0          |
+--------+------+------+------+-----+---------------------+
```

### 5.2 Immediate Load

```
MOVZ x1, #1234

63      52 51  47 46  42 41                               0
+--------+------+------+----------------------------------+
| 0x101  | 0x01 | 0x00 |             1234                 |
+--------+------+------+----------------------------------+
```

### 5.3 Conditional Branch

```
B.EQ label

63      52 51   48 47                                     0
+--------+-------+----------------------------------------+
| 0x504  | 0x0   |              offset                    |
+--------+-------+----------------------------------------+
```

## 6. Instruction Binary Layouts

Each instruction type's binary layout is fully specified. For implementation reference:

### 6.1 Binary Layout Structures

```c
struct RType {
    uint64_t opcode : 12;
    uint64_t rd : 5;
    uint64_t rn : 5;
    uint64_t rm : 5;
    uint64_t mode : 3;
    uint64_t shift_type : 2;
    uint64_t shift_amount : 6;
    uint64_t reserved : 26;
};

struct IType {
    uint64_t opcode : 12;
    uint64_t rd : 5;
    uint64_t rn : 5;
    uint64_t immediate : 42;
};

struct BType {
    uint64_t opcode : 12;
    uint64_t cond : 4;
    uint64_t offset : 48;
};

struct MType {
    uint64_t opcode : 12;
    uint64_t rd : 5;
    uint64_t rn : 5;
    uint64_t offset : 16;
    uint64_t mode : 3;
    uint64_t scale : 2;
    uint64_t reserved : 21;
};

struct VType {
    uint64_t opcode : 12;
    uint64_t vd : 5;
    uint64_t vn : 5;
    uint64_t vm : 5;
    uint64_t mode : 3;
    uint64_t vector_op : 8;
    uint64_t reserved : 26;
};
```