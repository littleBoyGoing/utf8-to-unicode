/* Convert UTF-8 code to Unicode */
#include <stdio.h>
#include <stdint.h>

/* 0177 == 01111111(bin), 0377 == 11111111(bin) */
#define ONES_COUNT_MASK (0177)
#define MEET_ONE (0377)

int count_prefix_ones(uint8_t c)
{
	int n_ones = 0;
	while ((c | ONES_COUNT_MASK) == MEET_ONE) {
		/* c 的最高位为 1 */
		n_ones++;
		c = c << 1;
	}
	
	return n_ones;
}

int count_utf8_bytes(uint8_t c)
{
	int n_ones = count_prefix_ones(c);
	switch(n_ones) {
	case 0:
		return 1;
		break;
	case 1:
		return 0;
		break;
	default:
		return n_ones;
		break;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <WORDS> [TO] [BE] [CONVERTED]...\n",
				argv[0]);
		return 1;
	}

	int n_remaining_bytes;
	int i, j;
	int nprefix;
	uint32_t unicode = 0;
	for (i = 1; i < argc; i++) {
		printf("%s = ", argv[i]);

		for (j = 0; argv[i][j] != '\0';
				j++) {
			/* 开始转换并向 unicode 中填入编码 */
			n_remaining_bytes = count_utf8_bytes(argv[i][j]);
			while (n_remaining_bytes > 0) {
				/* nprefix = (分隔符0) + (1的数量) */
				nprefix = 1 + count_prefix_ones(argv[i][j]);

				/* 将 argv[i][j] 的前缀位设为 0 */
				argv[i][j] = ((uint8_t) argv[i][j]) << nprefix;
				argv[i][j] = ((uint8_t) argv[i][j]) >> nprefix;

				/* 将 argv[i][j] 的值插入到 unicode 的末尾 */
				unicode = unicode << (8-nprefix);
				unicode = unicode | (uint32_t)(argv[i][j]);

				if (--n_remaining_bytes > 0)
					j++;
			}

			printf("\\u%04X", unicode);
			unicode = 0;
		}

		putchar('\n');
	}

	return 0;
}
