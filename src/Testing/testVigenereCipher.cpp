//! Unit Tests for MPAGSCipher CaesarCipher Class
#include "gtest/gtest.h"

#include "VigenereCipher.hpp"

TEST(VigenereCipher, Encrypt)
{
    VigenereCipher cc{"hello"};
    EXPECT_EQ(
        cc.applyCipher("BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING",
                       CipherMode::Encrypt),
        "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA");
}