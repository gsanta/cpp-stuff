

/**
 * storage: static
 * linkage: external
 * scope: file
 *
 * (defining declaration)
 */
char *a = "char *a -> (static,external,file)";

/**
 * storage: static
 * linkage: external
 * scope: file
 */
static char *b = "static char *b -> (static,internal,file)";

/**
 * storage: static
 * linkage: internal
 * scope: file
 */
const char *const e = "in file file1.cpp: const char *const e -> (static,internal,file)";

/**
 * storage: static
 * linkage: external
 * scope: file
 */
extern const char *const f = "extern const char *const f -> (static,external,file)";

char *return_b()
{
  return b;
}

const char *const return_e()
{
  return e;
}

char *static_local()
{
  /**
   * storage: static
   * linkage: no linkage
   * scope: block
   */
  static char *c = "within function: static char *c -> (static,no linkage,block)";

  return c;
}

char *automatic_local()
{
  /**
   * storage: automatic
   * linkage: no linkage
   * scope: block
   */
  char *d = "within function: char *d -> (automatic,no linkage,block)";

  return d;
}
