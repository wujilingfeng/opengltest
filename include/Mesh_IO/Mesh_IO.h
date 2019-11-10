
#include<stdio.h>
#include<Mesh/_Func_.h>
#define _ReadOff_   LibCell_ReadOff_
#define _ReadCell_  LibCell_ReadCell_
#define _WriteCell_ LibCell_WriteCell_
//当off文件描述单形是可以用_ReadOff_
void _ReadOff_(template_m* ,char const * ,int);
void _ReadCell_(template_m*,char const *);
void _WriteCell_(template_m*,char const *);


