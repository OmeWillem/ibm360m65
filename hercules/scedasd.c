/* SCEDASD.C    (c) Copyright Jan Jaeger, 1999-2009                  */
/*              Service Control Element DASD I/O functions           */

// $Id: scedasd.c 5306 2009-04-03 17:57:43Z rbowler $

#include "hstdinc.h"

#define _HENGINE_DLL_

#include "hercules.h"
#include "opcode.h"

#if !defined(_SCEDASD_C)
#define _SCEDASD_C

static TID     scedio_tid;             /* Thread id of the i/o driver
                                                                     */
static char *sce_basedir = NULL;


char *get_sce_dir()
{
    return sce_basedir;
}


void set_sce_dir(char *path)
{
char realdir[MAX_PATH];
char tempdir[MAX_PATH];

    if(sce_basedir)
    {
        free(sce_basedir);
        sce_basedir = NULL;
    }

    if(!path)
        sce_basedir = NULL;
    else
        if(!realpath(path,tempdir))
        {
            logmsg(_("HHCSC011E set_sce_dir: %s: %s\n"),path,strerror(errno));
            sce_basedir = NULL;
        }
        else
        {
            hostpath(realdir, tempdir, sizeof(realdir));
            strlcat(realdir,"/",sizeof(realdir));
            sce_basedir = strdup(realdir);
        }
}


static char *set_sce_basedir(char *path)
{
char *basedir;
char realdir[MAX_PATH];
char tempdir[MAX_PATH];

    if(sce_basedir)
    {
        free(sce_basedir);
        sce_basedir = NULL;
    }

    if(!realpath(path,tempdir))
    {
        logmsg(_("HHCSC012E set_sce_basedir: %s: %s\n"),path,strerror(errno));
        sce_basedir = NULL;
        return NULL;
    }
    hostpath(realdir, tempdir, sizeof(realdir));

    if((basedir = strrchr(realdir,'/')))
    {
        *(++basedir) = '\0';
        sce_basedir = strdup(realdir);
        return (basedir = strrchr(path,'/')) ? ++basedir : path;
    }
    else
    {
        sce_basedir = NULL; 
        return path;
    }
}


static char *check_sce_filepath(const char *path, char *fullpath)
{
char temppath[MAX_PATH];
char tempreal[MAX_PATH];

    /* Return file access error if no basedir has been set */
    if(!sce_basedir)
    {
        strlcpy(fullpath,path,sizeof(temppath));
        errno = EACCES;
        return NULL;
    }

    /* Establish the full path of the file we are trying to access */
    strlcpy(temppath,sce_basedir,sizeof(temppath));
    strlcat(temppath,path,sizeof(temppath));
    
    if(!realpath(temppath,tempreal))
    {
        hostpath(fullpath, tempreal, sizeof(temppath));
        if(strncmp( sce_basedir, fullpath, strlen(sce_basedir)))
            errno = EACCES;
        return NULL;
    }
    
    hostpath(fullpath, tempreal, sizeof(temppath));
    if(strncmp( sce_basedir, fullpath, strlen(sce_basedir)))
    {
        errno = EACCES;
        return NULL;
    }

    return fullpath;
}

#endif /* !defined(_SCEDASD_C) */


/*-------------------------------------------------------------------*/
/* function load_hmc simulates the load from the service processor   */
/*   the filename pointed to is a descriptor file which has the      */
/*   following format:                                               */
/*                                                                   */
/*   '*' in col 1 is comment                                         */
/*   core image file followed by address where it should be loaded   */
/*                                                                   */
/* For example:                                                      */
/*                                                                   */
/* * Linux/390 cdrom boot image                                      */
/* boot_images/tapeipl.ikr 0x00000000                                */
/* boot_images/initrd 0x00800000                                     */
/* boot_images/parmfile 0x00010480                                   */
/*                                                                   */
/* The location of the image files is relative to the location of    */
/* the descriptor file.                         Jan Jaeger 10-11-01  */
/*                                                                   */
/*-------------------------------------------------------------------*/
int ARCH_DEP(load_hmc) (char *fname, int cpu, int clear)
{
REGS   *regs;                           /* -> Regs                   */
FILE   *fp;
char    inputbuff[MAX_PATH];
char   *inputline;
char    filename[MAX_PATH];                 /* filename of image file    */
char    pathname[MAX_PATH];                 /* pathname of image file    */
U32     fileaddr;
int     rc = 0;                         /* Return codes (work)       */

    /* Get started */
    if (ARCH_DEP(common_load_begin) (cpu, clear) != 0)
        return -1;

    /* The actual IPL proper starts here... */

    regs = sysblk.regs[cpu];    /* Point to IPL CPU's registers */

    if(fname == NULL)                   /* Default ipl from DASD     */
        fname = "HERCULES.ins";         /*   from HERCULES.ins       */

    hostpath(pathname, fname, sizeof(pathname));

    if(!(fname = set_sce_basedir(pathname)))
        return -1;

    /* Construct and check full pathname */
    if(!check_sce_filepath(fname,filename))
    {
        logmsg(_("HHCSC001E Load from %s failed: %s\n"),fname,strerror(errno));
        return -1;
    }
    
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        logmsg(_("HHCSC002E Load from %s failed: %s\n"),fname,strerror(errno));
        return -1;
    }

    do
    {
        inputline = fgets(inputbuff,sizeof(inputbuff),fp);

#if !defined(_MSVC_)
        if(inputline && *inputline == 0x1a)
            inputline = NULL;
#endif /*!defined(_MSVC_)*/

        if(inputline)
        {
            rc = sscanf(inputline,"%" MSTRING(MAX_PATH) "s %i",filename,&fileaddr);
        }

        /* If no load address was found load to location zero */
        if(inputline && rc < 2)
            fileaddr = 0;

        if(inputline && rc > 0 && *filename != '*' && *filename != '#')
        {
            hostpath(pathname, filename, sizeof(pathname));

            /* Construct and check full pathname */
            if(!check_sce_filepath(pathname,filename))
            {
                logmsg(_("HHCSC003E Load from %s failed: %s\n"),pathname,strerror(errno));
                return -1;
            }

            if( ARCH_DEP(load_main) (filename, fileaddr) < 0 )
            {
                fclose(fp);
                HDC1(debug_cpu_state, regs);
                return -1;
            }
            sysblk.main_clear = sysblk.xpnd_clear = 0;
        }
    } while(inputline);
    fclose(fp);

    /* Finish up... */
    return ARCH_DEP(common_load_finish) (regs);

} /* end function load_hmc */


/*-------------------------------------------------------------------*/
/* Function to Load (read) specified file into absolute main storage */
/*-------------------------------------------------------------------*/
int ARCH_DEP(load_main) (char *fname, RADR startloc)
{
int fd;
int len;
int rc = 0;
RADR pageaddr;
U32  pagesize;

    fd = open (fname, O_RDONLY|O_BINARY);
    if (fd < 0)
    {
        if(errno != ENOENT)
            logmsg(_("HHCSC031E load_main: %s: %s\n"), fname, strerror(errno));
        return fd;
    }

    pagesize = PAGEFRAME_PAGESIZE - (startloc & PAGEFRAME_BYTEMASK);
    pageaddr = startloc;

    for( ; ; ) {
        if (pageaddr >= sysblk.mainsize)
        {
            logmsg(_("HHCSC032W load_main: terminated at end of mainstor\n"));
            close(fd);
            return rc;
        }

        len = read(fd, sysblk.mainstor + pageaddr, pagesize);
        if (len > 0)
        {
            STORAGE_KEY(pageaddr, &sysblk) |= STORKEY_REF|STORKEY_CHANGE;
            rc += len;
        }

        if (len < (int)pagesize)
        {
            close(fd);
            return rc;
        }

        pageaddr += PAGEFRAME_PAGESIZE;
        pageaddr &= PAGEFRAME_PAGEMASK;
        pagesize  = PAGEFRAME_PAGESIZE;
    }

} /* end function load_main */


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "scedasd.c"
#endif

#if defined(_ARCHMODE3)
 #undef   _GEN_ARCH
 #define  _GEN_ARCH _ARCHMODE3
 #include "scedasd.c"
#endif


/*-------------------------------------------------------------------*/
/*  Service Processor Load    (load/ipl from the specified file)     */
/*-------------------------------------------------------------------*/

int load_hmc (char *fname, int cpu, int clear)
{
            return s370_load_hmc (fname, cpu, clear);
}


/*-------------------------------------------------------------------*/
/* Load/Read specified file into absolute main storage               */
/*-------------------------------------------------------------------*/
int load_main (char *fname, RADR startloc)
{
            return s370_load_main (fname, startloc);
}

#endif /*!defined(_GEN_ARCH)*/
