/**
 ** \file object/tasks.hh
 ** \brief Object module related tasks.
 */

#pragma once

#include <overload/binder.hh>
#include <task/libtask.hh>

namespace object::tasks
{

  TASK_GROUP("Object");

  /// Enable object extensions.
  BOOLEAN_TASK_DECLARE("o|object", "enable object extensions",
                       enable_object_extensions_p, "");

  /// Parse the input file, allowing objects.
  TASK_DECLARE("object-parse", "parse a file, allowing objects",
               object_parse, "object parse");

  TASK_DECLARE("object-bindings-compute", "bind the identifiers, allowing objects",
               object_bindings_compute, "object parse");

  /// Check for type violation, allowing objects.
  TASK_DECLARE("object-types-compute", "check for type violations, "
               "allowing objects",
               object_types_compute, "object-bindings-compute");

  /// Perform a renaming, before desugaring objects.
  TASK_DECLARE("object-rename",
               "rename identifiers to unique names, allowing objects",
               object_rename, "object-types-compute");

  /// Remove syntactic sugar from the Ast.
  TASK_DECLARE("object-desugar",
               "remove object constructs from the program",
               object_desugar, "object-rename");

  /// Remove syntactic sugar from the Ast without recomputing
  /// bindings nor types.
  TASK_DECLARE("raw-object-desugar",
               "remove object constructs from the program "
               "without recomputing bindings nor types",
               raw_object_desugar, "object-rename");

  // FIXME: Some code was deleted here.

} // namespace object::tasks
