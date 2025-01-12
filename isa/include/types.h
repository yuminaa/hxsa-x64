#pragma once
#include <cstdint>

namespace hxsa
{
    struct InstructionBits
    {
        uint64_t raw;

        [[nodiscard]] constexpr uint16_t opcode() const
        {
            return (raw >> 52) & 0xFFF;
        }

        [[nodiscard]] constexpr uint8_t rd() const
        {
            return (raw >> 47) & 0x1F;
        }

        [[nodiscard]] constexpr uint8_t rn() const
        {
            return (raw >> 42) & 0x1F;
        }

        [[nodiscard]] constexpr uint8_t rm() const
        {
            return (raw >> 37) & 0x1F;
        }

        [[nodiscard]] constexpr uint8_t mode() const
        {
            return (raw >> 34) & 0x7;
        }

        [[nodiscard]] constexpr uint64_t immediate() const
        {
            return raw & 0x3FFFFFFFFFF;
        }

        [[nodiscard]] constexpr uint64_t branch_offset() const
        {
            return raw & 0xFFFFFFFFFFFF;
        }

        [[nodiscard]] constexpr uint8_t shift_type() const
        {
            return (raw >> 32) & 0x3;
        }

        [[nodiscard]] constexpr uint8_t shift_amount() const
        {
            return (raw >> 26) & 0x3F;
        }
    };

    // Instruction patterns
    constexpr uint16_t PATTERN_R_TYPE = 0b0000'0000'0000;
    constexpr uint16_t PATTERN_I_TYPE = 0b0100'0000'0000;
    constexpr uint16_t PATTERN_B_TYPE = 0b1000'0000'0000;
    constexpr uint16_t PATTERN_M_TYPE = 0b1100'0000'0000;

    constexpr uint16_t TYPE_MASK = 0b1100'0000'0000;
    constexpr uint16_t OPCODE_MASK = 0b0011'1111'1111;

    // Register definitions
    enum class Register : uint8_t
    {
        X0 = 0,   // Zero register (hardwired)
        X1 = 1,   // First return value
        X2 = 2,   // Second return value
        X3 = 3,   // First argument
        X4 = 4,   // Second argument
        X5 = 5,   // Third argument
        X6 = 6,   // Fourth argument
        X7 = 7,   // Fifth argument
        X8 = 8,   // Sixth argument
        X9 = 9,   // Temporary
        X10 = 10, // Temporary
        X11 = 11, // Temporary
        X12 = 12, // Temporary
        X13 = 13, // Temporary
        X14 = 14, // Temporary
        X15 = 15, // Temporary
        X16 = 16, // IP0 - Intra-procedure scratch
        X17 = 17, // IP1 - Intra-procedure scratch
        X18 = 18, // Platform register
        X19 = 19, // Callee-saved
        X20 = 20, // Callee-saved
        X21 = 21, // Callee-saved
        X22 = 22, // Callee-saved
        X23 = 23, // Callee-saved
        X24 = 24, // Callee-saved
        X25 = 25, // Callee-saved
        X26 = 26, // Callee-saved
        X27 = 27, // Callee-saved
        X28 = 28, // Callee-saved
        FP = 29,  // Frame pointer
        LR = 30,  // Link register
        SP = 31   // Stack pointer
    };

    struct StatusFlags
    {
        uint32_t N: 1; // Negative
        uint32_t Z: 1; // Zero
        uint32_t C: 1; // Carry
        uint32_t V: 1; // Overflow
        uint32_t I: 1; // IRQ disable
        uint32_t F: 1; // FIQ disable
        uint32_t T: 1; // Thumb state
        uint32_t M: 5; // Mode bits
        uint32_t reserved: 20;
    };

    enum class ShiftType : uint8_t
    {
        LSL = 0, // Logical shift left
        LSR = 1, // Logical shift right
        ASR = 2, // Arithmetic shift right
        ROR = 3  // Rotate right
    };

    enum class MemoryMode : uint8_t
    {
        OFFSET = 0,     // [base + offset]
        PRE_INDEX = 1,  // [base + offset]!
        POST_INDEX = 2, // [base], offset
        REGISTER = 3,   // [base, Rm{, extend {#amount}}]
        SCALED = 4,     // [base, Rm, LSL #amount]
    };

    enum class Condition : uint8_t
    {
        EQ = 0x0, // Equal
        NE = 0x1, // Not equal
        CS = 0x2, // Carry set
        CC = 0x3, // Carry clear
        MI = 0x4, // Minus/negative
        PL = 0x5, // Plus/positive or zero
        VS = 0x6, // Overflow
        VC = 0x7, // No overflow
        HI = 0x8, // Unsigned higher
        LS = 0x9, // Unsigned lower or same
        GE = 0xA, // Signed greater than or equal
        LT = 0xB, // Signed less than
        GT = 0xC, // Signed greater than
        LE = 0xD, // Signed less than or equal
        AL = 0xE, // Always
        NV = 0xF  // Never
    };
}
