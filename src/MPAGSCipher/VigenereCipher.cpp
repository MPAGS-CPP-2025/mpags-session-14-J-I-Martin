#include "VigenereCipher.hpp"
#include "Alphabet.hpp"

#include <algorithm>
#include <string>

/**
 * \file VigenereCipher.cpp
 * \brief Contains the implementation of the VigenereCipher class
 */

VigenereCipher::VigenereCipher(const std::string& key)
{
    this->setKey(key);
}

void VigenereCipher::setKey(const std::string& key)
{
    // Store the key
    key_ = key;
    // Make sure the key is uppercase
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                   ::toupper);
    // Remove non-alphabet characters
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),
                              [](char c) { return !std::isalpha(c); }),
               std::end(key_));
    // Check if the key is empty and replace with default if so
    if (key.empty()) {
        key_ = "A";
    }
    // loop over the key
    for (std::size_t i{0}; i < key_.size(); ++i) {
        char c{key_[i]};
        // Find the letter position in the alphabet
        std::size_t charPos{Alphabet::alphabet.find(c)};
        // Create a CaesarCipher using this position as a key
        CaesarCipher keyCipher{CaesarCipher(charPos)};
        // Insert a std::pair of the letter and CaesarCipher into the lookup
        std::pair<char, CaesarCipher> mapPair{c, keyCipher};
        charLookup_.insert(mapPair);
    }
}

std::string VigenereCipher::applyCipher(const std::string& inputText,
                                        const CipherMode cipherMode) const
{
    std::string outputText{""};
    // For each letter in input:
    for (std::size_t i{0}; i < inputText.size(); ++i) {
        std::string charAsString{inputText[i]};
        // Find the corresponding letter in the key
        char keyChar{key_[i % key_.size()]};
        // Find the Caesar cipher from the lookup
        CaesarCipher charCipher{charLookup_.find(keyChar)->second};
        // Run the (de)encryption
        std::string newChar{charCipher.applyCipher(charAsString, cipherMode)};
        // Add the result to the output
        outputText += newChar;
    }
    return outputText;
}
