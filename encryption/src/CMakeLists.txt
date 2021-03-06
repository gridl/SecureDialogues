project(encryption)


set(ENCRYPTION_SOURCES
   asymetrical/asymetricalkeystore.cpp
   asymetrical/asymetricalkeygenerator.cpp
   asymetrical/remotepeeroperations.cpp
   asymetrical/localpeeroperations.cpp

   serialization/fileasynckeyserializer.cpp
   serialization/serializations.cpp

   symetrical/aescipher.cpp
   symetrical/aeskeygenerator.cpp
   symetrical/symetricalsystemfactories.cpp
)


set(ENCRYPTION_HEADERS
    interfaces/encryptor.h
    interfaces/decryptor.h
    interfaces/asymetricalkeyserializer.h
    interfaces/signer.h
    interfaces/signaturechecker.h
    interfaces/generator.h
    interfaces/symetricalcipher.h

    asymetrical/asymetricalkeystore.h
    asymetrical/asymetricalkeygenerator.h
    asymetrical/remotepeeroperations.h
    asymetrical/localpeeroperations.h

    serialization/fileasynckeyserializer.h
    serialization/serializations.h

    symetrical/aescipher.h
    symetrical/aeskeystruct.h
    symetrical/aeskeygenerator.h
    symetrical/symetricalsystemfactories.h


)


add_library(encryption STATIC ${ENCRYPTION_SOURCES} ${ENCRYPTION_HEADERS})

target_include_directories(encryption PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${MCRYPTO_INCLUDE_DIR})
target_link_libraries( encryption cryptopp-static utils)
