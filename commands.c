#include "commands.h"

int python_connect(vfs_handle_struct *handle,
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

    if (success == 1)
    {
        return SMB_VFS_NEXT_CONNECT(handle, service, user);
    }
    else
    {
        return -1;
    }
}

void python_disconnect(vfs_handle_struct *handle)
{
    SMB_VFS_NEXT_DISCONNECT(handle);
}


int python_mkdir(vfs_handle_struct *handle,
                 const char *path,
                 mode_t mode)
{
    int success = 1;

    PyObject *py_func = get_func(handle, "mkdir");
    if (py_func != NULL)
    {
        PyObject *py_ret = PyObject_CallFunction(py_func, "s", path);
        success = PyObject_IsTrue(py_ret);
        Py_DECREF(py_ret);
    }

    if (success == 1)
    {
        return SMB_VFS_NEXT_MKDIR(handle, path, mode);
    }
    else
    {
        return -1;
    }
}

NTSTATUS python_create_file(struct vfs_handle_struct *handle,
                            struct smb_request *req,
                            uint16_t root_dir_fid,
                            struct smb_filename *smb_fname,
                            uint32_t access_mask,
                            uint32_t share_access,
                            uint32_t create_disposition,
                            uint32_t create_options,
                            uint32_t file_attributes,
                            uint32_t oplock_request,
                            uint64_t allocation_size,
                            uint32_t private_flags,
                            struct security_descriptor *sd,
                            struct ea_list *ea_list,
                            files_struct **result,
                            int *pinfo)
{
    int success = 1;

    PyObject *py_func = get_func(handle, "create_file");
    if (py_func != NULL)
    {
        PyObject *py_ret = PyObject_CallFunction(py_func, "s", smb_fname->base_name);
        success = PyObject_IsTrue(py_ret);
        Py_DECREF(py_ret);
    }

    if (success == 1)
    {
        return SMB_VFS_NEXT_CREATE_FILE(handle,
                                        req,
                                        root_dir_fid,
                                        smb_fname,
                                        access_mask,
                                        share_access,
                                        create_disposition,
                                        create_options,
                                        file_attributes,
                                        oplock_request,
                                        allocation_size,
                                        private_flags,
                                        sd,
                                        ea_list,
                                        result,
                                        pinfo);
    }


}