#include "include/includes.h"
#include "../lib/util/tevent_unix.h"
#include "../lib/util/tevent_ntstatus.h"
/*#include "/usr/include/python2.7/Python.h"*/

static int python_connect(vfs_handle_struct *handle,
                             const char *service,
                             const char *user)
{
    /*PyObject *py_imp_str, *py_imp_handle, *py_imp_dict, *py_imp_load_source;
    PyObject *py_dir, *py_lib_name, *py_args_tuple, *py_lib_mod, *py_lib_mod_dict, *py_func, *py_ret;
    const char *script = lp_parm_const_string(SNUM(handle->conn), "python", "script", NULL);

    py_dir = PyString_FromString(script);
    py_imp_str = PyString_FromString("imp");
    py_imp_handle = PyImport_Import(py_imp_str);
    py_imp_dict = PyModule_GetDict(py_imp_handle);
    py_imp_load_source = PyDict_GetItemString(py_imp_dict, "load_source");
    py_lib_name = PyString_FromString("connect");

    py_args_tuple = PyTuple_New(2);
    PyTuple_SetItem(py_args_tuple, 0, py_lib_name);
    PyTuple_SetItem(py_args_tuple, 1, py_dir);

    //call imp.load_source
    py_lib_mod = PyObject_CallObject(py_imp_load_source, py_args_tuple);
    py_lib_mod_dict = PyModule_GetDict(py_lib_mod);

    py_func = PyDict_GetItem(py_lib_mod_dict, py_lib_name);
    py_ret = PyObject_CallFunction(py_func, NULL);*/

    FILE *fp = fopen("/home/vortec/xx", "a");
    if (1)
    {
	fprintf(fp, "worked.\n");
    }
    else
    {
	fprintf(fp, "error\n");
    }
    fclose(fp);
    
    return SMB_VFS_NEXT_CONNECT(handle, service, user);
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
