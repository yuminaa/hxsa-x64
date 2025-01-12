// isa/include/instructions.h
#pragma once
#include <cstdint>
#include "opcodes.h"

namespace hxsa
{
    // Instruction format:
    // 63                  52 51    47 46    42 41    37 36   34 33                     0
    // +---------------------+--------+--------+--------+-------+------------------------+
    // |       OpCode        |   Rd   |   Rn   |   Rm   | Mode  |       Extended        |
    // +---------------------+--------+--------+--------+-------+------------------------+
    //         12 bits        5 bits   5 bits   5 bits  3 bits        34 bits

    struct Instruction
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

        [[nodiscard]] constexpr uint64_t memory_offset() const
        {
            return raw & 0xFFFFFFFF;
        }

        [[nodiscard]] constexpr uint8_t shift_amount() const
        {
            return (raw >> 26) & 0x3F;
        }
    };

    namespace builder
    {
        constexpr uint64_t r_type(Opcode op, const uint8_t rd, const uint8_t rn, const uint8_t rm)
        {
            return (static_cast<uint64_t>(op) << 52) |
                   (static_cast<uint64_t>(rd) << 47) |
                   (static_cast<uint64_t>(rn) << 42) |
                   (static_cast<uint64_t>(rm) << 37);
        }

        constexpr uint64_t i_type(Opcode op, const uint8_t rd, const uint8_t rn, const uint64_t imm)
        {
            return (static_cast<uint64_t>(op) << 52) |
                   (static_cast<uint64_t>(rd) << 47) |
                   (static_cast<uint64_t>(rn) << 42) |
                   (imm & 0x3FFFFFFFFFF);
        }

        constexpr uint64_t b_type(Opcode op, const uint64_t offset)
        {
            return (static_cast<uint64_t>(op) << 52) |
                   (offset & 0xFFFFFFFFFFFF);
        }

        constexpr uint64_t m_type(Opcode op, const uint8_t rd, const uint8_t rn, const uint32_t offset)
        {
            return (static_cast<uint64_t>(op) << 52) |
                   (static_cast<uint64_t>(rd) << 47) |
                   (static_cast<uint64_t>(rn) << 42) |
                   (offset & 0xFFFFFFFF);
        }
    }
}
