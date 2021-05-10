//
// Created by Gustavo Lima on 5/9/21.
//

#ifndef INC_8_05_SYSCALLS_H
#define INC_8_05_SYSCALLS_H

#define DIRSIZE 1024

#include <zconf.h>

struct direct                          /* directory */
{
    ino_t d_ino;                       /* inode number */
    char d_name[DIRSIZE];              /* long name does not have '\0' */
};

#endif //INC_8_05_SYSCALLS_H
