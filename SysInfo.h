/*
Copyright (c) 2015 Colum Paget <colums.projects@googlemail.com>
* SPDX-License-Identifier: LGPL-3.0-or-later
*/

#ifndef LIBUSEFUL_SYSINFO_H
#define LIBUSEFUL_SYSINFO_H


#include "defines.h"
#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {OSINFO_TYPE, OSINFO_ARCH, OSINFO_RELEASE, OSINFO_HOSTNAME, OSINFO_UPTIME, OSINFO_TOTALMEM, OSINFO_FREEMEM, OSINFO_BUFFERMEM, OSINFO_TOTALSWAP, OSINFO_FREESWAP, OSINFO_LOAD1MIN, OSINFO_LOAD5MIN, OSINFO_LOAD15MIN, OSINFO_HOMEDIR, OSINFO_TMPDIR, OSINFO_PROCS, OSINFO_USERINFO, OSINFO_DOMAINNAME, OSINFO_INTERFACES, OSINFO_LOCALE, OSINFO_LANG, OSINFO_COUNTRY, OSINFO_CURRENCY, OSINFO_CURRENCY_SYM, OSINFO_PAGESIZE, OSINFO_OPENMAX, OSINFO_CLOCKTICK} EOSInfo;


// pass in one of the OSINFO_ defines above to get out a string answer
//OSINFO_TYPE         system type, e.g. 'linux'
//OSINFO_ARCH         system architecture, e.g. 'arm' 'i386'
//OSINFO_RELEASE      system kernel version
//OSINFO_HOSTNAME     system hostname
//OSINFO_DOMAINNAME   system domainname
//OSINFO_INTERFACES   list of network interfaces
//OSINFO_HOMEDIR      user home directory
//OSINFO_TMPDIR       user temporary directory
//OSINFO_LOCALE       user locale (en_US, en_GB, fr_FR, jp_JP etc)
//OSINFO_LANG         user locale lang (en, fr, jp etc)
//OSINFO_COUNTRY      user locale country (US, GB, FR, JP, ZH)
//OSINFO_CURRENCY     user locale currency code (USD, GBP, EU, etc)
//OSINFO_CURRENCY_SYM user locale currency sym ($ etc)

const char *OSSysInfoString(int Info);



// pass in one of the OSINFO_ defines to get a numeric answer
// OSINFO_UPTIME     seconds since boot
// OSINFO_TOTALMEM   visible system memory
// OSINFO_FREEMEM    available system memory
// OSINFO_BUFFERMEM  memory used in buffers
// OSINFO_TOTALSWAP  total swap space
// OSINFO_FREESWAP   free swap space
// OSINFO_LOAD1MIN   system load in last minute
// OSINFO_LOAD5MIN   system load in last five minutes
// OSINFO_LOAD15MIN  system load in last fifteen minutes
// OSINFO_PROCS      number of processes running
// OSINFO_PAGESIZE   pagesize of system
// OSINFO_OPENMAX    max number of files open by a process
// OSINFO_CLOCKTICK  clockticks per second (accurate value

size_t OSSysInfoLong(int Info);

#ifdef __cplusplus
}
#endif


#endif

