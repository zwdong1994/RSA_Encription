#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gmp.h>
#define mpz_set_str_gmpz_set_str

void GMP_RSA(mpz_t p,mpz_t q,mpz_t n,mpz_t fn,mpz_t e,mpz_t d,int l,int seed)
{
	unsigned long i;
	mpz_t p0,q0,re;
	mpz_init(p0);
	mpz_init(q0);
	mpz_init(re);
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,seed);
	mpz_urandomb(p,state,l);
	mpz_nextprime(p,p);
	gmp_printf("素数p:	%Zd\n",p);
	gmp_randseed_ui(state,seed+1);
	mpz_urandomb(q,state,l);
	mpz_nextprime(q,q);
	gmp_printf("\n素数q:	%Zd\n",q);
	mpz_mul(n,p,q);
	gmp_printf("\n大数n:	%Zd\n",n);
	gmp_randseed_ui(state,seed+2);
	mpz_urandomb(e,state,2*l);
	mpz_sub_ui(p0,p,1);
	mpz_sub_ui(q0,q,1);
	mpz_mul(fn,p0,q0);
	gmp_printf("\n欧拉数fn: %Zd\n\n",fn);
	mpz_divexact_ui(re,fn,2);
	gmp_randseed_ui(state,seed+1);
	mpz_urandomm(e,state,re);
	mpz_nextprime(e,e);
	i=mpz_invert(d,e,fn);
	mpz_clear(p0);
	mpz_clear(q0);
	mpz_clear(re);
	gmp_randclear (state);
}
int main()
{
	int l,seed=0;
	char s[1000];
	mpz_t p,q,n,fn,e,d,m,E,D;
	gmp_randstate_t state;
	mpz_init(p);
	mpz_init(q);
	mpz_init(n);
	mpz_init(fn);
	mpz_init(d);
	mpz_init(e);
	mpz_init(m);
	mpz_init(E);
	mpz_init(D);
	gmp_randinit_default (state);
	srand(time(NULL));
	seed=rand()%(1<<31);
    printf("手动输入明文如下：\n");
    gets(s);
    mpz_set_str(m,s,10);
	printf("\n请输入素数p,q的最大长度：");
	scanf("%d",&l);
	GMP_RSA(p,q,n,fn,e,d,l,seed);
	gmp_printf("加密指数e: %Zd\n",e);
	gmp_printf("\n私密钥d: %Zd\n",d);
	mpz_powm(E,m,e,n);
	gmp_printf("\n密文: %Zd\n\n",E);
	mpz_powm(D,E,d,n);
	printf("解密得到的明文为：\n");
	gmp_printf("%Zd\n",D);
	mpz_clear(p);
	mpz_clear(q);
	mpz_clear(n);
	mpz_clear(fn);
	mpz_clear(e);
	mpz_clear(d);
	mpz_clear(m);
	mpz_clear(E);
	mpz_clear(D);
	return 0;
}
