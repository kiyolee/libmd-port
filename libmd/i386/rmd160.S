/* Run the C pre-processor over this file with one of the following defined
 * ELF - elf object files,
 * OUT - a.out object files,
 * BSDI - BSDI style a.out object files
 * SOL - Solaris style elf
 */

#ifndef PIC
#define TYPE(a,b)       .type   a,b
#define SIZE(a,b)       .size   a,b

#if defined(OUT) || defined(BSDI) || defined(CYGWIN)
#define ripemd160_block_x86 _ripemd160_block_x86

#endif

#ifdef OUT
#define OK	1
#define ALIGN	4
#endif

#if defined(BSDI) || defined(CYGWIN)
#define OK              1
#define ALIGN           4
#undef SIZE
#undef TYPE
#define SIZE(a,b)
#define TYPE(a,b)
#endif

#if defined(ELF) || defined(SOL)
#define OK              1
#define ALIGN           4
#endif

#ifndef OK
You need to define one of
ELF - elf systems - linux-elf, NetBSD and DG-UX
OUT - a.out systems - linux-a.out and FreeBSD
SOL - solaris systems, which are elf with strange comment lines
BSDI - a.out with a very primative version of as.
#endif

/* Let the Assembler begin :-) */
	/* Don't even think of reading this code */
	/* It was automatically generated by rmd-586.pl */
	/* Which is a perl program used to generate the x86 assember for */
	/* any of elf, a.out, BSDI,Win32, or Solaris */
	/* eric <eay@cryptsoft.com> */

	.file	"rmd-586.s"
	.version	"01.01"
gcc2_compiled.:
.text
	.p2align ALIGN
.globl ripemd160_block_x86
	TYPE(ripemd160_block_x86,@function)
ripemd160_block_x86:
	pushl	%esi
	movl	16(%esp),	%ecx
	pushl	%edi
	movl	16(%esp),	%esi
	pushl	%ebp
	addl	%esi,		%ecx
	pushl	%ebx
	subl	$64,		%ecx
	subl	$88,		%esp
	movl	%ecx,		(%esp)
	movl	108(%esp),	%edi
.L000start:

	movl	(%esi),		%eax
	movl	4(%esi),	%ebx
	movl	%eax,		4(%esp)
	movl	%ebx,		8(%esp)
	movl	8(%esi),	%eax
	movl	12(%esi),	%ebx
	movl	%eax,		12(%esp)
	movl	%ebx,		16(%esp)
	movl	16(%esi),	%eax
	movl	20(%esi),	%ebx
	movl	%eax,		20(%esp)
	movl	%ebx,		24(%esp)
	movl	24(%esi),	%eax
	movl	28(%esi),	%ebx
	movl	%eax,		28(%esp)
	movl	%ebx,		32(%esp)
	movl	32(%esi),	%eax
	movl	36(%esi),	%ebx
	movl	%eax,		36(%esp)
	movl	%ebx,		40(%esp)
	movl	40(%esi),	%eax
	movl	44(%esi),	%ebx
	movl	%eax,		44(%esp)
	movl	%ebx,		48(%esp)
	movl	48(%esi),	%eax
	movl	52(%esi),	%ebx
	movl	%eax,		52(%esp)
	movl	%ebx,		56(%esp)
	movl	56(%esi),	%eax
	movl	60(%esi),	%ebx
	movl	%eax,		60(%esp)
	movl	%ebx,		64(%esp)
	addl	$64,		%esi
	movl	(%edi),		%eax
	movl	%esi,		112(%esp)
	movl	4(%edi),	%ebx
	movl	8(%edi),	%ecx
	movl	12(%edi),	%edx
	movl	16(%edi),	%ebp
	/* 0 */
	movl	%ecx,		%esi
	xorl	%edx,		%esi
	movl	4(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%edi,		%eax
	roll	$10,		%ecx
	addl	%esi,		%eax
	movl	%ebx,		%esi
	roll	$11,		%eax
	addl	%ebp,		%eax
	/* 1 */
	xorl	%ecx,		%esi
	movl	8(%esp),	%edi
	xorl	%eax,		%esi
	addl	%esi,		%ebp
	movl	%eax,		%esi
	roll	$10,		%ebx
	addl	%edi,		%ebp
	xorl	%ebx,		%esi
	roll	$14,		%ebp
	addl	%edx,		%ebp
	/* 2 */
	movl	12(%esp),	%edi
	xorl	%ebp,		%esi
	addl	%edi,		%edx
	roll	$10,		%eax
	addl	%esi,		%edx
	movl	%ebp,		%esi
	roll	$15,		%edx
	addl	%ecx,		%edx
	/* 3 */
	xorl	%eax,		%esi
	movl	16(%esp),	%edi
	xorl	%edx,		%esi
	addl	%esi,		%ecx
	movl	%edx,		%esi
	roll	$10,		%ebp
	addl	%edi,		%ecx
	xorl	%ebp,		%esi
	roll	$12,		%ecx
	addl	%ebx,		%ecx
	/* 4 */
	movl	20(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%edi,		%ebx
	roll	$10,		%edx
	addl	%esi,		%ebx
	movl	%ecx,		%esi
	roll	$5,		%ebx
	addl	%eax,		%ebx
	/* 5 */
	xorl	%edx,		%esi
	movl	24(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%esi,		%eax
	movl	%ebx,		%esi
	roll	$10,		%ecx
	addl	%edi,		%eax
	xorl	%ecx,		%esi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 6 */
	movl	28(%esp),	%edi
	xorl	%eax,		%esi
	addl	%edi,		%ebp
	roll	$10,		%ebx
	addl	%esi,		%ebp
	movl	%eax,		%esi
	roll	$7,		%ebp
	addl	%edx,		%ebp
	/* 7 */
	xorl	%ebx,		%esi
	movl	32(%esp),	%edi
	xorl	%ebp,		%esi
	addl	%esi,		%edx
	movl	%ebp,		%esi
	roll	$10,		%eax
	addl	%edi,		%edx
	xorl	%eax,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 8 */
	movl	36(%esp),	%edi
	xorl	%edx,		%esi
	addl	%edi,		%ecx
	roll	$10,		%ebp
	addl	%esi,		%ecx
	movl	%edx,		%esi
	roll	$11,		%ecx
	addl	%ebx,		%ecx
	/* 9 */
	xorl	%ebp,		%esi
	movl	40(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%esi,		%ebx
	movl	%ecx,		%esi
	roll	$10,		%edx
	addl	%edi,		%ebx
	xorl	%edx,		%esi
	roll	$13,		%ebx
	addl	%eax,		%ebx
	/* 10 */
	movl	44(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%edi,		%eax
	roll	$10,		%ecx
	addl	%esi,		%eax
	movl	%ebx,		%esi
	roll	$14,		%eax
	addl	%ebp,		%eax
	/* 11 */
	xorl	%ecx,		%esi
	movl	48(%esp),	%edi
	xorl	%eax,		%esi
	addl	%esi,		%ebp
	movl	%eax,		%esi
	roll	$10,		%ebx
	addl	%edi,		%ebp
	xorl	%ebx,		%esi
	roll	$15,		%ebp
	addl	%edx,		%ebp
	/* 12 */
	movl	52(%esp),	%edi
	xorl	%ebp,		%esi
	addl	%edi,		%edx
	roll	$10,		%eax
	addl	%esi,		%edx
	movl	%ebp,		%esi
	roll	$6,		%edx
	addl	%ecx,		%edx
	/* 13 */
	xorl	%eax,		%esi
	movl	56(%esp),	%edi
	xorl	%edx,		%esi
	addl	%esi,		%ecx
	movl	%edx,		%esi
	roll	$10,		%ebp
	addl	%edi,		%ecx
	xorl	%ebp,		%esi
	roll	$7,		%ecx
	addl	%ebx,		%ecx
	/* 14 */
	movl	60(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%edi,		%ebx
	roll	$10,		%edx
	addl	%esi,		%ebx
	movl	%ecx,		%esi
	roll	$9,		%ebx
	addl	%eax,		%ebx
	/* 15 */
	xorl	%edx,		%esi
	movl	64(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%esi,		%eax
	movl	$-1,		%esi
	roll	$10,		%ecx
	addl	%edi,		%eax
	movl	32(%esp),	%edi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 16 */
	addl	%edi,		%ebp
	movl	%ebx,		%edi
	subl	%eax,		%esi
	andl	%eax,		%edi
	andl	%ecx,		%esi
	orl	%esi,		%edi
	movl	20(%esp),	%esi
	roll	$10,		%ebx
	leal	1518500249(%ebp,%edi,1),%ebp
	movl	$-1,		%edi
	roll	$7,		%ebp
	addl	%edx,		%ebp
	/* 17 */
	addl	%esi,		%edx
	movl	%eax,		%esi
	subl	%ebp,		%edi
	andl	%ebp,		%esi
	andl	%ebx,		%edi
	orl	%edi,		%esi
	movl	56(%esp),	%edi
	roll	$10,		%eax
	leal	1518500249(%edx,%esi,1),%edx
	movl	$-1,		%esi
	roll	$6,		%edx
	addl	%ecx,		%edx
	/* 18 */
	addl	%edi,		%ecx
	movl	%ebp,		%edi
	subl	%edx,		%esi
	andl	%edx,		%edi
	andl	%eax,		%esi
	orl	%esi,		%edi
	movl	8(%esp),	%esi
	roll	$10,		%ebp
	leal	1518500249(%ecx,%edi,1),%ecx
	movl	$-1,		%edi
	roll	$8,		%ecx
	addl	%ebx,		%ecx
	/* 19 */
	addl	%esi,		%ebx
	movl	%edx,		%esi
	subl	%ecx,		%edi
	andl	%ecx,		%esi
	andl	%ebp,		%edi
	orl	%edi,		%esi
	movl	44(%esp),	%edi
	roll	$10,		%edx
	leal	1518500249(%ebx,%esi,1),%ebx
	movl	$-1,		%esi
	roll	$13,		%ebx
	addl	%eax,		%ebx
	/* 20 */
	addl	%edi,		%eax
	movl	%ecx,		%edi
	subl	%ebx,		%esi
	andl	%ebx,		%edi
	andl	%edx,		%esi
	orl	%esi,		%edi
	movl	28(%esp),	%esi
	roll	$10,		%ecx
	leal	1518500249(%eax,%edi,1),%eax
	movl	$-1,		%edi
	roll	$11,		%eax
	addl	%ebp,		%eax
	/* 21 */
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	subl	%eax,		%edi
	andl	%eax,		%esi
	andl	%ecx,		%edi
	orl	%edi,		%esi
	movl	64(%esp),	%edi
	roll	$10,		%ebx
	leal	1518500249(%ebp,%esi,1),%ebp
	movl	$-1,		%esi
	roll	$9,		%ebp
	addl	%edx,		%ebp
	/* 22 */
	addl	%edi,		%edx
	movl	%eax,		%edi
	subl	%ebp,		%esi
	andl	%ebp,		%edi
	andl	%ebx,		%esi
	orl	%esi,		%edi
	movl	16(%esp),	%esi
	roll	$10,		%eax
	leal	1518500249(%edx,%edi,1),%edx
	movl	$-1,		%edi
	roll	$7,		%edx
	addl	%ecx,		%edx
	/* 23 */
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	subl	%edx,		%edi
	andl	%edx,		%esi
	andl	%eax,		%edi
	orl	%edi,		%esi
	movl	52(%esp),	%edi
	roll	$10,		%ebp
	leal	1518500249(%ecx,%esi,1),%ecx
	movl	$-1,		%esi
	roll	$15,		%ecx
	addl	%ebx,		%ecx
	/* 24 */
	addl	%edi,		%ebx
	movl	%edx,		%edi
	subl	%ecx,		%esi
	andl	%ecx,		%edi
	andl	%ebp,		%esi
	orl	%esi,		%edi
	movl	4(%esp),	%esi
	roll	$10,		%edx
	leal	1518500249(%ebx,%edi,1),%ebx
	movl	$-1,		%edi
	roll	$7,		%ebx
	addl	%eax,		%ebx
	/* 25 */
	addl	%esi,		%eax
	movl	%ecx,		%esi
	subl	%ebx,		%edi
	andl	%ebx,		%esi
	andl	%edx,		%edi
	orl	%edi,		%esi
	movl	40(%esp),	%edi
	roll	$10,		%ecx
	leal	1518500249(%eax,%esi,1),%eax
	movl	$-1,		%esi
	roll	$12,		%eax
	addl	%ebp,		%eax
	/* 26 */
	addl	%edi,		%ebp
	movl	%ebx,		%edi
	subl	%eax,		%esi
	andl	%eax,		%edi
	andl	%ecx,		%esi
	orl	%esi,		%edi
	movl	24(%esp),	%esi
	roll	$10,		%ebx
	leal	1518500249(%ebp,%edi,1),%ebp
	movl	$-1,		%edi
	roll	$15,		%ebp
	addl	%edx,		%ebp
	/* 27 */
	addl	%esi,		%edx
	movl	%eax,		%esi
	subl	%ebp,		%edi
	andl	%ebp,		%esi
	andl	%ebx,		%edi
	orl	%edi,		%esi
	movl	12(%esp),	%edi
	roll	$10,		%eax
	leal	1518500249(%edx,%esi,1),%edx
	movl	$-1,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 28 */
	addl	%edi,		%ecx
	movl	%ebp,		%edi
	subl	%edx,		%esi
	andl	%edx,		%edi
	andl	%eax,		%esi
	orl	%esi,		%edi
	movl	60(%esp),	%esi
	roll	$10,		%ebp
	leal	1518500249(%ecx,%edi,1),%ecx
	movl	$-1,		%edi
	roll	$11,		%ecx
	addl	%ebx,		%ecx
	/* 29 */
	addl	%esi,		%ebx
	movl	%edx,		%esi
	subl	%ecx,		%edi
	andl	%ecx,		%esi
	andl	%ebp,		%edi
	orl	%edi,		%esi
	movl	48(%esp),	%edi
	roll	$10,		%edx
	leal	1518500249(%ebx,%esi,1),%ebx
	movl	$-1,		%esi
	roll	$7,		%ebx
	addl	%eax,		%ebx
	/* 30 */
	addl	%edi,		%eax
	movl	%ecx,		%edi
	subl	%ebx,		%esi
	andl	%ebx,		%edi
	andl	%edx,		%esi
	orl	%esi,		%edi
	movl	36(%esp),	%esi
	roll	$10,		%ecx
	leal	1518500249(%eax,%edi,1),%eax
	movl	$-1,		%edi
	roll	$13,		%eax
	addl	%ebp,		%eax
	/* 31 */
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	subl	%eax,		%edi
	andl	%eax,		%esi
	andl	%ecx,		%edi
	orl	%edi,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebx
	leal	1518500249(%ebp,%esi,1),%ebp
	subl	%eax,		%edi
	roll	$12,		%ebp
	addl	%edx,		%ebp
	/* 32 */
	movl	16(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%edx
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	1859775393(%edx,%edi,1),%edx
	subl	%ebp,		%esi
	roll	$11,		%edx
	addl	%ecx,		%edx
	/* 33 */
	movl	44(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ecx
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	1859775393(%ecx,%esi,1),%ecx
	subl	%edx,		%edi
	roll	$13,		%ecx
	addl	%ebx,		%ecx
	/* 34 */
	movl	60(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%ebx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	1859775393(%ebx,%edi,1),%ebx
	subl	%ecx,		%esi
	roll	$6,		%ebx
	addl	%eax,		%ebx
	/* 35 */
	movl	20(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%eax
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	1859775393(%eax,%esi,1),%eax
	subl	%ebx,		%edi
	roll	$7,		%eax
	addl	%ebp,		%eax
	/* 36 */
	movl	40(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%ebp
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	1859775393(%ebp,%edi,1),%ebp
	subl	%eax,		%esi
	roll	$14,		%ebp
	addl	%edx,		%ebp
	/* 37 */
	movl	64(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%edx
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%eax
	leal	1859775393(%edx,%esi,1),%edx
	subl	%ebp,		%edi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 38 */
	movl	36(%esp),	%esi
	orl	%edx,		%edi
	addl	%esi,		%ecx
	xorl	%eax,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebp
	leal	1859775393(%ecx,%edi,1),%ecx
	subl	%edx,		%esi
	roll	$13,		%ecx
	addl	%ebx,		%ecx
	/* 39 */
	movl	8(%esp),	%edi
	orl	%ecx,		%esi
	addl	%edi,		%ebx
	xorl	%ebp,		%esi
	movl	$-1,		%edi
	roll	$10,		%edx
	leal	1859775393(%ebx,%esi,1),%ebx
	subl	%ecx,		%edi
	roll	$15,		%ebx
	addl	%eax,		%ebx
	/* 40 */
	movl	12(%esp),	%esi
	orl	%ebx,		%edi
	addl	%esi,		%eax
	xorl	%edx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ecx
	leal	1859775393(%eax,%edi,1),%eax
	subl	%ebx,		%esi
	roll	$14,		%eax
	addl	%ebp,		%eax
	/* 41 */
	movl	32(%esp),	%edi
	orl	%eax,		%esi
	addl	%edi,		%ebp
	xorl	%ecx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebx
	leal	1859775393(%ebp,%esi,1),%ebp
	subl	%eax,		%edi
	roll	$8,		%ebp
	addl	%edx,		%ebp
	/* 42 */
	movl	4(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%edx
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	1859775393(%edx,%edi,1),%edx
	subl	%ebp,		%esi
	roll	$13,		%edx
	addl	%ecx,		%edx
	/* 43 */
	movl	28(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ecx
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	1859775393(%ecx,%esi,1),%ecx
	subl	%edx,		%edi
	roll	$6,		%ecx
	addl	%ebx,		%ecx
	/* 44 */
	movl	56(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%ebx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	1859775393(%ebx,%edi,1),%ebx
	subl	%ecx,		%esi
	roll	$5,		%ebx
	addl	%eax,		%ebx
	/* 45 */
	movl	48(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%eax
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	1859775393(%eax,%esi,1),%eax
	subl	%ebx,		%edi
	roll	$12,		%eax
	addl	%ebp,		%eax
	/* 46 */
	movl	24(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%ebp
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	1859775393(%ebp,%edi,1),%ebp
	subl	%eax,		%esi
	roll	$7,		%ebp
	addl	%edx,		%ebp
	/* 47 */
	movl	52(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%edx
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%eax
	leal	1859775393(%edx,%esi,1),%edx
	movl	%eax,		%esi
	roll	$5,		%edx
	addl	%ecx,		%edx
	/* 48 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	8(%esp),	%esi
	roll	$10,		%ebp
	leal	2400959708(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	roll	$11,		%ecx
	addl	%ebx,		%ecx
	/* 49 */
	subl	%ebp,		%edi
	andl	%ecx,		%esi
	andl	%edx,		%edi
	orl	%esi,		%edi
	movl	40(%esp),	%esi
	roll	$10,		%edx
	leal	2400959708(%ebx,%edi,),%ebx
	movl	$-1,		%edi
	addl	%esi,		%ebx
	movl	%edx,		%esi
	roll	$12,		%ebx
	addl	%eax,		%ebx
	/* 50 */
	subl	%edx,		%edi
	andl	%ebx,		%esi
	andl	%ecx,		%edi
	orl	%esi,		%edi
	movl	48(%esp),	%esi
	roll	$10,		%ecx
	leal	2400959708(%eax,%edi,),%eax
	movl	$-1,		%edi
	addl	%esi,		%eax
	movl	%ecx,		%esi
	roll	$14,		%eax
	addl	%ebp,		%eax
	/* 51 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	44(%esp),	%esi
	roll	$10,		%ebx
	leal	2400959708(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	roll	$15,		%ebp
	addl	%edx,		%ebp
	/* 52 */
	subl	%ebx,		%edi
	andl	%ebp,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	4(%esp),	%esi
	roll	$10,		%eax
	leal	2400959708(%edx,%edi,),%edx
	movl	$-1,		%edi
	addl	%esi,		%edx
	movl	%eax,		%esi
	roll	$14,		%edx
	addl	%ecx,		%edx
	/* 53 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	36(%esp),	%esi
	roll	$10,		%ebp
	leal	2400959708(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	roll	$15,		%ecx
	addl	%ebx,		%ecx
	/* 54 */
	subl	%ebp,		%edi
	andl	%ecx,		%esi
	andl	%edx,		%edi
	orl	%esi,		%edi
	movl	52(%esp),	%esi
	roll	$10,		%edx
	leal	2400959708(%ebx,%edi,),%ebx
	movl	$-1,		%edi
	addl	%esi,		%ebx
	movl	%edx,		%esi
	roll	$9,		%ebx
	addl	%eax,		%ebx
	/* 55 */
	subl	%edx,		%edi
	andl	%ebx,		%esi
	andl	%ecx,		%edi
	orl	%esi,		%edi
	movl	20(%esp),	%esi
	roll	$10,		%ecx
	leal	2400959708(%eax,%edi,),%eax
	movl	$-1,		%edi
	addl	%esi,		%eax
	movl	%ecx,		%esi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 56 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	56(%esp),	%esi
	roll	$10,		%ebx
	leal	2400959708(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	roll	$9,		%ebp
	addl	%edx,		%ebp
	/* 57 */
	subl	%ebx,		%edi
	andl	%ebp,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	16(%esp),	%esi
	roll	$10,		%eax
	leal	2400959708(%edx,%edi,),%edx
	movl	$-1,		%edi
	addl	%esi,		%edx
	movl	%eax,		%esi
	roll	$14,		%edx
	addl	%ecx,		%edx
	/* 58 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	32(%esp),	%esi
	roll	$10,		%ebp
	leal	2400959708(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	roll	$5,		%ecx
	addl	%ebx,		%ecx
	/* 59 */
	subl	%ebp,		%edi
	andl	%ecx,		%esi
	andl	%edx,		%edi
	orl	%esi,		%edi
	movl	64(%esp),	%esi
	roll	$10,		%edx
	leal	2400959708(%ebx,%edi,),%ebx
	movl	$-1,		%edi
	addl	%esi,		%ebx
	movl	%edx,		%esi
	roll	$6,		%ebx
	addl	%eax,		%ebx
	/* 60 */
	subl	%edx,		%edi
	andl	%ebx,		%esi
	andl	%ecx,		%edi
	orl	%esi,		%edi
	movl	60(%esp),	%esi
	roll	$10,		%ecx
	leal	2400959708(%eax,%edi,),%eax
	movl	$-1,		%edi
	addl	%esi,		%eax
	movl	%ecx,		%esi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 61 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	24(%esp),	%esi
	roll	$10,		%ebx
	leal	2400959708(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	roll	$6,		%ebp
	addl	%edx,		%ebp
	/* 62 */
	subl	%ebx,		%edi
	andl	%ebp,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	28(%esp),	%esi
	roll	$10,		%eax
	leal	2400959708(%edx,%edi,),%edx
	movl	$-1,		%edi
	addl	%esi,		%edx
	movl	%eax,		%esi
	roll	$5,		%edx
	addl	%ecx,		%edx
	/* 63 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	12(%esp),	%esi
	roll	$10,		%ebp
	leal	2400959708(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	subl	%ebp,		%edi
	roll	$12,		%ecx
	addl	%ebx,		%ecx
	/* 64 */
	movl	20(%esp),	%esi
	orl	%edx,		%edi
	addl	%esi,		%ebx
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	2840853838(%ebx,%edi,1),%ebx
	subl	%edx,		%esi
	roll	$9,		%ebx
	addl	%eax,		%ebx
	/* 65 */
	movl	4(%esp),	%edi
	orl	%ecx,		%esi
	addl	%edi,		%eax
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	2840853838(%eax,%esi,1),%eax
	subl	%ecx,		%edi
	roll	$15,		%eax
	addl	%ebp,		%eax
	/* 66 */
	movl	24(%esp),	%esi
	orl	%ebx,		%edi
	addl	%esi,		%ebp
	xorl	%eax,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	2840853838(%ebp,%edi,1),%ebp
	subl	%ebx,		%esi
	roll	$5,		%ebp
	addl	%edx,		%ebp
	/* 67 */
	movl	40(%esp),	%edi
	orl	%eax,		%esi
	addl	%edi,		%edx
	xorl	%ebp,		%esi
	movl	$-1,		%edi
	roll	$10,		%eax
	leal	2840853838(%edx,%esi,1),%edx
	subl	%eax,		%edi
	roll	$11,		%edx
	addl	%ecx,		%edx
	/* 68 */
	movl	32(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%ecx
	xorl	%edx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebp
	leal	2840853838(%ecx,%edi,1),%ecx
	subl	%ebp,		%esi
	roll	$6,		%ecx
	addl	%ebx,		%ecx
	/* 69 */
	movl	52(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ebx
	xorl	%ecx,		%esi
	movl	$-1,		%edi
	roll	$10,		%edx
	leal	2840853838(%ebx,%esi,1),%ebx
	subl	%edx,		%edi
	roll	$8,		%ebx
	addl	%eax,		%ebx
	/* 70 */
	movl	12(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%eax
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ecx
	leal	2840853838(%eax,%edi,1),%eax
	subl	%ecx,		%esi
	roll	$13,		%eax
	addl	%ebp,		%eax
	/* 71 */
	movl	44(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%ebp
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebx
	leal	2840853838(%ebp,%esi,1),%ebp
	subl	%ebx,		%edi
	roll	$12,		%ebp
	addl	%edx,		%ebp
	/* 72 */
	movl	60(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%edx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	2840853838(%edx,%edi,1),%edx
	subl	%eax,		%esi
	roll	$5,		%edx
	addl	%ecx,		%edx
	/* 73 */
	movl	8(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%ecx
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	2840853838(%ecx,%esi,1),%ecx
	subl	%ebp,		%edi
	roll	$12,		%ecx
	addl	%ebx,		%ecx
	/* 74 */
	movl	16(%esp),	%esi
	orl	%edx,		%edi
	addl	%esi,		%ebx
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	2840853838(%ebx,%edi,1),%ebx
	subl	%edx,		%esi
	roll	$13,		%ebx
	addl	%eax,		%ebx
	/* 75 */
	movl	36(%esp),	%edi
	orl	%ecx,		%esi
	addl	%edi,		%eax
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	2840853838(%eax,%esi,1),%eax
	subl	%ecx,		%edi
	roll	$14,		%eax
	addl	%ebp,		%eax
	/* 76 */
	movl	48(%esp),	%esi
	orl	%ebx,		%edi
	addl	%esi,		%ebp
	xorl	%eax,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	2840853838(%ebp,%edi,1),%ebp
	subl	%ebx,		%esi
	roll	$11,		%ebp
	addl	%edx,		%ebp
	/* 77 */
	movl	28(%esp),	%edi
	orl	%eax,		%esi
	addl	%edi,		%edx
	xorl	%ebp,		%esi
	movl	$-1,		%edi
	roll	$10,		%eax
	leal	2840853838(%edx,%esi,1),%edx
	subl	%eax,		%edi
	roll	$8,		%edx
	addl	%ecx,		%edx
	/* 78 */
	movl	64(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%ecx
	xorl	%edx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebp
	leal	2840853838(%ecx,%edi,1),%ecx
	subl	%ebp,		%esi
	roll	$5,		%ecx
	addl	%ebx,		%ecx
	/* 79 */
	movl	56(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ebx
	xorl	%ecx,		%esi
	movl	108(%esp),	%edi
	roll	$10,		%edx
	leal	2840853838(%ebx,%esi,1),%ebx
	movl	%eax,		68(%esp)
	roll	$6,		%ebx
	addl	%eax,		%ebx
	movl	(%edi),		%eax
	movl	%ebx,		72(%esp)
	movl	%ecx,		76(%esp)
	movl	4(%edi),	%ebx
	movl	%edx,		80(%esp)
	movl	8(%edi),	%ecx
	movl	%ebp,		84(%esp)
	movl	12(%edi),	%edx
	movl	16(%edi),	%ebp
	/* 80 */
	movl	$-1,		%edi
	subl	%edx,		%edi
	movl	24(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%eax
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ecx
	leal	1352829926(%eax,%edi,1),%eax
	subl	%ecx,		%esi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 81 */
	movl	60(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%ebp
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebx
	leal	1352829926(%ebp,%esi,1),%ebp
	subl	%ebx,		%edi
	roll	$9,		%ebp
	addl	%edx,		%ebp
	/* 82 */
	movl	32(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%edx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	1352829926(%edx,%edi,1),%edx
	subl	%eax,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 83 */
	movl	4(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%ecx
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	1352829926(%ecx,%esi,1),%ecx
	subl	%ebp,		%edi
	roll	$11,		%ecx
	addl	%ebx,		%ecx
	/* 84 */
	movl	40(%esp),	%esi
	orl	%edx,		%edi
	addl	%esi,		%ebx
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	1352829926(%ebx,%edi,1),%ebx
	subl	%edx,		%esi
	roll	$13,		%ebx
	addl	%eax,		%ebx
	/* 85 */
	movl	12(%esp),	%edi
	orl	%ecx,		%esi
	addl	%edi,		%eax
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	1352829926(%eax,%esi,1),%eax
	subl	%ecx,		%edi
	roll	$15,		%eax
	addl	%ebp,		%eax
	/* 86 */
	movl	48(%esp),	%esi
	orl	%ebx,		%edi
	addl	%esi,		%ebp
	xorl	%eax,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	1352829926(%ebp,%edi,1),%ebp
	subl	%ebx,		%esi
	roll	$15,		%ebp
	addl	%edx,		%ebp
	/* 87 */
	movl	20(%esp),	%edi
	orl	%eax,		%esi
	addl	%edi,		%edx
	xorl	%ebp,		%esi
	movl	$-1,		%edi
	roll	$10,		%eax
	leal	1352829926(%edx,%esi,1),%edx
	subl	%eax,		%edi
	roll	$5,		%edx
	addl	%ecx,		%edx
	/* 88 */
	movl	56(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%ecx
	xorl	%edx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebp
	leal	1352829926(%ecx,%edi,1),%ecx
	subl	%ebp,		%esi
	roll	$7,		%ecx
	addl	%ebx,		%ecx
	/* 89 */
	movl	28(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ebx
	xorl	%ecx,		%esi
	movl	$-1,		%edi
	roll	$10,		%edx
	leal	1352829926(%ebx,%esi,1),%ebx
	subl	%edx,		%edi
	roll	$7,		%ebx
	addl	%eax,		%ebx
	/* 90 */
	movl	64(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%eax
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ecx
	leal	1352829926(%eax,%edi,1),%eax
	subl	%ecx,		%esi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 91 */
	movl	36(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%ebp
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebx
	leal	1352829926(%ebp,%esi,1),%ebp
	subl	%ebx,		%edi
	roll	$11,		%ebp
	addl	%edx,		%ebp
	/* 92 */
	movl	8(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%edx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	1352829926(%edx,%edi,1),%edx
	subl	%eax,		%esi
	roll	$14,		%edx
	addl	%ecx,		%edx
	/* 93 */
	movl	44(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%ecx
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	1352829926(%ecx,%esi,1),%ecx
	subl	%ebp,		%edi
	roll	$14,		%ecx
	addl	%ebx,		%ecx
	/* 94 */
	movl	16(%esp),	%esi
	orl	%edx,		%edi
	addl	%esi,		%ebx
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	1352829926(%ebx,%edi,1),%ebx
	subl	%edx,		%esi
	roll	$12,		%ebx
	addl	%eax,		%ebx
	/* 95 */
	movl	52(%esp),	%edi
	orl	%ecx,		%esi
	addl	%edi,		%eax
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	1352829926(%eax,%esi,1),%eax
	movl	%ecx,		%esi
	roll	$6,		%eax
	addl	%ebp,		%eax
	/* 96 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	28(%esp),	%esi
	roll	$10,		%ebx
	leal	1548603684(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	roll	$9,		%ebp
	addl	%edx,		%ebp
	/* 97 */
	subl	%ebx,		%edi
	andl	%ebp,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	48(%esp),	%esi
	roll	$10,		%eax
	leal	1548603684(%edx,%edi,),%edx
	movl	$-1,		%edi
	addl	%esi,		%edx
	movl	%eax,		%esi
	roll	$13,		%edx
	addl	%ecx,		%edx
	/* 98 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	16(%esp),	%esi
	roll	$10,		%ebp
	leal	1548603684(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	roll	$15,		%ecx
	addl	%ebx,		%ecx
	/* 99 */
	subl	%ebp,		%edi
	andl	%ecx,		%esi
	andl	%edx,		%edi
	orl	%esi,		%edi
	movl	32(%esp),	%esi
	roll	$10,		%edx
	leal	1548603684(%ebx,%edi,),%ebx
	movl	$-1,		%edi
	addl	%esi,		%ebx
	movl	%edx,		%esi
	roll	$7,		%ebx
	addl	%eax,		%ebx
	/* 100 */
	subl	%edx,		%edi
	andl	%ebx,		%esi
	andl	%ecx,		%edi
	orl	%esi,		%edi
	movl	4(%esp),	%esi
	roll	$10,		%ecx
	leal	1548603684(%eax,%edi,),%eax
	movl	$-1,		%edi
	addl	%esi,		%eax
	movl	%ecx,		%esi
	roll	$12,		%eax
	addl	%ebp,		%eax
	/* 101 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	56(%esp),	%esi
	roll	$10,		%ebx
	leal	1548603684(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	roll	$8,		%ebp
	addl	%edx,		%ebp
	/* 102 */
	subl	%ebx,		%edi
	andl	%ebp,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	24(%esp),	%esi
	roll	$10,		%eax
	leal	1548603684(%edx,%edi,),%edx
	movl	$-1,		%edi
	addl	%esi,		%edx
	movl	%eax,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 103 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	44(%esp),	%esi
	roll	$10,		%ebp
	leal	1548603684(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	roll	$11,		%ecx
	addl	%ebx,		%ecx
	/* 104 */
	subl	%ebp,		%edi
	andl	%ecx,		%esi
	andl	%edx,		%edi
	orl	%esi,		%edi
	movl	60(%esp),	%esi
	roll	$10,		%edx
	leal	1548603684(%ebx,%edi,),%ebx
	movl	$-1,		%edi
	addl	%esi,		%ebx
	movl	%edx,		%esi
	roll	$7,		%ebx
	addl	%eax,		%ebx
	/* 105 */
	subl	%edx,		%edi
	andl	%ebx,		%esi
	andl	%ecx,		%edi
	orl	%esi,		%edi
	movl	64(%esp),	%esi
	roll	$10,		%ecx
	leal	1548603684(%eax,%edi,),%eax
	movl	$-1,		%edi
	addl	%esi,		%eax
	movl	%ecx,		%esi
	roll	$7,		%eax
	addl	%ebp,		%eax
	/* 106 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	36(%esp),	%esi
	roll	$10,		%ebx
	leal	1548603684(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	roll	$12,		%ebp
	addl	%edx,		%ebp
	/* 107 */
	subl	%ebx,		%edi
	andl	%ebp,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	52(%esp),	%esi
	roll	$10,		%eax
	leal	1548603684(%edx,%edi,),%edx
	movl	$-1,		%edi
	addl	%esi,		%edx
	movl	%eax,		%esi
	roll	$7,		%edx
	addl	%ecx,		%edx
	/* 108 */
	subl	%eax,		%edi
	andl	%edx,		%esi
	andl	%ebp,		%edi
	orl	%esi,		%edi
	movl	20(%esp),	%esi
	roll	$10,		%ebp
	leal	1548603684(%ecx,%edi,),%ecx
	movl	$-1,		%edi
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	roll	$6,		%ecx
	addl	%ebx,		%ecx
	/* 109 */
	subl	%ebp,		%edi
	andl	%ecx,		%esi
	andl	%edx,		%edi
	orl	%esi,		%edi
	movl	40(%esp),	%esi
	roll	$10,		%edx
	leal	1548603684(%ebx,%edi,),%ebx
	movl	$-1,		%edi
	addl	%esi,		%ebx
	movl	%edx,		%esi
	roll	$15,		%ebx
	addl	%eax,		%ebx
	/* 110 */
	subl	%edx,		%edi
	andl	%ebx,		%esi
	andl	%ecx,		%edi
	orl	%esi,		%edi
	movl	8(%esp),	%esi
	roll	$10,		%ecx
	leal	1548603684(%eax,%edi,),%eax
	movl	$-1,		%edi
	addl	%esi,		%eax
	movl	%ecx,		%esi
	roll	$13,		%eax
	addl	%ebp,		%eax
	/* 111 */
	subl	%ecx,		%edi
	andl	%eax,		%esi
	andl	%ebx,		%edi
	orl	%esi,		%edi
	movl	12(%esp),	%esi
	roll	$10,		%ebx
	leal	1548603684(%ebp,%edi,),%ebp
	movl	$-1,		%edi
	addl	%esi,		%ebp
	subl	%eax,		%edi
	roll	$11,		%ebp
	addl	%edx,		%ebp
	/* 112 */
	movl	64(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%edx
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	1836072691(%edx,%edi,1),%edx
	subl	%ebp,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 113 */
	movl	24(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ecx
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	1836072691(%ecx,%esi,1),%ecx
	subl	%edx,		%edi
	roll	$7,		%ecx
	addl	%ebx,		%ecx
	/* 114 */
	movl	8(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%ebx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	1836072691(%ebx,%edi,1),%ebx
	subl	%ecx,		%esi
	roll	$15,		%ebx
	addl	%eax,		%ebx
	/* 115 */
	movl	16(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%eax
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	1836072691(%eax,%esi,1),%eax
	subl	%ebx,		%edi
	roll	$11,		%eax
	addl	%ebp,		%eax
	/* 116 */
	movl	32(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%ebp
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	1836072691(%ebp,%edi,1),%ebp
	subl	%eax,		%esi
	roll	$8,		%ebp
	addl	%edx,		%ebp
	/* 117 */
	movl	60(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%edx
	xorl	%ebx,		%esi
	movl	$-1,		%edi
	roll	$10,		%eax
	leal	1836072691(%edx,%esi,1),%edx
	subl	%ebp,		%edi
	roll	$6,		%edx
	addl	%ecx,		%edx
	/* 118 */
	movl	28(%esp),	%esi
	orl	%edx,		%edi
	addl	%esi,		%ecx
	xorl	%eax,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebp
	leal	1836072691(%ecx,%edi,1),%ecx
	subl	%edx,		%esi
	roll	$6,		%ecx
	addl	%ebx,		%ecx
	/* 119 */
	movl	40(%esp),	%edi
	orl	%ecx,		%esi
	addl	%edi,		%ebx
	xorl	%ebp,		%esi
	movl	$-1,		%edi
	roll	$10,		%edx
	leal	1836072691(%ebx,%esi,1),%ebx
	subl	%ecx,		%edi
	roll	$14,		%ebx
	addl	%eax,		%ebx
	/* 120 */
	movl	48(%esp),	%esi
	orl	%ebx,		%edi
	addl	%esi,		%eax
	xorl	%edx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ecx
	leal	1836072691(%eax,%edi,1),%eax
	subl	%ebx,		%esi
	roll	$12,		%eax
	addl	%ebp,		%eax
	/* 121 */
	movl	36(%esp),	%edi
	orl	%eax,		%esi
	addl	%edi,		%ebp
	xorl	%ecx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebx
	leal	1836072691(%ebp,%esi,1),%ebp
	subl	%eax,		%edi
	roll	$13,		%ebp
	addl	%edx,		%ebp
	/* 122 */
	movl	52(%esp),	%esi
	orl	%ebp,		%edi
	addl	%esi,		%edx
	xorl	%ebx,		%edi
	movl	$-1,		%esi
	roll	$10,		%eax
	leal	1836072691(%edx,%edi,1),%edx
	subl	%ebp,		%esi
	roll	$5,		%edx
	addl	%ecx,		%edx
	/* 123 */
	movl	12(%esp),	%edi
	orl	%edx,		%esi
	addl	%edi,		%ecx
	xorl	%eax,		%esi
	movl	$-1,		%edi
	roll	$10,		%ebp
	leal	1836072691(%ecx,%esi,1),%ecx
	subl	%edx,		%edi
	roll	$14,		%ecx
	addl	%ebx,		%ecx
	/* 124 */
	movl	44(%esp),	%esi
	orl	%ecx,		%edi
	addl	%esi,		%ebx
	xorl	%ebp,		%edi
	movl	$-1,		%esi
	roll	$10,		%edx
	leal	1836072691(%ebx,%edi,1),%ebx
	subl	%ecx,		%esi
	roll	$13,		%ebx
	addl	%eax,		%ebx
	/* 125 */
	movl	4(%esp),	%edi
	orl	%ebx,		%esi
	addl	%edi,		%eax
	xorl	%edx,		%esi
	movl	$-1,		%edi
	roll	$10,		%ecx
	leal	1836072691(%eax,%esi,1),%eax
	subl	%ebx,		%edi
	roll	$13,		%eax
	addl	%ebp,		%eax
	/* 126 */
	movl	20(%esp),	%esi
	orl	%eax,		%edi
	addl	%esi,		%ebp
	xorl	%ecx,		%edi
	movl	$-1,		%esi
	roll	$10,		%ebx
	leal	1836072691(%ebp,%edi,1),%ebp
	subl	%eax,		%esi
	roll	$7,		%ebp
	addl	%edx,		%ebp
	/* 127 */
	movl	56(%esp),	%edi
	orl	%ebp,		%esi
	addl	%edi,		%edx
	xorl	%ebx,		%esi
	movl	36(%esp),	%edi
	roll	$10,		%eax
	leal	1836072691(%edx,%esi,1),%edx
	movl	$-1,		%esi
	roll	$5,		%edx
	addl	%ecx,		%edx
	/* 128 */
	addl	%edi,		%ecx
	movl	%ebp,		%edi
	subl	%edx,		%esi
	andl	%edx,		%edi
	andl	%eax,		%esi
	orl	%esi,		%edi
	movl	28(%esp),	%esi
	roll	$10,		%ebp
	leal	2053994217(%ecx,%edi,1),%ecx
	movl	$-1,		%edi
	roll	$15,		%ecx
	addl	%ebx,		%ecx
	/* 129 */
	addl	%esi,		%ebx
	movl	%edx,		%esi
	subl	%ecx,		%edi
	andl	%ecx,		%esi
	andl	%ebp,		%edi
	orl	%edi,		%esi
	movl	20(%esp),	%edi
	roll	$10,		%edx
	leal	2053994217(%ebx,%esi,1),%ebx
	movl	$-1,		%esi
	roll	$5,		%ebx
	addl	%eax,		%ebx
	/* 130 */
	addl	%edi,		%eax
	movl	%ecx,		%edi
	subl	%ebx,		%esi
	andl	%ebx,		%edi
	andl	%edx,		%esi
	orl	%esi,		%edi
	movl	8(%esp),	%esi
	roll	$10,		%ecx
	leal	2053994217(%eax,%edi,1),%eax
	movl	$-1,		%edi
	roll	$8,		%eax
	addl	%ebp,		%eax
	/* 131 */
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	subl	%eax,		%edi
	andl	%eax,		%esi
	andl	%ecx,		%edi
	orl	%edi,		%esi
	movl	16(%esp),	%edi
	roll	$10,		%ebx
	leal	2053994217(%ebp,%esi,1),%ebp
	movl	$-1,		%esi
	roll	$11,		%ebp
	addl	%edx,		%ebp
	/* 132 */
	addl	%edi,		%edx
	movl	%eax,		%edi
	subl	%ebp,		%esi
	andl	%ebp,		%edi
	andl	%ebx,		%esi
	orl	%esi,		%edi
	movl	48(%esp),	%esi
	roll	$10,		%eax
	leal	2053994217(%edx,%edi,1),%edx
	movl	$-1,		%edi
	roll	$14,		%edx
	addl	%ecx,		%edx
	/* 133 */
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	subl	%edx,		%edi
	andl	%edx,		%esi
	andl	%eax,		%edi
	orl	%edi,		%esi
	movl	64(%esp),	%edi
	roll	$10,		%ebp
	leal	2053994217(%ecx,%esi,1),%ecx
	movl	$-1,		%esi
	roll	$14,		%ecx
	addl	%ebx,		%ecx
	/* 134 */
	addl	%edi,		%ebx
	movl	%edx,		%edi
	subl	%ecx,		%esi
	andl	%ecx,		%edi
	andl	%ebp,		%esi
	orl	%esi,		%edi
	movl	4(%esp),	%esi
	roll	$10,		%edx
	leal	2053994217(%ebx,%edi,1),%ebx
	movl	$-1,		%edi
	roll	$6,		%ebx
	addl	%eax,		%ebx
	/* 135 */
	addl	%esi,		%eax
	movl	%ecx,		%esi
	subl	%ebx,		%edi
	andl	%ebx,		%esi
	andl	%edx,		%edi
	orl	%edi,		%esi
	movl	24(%esp),	%edi
	roll	$10,		%ecx
	leal	2053994217(%eax,%esi,1),%eax
	movl	$-1,		%esi
	roll	$14,		%eax
	addl	%ebp,		%eax
	/* 136 */
	addl	%edi,		%ebp
	movl	%ebx,		%edi
	subl	%eax,		%esi
	andl	%eax,		%edi
	andl	%ecx,		%esi
	orl	%esi,		%edi
	movl	52(%esp),	%esi
	roll	$10,		%ebx
	leal	2053994217(%ebp,%edi,1),%ebp
	movl	$-1,		%edi
	roll	$6,		%ebp
	addl	%edx,		%ebp
	/* 137 */
	addl	%esi,		%edx
	movl	%eax,		%esi
	subl	%ebp,		%edi
	andl	%ebp,		%esi
	andl	%ebx,		%edi
	orl	%edi,		%esi
	movl	12(%esp),	%edi
	roll	$10,		%eax
	leal	2053994217(%edx,%esi,1),%edx
	movl	$-1,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 138 */
	addl	%edi,		%ecx
	movl	%ebp,		%edi
	subl	%edx,		%esi
	andl	%edx,		%edi
	andl	%eax,		%esi
	orl	%esi,		%edi
	movl	56(%esp),	%esi
	roll	$10,		%ebp
	leal	2053994217(%ecx,%edi,1),%ecx
	movl	$-1,		%edi
	roll	$12,		%ecx
	addl	%ebx,		%ecx
	/* 139 */
	addl	%esi,		%ebx
	movl	%edx,		%esi
	subl	%ecx,		%edi
	andl	%ecx,		%esi
	andl	%ebp,		%edi
	orl	%edi,		%esi
	movl	40(%esp),	%edi
	roll	$10,		%edx
	leal	2053994217(%ebx,%esi,1),%ebx
	movl	$-1,		%esi
	roll	$9,		%ebx
	addl	%eax,		%ebx
	/* 140 */
	addl	%edi,		%eax
	movl	%ecx,		%edi
	subl	%ebx,		%esi
	andl	%ebx,		%edi
	andl	%edx,		%esi
	orl	%esi,		%edi
	movl	32(%esp),	%esi
	roll	$10,		%ecx
	leal	2053994217(%eax,%edi,1),%eax
	movl	$-1,		%edi
	roll	$12,		%eax
	addl	%ebp,		%eax
	/* 141 */
	addl	%esi,		%ebp
	movl	%ebx,		%esi
	subl	%eax,		%edi
	andl	%eax,		%esi
	andl	%ecx,		%edi
	orl	%edi,		%esi
	movl	44(%esp),	%edi
	roll	$10,		%ebx
	leal	2053994217(%ebp,%esi,1),%ebp
	movl	$-1,		%esi
	roll	$5,		%ebp
	addl	%edx,		%ebp
	/* 142 */
	addl	%edi,		%edx
	movl	%eax,		%edi
	subl	%ebp,		%esi
	andl	%ebp,		%edi
	andl	%ebx,		%esi
	orl	%esi,		%edi
	movl	60(%esp),	%esi
	roll	$10,		%eax
	leal	2053994217(%edx,%edi,1),%edx
	movl	$-1,		%edi
	roll	$15,		%edx
	addl	%ecx,		%edx
	/* 143 */
	addl	%esi,		%ecx
	movl	%ebp,		%esi
	subl	%edx,		%edi
	andl	%edx,		%esi
	andl	%eax,		%edi
	orl	%esi,		%edi
	movl	%edx,		%esi
	roll	$10,		%ebp
	leal	2053994217(%ecx,%edi,1),%ecx
	xorl	%ebp,		%esi
	roll	$8,		%ecx
	addl	%ebx,		%ecx
	/* 144 */
	movl	52(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%edi,		%ebx
	roll	$10,		%edx
	addl	%esi,		%ebx
	movl	%ecx,		%esi
	roll	$8,		%ebx
	addl	%eax,		%ebx
	/* 145 */
	xorl	%edx,		%esi
	movl	64(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%esi,		%eax
	movl	%ebx,		%esi
	roll	$10,		%ecx
	addl	%edi,		%eax
	xorl	%ecx,		%esi
	roll	$5,		%eax
	addl	%ebp,		%eax
	/* 146 */
	movl	44(%esp),	%edi
	xorl	%eax,		%esi
	addl	%edi,		%ebp
	roll	$10,		%ebx
	addl	%esi,		%ebp
	movl	%eax,		%esi
	roll	$12,		%ebp
	addl	%edx,		%ebp
	/* 147 */
	xorl	%ebx,		%esi
	movl	20(%esp),	%edi
	xorl	%ebp,		%esi
	addl	%esi,		%edx
	movl	%ebp,		%esi
	roll	$10,		%eax
	addl	%edi,		%edx
	xorl	%eax,		%esi
	roll	$9,		%edx
	addl	%ecx,		%edx
	/* 148 */
	movl	8(%esp),	%edi
	xorl	%edx,		%esi
	addl	%edi,		%ecx
	roll	$10,		%ebp
	addl	%esi,		%ecx
	movl	%edx,		%esi
	roll	$12,		%ecx
	addl	%ebx,		%ecx
	/* 149 */
	xorl	%ebp,		%esi
	movl	24(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%esi,		%ebx
	movl	%ecx,		%esi
	roll	$10,		%edx
	addl	%edi,		%ebx
	xorl	%edx,		%esi
	roll	$5,		%ebx
	addl	%eax,		%ebx
	/* 150 */
	movl	36(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%edi,		%eax
	roll	$10,		%ecx
	addl	%esi,		%eax
	movl	%ebx,		%esi
	roll	$14,		%eax
	addl	%ebp,		%eax
	/* 151 */
	xorl	%ecx,		%esi
	movl	32(%esp),	%edi
	xorl	%eax,		%esi
	addl	%esi,		%ebp
	movl	%eax,		%esi
	roll	$10,		%ebx
	addl	%edi,		%ebp
	xorl	%ebx,		%esi
	roll	$6,		%ebp
	addl	%edx,		%ebp
	/* 152 */
	movl	28(%esp),	%edi
	xorl	%ebp,		%esi
	addl	%edi,		%edx
	roll	$10,		%eax
	addl	%esi,		%edx
	movl	%ebp,		%esi
	roll	$8,		%edx
	addl	%ecx,		%edx
	/* 153 */
	xorl	%eax,		%esi
	movl	12(%esp),	%edi
	xorl	%edx,		%esi
	addl	%esi,		%ecx
	movl	%edx,		%esi
	roll	$10,		%ebp
	addl	%edi,		%ecx
	xorl	%ebp,		%esi
	roll	$13,		%ecx
	addl	%ebx,		%ecx
	/* 154 */
	movl	56(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%edi,		%ebx
	roll	$10,		%edx
	addl	%esi,		%ebx
	movl	%ecx,		%esi
	roll	$6,		%ebx
	addl	%eax,		%ebx
	/* 155 */
	xorl	%edx,		%esi
	movl	60(%esp),	%edi
	xorl	%ebx,		%esi
	addl	%esi,		%eax
	movl	%ebx,		%esi
	roll	$10,		%ecx
	addl	%edi,		%eax
	xorl	%ecx,		%esi
	roll	$5,		%eax
	addl	%ebp,		%eax
	/* 156 */
	movl	4(%esp),	%edi
	xorl	%eax,		%esi
	addl	%edi,		%ebp
	roll	$10,		%ebx
	addl	%esi,		%ebp
	movl	%eax,		%esi
	roll	$15,		%ebp
	addl	%edx,		%ebp
	/* 157 */
	xorl	%ebx,		%esi
	movl	16(%esp),	%edi
	xorl	%ebp,		%esi
	addl	%esi,		%edx
	movl	%ebp,		%esi
	roll	$10,		%eax
	addl	%edi,		%edx
	xorl	%eax,		%esi
	roll	$13,		%edx
	addl	%ecx,		%edx
	/* 158 */
	movl	40(%esp),	%edi
	xorl	%edx,		%esi
	addl	%edi,		%ecx
	roll	$10,		%ebp
	addl	%esi,		%ecx
	movl	%edx,		%esi
	roll	$11,		%ecx
	addl	%ebx,		%ecx
	/* 159 */
	xorl	%ebp,		%esi
	movl	48(%esp),	%edi
	xorl	%ecx,		%esi
	addl	%esi,		%ebx
	roll	$10,		%edx
	addl	%edi,		%ebx
	movl	108(%esp),	%edi
	roll	$11,		%ebx
	addl	%eax,		%ebx
	movl	4(%edi),	%esi
	addl	%esi,		%edx
	movl	76(%esp),	%esi
	addl	%esi,		%edx
	movl	8(%edi),	%esi
	addl	%esi,		%ebp
	movl	80(%esp),	%esi
	addl	%esi,		%ebp
	movl	12(%edi),	%esi
	addl	%esi,		%eax
	movl	84(%esp),	%esi
	addl	%esi,		%eax
	movl	16(%edi),	%esi
	addl	%esi,		%ebx
	movl	68(%esp),	%esi
	addl	%esi,		%ebx
	movl	(%edi),		%esi
	addl	%esi,		%ecx
	movl	72(%esp),	%esi
	addl	%esi,		%ecx
	movl	%edx,		(%edi)
	movl	%ebp,		4(%edi)
	movl	%eax,		8(%edi)
	movl	%ebx,		12(%edi)
	movl	%ecx,		16(%edi)
	movl	(%esp),		%edi
	movl	112(%esp),	%esi
	cmpl	%esi,		%edi
	movl	108(%esp),	%edi
	jae	.L000start
	addl	$88,		%esp
	popl	%ebx
	popl	%ebp
	popl	%edi
	popl	%esi
	ret
.ripemd160_block_x86_end:
	SIZE(ripemd160_block_x86,.ripemd160_block_x86_end-ripemd160_block_x86)
.ident	"desasm.pl"
#endif /* not PIC */
