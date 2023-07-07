//#include "encryption.h"
//#include <qdebug.h>
//#include "cryptlib.h"
//#include "rijndael.h"
//#include "modes.h"
//#include "files.h"
//#include "osrng.h"
//#include "hex.h"

//using namespace crypt;
//using namespace CryptoPP;

//std::string crypt::encrypt(std::string plaintext) {
//    std::string output;

//    //AutoSeededRandomPool prng;
//    //HexEncoder encoder(new FileSink(std::cout));

//    //SecByteBlock key(AES::DEFAULT_KEYLENGTH);
//    //SecByteBlock iv(AES::BLOCKSIZE);

//    //prng.GenerateBlock(key, key.size());
//    //prng.GenerateBlock(iv, iv.size());

//    /*try
//       {
//           CBC_Mode< AES >::Encryption e;
//           e.SetKeyWithIV(key, key.size(), iv);

//           StringSource s(plaintext, true,
//               new StreamTransformationFilter(e,
//                   new StringSink(output)
//               ) // StreamTransformationFilter
//           ); // StringSource
//       }
//       catch(const Exception& e)
//       {
//           qDebug() << e.what();
//           exit(1);
//       }*/

//    return output;
//}

//std::string crypt::decrypt(std::string cipher) {
//    std::string output;

//    //AutoSeededRandomPool prng;
//    //HexEncoder encoder(new FileSink(std::cout));

//    //SecByteBlock key(AES::DEFAULT_KEYLENGTH);
//    //SecByteBlock iv(AES::BLOCKSIZE);

//    //prng.GenerateBlock(key, key.size());
//    //prng.GenerateBlock(iv, iv.size());

//    /*try
//    {
//        CBC_Mode< AES >::Decryption d;
//        d.SetKeyWithIV(key, key.size(), iv);

//        StringSource s(cipher, true,
//            new StreamTransformationFilter(d,
//                new StringSink(output)
//            ) // StreamTransformationFilter
//        ); // StringSource
//    }
//    catch(const Exception& e)
//    {
//        qDebug() << e.what();
//        exit(1);
//    }*/

//    return output;
//}
