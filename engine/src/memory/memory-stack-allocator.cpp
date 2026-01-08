#pragma once

#include "memory.hpp"

namespace ifb::eng {

        memory_stack_allocator::
        memory_stack_allocator(
            memory_region* region,
            u32            granularity_min,
            u32            page_size_min) {


        }

        auto memory_stack_allocator::
        validate(
            void) const -> void {

        }

        auto memory_stack_allocator::
        reset(
            void) -> void {

        }

        auto memory_stack_allocator::
        push(
            const u32 size,
            const u32 alignment) -> void* {

            return(NULL);
        }

        auto memory_stack_allocator::
        pull(
            const u32 size,
            const u32 alignment) -> void {

        }

        auto memory_stack_allocator::
        save(
            void) -> void {

        }

        auto memory_stack_allocator::
        roll_back(
            void) -> void {

        }   

        template<typename t> auto memory_stack_allocator::
        push_struct(
            const u32 count) -> t* {

        }

        template<typename t> auto memory_stack_allocator::
        pull_struct(
            const u32 count) -> void {

        }
};