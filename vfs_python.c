#include "include/includes.h"
#include "../lib/util/tevent_unix.h"
#include "../lib/util/tevent_ntstatus.h"
#include "python2.7/Python.h"

PyObject *py_handler;
bool always_import = false;

static void debug(const char *text)
{
	FILE *fp = fopen("/home/vortec/workspace/vfs_python/log", "a");

	if (fp)
	{
		fprintf(fp, "SAMBA: %s\n", text);
		fclose(fp);
	}
}

static const char *get_conf(vfs_handle_struct *handle, const char *name)
{
	return lp_parm_const_string(SNUM(handle->conn), "python", name, NULL);
}

static struct PyObject *get_py_mod(const char *script_path)
{
	PyObject *py_mod;
	PyObject *py_imp_str, *py_imp_handle, *py_imp_dict;
	PyObject *py_imp_load_source, *py_args_tuple;

	Py_Initialize();

	py_imp_str = PyString_FromString("imp");
	py_imp_handle = PyImport_Import(py_imp_str);
	py_imp_dict = PyModule_GetDict(py_imp_handle);
	py_imp_load_source = PyDict_GetItemString(py_imp_dict, "load_source");

	py_args_tuple = PyTuple_New(2);
	PyTuple_SetItem(py_args_tuple, 0, PyString_FromString("handler"));
	PyTuple_SetItem(py_args_tuple, 1, PyString_FromString(script_path));

	py_mod = PyObject_CallObject(py_imp_load_source, py_args_tuple);

	Py_DECREF(py_args_tuple);
	Py_DECREF(py_imp_str);
	Py_DECREF(py_imp_handle);
	Py_DECREF(py_imp_dict);
	Py_DECREF(py_imp_load_source);

	return py_mod;
}

static struct PyObject *get_py_func(PyObject *py_mod, const char *func_name)
{
	PyObject *py_func_name = PyString_FromString(func_name);
	PyObject *py_func = PyObject_GetAttr(py_mod, py_func_name);
	Py_DECREF(py_func_name);

	if (py_func != NULL)
	{
		if (PyCallable_Check(py_func) == 1)
		{
			return py_func;
		}
	}
	debug("something went wrong get_py_func.");
	return NULL;
}

static struct PyObject *get_func(vfs_handle_struct *handle, const char *func_name)
{
	debug("get_func");
	if ((py_handler == NULL) || (always_import == true))
	{
		debug("importing module.");
		const char *script_path = get_conf(handle, "script");
		py_handler = get_py_mod(script_path);
	}

	return get_py_func(py_handler, func_name);
}



/************************************************/


static int python_connect(vfs_handle_struct *handle,
						  const char *service,
						  const char *user)
{
	int success = 1;

	PyObject *py_func = get_func(handle, "connect");
	if (py_func != NULL)
	{
		PyObject *py_ret = PyObject_CallFunction(py_func, "ss", service, user);
		success = PyObject_IsTrue(py_ret);
		Py_DECREF(py_ret);
	}

	debug("connected.");

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
	SMB_VFS_NEXT_DISCONNECT(handle);
}


static int python_mkdir(vfs_handle_struct *handle, const char *path, mode_t mode)
{
	debug("nicely");
	return -1;
}






/************************************************/

static struct vfs_fn_pointers vfs_python_fns = {
		.connect_fn = python_connect,
		.disconnect_fn = python_disconnect,
		.mkdir_fn = python_mkdir
};

#define vfs_python_init samba_init_module

NTSTATUS vfs_python_init(void)
{
	return smb_register_vfs(SMB_VFS_INTERFACE_VERSION,
							"python",
							&vfs_python_fns);
}
