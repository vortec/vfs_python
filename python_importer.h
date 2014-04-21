#include "include/includes.h"
#include "python2.7/Python.h"

PyObject *py_handler;
bool always_import;

void debug(const char *text);

const char *get_conf(vfs_handle_struct *handle, const char *name);
struct PyObject *get_py_mod(const char *script_path);
struct PyObject *get_py_func(PyObject *py_mod, const char *func_name);
struct PyObject *get_func(vfs_handle_struct *handle, const char *func_name);
