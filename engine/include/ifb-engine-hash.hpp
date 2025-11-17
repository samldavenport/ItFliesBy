#ifndef IFB_eng_hash128_HPP
#define IFB_eng_hash128_HPP

#include <sld-hash.hpp>

#include "ifb-engine.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    typedef sld::hash128_t       eng_hash128_t;
    typedef sld::hash128_state_t eng_hash128_state_t;
    typedef sld::hash128_seed_t  eng_hash128_seed_t;
    typedef sld::hash32_t        eng_hash32_t;
    typedef sld::hash32_seed_t   eng_hash32_seed_t;

    //-------------------------------------------------------------------
    // API
    //-------------------------------------------------------------------

    IFB_ENG_INLINE const eng_hash128_t  eng_hash128               (const byte*          data,   const u32           length);
    IFB_ENG_INLINE bool                 eng_hash128_batch         (const u32            count,  const byte*         data,   const u32             stride, eng_hash128_t* hashes);
    IFB_ENG_INLINE bool                 eng_hash128_is_equal      (const byte*          data_a, const byte*         data_b, const u32             length);
    IFB_ENG_INLINE bool                 eng_hash128_is_equal      (const eng_hash128_t& hash,   const byte*         data,   const u32             length);
    IFB_ENG_INLINE bool                 eng_hash128_search        (const u32            count,  const eng_hash128_t search, const eng_hash128_t*  array,  u32& index);
    IFB_ENG_INLINE void                 eng_hash128_block_begin   (eng_hash128_state_t& state);
    IFB_ENG_INLINE void                 eng_hash128_block_consume (eng_hash128_state_t& state, const u64 block_size, const byte* block_data);
    IFB_ENG_INLINE const eng_hash128_t  eng_hash128_block_end     (eng_hash128_state_t& state);

    IFB_ENG_INLINE const eng_hash32_t   eng_hash32_data           (const byte*         data,   const u32          length);
    IFB_ENG_INLINE bool                 eng_hash32_data_batch     (const u32           count,  const byte*        data,   const u32           stride, eng_hash32_t* hashes);
    IFB_ENG_INLINE bool                 eng_hash32_is_equal       (const byte*         data_a, const byte*        data_b, const u32           length);
    IFB_ENG_INLINE bool                 eng_hash32_is_equal       (const eng_hash32_t& hash,   const byte*        data,   const u32           length);
    IFB_ENG_INLINE bool                 eng_hash32_search         (const u32           count,  const eng_hash32_t search, const eng_hash32_t* array,  u32& index);

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    constexpr eng_hash128_seed_t _eng_hash128_seed = {
        "maytheroadriseto" 
        "meetyouthewindbe"
        "alwaysatyourback"
        "thesunshinewarmu"
        "ponyourfacethera"
        "insfallsoftupony"
        "ougodholdyouinth"
        "epalmofhishand"
    };

    //-------------------------------------------------------------------
    // HASH 128
    //-------------------------------------------------------------------

    IFB_ENG_INLINE const eng_hash128_t
    eng_hash128(
        const byte* data,
        const u32   length) {

        const eng_hash128_t hash = sld::hash128_data(
            _eng_hash128_seed,
            data,
            length            
        );

        return(hash);
    }

    IFB_ENG_INLINE bool
    eng_hash128_batch(
        const u32    count,
        const byte*  data,
        const u32    stride,
        eng_hash128_t* hashes) {

        const bool is_hashed = sld::hash128_data_batch(
            _eng_hash128_seed,
            count,
            data,
            stride,
            hashes            
        );

        return(is_hashed);
    }

    IFB_ENG_INLINE bool
    eng_hash128_is_equal(
        const byte* data_a,
        const byte* data_b,
        const u32   length) {

        const bool is_equal = sld::hash128_is_equal(
            _eng_hash128_seed,
            data_a,
            data_b,
            length
        );

        return(is_equal);
    }

    IFB_ENG_INLINE bool
    eng_hash128_is_equal(
        const eng_hash128_t& hash,
        const byte*        data,
        const u32          length) {

        const bool is_equal = sld::hash128_is_equal(
            _eng_hash128_seed,
            hash,
            data,
            length
        );

        return(is_equal);
    }

    IFB_ENG_INLINE bool
    eng_hash128_search(
        const u32          count, 
        const eng_hash128_t  search,
        const eng_hash128_t* array,
        u32&               index) {

        const bool is_found = sld::hash128_search(
            count,
            search,
            array,
            index            
        );

        return(is_found);
    }

    IFB_ENG_INLINE void
    eng_hash128_block_begin(
        eng_hash128_state_t& state) {

        sld::hash128_block_begin(state,_eng_hash128_seed);
    }

    IFB_ENG_INLINE void
    eng_hash128_block_consume(
        eng_hash128_state_t& state,
        const u64          block_size,
        const byte*        block_data) {

        sld::hash128_block_consume(state, block_size, block_data);
    }

    IFB_ENG_INLINE const eng_hash128_t
    eng_hash128_block_end(
        eng_hash128_state_t& state) {

        const eng_hash128_t hash = sld::hash128_block_end(state);
        return(hash);
    }

    //-------------------------------------------------------------------
    // HASH 32
    //-------------------------------------------------------------------

    constexpr eng_hash32_seed_t _hash32_seed = { 0xDEADBEEF };

    IFB_ENG_INLINE const eng_hash32_t
    eng_hash32_data(
        const byte* data,
        const u32   length) {

        const eng_hash32_t hash = sld::hash32(_hash32_seed, data, length);
        return(hash);
    }

    IFB_ENG_INLINE bool
    eng_hash32_batch(
        const u32   count,
        const byte* data,
        const u32   stride,
        eng_hash32_t*   hashes) {

        const bool did_hash = sld::hash32_batch(
            _hash32_seed,
            data,
            stride,
            count,
            hashes
        );
        return(did_hash);
    }

    IFB_ENG_INLINE bool
    eng_hash32_is_equal(
        const eng_hash32_t& hash,
        const byte*     data,
        const u32       length) {

        const bool is_equal = sld::hash32_is_equal(
            _hash32_seed,
            data,
            length,            
            hash
        );
        return(is_equal);
    }

    IFB_ENG_INLINE bool
    eng_hash32_search(
        const u32       count,
        const eng_hash32_t  search,
        const eng_hash32_t* array,
        u32&            index) {

        const bool did_find = sld::hash32_search(
            count,
            search,
            array,
            index            
        );
        return(did_find);
    }
};

#endif //IFB_eng_hash128_HPP