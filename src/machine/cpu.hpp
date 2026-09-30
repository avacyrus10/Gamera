#include <array>
#include <cstdint>

class CPU{

    private:
            std::array<uint32_t,32> registers;
            uint32_t pc;
    public:

            CPU();
            uint32_t getPC() const;
            void setPC(uint32_t value);

            uint32_t getRegister(std::size_t index) const;
            void setRegister(std::size_t index, uint32_t value);




};