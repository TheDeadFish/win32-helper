// stdshit.h: Single file version
// DeadFish Shitware 2013-2014
// BuildDate: 03/02/16 11:16:39

#ifndef _STDSHIT_H_
#ifndef _STDSHIT_X_
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#define MCAT2(name, ...) name##__VA_ARGS__
#define MCAT(name, ...) MCAT2(name, __VA_ARGS__)
#define EXTRACT(...) EXTRACT __VA_ARGS__
#define NOTHING_EXTRACT
#define UNPAREN(x) MCAT(NOTHING_, EXTRACT x)
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,##__VA_ARGS__, 4, 3, 2, 1, 0)
#define VARARG_IMPL2(base, count, ...) base##count(__VA_ARGS__)
#define VARARG_IMPL(base, count, ...) VARARG_IMPL2(base, count, __VA_ARGS__)
#define VARARG(base, ...) VARARG_IMPL(base, VA_NARGS(__VA_ARGS__), __VA_ARGS__)
#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0 (EVAL0 (EVAL0 (__VA_ARGS__)))
#define EVAL2(...) EVAL1 (EVAL1 (EVAL1 (__VA_ARGS__)))
#define EVAL3(...) EVAL2 (EVAL2 (EVAL2 (__VA_ARGS__)))
#define EVAL4(...) EVAL3 (EVAL3 (EVAL3 (__VA_ARGS__)))
#define EVAL(...)  EVAL4 (EVAL4 (EVAL4 (__VA_ARGS__)))
#define MAP_END(...)
#define MAP_OUT
#define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0 (test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1 (MAP_GET_END test, next)
#define MAP0(f, x, peek, ...) f(x) MAP_NEXT (peek, MAP1) (f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT (peek, MAP0) (f, peek, __VA_ARGS__)
#define MAP(f, ...) EVAL (MAP1 (f, __VA_ARGS__, (), 0))
template<class T,class U>
union _CAST_{T src;U dst;};
#define CAST(type, x) (((_CAST_<typeof(x), type>*)&(x))->dst)
#define PCST(type, x) (((_CAST_<typeof(*x), type>*)(x))->dst)
#define ALWAYS_INLINE __inline__ __attribute__((always_inline))
#define NEVER_INLINE __attribute__ ((noinline))
#define NORETURN  __attribute__((noreturn))
#define UNREACH __builtin_unreachable()
#define FATALFUNC __attribute__((noreturn,cold))
#define NOTHROW __attribute__((__nothrow__))
#define getReturn() __builtin_return_address(0)
#define TLS_VAR __thread
#define TLS_EXTERN extern __thread
#define INITIALIZER(f) \
 __attribute__((constructor)) void f(void)
#define REGCALL(x) __attribute__((stdcall,regparm(x)))
#define SHITCALL2 __fastcall
#define SHITCALL __stdcall
#define SHITSTATIC __stdcall static
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#define ARGFIX(arg) asm("" : "+m"(arg));
#define VARFIX(var) asm("" : "+g"(var));
#define REF_SYMBOL(symb)  asm(".def	_"#symb";	.scl	2;	.type	32;	.endef")
#define VOIDPROC(proc) Void((void*)&proc)
#define PACK1(...) _Pragma("pack(push, 1)") __VA_ARGS__ _Pragma("pop")
#define TMPL(t) template <class t>
#define TMPL2(t,u) template <class t, class u>
#define _MCSE(arg) case arg:
#define MCSE(...) MAP(_MCSE, __VA_ARGS__)
#define HOTCALL(ftype, addr) (*((typeof(&ftype))(size_t(addr))))
#define __assume(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
#define ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
#define ZINIT memfillX(*this);
#define ei else if
#define THIS_NULL_CHECK() if(this == NULL) return 0;
#define ALIGN4(arg) ALIGN(arg, 3)
#define ALIGN_PAGE(arg) ALIGN(arg, 4095)
static inline size_t ALIGN(size_t arg,size_t bound)
{return((arg+bound)&~bound);}
#define PTRADD(ptr, offset) (ptr = Void(ptr)+(offset))
#define PTRDIFF(ptr1, ptr2) (size_t(ptr1)-size_t(ptr2))
#define offsetof(st, m) ((size_t)(&((st *)0)->m))
#define endsetof(st, m) ((size_t)((&((st *)0)->m)+1))
#define rangeof(st, m1, m2) (endsetof(st,m2)-offsetof(st,m1))
#define RangeOf(m1,m2) (size_t((&m2)+1)-size_t(&m1))
#define RANGE_ARG(m1, m2) (byte*)&m1, RangeOf(m1,m2)
#define RANGE2_ARG(src, m1, m2) (byte*)&m1, src, RangeOf(m1,m2)
#define RANGE_ARGX(m1, m2) &m1, RangeOf(m1,m2)
#define RANGE2_ARGX(src, m1, m2) &m1, src, RangeOf(m1,m2)
#define TMPNAME(name) MCAT(name,__LINE__)
#define DEF_BEGINEND(type, ptr, len) \
	type* begin(size_t ofs=0) { return ((type*)ptr)+ofs; } \
	type* end(size_t ofs=0) { return ((type*)(ptr+len))+ofs; } \
	operator type*() { return ptr; }
#define DEF_RETPAIR_(n1,n2,T,a,U,b,x,y) struct n1{union{T a;T m1;};union\
	{U b;U m2;};n2(){}n2(T ai){a=ai;} n2(T ai,U bi){a=ai;b=bi;}\
	operator T&(){return a;}x operator->(){return y;}};
#define DEF_RETPAIR(n,T,a,U,b) DEF_RETPAIR_(n,n,T,a,U,b,T,a)
#define DEF_RETPAIR2(n,T,a,U,b) DEF_RETPAIR_(n,n,T,a,U,b,U,b)
#define DEF_RETPAIR3(n,n2,T,a,U,b) DEF_RETPAIR_(n,n2,T,a,U,b,U,b)
#define GET_RETPAIR2(var1, var2, call) auto TMPNAME(RPTmp)=call;\
	var1 TMPNAME(RPTmp).m1;var2 TMPNAME(RPTmp).m2;
#define GET_RETPAIR(var1, var2, call) GET_RETPAIR2(var1=, var2=, call)
TMPL(T)struct RetEdx{int eax;T edx;RetEdx(int var)
{asm("":"=a"(eax));edx=var;}operator T&(){return edx;}};
TMPL(T)bool _BTST(T&var,int bit){return var&(1<<bit);}
TMPL(T)bool _BSET(T&var,int bit){
bool result=_BTST(var,bit);var|=(1<<bit);return result;}
TMPL(T)bool _BCLR(T&var,int bit){
bool result=_BTST(var,bit);var&=~(1<<bit);return result;}
typedef unsigned char 	byte;
typedef unsigned short 	word;
typedef unsigned int 	uint;
typedef unsigned int 	u32;
typedef signed int 		s32;
typedef unsigned char 	u8;
typedef signed char 	s8;
typedef unsigned short 	u16;
typedef signed short 	s16;
static inline INT32 iDiv6432(INT64 num,INT32 dom){UINT32 result;
asm("idivl %2":"=a"(result):"A"(num),"rm"(dom));return result;}
static inline UINT32 uDiv6432(UINT64 num,UINT32 dom){UINT32 result;
asm("divl %2":"=a"(result):"A"(num),"rm"(dom));return result;}
TMPL2(T,U=T)T release(T&ptr,U newPtr=0){
T tmpPtr=ptr;ptr=newPtr;return tmpPtr;}
TMPL2(T,U=T)T replace(T&ptr,U newPtr){
free(ptr);return ptr=newPtr;}
#define free_repl(ptr, newPtr) (::free(ptr), ptr = newPtr)
#define ADDP(ptr, len) asm(".if %c1 == 1\n\tinc %0\n\t.elseif %c1 == -1\n\t" \
	"dec %0\n\t.else\n\tlea %c1(%0),%0\n\t.endif" : "+r"(ptr) : "e"(len));
#define INCP(ptr) ADDP(ptr, sizeof(*ptr))
#define WRI(ptr, data) ({ VARFIX(ptr); *ptr = data; INCP(ptr); })
#define RDI(ptr) ({ RDI2(ptr, auto ret); ret;})
#define RDI2(ptr, data) VARFIX(ptr); data = *ptr; INCP(ptr);
#define swapReg(x, y) asm("XCHG %0, %1" : "+r"(x), "+r"(y));
#define DEF_PX(n,T) TMPL(Z) T*& MCAT(P,n)(Z& p) { return CAST(T*, p); } \
	TMPL(Z) T& MCAT(R,n)(Z p, size_t o=0,size_t n=0) { return ((T*)(PB(p)+o))[n]; } \
	TMPL(Z) T* MCAT(P,n)(Z p, size_t o,size_t n=0) { return &MCAT(R,n)(PB(p), o, n); }
DEF_PX(B,BYTE)DEF_PX(C,CHAR)DEF_PX(S,INT16)DEF_PX(W,WORD)
DEF_PX(I,INT32)DEF_PX(U,DWORD)DEF_PX(L,INT64)DEF_PX(Q,UINT64)
DEF_PX(T,SIZE_T)DEF_PX(R,SSIZE_T)DEF_PX(F,float)DEF_PX(D,double)
#include <type_traits>
template<bool T,typename V>
using enable_if_t=typename std::enable_if<T,V>::type;
template<bool B,class T,class F>
using conditional_t=typename std::conditional<B,T,F>::type;
TMPL(T)
enable_if_t<!std::is_class<T>::value,bool>isNeg(const T&value)
{return(typename std::make_signed<T>::type)(value)<0;}
struct is_cstyle_castable_impl{
template<typename _From,typename _To,typename
=decltype((_To)(std::declval<_From>()))>
static std::true_type __test(int);
template<typename,typename>
static std::false_type __test(...);};
template<typename _From,typename _To>
struct is_cstyle_castable
:public std::integral_constant<bool,(decltype(
is_cstyle_castable_impl::__test<_From,_To>(0))::value)>{};
#include <tuple>
#define MakeDelegate(obj, func) \
	decltype(Delegate_(obj, func))::Bind<func>(obj)
template<class R,class... P>
struct Delegate{
Delegate(){}Delegate(void*stub){stub_ptr=(stub_type)stub;}
Delegate(void*object,void*stub){
object_ptr=object;stub_ptr=(stub_type)stub;}
TMPL(T)
void set(T object,R(__thiscall*stub)(T,P... params))
{object_ptr=(void*)object;
stub_ptr=(stub_type)stub;}
TMPL(T)
void set(T*object,R(T::*stub)(P... params))
{object_ptr=(void*)object;
stub_ptr=(void*)(object_ptr->*stub);}
R operator()(P... params)const
{return(*stub_ptr)(object_ptr,params...);}
bool isValid(void)
{return(stub_ptr!=0);}
typedef R(__thiscall*stub_type)
(void*object_ptr,P... params);
void*object_ptr;
stub_type stub_ptr;};
template<class R,class... P>
struct MemberFunc{
MemberFunc(){}
MemberFunc(void*stub){stub_ptr=(stub_type)stub;}
R operator()(void*object_ptr,P... params)const
{return(*stub_ptr)(object_ptr,params...);}
bool isValid(void)
{return(stub_ptr!=0);}
typedef R(__thiscall*stub_type)
(void*object_ptr,P... params);
stub_type stub_ptr;};
#define DELEGATE_WCTX(nm, cv, ck) template <class T, class R, typename... P> struct nm {template \
<R (cv *TMethod)(T*, P...)> struct Bind { Bind(T* ctx) { object_ptr = (void*)ctx; } void* \
object_ptr; template <class RO, class... PO> static RO __thiscall stub(void* ctx, PO... params) {\
return TMethod((T*)ctx, params...); } template <class RO, class... PO> operator Delegate<RO, \
PO...>() { UNPAREN(ck); return Delegate<RO, PO...>(object_ptr, (void*)&stub<RO, PO...>); }};}; \
template <class T, class R, typename... P> nm<T, R, P...> Delegate_(T* obj, R (cv *TMethod)(T*, \
P... params)) { return nm<T, R, P...>(); }
DELEGATE_WCTX(Delegate_cdecl,,);DELEGATE_WCTX(Delegate_std,__stdcall,);
DELEGATE_WCTX(Delegate_this,__thiscall,(if(std::is_same
<std::tuple<P...>,std::tuple<PO...>>::value)return Delegate<RO,PO...>(0,(void*)TMethod);));
#define DELEGATE_WOCTX(nm, cv, ck) template <class R, typename... P> struct nm { template <R (cv \
*TMethod)(P...)> struct Bind { Bind(int dummy) {} template <class RO, class... PO> static RO \
__thiscall stub(void* ctx, PO... params) {	return TMethod(params...); } template <class RO,  \
class... PO> operator Delegate<RO, PO...>() { UNPAREN(ck); return Delegate<RO, PO...>((void*)0, \
(void*)&stub<RO, PO...>); }};}; template <class R, typename... P> nm<R, P...> Delegate_( \
int dummy, R (cv *TMethod)(P... params)) { return nm<R, P...>(); }
DELEGATE_WOCTX(Delegate_noctx,,)DELEGATE_WOCTX(Delegate_noctx2,__stdcall,(if(std::is_same
<std::tuple<P...>,std::tuple<PO...>>::value)return Delegate<RO,PO...>(0,(void*)TMethod);))
template<class S,class T,class R,typename... P>
struct Delegate_member{
template<R(T::*TMethod)(P...)>
struct Bind{
Bind(S*ctx){object_ptr=(void*)static_cast<T*>(ctx);}
void*object_ptr;
template<class RO,class... PO>
static RO __thiscall stub(void*ctx,PO... params)
{return(((T*)ctx)->*TMethod)(params...);}
template<class RO,class... PO>
operator Delegate<RO,PO...>(){
if(std::is_same<std::tuple<P...>,std::tuple<PO...>>::value)
return Delegate<RO,PO...>(object_ptr,
(void*)(((T*)object_ptr)->*TMethod));
return Delegate<RO,PO...>(
object_ptr,(void*)&stub<RO,PO...>);}
operator MemberFunc<R,P...>(){
Delegate<R,P...>delgate=*this;
return MemberFunc<R,P...>((void*)delgate.stub_ptr);}};};
template<class S,class T,class R,typename... P>Delegate_member<S,T,R,P...>Delegate_(
S*obj,R(T::*TMethod)(P... params)){return Delegate_member<S,T,R,P...>();}
template<typename T,typename U>
struct helper:helper<T,decltype(&U::operator())>{};
template<typename T,typename C,typename R,typename... A>
struct helper<T,R(C::*)(A...)const>{
static const bool value=std::is_convertible<T,R(*)(A...)>::value;};
template<typename T>struct is_stateless{
static const bool value=helper<T,T>::value;};
template<class F>
struct Delegate_lambda{const F&func;
Delegate_lambda(const F&func_):func(func_){}
template<class RO,class... PO>
static RO __thiscall stub(void*ctx,PO... params)
{return(*(F*)ctx)(params...);}
template<class RO,class... PO>
operator Delegate<RO,PO...>(){return Delegate<RO,PO...>(
is_stateless<F>::value?0:(void*)&func,(void*)&stub<RO,PO...>);}};
template<class F>
Delegate_lambda<F>MakeDlgtLmbd(const F&func)
{return Delegate_lambda<F>(func);}
template<class T,class F>
struct Delegate_lambda2{const F&func;T*obj;
Delegate_lambda2(T*obj_,const F&func_):obj(obj_),func(func_){}
template<class RO,class... PO>
static RO __thiscall stub(void*ctx,PO... params)
{return(*(F*)0)((T*)ctx,params...);}
template<class RO,class... PO>
operator Delegate<RO,PO...>(){return Delegate<RO,PO...>(
(void*)obj,(void*)&stub<RO,PO...>);}};
template<class T,class F>
Delegate_lambda2<T,F>MakeDlgtLmbd(T*obj,const F&func)
{return Delegate_lambda2<T,F>(obj,func);}
#define DEF_EAX(arg) register arg asm ("eax")
#define DEF_EBX(arg) register arg asm ("ebx")
#define DEF_ECX(arg) register arg asm ("ecx")
#define DEF_EDX(arg) register arg asm ("edx")
#define DEF_ESI(arg) register arg asm ("esi")
#define DEF_EDI(arg) register arg asm ("edi")
#define movzx(o,p,r) ({ \
	if(sizeof(p) == 1) asm("movzbl %1, %0" : "="#r(o) : "m"(p)); \
	ei(sizeof(p) == 2) asm("movzwl %1, %0" : "="#r(o) : "m"(p)); })
#define lodsx(ptr, ax) ({if(sizeof(ax) == 1) lodsb(ptr, ax); \
	ei(sizeof(ax) == 2) lodsw(ptr, ax); else lodsl(ptr, ax);})
#define lodsb(ptr, ax) ({ asm ("lodsb" :"=a"(ax), "=S"(ptr) : "a"(ax), "S"(ptr)); })
#define lodsw(ptr, ax) ({ asm ("lodsw" :"=a"(ax), "=S"(ptr) : "a"(ax), "S"(ptr)); })
#define lodsl(ptr, ax) ({ asm ("lodsl" :"=a"(ax), "=S"(ptr) : "a"(ax), "S"(ptr)); })
#define stosx(ptr, ax) ({if(sizeof(ax) == 1) stosb(ptr, ax); \
	ei(sizeof(ax) == 2) stosw(ptr, ax); else stosl(ptr, ax);})
#define stosb(ptr, ax) ({ asm volatile ("stosb" : "=D"(ptr) : "D"(ptr), "a"(ax)); })
#define stosw(ptr, ax) ({ asm volatile ("stosw" : "=D"(ptr) : "D"(ptr), "a"(ax)); })
#define stosl(ptr, ax) ({ asm volatile ("stosl" : "=D"(ptr) : "D"(ptr), "a"(ax)); })
#define incml(ptr) ({ \
	asm ("incl %0" :"=m"(ptr) : "m"(ptr)); })
#define movfx(reg, data) ({ typeof(data) _x86bits_ = data;\
	asm volatile ("" :: #reg(_x86bits_)); _x86bits_; })
#define movbx2(dest, data, d, s) ({ asm ("movb %b2, %b0" \
	: "="#d(dest) : "0"(dest), #s(data)); })
#define movwx2(dest, data, d, s) ({ asm ("movw %w2, %w0" \
	: "="#d(dest) : "0"(dest), #s(data)); })
#define movlx2(dest, data, d, s) ({ asm ("movl %k2, %k0" \
	: "="#d(dest) : "0"(dest), #s(data)); })
#define movb2(dest, data) movbx2(dest, data, r, g)
#define movw2(dest, data) movwx2(dest, data, r, g)
#define movl2(dest, data) movlx2(dest, data, r, g)
#define movrb2(reg, dest, data) movbx2(dest, data, reg, g)
#define movrw2(reg, dest, data) movwx2(dest, data, reg, g)
#define movrl2(reg, dest, data) movlx2(dest, data, reg, g)
#define movbx(data, d, s) ({ typeof(data) _x86bits_; \
	asm ("movb %b1, %b0" : "="#d(_x86bits_) : #s(data)); _x86bits_; })
#define movwx(data, d, s)({ typeof(data) _x86bits_; \
	asm ("movw %w1, %w0" : "="#d(_x86bits_) : #s(data)); _x86bits_; })
#define movlx(data, d, s) ({ typeof(data) _x86bits_; \
	asm ("movl %k1, %k0" : "="#d(_x86bits_) : #s(data)); _x86bits_; })
#define movbb(data) movbx(data, g, g)
#define movww(data) movwx(data, g, g)
#define movll(data) movlx(data, g, g)
#define movrb(reg, data) movbx(data, reg, g)
#define movrw(reg, data) movwx(data, reg, g)
#define movrl(reg, data) movlx(data, reg, g)
#define nothing() ({ asm(" "); })
#define clobber(reg) asm("" ::: "%"#reg);
template<class T,class U>
typename std::common_type<T&&,U&&>::type
min(T&&a,U&&b){
if(b<a)
return std::forward<U>(b);
return std::forward<T>(a);}
template<class T,class U>
typename std::common_type<T&&,U&&>::type
max(T&&a,U&&b){
if(b>a)
return std::forward<U>(b);
return std::forward<T>(a);}
template<class T,class U,class V>
typename std::common_type<T&&,
typename std::common_type<U&&,V&&>::type>::type
min_max(T&&val,U&&low,V&&high){
if(val<low)return std::forward<U>(low);
if(val>high)return std::forward<V>(high);
return std::forward<T>(val);}
template<class T,class U>
T&min_ref(T&obj,const U&val){if(obj>val)obj=val;return obj;}
template<class T,class U>
T&min1_ref(T&obj,const U&val){if(obj>=val)obj=val-1;return obj;}
template<class T,class U>
T&max_ref(T&obj,const U&val){if(obj<val)obj=val;return obj;}
#include <algorithm>
template<typename _ForwardIterator,typename _Tp>
size_t lower_bound(_ForwardIterator __first,size_t length,const _Tp&__val)
{return std::lower_bound(__first,__first+length,__val)-__first;}
template<typename _ForwardIterator,typename _Tp,typename _Compare>
size_t lower_bound(_ForwardIterator __first,size_t length,const _Tp&__val,_Compare __comp)
{return std::lower_bound(__first,__first+length,__val,__comp)-__first;}
template<typename _ForwardIterator,typename _Tp>
size_t upper_bound(_ForwardIterator __first,size_t length,const _Tp&__val)
{return std::upper_bound(__first,__first+length,__val)-__first;}
template<typename _ForwardIterator,typename _Tp,typename _Compare>
size_t upper_bound(_ForwardIterator __first,size_t length,const _Tp&__val,_Compare __comp)
{return std::upper_bound(__first,__first+length,__val,__comp)-__first;}
TMPL(T)
struct IndexRef{int offset;IndexRef(){}
IndexRef(int in){offset=in;}
operator int(){return offset;}};
struct Void{
char*data;Void(){}
TMPL(T)Void(T in,size_t o=0){data=((char*)in)+o;}
TMPL(T)Void operator=(T in){data=(char*)in;return*this;}
TMPL(T)operator T(){return(T)data;}
TMPL(T)operator T()const 	{return(T)data;}
Void operator++(int){return this->data++;}
Void operator--(int){return this->data--;}
Void operator+=(Void offset){return data+=size_t(offset.data);}
Void operator-=(Void offset){return data-=size_t(offset.data);}
Void operator+(size_t offset){return data+offset;}
unsigned char&operator[](size_t n){return*(unsigned char*)(data+n);}
unsigned char&operator*(){return*(unsigned char*)(data+0);}
TMPL(T)T*&ptr(void){return*(T**)&data;}
TMPL(T)T&ref(size_t n=0){return Ref<T>(0,n);}
TMPL(T)T*ptr(size_t n){return Ptr<T>(0,n);}
BYTE&byte(size_t n=0){return Byte(0,n);}
WORD&word(size_t n=0){return Word(0,n);}
DWORD&dword(size_t n=0){return Dword(0,n);}
size_t sizet(size_t n=0){return Sizet(0,n);}
TMPL(T)T&Ref(size_t o,size_t n=0){return((T*)(data+o))[n];}
TMPL(T)T*Ptr(size_t o,size_t n=0){return&((T*)(data+o))[n];}
BYTE&Byte(size_t o,size_t n=0){return((BYTE*)(data+o))[n];}
WORD&Word(size_t o,size_t n=0){return((WORD*)(data+o))[n];}
DWORD&Dword(size_t o,size_t n=0){return((DWORD*)(data+o))[n];}
size_t&Sizet(size_t o,size_t n=0){return((size_t*)(data+o))[n];}
int offset(Void ptr){return ptr.data-data;}
void align(int size){data=(char*)((size_t(data)+(size-1))&~(size-1));}
TMPL(T)T&operator()(IndexRef<T>ref){return*(T*)(data+ref);}};
#define VOID_OPERATOR(retType) \
	TMPL2(T,U) enable_if_t< \
	is_cstyle_castable<T, size_t>::value \
	&& is_cstyle_castable<U, size_t>::value \
	&& (std::is_same<T, Void>::value \
	|| std::is_same<U, Void>::value), retType>
VOID_OPERATOR(Void)operator-(const T&a,const U&b){
return(char*)(a)-(char*)(b);}
VOID_OPERATOR(bool)operator==(const T&a,const U&b){
return(char*)(a)==(char*)(b);}
VOID_OPERATOR(bool)operator!=(const T&a,const U&b){
return(char*)(a)!=(char*)(b);}
VOID_OPERATOR(bool)operator<(const T&a,const U&b){
return(char*)(a)<(char*)(b);}
VOID_OPERATOR(bool)operator>(const T&a,const U&b){
return(char*)(a)>(char*)(b);}
VOID_OPERATOR(bool)operator<=(const T&a,const U&b){
return(char*)(a)<=(char*)(b);}
VOID_OPERATOR(bool)operator>=(const T&a,const U&b){
return(char*)(a)>=(char*)(b);}
DEF_RETPAIR(VoidLen,Void,ptr,int,offset);
static uint snapUpSize(uint val){return 2<<(__builtin_clz(val-1)^31);}
SHITCALL void free_ref(Void&ptr);SHITCALL uint snapNext(uint val);
SHITCALL void freeLst(Void ptr,int count);
SHITCALL void freeLst_ref(Void&ptr,int count);
#define fclose fclose_
SHITCALL int fclose_(FILE*stream);
SHITCALL void fclose_ref(FILE*&stream);
SHITCALL Void calloc(size_t size);
TMPL(T)static inline Void realloc2(T&ptr,size_t size){Void tmp=
realloc(ptr,size);if(tmp)ptr=tmp;return tmp;}
static inline Void malloc_(size_t size){return malloc(size);}
static inline Void realloc_(void*ptr,size_t size){return realloc(ptr,size);}
#define malloc malloc_
#define realloc realloc_
SHITCALL2 Void xmalloc(size_t size);SHITCALL2 Void xrealloc(Void&ptr,size_t size);
SHITCALL2 Void xcalloc(size_t size);SHITCALL2 Void xrecalloc(Void&ptr,size_t size);
SHITCALL2 Void xnxalloc(Void&ptr,size_t&count,size_t size);
SHITCALL2 Void nxalloc(Void&ptr,size_t&count,size_t size);
TMPL(T)void free_ref(T*&p){free_ref(*(Void*)&p);}
TMPL(T)void freeLst_ref(T&p,int c){freeLst_ref(*(Void*)&p,c);}
#define _Realloc(n1, n2) TMPL(T) Void n1(T*& p, size_t sz) { return n1(*(Void*)&p, \
	sz); } TMPL(T) Void n2(T*& p, size_t sz) { return n1(p, sz*sizeof(T)); }
_Realloc(xrealloc,xRealloc)_Realloc(xrecalloc,xRecalloc)
#define _Nxalloc(n1, n2) TMPL2(T,U) Void n1(T*& p, U& ct, size_t sz) { return n1(*(Void*)&p, \
	*(size_t*)&ct, sz); } TMPL2(T,U) T& n2(T*& p, U& ct){ return *(T*)n1(p, *(size_t*)&ct, sizeof(T)); }
_Nxalloc(xnxalloc,xNextAlloc)_Nxalloc(nxalloc,NextAlloc)
#define xMalloc_(name, func) struct name { name(size_t sz) : sz(sz) {} \
	operator void*() { return func(sz); } TMPL(T) \
	operator T*() { return (T*)func(sizeof(T)*sz); } private: size_t sz; };
xMalloc_(xMalloc,xmalloc);xMalloc_(xCalloc,xcalloc);
xMalloc_(Malloc,malloc);xMalloc_(Calloc,calloc);
static inline void setTxtMode(FILE*fp,bool ena){
_setmode(fp->_file,ena?0x4000:0x8000);}
TMPL(T)struct cstr_;
typedef cstr_<char>cstrA;
typedef cstr_<wchar_t>cstrW;
#define cstrT cstr_<NCHAR>
SHITCALL cstrA cstr_len(const char*);
SHITCALL cstrW cstr_len(const wchar_t*);
TMPL(T)struct cstr_{
typedef T vt;typedef const vt cvt;
vt*data;uint slen;
cstr_()=default;cstr_(const cstr_&that)=default;
cstr_(cvt*d):cstr_(cstr_len(d)){}
cstr_(cvt*d,int l):data((vt*)d),slen(l){}
cstr_(cvt*d,cvt*e):data((vt*)d),slen(e-d){}
template<int l>cstr_(const T(&d)[l]):cstr_(d,l-1){}
template<typename... Args>cstr_&init(Args... args)
{return*this=cstr_(args...);}
cstr_ left(int i){return cstr_(data,i);}
cstr_ right(int i){return cstr_(data+i,slen-i);}
cstr_ endRel(int i){return cstr_(end(),i-slen);}
void setbase(vt*pos){
slen+=data-pos;data=pos;}
void setend(vt*pos){slen=pos-data;}
int offset(vt*pos){pos-data;}
DEF_BEGINEND(vt,data,slen);
DEF_RETPAIR(prn_t,int,slen,vt*,data);
prn_t prn(){return prn_t(slen,data);}
struct Ptr{vt*data;vt*end;bool chk(){return end>data;}
ALWAYS_INLINE vt&f(){return*data;}vt&l(){return end[-1];}
ALWAYS_INLINE vt&fi(){return*data++;}vt&ld(){return*--end;}};
ALWAYS_INLINE Ptr ptr(){return Ptr{data,end()};}
ALWAYS_INLINE void set(Ptr ptr){init(ptr.data,ptr.end);}
ALWAYS_INLINE void sete(Ptr ptr){setend(ptr.end);}};
SHITCALL cstrA getPath(cstrA);SHITCALL cstrW getPath(cstrW);
SHITCALL cstrA getName(cstrA);SHITCALL cstrW getName(cstrW);
TMPL(T)struct bstr_;
typedef bstr_<char>bstrA;
typedef bstr_<wchar_t>bstrW;
#define bstrT bstr_<NCHAR>
#define CSTR_FN2(r, n, t) r n(const t*); r n(const t*, int len); \
	r n(cstr_<t> str) { return n(str.data, str.len); }
TMPL(T)struct bstr_:cstr_<T>{
int mlen;
bstr_&strcpy(const T*);bstr_&strcpy(cstr_<T>);
bstr_&strcat(const T*);bstr_&strcat(cstr_<T>);
bstr_&fmtcpy(const T*,...);
bstr_&fmtcat(const T*,...);
REGCALL(1)cstr_<T>nullTerm(void);
SHITCALL cstr_<T>calcLen(void);
SHITCALL cstr_<T>updateLen(void);
REGCALL(2)T*xreserve(int len);
REGCALL(2)T*xresize(int len);
REGCALL(2)T*xralloc(int len);
REGCALL(2)T*xnalloc(int len);
DEF_RETPAIR(alloc_t,bstr_*,
This,int,len_);
REGCALL(2)alloc_t alloc(int len);};
#define memcpyx_ref(sz, inst) TMPL2(T,U) \
	ALWAYS_INLINE void memcpy##sz##_ref(T*& dst, U*& src, size_t count) { \
	if(__builtin_constant_p(count) && (count <= 6))	while(count--) \
		asm volatile(#inst : "=S"(src), "=D"(dst) : "S"(src), "D"(dst)); \
	else asm volatile("rep "#inst : "=S"(src), "=D"(dst), "=c"(count) \
		: "S"(src), "D"(dst), "c"(count)); } TMPL(T) \
		ALWAYS_INLINE T* memcpy##sz(T* dst, const void* src, size_t count) { \
		memcpy##sz##_ref(dst, src, count); return dst;  }
memcpyx_ref(8,movsb);memcpyx_ref(16,movsw);memcpyx_ref(32,movsd);
#define _memcpy_sz(macro) { \
	if((sizeof(T) % 4) == 0) macro(32, count*(sizeof(T)/4)) \
	ei((sizeof(T) % 2) == 0) macro(16, count*(sizeof(T)/2)) \
	else				 macro(8, count*sizeof(T)) }
#define _rep_memcpy_sz_(size, count) \
	memcpy##size##_ref(dst, src, count);
TMPL2(T,U)ALWAYS_INLINE
void memcpy_ref(T*&dst,U*&src,size_t count){
_memcpy_sz(_rep_memcpy_sz_);}
TMPL(T)ALWAYS_INLINE T*memcpyX(T*dst,const void*src,
size_t count){memcpy_ref(dst,src,count);return dst;}
TMPL(T)ALWAYS_INLINE Void memcpyY(T*dst,const void*src,
size_t count){memcpy_ref(dst,src,count);return src;}
#define memsetx_ref(sz, inst, init...) template<class T,class U> \
	ALWAYS_INLINE void memset##sz##_ref(T*&dst,size_t count,const U&src){	init; \
	if(__builtin_constant_p(count) && (count <= 6)) while(count--) \
		asm volatile(#inst :"=D"(dst) :"a"(src),"D"(dst)); \
	else asm volatile("rep "#inst :"=D"(dst),"=c"(count) \
		:"a"(src),"D"(dst),"c"(count)); } template<class T,class U> \
	ALWAYS_INLINE T*memset##sz(T*dst,size_t count,const U&src){\
		memset##sz##_ref(dst,count,src);return dst; }
memsetx_ref(8,stosb,byte val=src);
memsetx_ref(16,stosw,typename std::conditional<sizeof(U)<2
,word,const U&>::type val=src;)
memsetx_ref(32,stosl,typedef typename std::conditional<std::
is_same<double,U>::value,float,const U&>::type type;
typename std::conditional<sizeof(U)<4,uint,type>::type val=src)
template<class T,class U>
void memset_ref(T*&dst,size_t count,const U&src){
if(sizeof(T)==4)memset32_ref(dst,count,src);
ei(sizeof(T)==2)memset16_ref(dst,count,src);
else	  		 memset8_ref(dst,count,src);}
template<class T,class U>T*memsetX(T*dst,size_t count,const U&src){
memset_ref(dst,count,src);return dst;}
template<class T,class U,size_t N>
void memsetX(T(*array)[N],size_t count,const U&val){
memsetX((T*)array,N*count,val);}
template<class T,class U,size_t N>
void memsetX(T(&array)[N],const U&val){
memsetX(array,N,val);}
template<class T,class U,size_t N,size_t M>
void memsetX(T(&array)[N][M],const U&val){
memsetX(array,N,val);}
#define _rep_memset_sz_(size, count) \
	memset##size##_ref(dst, count, fill);
template<class T>
void memfill_ref(T*&dst,size_t count,size_t fill){
_memcpy_sz(_rep_memset_sz_);}
template<class T>
T*memfillX(T*dst,size_t count,size_t fill=0){
memfill_ref(dst,count,fill);return dst;}
template<class T>void memfillX(T&obj,size_t fill=0){
memfillX(&obj,1,fill);}
#define memfill2(dst_, dstEnd, fill) {\
	uint byteLen = RangeOf(dst_, dstEnd); char* dst = (char*)&dst_;\
	if(!__builtin_constant_p(byteLen)) memset8_ref(dst,byteLen,(char)fill);\
	ei((byteLen % 4) == 0) memset32_ref(dst,byteLen/4,fill);\
	ei((byteLen % 2) == 0) memset16_ref(dst,byteLen/2,(word)fill);\
	else { memset8(dst,byteLen,(char)fill); }\
	__assume(dst == ((char*)&dst_)+byteLen); }
constexpr u8 rol_8(u8 val,int shift){return(val<<shift)|(val>>(8-shift));}
constexpr u8 ror_8(u8 val,int shift){return(val>>shift)|(val<<(8-shift));}
constexpr u16 rol_16(u16 val,int shift){return(val<<shift)|(val>>(16-shift));}
constexpr u16 ror_16(u16 val,int shift){return(val>>shift)|(val<<(16-shift));}
constexpr u32 rol_32(u32 val,int shift){return(val<<shift)|(val>>(32-shift));}
constexpr u32 ror_32(u32 val,int shift){return(val>>shift)|(val<<(32-shift));}
REGCALL(1)constexpr static int toUpper(int ch){return((ch>='a')&&(ch<='z'))?ch-32:ch;}
REGCALL(1)constexpr static int toLower(int ch){return((ch>='A')&&(ch<='Z'))?ch+32:ch;}
constexpr static bool isPathSep(int ch){return(ch=='\\')||(ch=='/');}
template<class F>
class finally_type{F function;
public:finally_type(F f):function(f){}
__attribute__((always_inline))~finally_type(){function();}};
template<class F>finally_type<F>
finally(F f){return finally_type<F>(f);}
#define SCOPE_EXIT(f) auto MCAT(sExit, __COUNTER__) = \
	finally([&](void) __attribute__((always_inline)) {f;})
template<typename T>struct Range1_type2
{T value;
Range1_type2(T in):value(in){}
T operator*(){return value;}
bool operator!=(const Range1_type2<T>&that)const
{return that.value!=value;}
void operator++(){value++;}};
template<typename T>class Range1_type{
public:Range1_type(T start,T end):
begin_(start),end_(end){}
Range1_type2<T>begin(){return begin_;}
Range1_type2<T>end(){return end_;}
Range1_type2<T>begin_,end_;};
template<typename T>class Range2_type{
public:Range2_type(T*collection,size_t size):
mCollection(collection),mSize(size){}
T*begin(){return&mCollection[0];}
T*end(){return&mCollection[mSize];}
private:T*mCollection;size_t mSize;};
template<typename T>
Range1_type<T>Range(T start,T end)
{return Range1_type<T>(start,end);}
template<typename T>
Range2_type<T>Range(T*array,size_t size)
{return Range2_type<T>(array,size);}
template<class Type,class Next>
bool is_one_of(const Type&needle,const Next&next)
{return needle==next;}
template<class Type,class Next,class ... Rest>
bool is_one_of(const Type&needle,const Next&next,const Rest&... haystack)
{return needle==next||is_one_of(needle,haystack...);}
#define bswap32 __builtin_bswap32
#define bswap16 __builtin_bswap16
static inline
char*stradd(char*dst,const char*src){
char ch;while(lodsb(src,ch),ch)stosb(dst,ch);
*dst=ch;return dst;}
static inline
wchar_t*stradd(wchar_t*dst,const wchar_t*src){
wchar_t ch;while(lodsw(src,ch),ch)stosw(dst,ch);
*dst=ch;return dst;}
SHITCALL void xfread(void*,size_t,size_t,FILE*);
SHITCALL void xfwrite(const void*,size_t,size_t,FILE*);
SHITCALL void xchsize(FILE*fp,long size);
SHITCALL int fsize(FILE*fp);
DEF_RETPAIR(loadFile_t,byte*,data,size_t,size);
SHITCALL loadFile_t loadFile(FILE*fp,int extra=0);
SHITCALL char**loadText(FILE*fp,int&LineCount);
int xvfprintf(FILE*stream,const char*format,va_list arg);
int xfprintf(FILE*stream,const char*format,...);
void xfputs(const char*str,FILE*stream);
TMPL(T)void xfread(T*ptr,size_t size,FILE*fp){xfread(ptr,sizeof(T),size,fp);}
TMPL(T)void xfwrite(const T*ptr,size_t size,FILE*fp){xfwrite(ptr,sizeof(T),size,fp);}
TMPL(T)void xfread(T&ptr,FILE*fp){xfread(&ptr,1,fp);}
TMPL(T)void xfwrite(const T&ptr,FILE*fp){xfwrite(&ptr,1,fp);}
template<typename T,int size>void xfread(T(&ptr)[size],FILE*fp){xfread(ptr,size,fp);}
template<typename T,int size>void xfwrite(T(&ptr)[size],FILE*fp){xfwrite(ptr,size,fp);}
inline FILE*fopen(const wchar_t*fName,const wchar_t*mode)
{return _wfopen(fName,mode);}
inline wchar_t*fgets(wchar_t*str,int num,FILE*fp)
{return fgetws(str,num,fp);}
inline size_t strlen(const wchar_t*str){return wcslen(str);}
inline wchar_t*strcpy(wchar_t*d,const wchar_t*s){return wcscpy(d,s);}
inline int strcmp(const wchar_t*str1,const wchar_t*str2){return wcscmp(str1,str2);}
inline int stricmp(const wchar_t*str1,const wchar_t*str2){return wcsicmp(str1,str2);}
inline int strncmp(const wchar_t*str1,const wchar_t*str2,size_t num){return wcsncmp(str1,str2,num);}
inline int strnicmp(const wchar_t*str1,const wchar_t*str2,size_t num){return wcsnicmp(str1,str2,num);}
inline wchar_t*strdup(const wchar_t*str){return wcsdup(str);}
inline int vsprintf(wchar_t*s,const wchar_t*format,va_list arg){
return vswprintf(s,format,arg);}
template<typename T,int size>
int strncmp(const T*str1,const T(&str2)[size])
{return strncmp(str1,str2,size-1);}
template<typename T,int size>
int strnicmp(const T*str1,const T(&str2)[size])
{return strnicmp(str1,str2,size-1);}
template<class TCH>
struct xstrfmt_fmt{enum{FLAG_ABSLEN=1<<16,
SPACE_POSI=1,FLAG_XCLMTN=2,FLAG_QUOTE=4,FLAG_HASH=8,
FLAG_DOLAR=16,FLAG_PRCNT=32,FLAG_AMPRSND=64,FLAG_APOSTR=128,
FLAG_LBRACE=256,FLAG_RBRACE=512,UPPER_CASE=1024,FORCE_SIGN=2048,
FLAG_COMMA=4096,LEFT_JUSTIFY=8192,FLAG_SLASH=1<<15,PADD_ZEROS=1<<16};
va_list ap;TCH*dstPosArg;uint flags;
int width;int precision;int length;};
#define xstrfmt_fmtA xstrfmt_fmt<char>
#define xstrfmt_fmtW xstrfmt_fmt<wchar_t>
TMPL2(T,F)void qsort(T*base,size_t num,F compar)
{typedef int(*qcomp)(const T&,const T&);
qsort(base,num,sizeof(*base),(Void)(qcomp)compar);}
TMPL2(T,F)void qsort(T&array,F compar)
{qsort(std::begin(array),std::end(array)-std::begin(array),compar);}
TMPL2(T,F)T*bsearch(void*key,T*base,size_t num,F compar)
{typedef int(*qcomp)(const T&,const T&);return(T*)
bsearch(key,base,num,sizeof(*base),(Void)(qcomp)compar);}
TMPL2(T,F)T*bsearch(void*key,T&array,F compar){return
bsearch(key,std::begin(array),std::end(array)-std::begin(array),compar);}
SHITCALL2 Void xmemdup8(Void src,int count);
SHITCALL2 Void xmemdup16(Void src,int count);
SHITCALL2 Void xmemdup32(Void src,int count);
TMPL(T)
T*xMemdup(const T*src,int count){
if((sizeof(T)%4)==0)return xmemdup32(src,count*(sizeof(T)/4));
ei((sizeof(T)%2)==0)return xmemdup16(src,count*(sizeof(T)/2));
else			  		 return xmemdup8(src,count*sizeof(T));}
int ifloor(float f);int iceil(float f);
extern const uint powersOf10[10];
extern const byte tableOfHex[2][16];
static inline void lrintf(int&dst,float x){
__asm__ __volatile__
("fistpl %0":"=m"(dst):"t"(x):"st");}
extern const char progName[];
void contError(HWND hwnd,const char*fmt,...);
FATALFUNC void fatalError(const char*fmt,...);
FATALFUNC void fatalError(HWND hwnd,const char*fmt,...);
FATALFUNC void errorAlloc();
FATALFUNC void errorMaxPath();
FATALFUNC void errorDiskSpace();
FATALFUNC void errorDiskWrite();
FATALFUNC void errorDiskFail();
FATALFUNC void errorBadFile();
TMPL(T)T errorAlloc(T ptr)
{if(!ptr)errorAlloc();return ptr;}
Void memmem(const void*b1,const void*b2,
size_t len1,size_t len2);
#define __forceinline inline
#define _vsnwprintf_s _vsnprintf_s
#define swprintf_s sprintf_s
#define _vsntprintf_s _vsnprintf_s
#define _stprintf_s sprintf_s
int _vsnprintf_s(char*buffer,size_t sizeOfBuffer,
const char*format,va_list ap);
int sprintf_s(char*buffer,size_t sizeOfBuffer,
const char*format,...);
int _vsnprintf_s(wchar_t*buffer,size_t sizeOfBuffer,
const wchar_t*format,va_list ap);
int sprintf_s(wchar_t*buffer,size_t sizeOfBuffer,
const wchar_t*format,...);
#define _ARRAY_MEM_FIX
template<class T,typename... Args>
T*pNew(T*ptr,Args&&... args){__assume(ptr!=NULL);
return new(ptr)T(args...);}
TMPL(T)void pDel(T*ptr){ptr->~T();}
struct xvector_{
Void dataPtr;size_t dataSize,allocSize;
void init_(){ZINIT;}
void init_(Void buff,int buffSize){
dataPtr=buff;dataSize=0;allocSize=buffSize;}
void free_(){free_ref(dataPtr);}
void clear_(){free_();dataSize=0;allocSize=0;}
Void release_(void){::release(dataPtr);}
Void xalloc_(size_t size);
Void xreserve_(size_t size);Void xresize_(size_t size);
VoidLen xnxalloc2_(size_t size);VoidLen xrxalloc2_(size_t size);
Void xnxalloc_(size_t size){return xnxalloc2_(size);}
Void xrxalloc_(size_t size){return xrxalloc2_(size);}
Void begin(size_t offset=0){return dataPtr+offset;}
Void end(size_t offset=0){return dataPtr+dataSize+offset;}
size_t addSize(size_t val){return::release(dataSize,dataSize+val);}
size_t setEnd(Void endPos){return::release(dataSize,endPos-dataPtr);}
TMPL(T)
T&operator()(IndexRef<T>ref){return dataPtr(ref);}
#define _xvector_write_(sz, count) return write##sz(src,count);
TMPL(T)int write(const T*src,int count){
_memcpy_sz(_xvector_write_);}
TMPL(T)int write(const T&val){
if(sizeof(T)==1)return write8(CAST(byte,val));
ei(sizeof(T)==2)return write16(CAST(word,val));
ei(sizeof(T)==4)return write32(CAST(uint,val));
ei(sizeof(T)==8)return write64(CAST(INT64,val));
else write(&val,1);}
RetEdx<int>write8(Void src,int count);
RetEdx<int>write16(Void src,int count);
RetEdx<int>write32(Void src,int count);
RetEdx<int>write8(byte);RetEdx<int>write16(word);
RetEdx<int>write32(uint);RetEdx<int>write64(INT64);
RetEdx<int>strcat2(const char*str);
RetEdx<int>strcat2(const WCHAR*str);
int strcat(const char*str);
int strcat(const WCHAR*str);
void fmtcat(const char*fmt,...);
void fmtcat(const WCHAR*fmt,...);};
TMPL(T)
struct xvector:xvector_{
xvector(){}
xvector(const xvector<T>&That){init(That);}
xvector(T*di,size_t ci){init(di,ci);}
xvector(T*di,size_t ds,size_t as){init2(di,ds,as);}
size_t getCount()const{return dataSize/sizeof(T);}
size_t getAlloc()const{return allocSize/sizeof(T);}
DEF_BEGINEND(T,dataPtr,dataSize);
xvector<T>release2(void){xvector<T>result=*this;
this->init();return result;}
void Free(){if(std::is_trivially_destructible<T>::value)
{this->free_();}else{dtor();}}
void Clear(){this->Free();dataSize=0;allocSize=0;}
T*xCopy(const xvector<T>&That){return xCopy(That.dataPtr,That.getCount());}
T*xCopy(const T*di,size_t ci){if(std::is_trivially_destructible<T>::value)
{return xcopy(di,ci);}else{ctor((T*)di,ci);}}
T*xAlloc(size_t size){T*ptr=xalloc(size);
for(int i=0;i<size;i++)pNew(ptr);}
T*xReserve(size_t size){return xreserve_(size*sizeof(T));}
T*xNalloc(size_t size){T*ptr=xnalloc(size);
for(int i=0;i<size;i++)pNew(ptr+i);}
template<typename... Args>
T&push_back(Args... args){T*ptr=xnalloc(1);
__assume(ptr!=NULL);return*(new(ptr)T(args...));}
void pop_back(void){addCount(-1);end()->~T();}
T*xRalloc(size_t size){return xrxalloc_(size*sizeof(T));}
void addCount(size_t val){dataSize+=(val*sizeof(T));}
void setCount(size_t val){dataSize=(val*sizeof(T));}
void init(const xvector<T>&That){init2(That.dataPtr,That.dataSize,That.allocSize);}
void init(T*di,size_t ci){init2(di,ci*sizeof(T),ci*sizeof(T));}
void init2(T*di,size_t ds,size_t as){
this->dataPtr=di;this->dataSize=ds;this->allocSize=as;}
xvector<T>get2()const {return*this;}
T*xcopy(const xvector<T>&That){return xcopy(That.dataPtr,That.getCount());}
T*xcopy(const T*di,size_t ci){memcpyX(xresize(ci),di,ci);return this->dataPtr;}
T*xalloc(size_t size){return this->xalloc_(size*sizeof(T));}
T*xresize(size_t size){return xresize_(size*sizeof(T));}
T*xnalloc(size_t size){return xnxalloc_(size*sizeof(T));}
private:
__attribute__((noinline))void ctor(T*di,size_t ci){
T*dstPos=xalloc(ci);for(int i=0;i<ci;i++){
pNew(dstPos+i,di[i]);}}
__attribute__((noinline))void dtor(){if(dataPtr){
for(auto&obj:*this)obj.~T();::free(dataPtr);}}};
TMPL(T)
struct xVector:xvector<T>{
xVector(){xvector_::init_();}
xVector(const T*di,size_t ci){this->xCopy(di,ci);}
xVector(const xvector<T>&That){this->xCopy(That);}
xVector(const xVector<T>&That){this->xCopy(That.get2());}
xVector(xVector<T>&&That){this->init2(
That.dataPtr,That.dataSize,That.allocSize);}
~xVector(){this->Free();}};
#endif
#undef NWIDE
#undef NCHAR
#undef DCHAR
#undef _N
#if defined(UNICODE) ^ defined(_STDSHIT_X_)
#define NWIDE 0
#define NCHAR char
#define DCHAR WORD
#define _N(str) str
#else
#define NWIDE 1
#define NCHAR wchar_t
#define DCHAR DWORD
#define _N(str) MCAT(L,str)
#endif
SHITCALL cstr_<NCHAR>xstrfmt(const NCHAR*,...);
SHITCALL int strfmt(NCHAR*buffer,const NCHAR*fmt,...);
SHITCALL int xstrfmt_len(const NCHAR*fmt,va_list ap);
SHITCALL NCHAR*xstrfmt_fill(NCHAR*buffer,
const NCHAR*fmt,va_list ap);
SHITCALL FILE*xfopen(const NCHAR*,const NCHAR*);
SHITCALL NCHAR*xfgets(NCHAR*,int,FILE*);
SHITCALL loadFile_t loadFile(const NCHAR*fileName,int extra=0);
SHITCALL char**loadText(const NCHAR*fileName,int&LineCount);
SHITCALL cstr_<NCHAR>xstrdup(const NCHAR*);
SHITCALL cstr_<NCHAR>xstrdup(const NCHAR*,size_t);
SHITCALL NCHAR*xstrdupr(NCHAR*&,const NCHAR*);
SHITCALL NCHAR*xstrdupr(NCHAR*&,const NCHAR*,size_t);
SHITCALL NCHAR*strScmp(const NCHAR*,const NCHAR*);
SHITCALL NCHAR*strSicmp(const NCHAR*,const NCHAR*);
SHITCALL int strEcmp(const NCHAR*,const NCHAR*);
SHITCALL int strEicmp(const NCHAR*,const NCHAR*);
SHITCALL int strNcpy(NCHAR*,const NCHAR*,int);
SHITCALL int removeCrap(NCHAR*);
SHITCALL int strmove(NCHAR*,const NCHAR*);
SHITCALL size_t strnlen(const NCHAR*,size_t maxLen);
SHITCALL NCHAR*strstr(const NCHAR*,const NCHAR*,int maxLen);
SHITCALL NCHAR*strstri(const NCHAR*,const NCHAR*,int maxLen);
SHITCALL int strcmp2(const NCHAR*str1,const NCHAR*str2);
SHITCALL int stricmp2(const NCHAR*str1,const NCHAR*str2);
SHITCALL cstrT strcpyn(NCHAR*,const NCHAR*,int);
SHITCALL bool strcmpn(const NCHAR*,const NCHAR*,int);
SHITCALL bool stricmpn(const NCHAR*,const NCHAR*,int);
SHITCALL int getPathLen(const NCHAR*);
SHITCALL int getPath(NCHAR*);
SHITCALL NCHAR*getName(const NCHAR*);
SHITCALL int getName(NCHAR*dst,const NCHAR*src,size_t max);
SHITCALL bool isFullPath(const NCHAR*);
#ifndef _STDSHIT_X_
#define _STDSHIT_X_
#ifndef _STDSHIT_CC_
#include "stdshit.h"
#endif
#else
_ARRAY_MEM_FIX
#define _STDSHIT_H_
#endif
#endif