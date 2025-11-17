#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb::eng {

    constexpr cchar  _db_file_default_header[]  = 
        "IFBASSETDATABASE"                                                                                  // (16 bytes) verification string
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"                                  // (16 bytes) hash (everything after this point)
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // (24 bytes) text table index
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // (24 bytes) image table index
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // (24 bytes) sound table index
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; // (24 bytes) font table index


    constexpr u32   _db_file_index_array_size  = (sizeof(eng_asset_db_file_index_t) * eng_asset_e32_type_count);
    constexpr cchar _db_file_path_cstr  []     = IFB_ENG_ASSET_DB_PATH;
    constexpr cchar _db_file_verif_cstr []     = IFB_ENG_ASSET_VERIF_STR;
    constexpr u32   _db_file_verif_size        = sizeof(_db_file_verif_cstr) - 1; 
    constexpr u32   _db_file_start_verif_data  = 0;
    constexpr u32   _db_file_start_hash        = _db_file_verif_size;
    constexpr u32   _db_file_start_index_array = _db_file_start_hash + sizeof(eng_hash128_t);
    constexpr u32   _db_file_header_size       = sizeof(_db_file_default_header) - 1; 

};