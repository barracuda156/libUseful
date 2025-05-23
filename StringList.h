
/*
Copyright (c) 2015 Colum Paget <colums.projects@googlemail.com>
* SPDX-License-Identifier: LGPL-3.0-or-later
*/

#ifndef LIBUSEFUL_STRINGLIST_H
#define LIBUSEFUL_STRINGLIST_H

/*
Utility functions to hand a string of strings, separated by a separator string or character
*/


#ifdef __cplusplus
extern "C" {
#endif

//check if Item is in string 'List' where 'List' is separated into strings by 'Sep'
//e.g. InStringList("that", "this,that,theother", ",");


int InStringList(const char *Item, const char *List, const char *Sep);
char *StringListGet(char *RetStr, const char *List, const char *Sep, int Pos);
char *StringListAdd(char *RetStr, const char *Item, const char *Sep);
char *StringListAddUnique(char *RetStr, const char *Item, const char *Sep);


#ifdef __cplusplus
}
#endif

#endif
