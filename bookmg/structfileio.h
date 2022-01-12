#ifndef structfileio_h
#define structfileio_h
#define MAX 100
#define BOOKNAME 40
#define WRITER 20

#define ON 1
#define OFF 0
typedef union
{
	unsigned code;
	struct {
		unsigned kubun : 2;
		unsigned type : 3;
		unsigned null : 3;
		unsigned number : 24;
	}cd;
}code;
struct borrow {
	time_t dateOfBorrowing;//���� ��¥
	time_t dateOfReturning;//�ݳ���¥
	char bookBorrower[20];
	int borrow;			// ���� ���� ���� 0:���Ⱑ��,1:������
};
typedef struct {
	code bcode;			//4Byte
	char bname[40];//40Byte
	char bwriter[20];//20Byte
	int bprice;			//4Byte
	struct borrow brPart;//40Byte
}bookRec; // 112Byte
int fileread(FILE* fp, bookRec* p);
void filewrite(FILE* fp, bookRec* p);
#endif