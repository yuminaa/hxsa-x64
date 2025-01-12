#pragma once
#include "types.h"

namespace hxsa
{
    enum class Opcode : uint16_t
    {
        // Data Movement
        MOV_REG = PATTERN_R_TYPE | 0x100,    // Move register
        MOV_IMM = PATTERN_I_TYPE | 0x100,    // Move immediate
        MOVZ    = PATTERN_I_TYPE | 0x101,    // Move with zero
        MOVK    = PATTERN_I_TYPE | 0x102,    // Move keeping bits
        
        // Arithmetic
        ADD_REG = PATTERN_R_TYPE | 0x200,    // Add registers
        ADD_IMM = PATTERN_I_TYPE | 0x200,    // Add immediate
        SUB_REG = PATTERN_R_TYPE | 0x201,    // Subtract registers
        SUB_IMM = PATTERN_I_TYPE | 0x201,    // Subtract immediate
        MUL     = PATTERN_R_TYPE | 0x202,    // Multiply
        SDIV    = PATTERN_R_TYPE | 0x203,    // Signed divide
        UDIV    = PATTERN_R_TYPE | 0x204,    // Unsigned divide
        
        // Logical
        AND_REG = PATTERN_R_TYPE | 0x300,    // AND registers
        AND_IMM = PATTERN_I_TYPE | 0x300,    // AND immediate
        ORR_REG = PATTERN_R_TYPE | 0x301,    // OR registers
        ORR_IMM = PATTERN_I_TYPE | 0x301,    // OR immediate
        EOR_REG = PATTERN_R_TYPE | 0x302,    // XOR registers
        EOR_IMM = PATTERN_I_TYPE | 0x302,    // XOR immediate
        
        // Shifts
        LSL_REG = PATTERN_R_TYPE | 0x400,    // Logical shift left by register
        LSL_IMM = PATTERN_I_TYPE | 0x400,    // Logical shift left by immediate
        LSR_REG = PATTERN_R_TYPE | 0x401,    // Logical shift right by register
        LSR_IMM = PATTERN_I_TYPE | 0x401,    // Logical shift right by immediate
        ASR_REG = PATTERN_R_TYPE | 0x402,    // Arithmetic shift right by register
        ASR_IMM = PATTERN_I_TYPE | 0x402,    // Arithmetic shift right by immediate
        
        // Comparison
        CMP_REG = PATTERN_R_TYPE | 0x500,    // Compare registers
        CMP_IMM = PATTERN_I_TYPE | 0x500,    // Compare immediate
        TST_REG = PATTERN_R_TYPE | 0x501,    // Test registers
        TST_IMM = PATTERN_I_TYPE | 0x501,    // Test immediate
        
        // Branches
        B       = PATTERN_B_TYPE | 0x600,    // Branch
        BL      = PATTERN_B_TYPE | 0x601,    // Branch and link
        BR      = PATTERN_R_TYPE | 0x602,    // Branch to register
        BLR     = PATTERN_R_TYPE | 0x603,    // Branch and link to register
        RET     = PATTERN_R_TYPE | 0x604,    // Return
        
        // Conditional Branches
        B_COND  = PATTERN_B_TYPE | 0x610,    // Conditional branch
        CBZ     = PATTERN_B_TYPE | 0x611,    // Compare and branch if zero
        CBNZ    = PATTERN_B_TYPE | 0x612,    // Compare and branch if not zero
        TBZ     = PATTERN_B_TYPE | 0x613,    // Test bit and branch if zero
        TBNZ    = PATTERN_B_TYPE | 0x614,    // Test bit and branch if not zero
        
        // Memory
        LDR     = PATTERN_M_TYPE | 0x700,    // Load register
        STR     = PATTERN_M_TYPE | 0x701,    // Store register
        LDRB    = PATTERN_M_TYPE | 0x702,    // Load byte
        STRB    = PATTERN_M_TYPE | 0x703,    // Store byte
        LDRH    = PATTERN_M_TYPE | 0x704,    // Load halfword
        STRH    = PATTERN_M_TYPE | 0x705,    // Store halfword
        LDRSW   = PATTERN_M_TYPE | 0x706,    // Load signed word
        
        // Stack
        PUSH    = PATTERN_M_TYPE | 0x800,    // Push registers
        POP     = PATTERN_M_TYPE | 0x801,    // Pop registers
        
        // System
        SVC     = PATTERN_I_TYPE | 0x900,    // Supervisor call
        HLT     = PATTERN_R_TYPE | 0x901,    // Halt
        NOP     = PATTERN_R_TYPE | 0x902,    // No operation
    };

    [[nodiscard]] constexpr bool is_r_type(Opcode op)
    {
        return (static_cast<uint16_t>(op) & TYPE_MASK) == PATTERN_R_TYPE;
    }

    [[nodiscard]] constexpr bool is_i_type(Opcode op)
    {
        return (static_cast<uint16_t>(op) & TYPE_MASK) == PATTERN_I_TYPE;
    }

    [[nodiscard]] constexpr bool is_b_type(Opcode op)
    {
        return (static_cast<uint16_t>(op) & TYPE_MASK) == PATTERN_B_TYPE;
    }

    [[nodiscard]] constexpr bool is_m_type(Opcode op)
    {
        return (static_cast<uint16_t>(op) & TYPE_MASK) == PATTERN_M_TYPE;
    }
} // namespace hxsa