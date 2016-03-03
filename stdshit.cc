// stdshit.h: Single file version
// DeadFish Shitware 2013-2014
// BuildDate: 03/02/16 11:16:39

#define _STDSHIT_CC_
#ifndef _STDSHIT_X_
#include "stdshit.h"
__attribute__((section(".text$powersOf10")))
const uint powersOf10[]={1,10,100,1000,10000,
100000,1000000,10000000,100000000,1000000000};
__attribute__((section(".text$tableOfHex")))
const byte tableOfHex[2][16]={
{'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'},
{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}};
int ifloor(float f){
asm(
"subl	$8, %esp				\n\t"
"fnstcw	6(%esp)					\n\t"
"flds	12(%esp)				\n\t"
"movw	6(%esp), %ax			\n\t"
"orb	$4, %ah					\n\t"
"movw	%ax, 4(%esp)			\n\t"
"fldcw	4(%esp)					\n\t"
"fistpl	(%esp)					\n\t"
"fldcw	6(%esp)					\n\t"
"movl	(%esp), %eax			\n\t"
"addl	$8, %esp				\n\t");}
int iceil(float f){
asm(
"subl	$8, %esp				\n\t"
"fnstcw	6(%esp)					\n\t"
"flds	12(%esp)				\n\t"
"movw	6(%esp), %ax			\n\t"
"orb	$8, %ah					\n\t"
"movw	%ax, 4(%esp)			\n\t"
"fldcw	4(%esp)					\n\t"
"fistpl	(%esp)					\n\t"
"fldcw	6(%esp)					\n\t"
"movl	(%esp), %eax			\n\t"
"addl	$8, %esp				\n\t");}
SHITCALL uint snapNext(uint val){if(val&(val-1))return 0;
if(val>=2)return val<<1;return val+1;}
SHITCALL void free_ref(Void&ptr){
if(ptr!=NULL){free(ptr);ptr=NULL;}}
SHITCALL void fclose_ref(FILE*&stream){
if(stream!=NULL){fclose(stream);stream=NULL;}}
#undef fclose
SHITCALL int fclose_(FILE*stream){
if(stream==NULL)return 0;return fclose(stream);}
SHITCALL void freeLst(Void ptr,int count){if(!ptr)return;
for(int i=0;i<count;i++)free((void*)ptr.sizet(i));}
SHITCALL void freeLst_ref(Void&ptr,int count){
freeLst(ptr,count);free_ref(ptr);}
SHITCALL Void calloc(size_t size){return calloc(1,size);}
SHITCALL2
Void nxalloc(Void&ptr,size_t&count_,size_t size){
size_t result=movrl(b,count_);incml(count_);
size_t count=movrl(d,result);
int count_1=movfx(a,result-1);
result*=size;Void ptr2;
if(likely(count&count_1)){
ptr2=ptr;goto SKIP_ALLOC;}
count<<=1;if(count==0)count++;
if(!(ptr2=realloc(ptr,size*count))){
return ptr2;count_--;}ptr=ptr2;
SKIP_ALLOC:
return ptr2+result;}
SHITCALL2 Void xmalloc(size_t size){if(size==0)return NULL;return errorAlloc(malloc(size));}
SHITCALL2 Void xcalloc(size_t size){if(size==0)return NULL;return errorAlloc(calloc(1,size));}
SHITCALL2 Void xrealloc(Void&ptr,size_t size){if(size==0){free_ref(ptr);return NULL;}
return ptr=errorAlloc(realloc(ptr,size));}
SHITCALL2 Void xrecalloc(Void&ptr,size_t size){if(ptr==NULL)return(ptr=xcalloc(size));
return xrealloc(ptr,size);}
SHITCALL2 Void xmemdup8(Void src,int count){if(count==0)return NULL;
void*dst=xmalloc(count);memcpy8(dst,src,count);return dst;}
SHITCALL2 Void xmemdup16(Void src,int count){if(count==0)return NULL;
void*dst=xmalloc(count*2);memcpy16(dst,src,count);return dst;}
SHITCALL2 Void xmemdup32(Void src,int count){if(count==0)return NULL;
void*dst=xmalloc(count*4);memcpy32(dst,src,count);return dst;}
SHITCALL2
Void xnxalloc(Void&ptr,size_t&count_,size_t size){
size_t result=movrl(b,count_);incml(count_);
size_t count=movrl(d,result);
int count_1=movfx(a,result-1);
result*=size;Void ptr2;
if(likely(count&count_1)){
ptr2=ptr;goto SKIP_ALLOC;}
count<<=1;if(count==0)count++;
ptr2=xrealloc(ptr,size*count);
SKIP_ALLOC:
return ptr2+result;}
Void xvector_::xalloc_(size_t size){
this->dataSize=size;
this->allocSize=size;
return dataPtr=xmalloc(size);}
Void xvector_::xreserve_(size_t size){
if(this->allocSize>=size)
return this->dataPtr;
this->allocSize=size;
return xrealloc(this->dataPtr,size);}
Void xvector_::xresize_(size_t size){
this->dataSize=size;
ARGFIX(size);
return this->xreserve_(size);}
VoidLen REGCALL(3)xvector_alloc(
size_t reqSize,size_t curSize,xvector_*This){
size_t memSize=This->allocSize<<1;
if(memSize<reqSize)memSize=reqSize;
memSize=ALIGN(memSize,7);This->allocSize=memSize;
return VoidLen(xrealloc(This->dataPtr,memSize),curSize);}
VoidLen xvector_::xnxalloc2_(size_t size){
size_t curSize=this->dataSize;
size_t reqSize=movfx(a,curSize+size);
this->dataSize=reqSize;
Void ptr2;
if(likely(this->allocSize>=reqSize)){
ptr2=this->dataPtr;goto SKIP_ALLOC;}
{GET_RETPAIR(ptr2,curSize,xvector_alloc(
reqSize,curSize,this))};
SKIP_ALLOC:
return VoidLen(ptr2+curSize,curSize);}
VoidLen xvector_::xrxalloc2_(size_t size){
size_t curSize=this->dataSize;
size_t reqSize=movfx(a,curSize+size);
Void ptr2;
if(likely(this->allocSize>=reqSize)){
ptr2=this->dataPtr;goto SKIP_ALLOC;}
{GET_RETPAIR(ptr2,curSize,xvector_alloc(
reqSize,curSize,this))};
SKIP_ALLOC:
return VoidLen(ptr2+curSize,curSize);}
RetEdx<int>xvector_::write8(Void src,int count){VoidLen vl=
xnxalloc2_(count);memcpy8((byte*)vl.ptr,src,count);return vl.offset;}
RetEdx<int>xvector_::write16(Void src,int count){VoidLen vl=
xnxalloc2_(count*2);memcpy16((word*)vl.ptr,src,count);return vl.offset;}
RetEdx<int>xvector_::write32(Void src,int count){VoidLen vl=
xnxalloc2_(count*4);memcpy32((uint*)vl.ptr,src,count);return vl.offset;}
RetEdx<int>xvector_::write8(byte val){VoidLen vl=xnxalloc2_(1);
*(byte*)vl.ptr=val;return vl.offset;}
RetEdx<int>xvector_::write16(word val){VoidLen vl=xnxalloc2_(2);
*(word*)vl.ptr=val;return vl.offset;}
RetEdx<int>xvector_::write32(uint val){VoidLen vl=xnxalloc2_(4);
*(uint*)vl.ptr=val;return vl.offset;}
RetEdx<int>xvector_::write64(INT64 val){VoidLen vl=xnxalloc2_(8);
*(INT64*)vl.ptr=val;return vl.offset;}
#define DEF_RDTEXT(name, text) \
	__attribute__((section(".text$"#name))) \
	static const char name[] = text;
DEF_RDTEXT(str_pcs_pcs,"%s: %s");
DEF_RDTEXT(str_fatal_error,"Fatal Error");
DEF_RDTEXT(str_error,"Error");
DEF_RDTEXT(str_out_of_mem,"Out of memory/resources");
DEF_RDTEXT(str_max_path,"MAX_PATH exceeded");
DEF_RDTEXT(str_out_of_space,"Out of disk space");
DEF_RDTEXT(str_io_fail,"file IO failure");
DEF_RDTEXT(str_bad_file,"invalid file format");
DEF_RDTEXT(str_open_fileA,"Cannot open file: \"%s\"");
DEF_RDTEXT(str_open_fileW,"Cannot open file: \"%S\"");
DEF_RDTEXT(str_rbA,"rb");
#define DEF_RDTEXTW(name, text) \
	__attribute__((section(".text$"#name))) \
	static const WCHAR name[] = text;
DEF_RDTEXTW(str_rbW,L"rb");
namespace std{
DEF_RDTEXT(length_error,"length_error: %s");
__attribute__((section(".text$nothrow_t")))
const nothrow_t nothrow=nothrow_t();
void __attribute__((__noreturn__))
__throw_length_error(const char*str){fatalError(length_error,str);}}
extern"C" void*emulate_nt_new(unsigned len,const std::nothrow_t&junk){
return malloc(len);}
extern"C" void*emulate_cc_new(unsigned len){return xmalloc(len);}
extern"C" void*emulate_delete(void*p){free(p);}
void*operator new(std::size_t,const std::nothrow_t&)__attribute__((alias("emulate_nt_new")));
void*operator new[](std::size_t,const std::nothrow_t&)__attribute__((alias("emulate_nt_new")));
void*operator new (unsigned len)__attribute__((alias("emulate_cc_new")));
void*operator new[](unsigned len)__attribute__((alias("emulate_cc_new")));
void  operator delete (void*p)__attribute__((alias("emulate_delete")));
void  operator delete[](void*p)__attribute__((alias("emulate_delete")));
__attribute__((section(".bss$cxa_pure_virtual")))
void*__cxa_pure_virtual=0;
void comnError(HWND hwnd,bool fatal,
const char*fmt,va_list args){
char caption[64];char text[2048];
sprintf(caption,str_pcs_pcs,progName,
fatal?str_fatal_error:str_error);
vsprintf(text,fmt,args);
MessageBoxA(hwnd,text,caption,MB_OK);
if(fatal)ExitProcess(1);}
#define ERRORM(hwnd, fatal, x) {				\
	va_list args; va_start (args, fmt);		\
	comnError(hwnd, fatal, fmt, args);		\
	va_end (args); x; }
void fatalError(const char*fmt,...)ERRORM(
GetLastActivePopup(GetActiveWindow()),true,UNREACH);
void fatalError(HWND hwnd,const char*fmt,...)ERRORM(hwnd,true,UNREACH)
void contError(HWND hwnd,const char*fmt,...)ERRORM(hwnd,false,)
void errorAlloc(){fatalError(str_out_of_mem);}
void errorMaxPath(){fatalError(str_max_path);}
void errorDiskSpace(){fatalError(str_out_of_space);}
void errorDiskFail(){fatalError(str_io_fail);}
void errorBadFile(){fatalError(str_bad_file);}
void errorDiskWrite(){(GetLastError()==ERROR_DISK_FULL)
?errorDiskSpace():errorDiskFail();}
#include "stdshit.cc"
#include "stdshit.h"
SHITCALL
void xfread(void*ptr,size_t size,size_t num,FILE*fp){
size_t result=fread(ptr,size,num,fp);
if(result!=num){
if(ferror(fp))
errorDiskFail();
else
errorBadFile();}}
SHITCALL
void xfwrite(const void*ptr,size_t size,size_t num,FILE*fp){
size_t result=fwrite(ptr,size,num,fp);
if(result!=num)
errorDiskWrite();}
SHITCALL
void xchsize(FILE*fp,long size){
int fd=fileno(fp);
if(_chsize(fd,size))
errorDiskWrite();}
SHITCALL
int fsize(FILE*fp){
int curPos=ftell(fp);
fseek(fp,0,SEEK_END);
int endPos=ftell(fp);
fseek(fp,curPos,SEEK_SET);
return endPos-curPos;}
loadFile_t loadFile(FILE*fp,int extra){
if(!fp)return loadFile_t(0,-1);
SCOPE_EXIT(fclose(fp));
loadFile_t result;result.size=fsize(fp);
if(result.data=malloc(result.size+extra)){
memset(result.data+result.size,0,extra);
xfread(result.data,result.size,fp);
}else{min_ref(result.size,0x7FFFFFFF);}
return result;}
char**loadText(FILE*fp,int&LineCount){
if(fp==NULL){LineCount=-1;
return NULL;}LineCount=0;
int fileSize=fsize(fp);Void fileData;
{SCOPE_EXIT(if(!(fp->_flag&0x82))fclose(fp));
if(fileSize==0)return NULL;
fileData=xmalloc(fileSize+1);
xfread(fileData,1,fileSize,fp);}
Void curPos=fileData;
Void endPos=curPos+fileSize;
char**lineData=NULL;
while(curPos<endPos){
xNextAlloc(lineData,LineCount)=curPos;
Void nextPos=strchr(curPos,'\n');
if(nextPos!=NULL)nextPos[0]='\0';
else nextPos=strchr(curPos,'\0');
removeCrap((char*)curPos);
curPos=nextPos+1;}
return lineData;}
Void memmem(const void*b1,const void*b2,
size_t len1,size_t len2){
char*sp=(char*)b1;
char*pp=(char*)b2;
char*eos  =sp+len1-len2;
if(!(b1&&b2&&len1&&len2))
return NULL;
while(sp<=eos){
if(*sp==*pp)
if(memcmp(sp,pp,len2)==0)
return sp;
sp++;}
return NULL;}
int xvfprintf(FILE*stream,const char*format,va_list arg){
int result=vfprintf(stream,format,arg);
if(result<0)errorDiskWrite();return result;}
int xfprintf(FILE*stream,const char*format,...){
va_list vl;va_start(vl,format);
return xvfprintf(stream,format,vl);va_end(vl);}
void xfputs(const char*str,FILE*stream){
if(fputs(str,stream)<0)errorDiskWrite();}
#endif
cstrT cstr_len(const NCHAR*str){
int len=0;if(str!=NULL){
#if NWIDE == 0
asm("push %2; call _strlen;"
#else
asm("push %2; call _wcslen;"
#endif
"movl %%eax, %%edx; pop %%eax":"=a"(str),
"=d"(len):"g"(str):"ecx");}return{str,len};}
SHITCALL cstrT getPath(cstrT str){
int i=str.slen;
while(i--){if(isPathSep(
str[i]))return str.left(i+1);}
return cstrT(str,0);}
SHITCALL cstrT getName(cstrT str){
auto tmp=getPath(str);
return tmp.endRel(str.slen);}
#define BSTR_ALLOC() auto* This = this; if(mlen<= len) {\
	GET_RETPAIR(This, len, alloc(len)); } NCHAR* data = \
	This->data; int slen = This->slen; data[len] = 0;
template<>
bstrT::alloc_t bstrT::alloc(int len){
if(mlen==0)data=NULL;
mlen=ALIGN(max(mlen+(mlen>>1),
len+1),(8/sizeof(NCHAR))-1);
xRealloc(data,mlen);
return{this,len};}
template<>
NCHAR*bstrT::xresize(int len){BSTR_ALLOC();
This->slen=len;return data;}
template<>
NCHAR*bstrT::xnalloc(int len){len+=slen;BSTR_ALLOC();
This->slen=len;return data+slen;}
template<>
NCHAR*bstrT::xreserve(int len){
BSTR_ALLOC();return data;}
template<>
NCHAR*bstrT::xralloc(int len){len+=slen;
BSTR_ALLOC();return data+slen;}
template<>
bstrT&bstrT::strcpy(const NCHAR*str){::strcpy(xresize(
strlen(str)),str);return*this;}
template<>
bstrT&bstrT::strcpy(cstrT str){memcpyX(xresize(
str.slen),str.data,str.slen);return*this;}
template<>
bstrT&bstrT::strcat(const NCHAR*str){::strcpy(xnalloc(
strlen(str)),str);return*this;}
template<>
bstrT&bstrT::strcat(cstrT str){memcpyX(xnalloc(
str.slen),str.data,str.slen);return*this;}
template<>
bstrT&bstrT::fmtcpy(const NCHAR*fmt,...){
va_list ap;va_start(ap,fmt);
NCHAR*buff=xresize(xstrfmt_len(fmt,ap)-1);
xstrfmt_fill(buff,fmt,ap);return*this;}
template<>
bstrT&bstrT::fmtcat(const NCHAR*fmt,...){
va_list ap;va_start(ap,fmt);
NCHAR*buff=xnalloc(xstrfmt_len(fmt,ap)-1);
xstrfmt_fill(buff,fmt,ap);return*this;}
template<>
cstrT bstrT::nullTerm(void){int len=slen;
BSTR_ALLOC();return{This->data,len};}
template<>
cstrT bstrT::calcLen(void){cstrT ret=cstr_len(data);
return{ret.data,slen=ret.slen};}
template<>
cstrT bstrT::updateLen(void){cstrT ret=cstr_len(data);
return{ret.data,slen+=ret.slen};}
#undef xstrfmt_fmt_
#define xstrfmt_fmt_ MCAT(xstrfmt_fmt_,NCHAR)
struct xstrfmt_fmt_:xstrfmt_fmt<NCHAR>{
xstrfmt_fmt_(NCHAR*dstPos,va_list ap1){
flags=0,dstPosArg=dstPos;ap=ap1;}
NCHAR getFillCh(){
char fillCh=' ';
if(flags&PADD_ZEROS)
movb2(fillCh,'0');
return fillCh;}
size_t ext_mode(){size_t(__thiscall*funcPtr)
(void*ctx)=va_arg(ap,Void);return funcPtr(this);}
size_t res_mode(){size_t	extraLen=(size_t)dstPosArg;
if(extraLen==0)extraLen=width;
ei(flags&UPPER_CASE)extraLen+=width;
return extraLen;}
size_t str_mode(bool fixed);
size_t dec_mode(bool sign);
size_t hex_mode();
DEF_RETPAIR(core_t,size_t,extraLen,NCHAR*,str);
static core_t SHITCALL core(NCHAR*str,va_list*ap,NCHAR*dstPos);};
size_t xstrfmt_fmt_::str_mode(bool fixed){
NCHAR*dstPos=dstPosArg;
size_t data=va_arg(ap,size_t);
if(fixed)precision=va_arg(ap,size_t);
movfx(S,data);
NCHAR*str=(NCHAR*)data;
if(str==NULL)str=(NCHAR*)_N("(null)");
size_t strLen=precision;
if(!fixed&&(!dstPos||width))
strLen=strnlen(str,strLen);
if(dstPos==0)
return max(strLen,width);
int len=width-strLen;
if(len>0){ARGFIX(flags);
NCHAR fillCh=getFillCh();
do{stosx(dstPos,fillCh);
}while(--len>0);}
if(fixed==true){
memcpy_ref(dstPos,str,strLen);
return(size_t)dstPos;}
NCHAR*endPos=str+strLen;asm goto(
"jmp %l1"::"r"(endPos)::LOOP_START);
do{{NCHAR ch;lodsx(str,ch);
if(ch=='\0')break;
stosx(dstPos,ch);}
LOOP_START:;
}while(str!=endPos);
return(size_t)dstPos;}
size_t xstrfmt_fmt_::dec_mode(bool sign){
NCHAR*dstPos=dstPosArg;
size_t data=va_arg(ap,size_t);
NCHAR signCh=0;
if(sign!=0){if(int(data)<0){
signCh='-';data=-data;}
ei(flags&SPACE_POSI)signCh=' ';
ei(flags&FORCE_SIGN)signCh='+';
}int strLen=1;
for(;strLen<ARRAYSIZE(powersOf10);strLen++){
if(powersOf10[strLen]>data)break;}
strLen=max(strLen+bool(signCh),width);
if(dstPos==NULL)return strLen;
NCHAR*endPos=dstPos+strLen;
NCHAR*curPos=endPos;
do{*(--curPos)='0'+data%10;
}while(data/=10);
if(curPos>dstPos){
NCHAR fillCh;
if(flags&PADD_ZEROS){
if(signCh)stosx(dstPos,signCh);
fillCh='0';
}else{
if(signCh)*(--curPos)=signCh;
fillCh=' ';}
while(curPos-->dstPos)
*curPos=fillCh;
}return(size_t)endPos;}
size_t xstrfmt_fmt_::hex_mode(void){
INT64 data=(length>=2)?
va_arg(ap,INT64):va_arg(ap,size_t);
int maxBit=(DWORD(data>>32))?
32+(__builtin_clz(data>>32)^31):(__builtin_clz(data|1)^31);
size_t strLen=max((maxBit+4)/4,width);
if(dstPosArg==NULL)return strLen;
NCHAR*endPos=dstPosArg+strLen;
NCHAR*curPos=endPos;
const byte*hexTab=(flags&UPPER_CASE)?
tableOfHex[1]:tableOfHex[0];
do{*(--curPos)=hexTab[data&15];
}while(data>>=4);
NCHAR fillCh=getFillCh();
while(curPos-->dstPosArg)
*curPos=fillCh;
return(size_t)endPos;}
xstrfmt_fmt_::core_t xstrfmt_fmt_::core(
NCHAR*str,va_list*ap,NCHAR*dstPos){
xstrfmt_fmt_ ctx(dstPos,*ap);
SCOPE_EXIT(*ap=ctx.ap);
NCHAR ch;NCHAR ch2;
while(lodsx(str,ch),ch2=ch-' ',
(ch2<17)&&(ch!='*')&&(ch!='.'))
ctx.flags|=1<<ch2;
int*dst=&ctx.width;
GET_INT_NEXT:{int result;
if(ch=='*'){lodsx(str,ch);
result=va_arg(ctx.ap,int);}
else{result=0;byte tmp;
while((tmp=ch-'0')<10){result*=10;
result+=tmp;lodsx(str,ch);}
}*dst=movfx(D,result);
if(dst==&ctx.width){
dst=&ctx.precision;*dst=0x7FFFFFFF;
if(ch=='.'){lodsx(str,ch);
goto GET_INT_NEXT;}}}
ctx.length=0;LENGTH_NEXT:
if(ch=='h'){ctx.length--;lodsx(str,ch);goto LENGTH_NEXT;}
if(ch=='l'){ctx.length++;lodsx(str,ch);goto LENGTH_NEXT;}
if(ch<'a'){asm("add $32, %0":"=r"(ch):"r"(ch));ctx.flags|=UPPER_CASE;}
size_t extraLen;
if(ch=='s')extraLen=ctx.str_mode(false);
ei(ch=='v')extraLen=ctx.str_mode(true);
ei(ch>'s')extraLen=(ch=='x')?ctx.hex_mode():ctx.dec_mode(false);
ei(ch=='q')extraLen=ctx.ext_mode();
else extraLen=(ch>'q')?ctx.res_mode():ctx.dec_mode(true);
return core_t(extraLen,str);}
SHITCALL
int xstrfmt_len(const NCHAR*fmt,va_list ap){
int extraLen=1;NCHAR ch;
NCHAR*curPos=(NCHAR*)fmt;
while(lodsx(curPos,ch),ch){
if(ch!='%'){
ESCAPE_PERCENT:extraLen++;}
ei(*curPos=='%'){curPos++;
goto ESCAPE_PERCENT;}
else{
auto result=xstrfmt_fmt_::core(
curPos,&ap,0);
curPos=result.str;
extraLen+=result.extraLen;}
}return extraLen;}
SHITCALL
NCHAR*xstrfmt_fill(NCHAR*buffer,
const NCHAR*fmt,va_list ap){
DEF_ESI(NCHAR*curPos)=(NCHAR*)fmt;
DEF_EDI(NCHAR*dstPos)=buffer;
while(1){
NCHAR ch;lodsx(curPos,ch);
if(ch!='%'){ESCAPE_PERCENT:
stosx(dstPos,ch);
if(ch=='\0')return dstPos;}
ei(*curPos=='%'){curPos++;
goto ESCAPE_PERCENT;}
else{
auto result=xstrfmt_fmt_::core(
curPos,&ap,dstPos);
curPos=result.str;
dstPos=(NCHAR*)result.extraLen;}}
return dstPos;}
SHITCALL
cstrT xstrfmt(const NCHAR*fmt,...){
va_list ap;va_start(ap,fmt);
NCHAR*buffer=xMalloc(xstrfmt_len(fmt,ap));
NCHAR*endPos=xstrfmt_fill(buffer,fmt,ap);
return{buffer,(endPos-1)-buffer};}
SHITCALL int strfmt(NCHAR*buffer,
const NCHAR*fmt,...){
va_list ap;va_start(ap,fmt);
NCHAR*endPos=xstrfmt_fill(buffer,fmt,ap);
return(endPos-1)-buffer;}
void xvector_::fmtcat(const NCHAR*fmt,...){
va_list ap;va_start(ap,fmt);
int strLen=xstrfmt_len(fmt,ap)*sizeof(NCHAR);
NCHAR*buffer=xnxalloc_(strLen);
dataSize-=sizeof(NCHAR);
xstrfmt_fill(buffer,fmt,ap);}
RetEdx<int>xvector_::strcat2(const NCHAR*str){
return this->write(str,strlen(str)+1);}
int xvector_::strcat(const NCHAR*str){
int strLen=strlen(str);
this->write(str,strLen+1);
dataSize-=sizeof(NCHAR);
return strLen;}
SHITCALL NCHAR*strstr(const NCHAR*str1,const NCHAR*str2,int maxLen){
int cmpLen=strlen(str2)-1;
if(cmpLen<0)return NULL;
const NCHAR*endPos=(maxLen<0)?(NCHAR*)size_t(-1)
:str1+(maxLen-cmpLen);
NCHAR findCh=*str2++;NCHAR ch;
while((str1<endPos)&&((lodsx(str1,ch),ch)))
if((ch==findCh)&&(!strncmp(str1,str2,cmpLen)))
return(NCHAR*)str1-1;
return NULL;}
SHITCALL NCHAR*strstri(const NCHAR*str1,const NCHAR*str2,int maxLen){
int cmpLen=strlen(str2)-1;
if(cmpLen<0)return NULL;
const NCHAR*endPos=(maxLen<0)?(NCHAR*)size_t(-1)
:str1+(maxLen-cmpLen);
NCHAR findCh=toUpper(*str2++);NCHAR ch;
while((str1<endPos)&&((lodsx(str1,ch),ch=toUpper(ch))))
if((ch==findCh)&&(!strnicmp(str1,str2,cmpLen)))
return(NCHAR*)str1-1;
return NULL;}
SHITCALL size_t strnlen(const NCHAR*str,size_t maxLen){
size_t len=0;
for(;str[len]&&(len<maxLen);len++);
return len;}
SHITCALL cstrT xstrdup(const NCHAR*str){
if(str==NULL)return{0,0};
int len=strlen(str);
NCHAR*ret=xMalloc(len+1);
return{strcpy(ret,str),len};}
SHITCALL cstrT xstrdup(const NCHAR*str,size_t maxLen){
if(str==NULL)return NULL;
int strLen=strnlen(str,maxLen);
NCHAR*buffer=xMalloc(strLen+1);
return strcpyn(buffer,str,strLen);}
SHITCALL
FILE*xfopen(const NCHAR*fName,const NCHAR*mode){
bool chkOpen=false;
if(mode[0]=='!'){
chkOpen=true;
mode++;}
LRETRY:
FILE*fp=fopen(fName,mode);
if(fp==NULL){
switch(errno){
case ENOENT:
case EACCES:
case EISDIR:
case EINVAL:
if(chkOpen)
#if NWIDE
fatalError(str_open_fileW,fName);
#else
fatalError(str_open_fileA,fName);
#endif
break;
case ENOSPC:
errorDiskSpace();
goto LRETRY;
default:
errorAlloc();}}
return fp;}
SHITCALL
NCHAR*xfgets(NCHAR*str,int num,FILE*fp){
NCHAR*tmp=fgets(str,num,fp);
if((!tmp)&&(ferror(fp)))
errorDiskFail();
return tmp;}
SHITCALL
loadFile_t loadFile(const NCHAR*fileName,int extra){
#if NWIDE
return loadFile(xfopen(fileName,str_rbW),extra);}
#else
return loadFile(xfopen(fileName,str_rbA),extra);}
#endif
SHITCALL
char**loadText(const NCHAR*fileName,int&LineCount){
#if NWIDE
return loadText(xfopen(fileName,str_rbW),LineCount);}
#else
return loadText(xfopen(fileName,str_rbA),LineCount);}
#endif
SHITCALL
NCHAR*xstrdupr(NCHAR*&str1,const NCHAR*str2){
return free_repl(str1,xstrdup(str2));}
SHITCALL
NCHAR*xstrdupr(NCHAR*&str1,const NCHAR*str2,size_t sz){
return free_repl(str1,xstrdup(str2,sz));}
SHITCALL
int strcmp2(const NCHAR*str1,const NCHAR*str2){
for(const NCHAR*curPos=str2;;curPos++){
NCHAR ch1;lodsx(str1,ch1);
NCHAR ch2=*curPos;
if(ch1!=ch2)return curPos-str2;
if(ch2==0)return-1;}}
SHITCALL
int stricmp2(const NCHAR*str1,const NCHAR*str2){
for(const NCHAR*curPos=str2;;curPos++){
NCHAR ch1;lodsx(str1,ch1);ch1=toUpper(ch1);
NCHAR ch2=toUpper(*curPos);
if(ch1!=ch2)return curPos-str2;
if(ch2==0)return-1;}}
SHITCALL
NCHAR*strScmp(const NCHAR*str1,const NCHAR*str2){
while(1){
NCHAR ch2;lodsx(str2,ch2);
if(ch2==0)
return(NCHAR*)str1;
if(ch2!=*str1++)
return NULL;}}
SHITCALL
NCHAR*strSicmp(const NCHAR*str1,const NCHAR*str2){
while(1){NCHAR ch2;
lodsx(str2,ch2);ch2=toUpper(ch2);
if(ch2==0)
return(NCHAR*)str1;
if(ch2!=toUpper(*str1++))
return NULL;}}
SHITCALL
int strEcmp(const NCHAR*str1,const NCHAR*str2){
int diff=strlen(str1)-strlen(str2);
if(diff<0)
return 1;
return strcmp(str1+diff,str2);}
SHITCALL
int strEicmp(const NCHAR*str1,const NCHAR*str2){
int diff=strlen(str1)-strlen(str2);
if(diff<0)
return 0;
return stricmp(str1+diff,str2);}
SHITCALL
int strNcpy(NCHAR*dst,const NCHAR*src,int num){
for(int i=0;i<num;i++)
if(!(dst[i]=src[i]))
return i;
if(num>=0)
dst[num]='\0';
return num;}
SHITCALL cstr_<NCHAR>strcpyn(
NCHAR*dst,const NCHAR*src,int len){
memcpyX(dst,src,len);
dst[len]='\0';return{dst,len};}
SHITCALL
bool strcmpn(const NCHAR*str1,const NCHAR*str2,int len){
if(strlen(str1)!=len)
return false;
return!strncmp(str1,str2,len);}
SHITCALL
bool stricmpn(const NCHAR*str1,const NCHAR*str2,int len){
if(strlen(str1)!=len)
return false;
return!strnicmp(str1,str2,len);}
SHITCALL
int removeCrap(NCHAR*str){
int len=strlen(str);
while(len--)
if(unsigned(str[len])>' ')
break;
str[len+1]='\0';
return len+1;}
SHITCALL
int strmove(NCHAR*dst,const NCHAR*src){
int len=strlen(src)+1;
memmove(dst,src,len*sizeof(NCHAR));
return len;}
SHITCALL
int getPathLen(const NCHAR*fName){
int i=strlen(fName);
while(i--){
if((fName[i]=='\\')
||(fName[i]=='/'))
return i+1;}
return 0;}
SHITCALL
int getPath(NCHAR*fName){
int len=getPathLen(fName);
fName[len]='\0';
return len;}
SHITCALL
NCHAR*getName(const NCHAR*fName)
{return(NCHAR*)fName+getPathLen(fName);}
SHITCALL
int getName(NCHAR*dst,const NCHAR*src,size_t max){
NCHAR*name=getName(src);
return strNcpy(dst,src,max-1);}
SHITCALL
bool isFullPath(const NCHAR*path){
if(path
&&((isPathSep(path[0]))
||(path[1]==':')))
return true;
return false;}
int _vsnprintf_s(NCHAR*buffer,size_t sizeOfBuffer,
const NCHAR*format,va_list ap){
if(sizeOfBuffer!=0){
#if NWIDE
size_t result=_vsnwprintf(buffer,sizeOfBuffer,format,ap);
#else
size_t result=_vsnprintf(buffer,sizeOfBuffer,format,ap);
#endif
if(result<sizeOfBuffer)
return result;
buffer[sizeOfBuffer-1]='\0';}
return-1;}
int sprintf_s(NCHAR*buffer,size_t sizeOfBuffer,
const NCHAR*format,...){
int count;va_list ap;
va_start(ap,format);
count=_vsnprintf_s(buffer,sizeOfBuffer,format,ap);
va_end(ap);return count;}