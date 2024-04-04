#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <string>

class Steg{

    static void encode(std::string filename, std::string message);

    static std::string decode(std::string filename);
};

#endif // STEGANOGRAPHY_H
