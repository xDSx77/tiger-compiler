/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */


#pragma once

#include <task/libtask.hh>

namespace bind::tasks
{
  
    TASK_GROUP("3. Binding");

    ///Dispaly the  bindings
    TASK_DECLARE("b|bindings-compute","display the binding",
        bindings_compute,"parse");

    ///Dispaly the  bindings
    TASK_DECLARE("B|bindings-display","display the binding",
            bindings_display,"parse");
}//namespace bind::tasks
