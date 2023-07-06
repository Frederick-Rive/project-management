#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <iostream>
#include <vector>
#include <string>
#include <cryptlib.h>
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

using namespace CryptoPP;

SecByteBlock key(AES::DEFAULT_KEYLENGTH);

std::string EncryptStandard(std::string plaintext) {
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
}

#endif // ENCRYPTION_H
