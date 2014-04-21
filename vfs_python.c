#include "vfs_python.h"


static struct vfs_fn_pointers vfs_python_fns = {
        .connect_fn = python_connect,
        .disconnect_fn = python_disconnect,
        .mkdir_fn = python_mkdir,
        .rmdir_fn = python_rmdir,
        .create_file_fn = python_create_file,
        .rename_fn = python_rename,
        .unlink_fn = python_unlink
};

#define vfs_python_init samba_init_module

NTSTATUS vfs_python_init(void)
{
    return smb_register_vfs(SMB_VFS_INTERFACE_VERSION,
                            "python",
                            &vfs_python_fns);
}
