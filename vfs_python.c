#include "include/includes.h"
#include "../lib/util/tevent_unix.h"
#include "../lib/util/tevent_ntstatus.h"
#include "python2.7/Python.h"

PyObject *py_mod;

static void debug(const char *text)
{
    FILE *fp = fopen("/home/vortec/workspace/vfs_python/log", "a");
    if (fp)
    {
	fprintf(fp, "SAMBA: %s\n", text);
	fclose(fp);
    }
}

static PyObject * py_import_handler(const char *script_path)
{
    PyObject *py_dir, *py_imp_str, *py_imp_handle, *py_imp_dict, *py_imp_load_source;
    PyObject *py_function_name, *py_args_tuple;
    
    Py_Initialize();
    
    py_dir = PyString_FromString(script_path);
    py_imp_str = PyString_FromString("imp");
    py_imp_handle = PyImport_Import(py_imp_str);
    py_imp_dict = PyModule_GetDict(py_imp_handle);
    py_imp_load_source = PyDict_GetItemString(py_imp_dict, "load_source");
    py_function_name = PyString_FromString("connect");

    py_args_tuple = PyTuple_New(2);  // may not be Py_DECREF'ed
    PyTuple_SetItem(py_args_tuple, 0, py_function_name);
    PyTuple_SetItem(py_args_tuple, 1, py_dir);
    
    py_mod = PyObject_CallObject(py_imp_load_source, py_args_tuple);
    
    Py_DECREF(py_dir);
    Py_DECREF(py_imp_str);
    Py_DECREF(py_imp_handle);
    Py_DECREF(py_imp_dict);
    Py_DECREF(py_imp_load_source);
    Py_DECREF(py_function_name);

    return py_mod;
}

static int python_connect(vfs_handle_struct *handle,
                             const char *service,
                             const char *user)
{
    const char *script_path = lp_parm_const_string(SNUM(handle->conn), "python", "script", NULL);
    const char *function_name = "connect";
    
    py_import_handler(script_path);
    
    PyObject *py_function_name = PyString_FromString(function_name);
    PyObject *py_mod_dict, *py_func, *py_ret;
    int success = 0;
    
    py_mod_dict = PyModule_GetDict(py_mod);
    py_func = PyDict_GetItem(py_mod_dict, py_function_name);
    
    // check before call:
    // does exist?
    // is callable?
    py_ret = PyObject_CallFunction(py_func, "ss", service, user);
    if (py_ret != NULL)
    {
	success = PyObject_IsTrue(py_ret);
    }
    
    Py_DECREF(py_function_name);
    Py_DECREF(py_mod_dict);
    Py_DECREF(py_func);
    Py_DECREF(py_ret);
    
    if (success == 1)
    {
	return SMB_VFS_NEXT_CONNECT(handle, service, user);
    }
    else
    {
	return -1;
    }
}

static void python_disconnect(vfs_handle_struct *handle)
{
    FILE *f = fopen("/tmp/mylog.txt", "a");
    if (f != NULL)
    {
        const char *text = "Connection disconnected.";
        fprintf(f, "%s\n", text);
        fclose(f);
    }

    SMB_VFS_NEXT_DISCONNECT(handle);
}



static struct vfs_fn_pointers vfs_python_fns = {
        .connect_fn = python_connect,
        .disconnect_fn = python_disconnect
};

#define vfs_python_init samba_init_module

NTSTATUS vfs_python_init(void)
{
    return smb_register_vfs(SMB_VFS_INTERFACE_VERSION,
                            "python",
                            &vfs_python_fns);
}
