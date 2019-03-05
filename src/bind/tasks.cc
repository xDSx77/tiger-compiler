/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

#include <iostream>
#include <ast/libast.hh>
#include <ast/tasks.hh>
#include <bind/libbind.hh>
#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS
#include <common.hh>
#include <misc/xalloc.hh>

namespace bind::tasks
{
    void
    bindings_display()
    {
        ast::bindings_display(std::cout) = true;
    }

    void
    bindings_compute()
    {
        task_error() << ::bind::bind(*ast::tasks::the_program);
        task_error().exit_on_error();
    }
}

