/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */


#pragma once

#include <task/libtask.hh>

namespace bind::tasks
{
  
    TASK_GROUP("3. Binding");

    ///Bind the name uses to their definitions
    TASK_DECLARE("b|bindings-compute","bind the name uses to their definitions",
        bindings_compute,"parse");

    ///Display the bindings
    TASK_DECLARE("B|bindings-display","display the binding",
        bindings_display,"parse");

    ///Make sure bindings are computed
    TASK_DECLARE("bound", "make sure bindings are computed",
        bound,"parse");
}//namespace bind::tasks
