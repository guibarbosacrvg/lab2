# Info regarding LAB2 - INF1316

- Will be using shared memory between different processes
- Will need to understand the usage of the <sys/shm.h> header and its functions
- Use attach() to connect a process to that memory and detach() to disconnect
##### To allocate memory, use shmget()
    int shmget(key_t key, size_t size, int shmflg);

#### Where: 
- key: memory id key (if known), otherwise use IPC_PRIVATE to generate a new id
- size: minimum amount of memory to be allocated
- shmflg: creation mode flags (read end of document for reference)


#### Returns:
- An id (IPC ID) for the allocated memory area in case of success
- -1 in case of error

### Annex shared memory (attach)
    void *shmat(int shmid, const void *shmaddr, int shmflg);

#### Where:
- shmid: id of the allocated area (allocated using shmget())
- shmaddr: reference address for the page allocation. - usually 0 or NULL
- shmflg: annex mode - usually 0 or NULL

#### Returns:
- 0 in case of success
- -1 in case of failure

### shmflg options
#### <sys/ipc.h>
- IPC_CREAT : Create entry if key does not exist.
- IPC_EXCL : Fail if key exists.
- IPC_NOWAIT : Error if request must wait.
#### <sys/stat.h>
- S_IRWXU : Read, write, execute/search by owner.
- S_IRUSR : Read permission, owner.
- S_IWUSR : Write permission, owner.
- S_IXUSR : Execute/search permission, owner.
- S_IRWXG : Read, write, execute/search by group.
- S_IRGRP : Read permission, group.
- S_IWGRP : Write permission, group.
- S_IXGRP : Execute/search permission, group.
- S_IRWXO : Read, write, execute/search by others.
- S_IROTH : Read permission, others.
- S_IWOTH : Write permission, others.
- S_IXOTH : Execute/search permission, others