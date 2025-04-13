#include "utils.h"
#include <sys/stat.h>
#include <unistd.h>



time_t obter_data_modificacao(const char *nome_arquivo) 
{
    struct stat info;

    if (stat(nome_arquivo, &info) == 0) 
        return info.st_mtime;

    return 0;
}

int obter_uid() 
{
    return getuid();  // pega UID do usuário atual
}
