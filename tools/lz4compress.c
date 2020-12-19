#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>

#include"lz4.h"
#include"lz4hc.h"

int main(int argc,char *argv[])
{
	if(strcmp(argv[1],"--help") == 0) {
		printf("lz4compress [input] [output]\n");
		return 0;
	}

	FILE *f;

       	f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("input error");
	}
	fseek(f, 0, SEEK_END);
	uint64_t fsize = ftell(f);
	char *input = malloc(fsize);
	fseek(f, 0, SEEK_SET);
	fread(input, sizeof(char), fsize, f);
	fclose(f);

	const int max_dst_size = LZ4_compressBound(fsize);
	char *compresed_data = malloc(max_dst_size);
	const int compress_result = LZ4_compress_HC(input, compresed_data, fsize, max_dst_size, 9);

	printf("file compressed from %"PRIu64"B to %dB\n", fsize, compress_result);

       	f = fopen(argv[2], "w");
	if (f == NULL) {
		perror("output error");
	}
	fwrite(&fsize, 8, 1, f);
	fwrite(compresed_data, compress_result, 1, f);
	fclose(f);
}
