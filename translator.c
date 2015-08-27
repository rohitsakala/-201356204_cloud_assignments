#include<stdio.h>
#include<string.h>
int main()
{
	char ch,
	file_name[25];
    FILE* file = fopen("32_bit.asm", "r"); /* should check the result */
    char line[256];
    FILE *f;
    f = fopen("64_bit.asm", "a");
    while (fgets(line, sizeof(line), file)) {
    	if(strstr(line,"pushl	%ebp"))
    	{
    		fprintf(f, "%s", "	pushq	%rbp\n");
    	}
    	else if(strstr(line,".cfi_def_cfa_offset 8"))
    	{
    		fprintf(f, "%s", "	.cfi_def_cfa_offset 16\n");
    	}
    	else if(strstr(line,".cfi_offset 5, -8"))
    	{
    		fprintf(f, "%s", "	.cfi_offset 6, -16\n");
    	}
    	else if(strstr(line,"movl	%esp, %ebp"))
    	{
    		fprintf(f, "%s", "	movq	%rsp, %rbp\n");
    	}
    	else if(strstr(line,".cfi_def_cfa_register 5"))
    	{
    		fprintf(f, "%s", "	.cfi_def_cfa_register 6\n");
    	}
    	else if(strstr(line,"subl	$16, %esp"))
    	{
    	}
    	else if(strstr(line,"movl	$8, -4(%ebp)"))
    	{
    		fprintf(f, "%s", "	movl	$8, -4(%rbp)\n");
    	}
    	else if(strstr(line,"movl	$8, -8(%ebp)"))
    	{
    		fprintf(f, "%s", "	movl	$8, -8(%rbp)\n");
    	}
    	else if(strstr(line,"movl	-4(%ebp), %edx"))
    	{
    		fprintf(f, "%s", "	movl	-4(%rbp), %edx\n");
    	}
    	else if(strstr(line,"movl	-8(%ebp), %eax"))
    	{
    		fprintf(f, "%s", "	movl	-8(%rbp), %eax\n");
    	}
    	else if(strstr(line,"addl	%edx, %eax"))
    	{
    		fprintf(f, "%s", "	addl	%edx, %eax\n");
    	}
    	else if(strstr(line,"movl	%eax, -12(%ebp)"))
    	{
    		fprintf(f, "%s", "	movl	%eax, -12(%rbp)\n");
    	}
    	else if(strstr(line,"movl	-12(%ebp), %eax"))
    	{
    		fprintf(f, "%s", "	movl	-12(%rbp), %eax\n");
    	}
    	else if(strstr(line,"leave"))
    	{
    		fprintf(f, "%s", "	popq	%rbp\n");
    	}
    	else if(strstr(line,".cfi_restore 5"))
    	{
    		fprintf(f, "%s", "	.cfi_def_cfa 7, 8\n");
    	}
    	else
    	{
    		fprintf(f, "%s", line);
    	} 
    }
    fclose(file);
    fclose(f);
    return 0;
}
