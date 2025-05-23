/*
Copyright (c) 2015 Colum Paget <colums.projects@googlemail.com>
* SPDX-License-Identifier: LGPL-3.0-or-later
*/

#ifndef LIBUSEFUL_SPAWN_H
#define LIBUSEFUL_SPAWN_H

#include "includes.h"

/*
These functions create new processes. Some create a new process with a pipe or pseudoterminal connection that can be
used to talk to the function. Many of these functions accept an argument 'Config'. Config is a space-separated list
of options, as follows:

user=<name>     run process as user 'name'
group=<name>    run process as group 'name'
dir=<path>      run process in directory 'path'
pidfile=<path>  create a pidfile 'path'. pidfile will be in /var/run unless path is absolute (starts with '/')
lockfile=<path> create a lockfile 'path'. lockfile will be in /var/lock unless path is absolute (starts with '/')
lockstdin=<path> create a lockfile and hook it to stdin. This is used with programs that close all their inherited file
                 descriptors. If they don't close stdin and we don't need to talk to them, we can attach the lockfile to stdin


trust           'trust' command. without this option certain characters are stripped from any commands that are run with the
                'SpawnCommand' functions, notably ';' and '|'. You cannot therefore concatanate commands without using this
		option.

pty             instead of using pipes to talk to the child process use a pseudo tty device. This creates a link where text sent
                to the command undergoes input processing as though it was from a keyboard

canon           perform canonical input processing (requires the 'pty' option) this means text is interpreted as characters typed
                by a user, and not sent straight to the process. It's sent to the processs only when linfeed is pressed.

echo            echo characters sent to the processs (requires 'pty')

ctrltty         set stdin to be controling tty for the process, so cntrl-c etc work (requires 'pty')

noshell         by default the spawn commands run a shell, and then run a command within that. To run a program without a parent
                shell use this option

setsid          start a new session for the process


sigdef          set all signal handlers to the default values (throw away any sighandlers set by parent process)
sigdefault      set all signal handlers to the default values (throw away any sighandlers set by parent process)

chroot=<path>   chroot process into <path>. This option happens before switching users, so that user info lookup, lockfile, pidfile,
								and chdir to directory specified with 'dir=<path>'  all happen within the chroot. Thus this is used when chrooting
                into a full unix filesystem

jail            jail the process. This does a chroot AFTER looking up the user id, creating lockfile, etc ,etc. This can be used to
                jail a process into an empty or private directory

ns=<path>       linux namespace to join. <path> is either a path to a namespace file, or a path to a directory (e.g. /proc/<pid>/ns )
                that contains namespace descriptor files

container       this us

nice=value      'nice' value of new process
prio=value       scheduling priority of new process (equivalent to 0 - nice value)
priority=value   scheduling priority of new process (equivalent to 0 - nice value)
mem=value        resource limit for memory (data segment)
fsize=value      resource limit for filesize
files=value      resource limit for open files
coredumps=value  resource limit for max size of coredump files
procs=value      resource limit for max number of processes ON A PER USER BASIS.

+stderr          combine spawned program's stderr and stdout on the pipe/STREAM used to talk to it
ptystderr        only for STREAMSpawnCommandAndPty. Send stderr from the spawned process to the pty.
stderr2null      redirect spawned program's stderr to /dev/null
stdout2null      redirect spawned program's stdout to /dev/null
innull           redirect spawned program's stdin to /dev/null
outnull          redirect spawned program's stdout and stderr to /dev/null
errnull          redirect spawned program's stderr to /dev/null
*/

#ifdef __cplusplus
extern "C" {
#endif


//call exec ON THE CURRENT PROCESS, switching it to be a different program (this doesn't spawn, it changes the process you're running)
void SwitchProgram(const char *CommandLine, const char *Config);

//fork, except with the options described above. Returns pid as per 'fork'.
pid_t xfork(const char *Config);

//fork, setting stdin, stdout and stderr to the supplied file descriptors
pid_t xforkio(int StdIn, int StdOut, int StdErr);

//fork then run a program with the options described above, and settings StdIn, StdOut and StdErr to the supplied file descriptors
pid_t SpawnWithIO(const char *CommandLine, const char *Config, int StdIn, int StdOut, int StdErr);

//fork, then run progam with options described above
#define Spawn(ProgName, Config) SpawnWithIO((ProgName), (Config), 0, 1, 2)


// This creates a child process that we can talk to using a couple of pipes. The child process runs the function 'Func'. 'Data' is any userdata we want passed.
pid_t PipeSpawnFunction(int *infd,int  *outfd,int  *errfd, BASIC_FUNC Func, void *Data, const char *Config);

// This creates a child process that we can talk to using a couple of pipes. The child process execs 'Command'
pid_t PipeSpawn(int *infd,int  *outfd,int  *errfd, const char *Command, const char *Config);

// This creates a child process that we can talk to using a pty. The child process runs the function 'Func'. 'Data' is any userdata we want passed.
pid_t PseudoTTYSpawnFunction(int *ret_pty, BASIC_FUNC Func, void *Data, int Flags, const char *Config);

// This creates a child process that we can talk to using a pty. The child process execs 'Command'
pid_t PseudoTTYSpawn(int *pty, const char *Command, const char *Config);

// This creates a child process that we can talk to using a STREAM. The child process runs the function 'Func'. 'Data' is any userdata we want passed.
STREAM *STREAMSpawnFunction(BASIC_FUNC Func, void *Data, const char *Config);

// This creates a child process that we can talk to using a STREAM. The child process execs 'Command'
STREAM *STREAMSpawnCommand(const char *Command, const char *Config);

// This creates a child process that we can talk to using a STREAM. The child process execs 'Command'. CmdS is the stream to the processes stdin, and PtyS is the stream to the pseudo terminal that the process sees as it's controlling terminal.
// In adition to the usual command it takes ptystderr, which sends the processes stderr to PtyS
int STREAMSpawnCommandAndPty(const char *Command, const char *Config, STREAM **CmdS, STREAM **PtyS);

//wait for a process connected on 'S' to exit. This will consume any further output
//from the process and throw it away
int STREAMSpawnWaitExit(STREAM *S);

#ifdef __cplusplus
}
#endif


#endif
