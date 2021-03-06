cmake_minimum_required(VERSION 3.8)
project(SecureDialogues)

find_package(Git REQUIRED)


SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all"
    )

SET (DOCUMENTS_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/documents
        CACHE PATH
        "Single Directory for all"
    )


set(CMAKE_AUTOUIC ON)
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)


set(MCRYPTO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/submodules)
set(TOP_DIR ${PROJECT_SOURCE_DIR})

ENABLE_TESTING()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/submodules/cryptopp)
    message("cryptopp dir not exists. Make dirrectory")
    execute_process(
        COMMAND bash ../cryptopp.sh
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/submodules
        )
else()
    message("cryptopp dir exists")
endif()

include_directories(${PROJECT_SOURCE_DIR}/submodules/spdlog/include)

add_subdirectory(submodules/crossguid)
add_subdirectory(submodules/cryptopp)
add_subdirectory(submodules/nlohmann_json)

add_subdirectory( messages )
add_subdirectory( gui )
add_subdirectory( main )
add_subdirectory(encryption)
add_subdirectory(utils)
add_subdirectory(oauth-agents)
add_subdirectory(doc)
add_subdirectory(curl-wrapper)




