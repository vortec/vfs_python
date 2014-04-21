#include "python2.7/Python.h"
#include "python_importer.h"

int python_connect(vfs_handle_struct *handle,
                   const char *service,
                   const char *user);
void python_disconnect(vfs_handle_struct *handle);
int python_mkdir(vfs_handle_struct *handle,
                 const char *path,
                 mode_t mode);
int python_rmdir(vfs_handle_struct *handle, const char *path);

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
                            int *pinfo);
int python_rename(vfs_handle_struct *handle,
                  const struct smb_filename *smb_fname_src,
                  const struct smb_filename *smb_fname_dst);
