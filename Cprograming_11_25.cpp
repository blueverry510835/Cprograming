#pragma warning(disable:4996)
#include <stdio.h>


int main(void) {
	FILE * src = fopen("src.bin", "rt");
	FILE * dst = fopen("dst.bin", "wt");
	char buf[20];
	int readCnt;
	if (src == NULL||dst ==NULL) {
		printf("file open failed");
		return -1;
	}
	int ch;
	while (1){
		readCnt = fread((void*)buf,1,sizeof(buf),src);
		if(readCnt< sizeof(buf)){
			if(feof(src)!=0){
				fwrite((void*)buf,1,readCnt,dst);
				break;
			}
			else
				puts("failed");
		}
		fwrite((void*)buf,1,sizeof(buf),src);
		
	}
	fclose(src);   // 스트림 닫기
	fclose(dst);
	return 0;
}

/*파일 복사
int main(void) {
	FILE * fp = fopen("/Users/ykong/C_Workspace/hello.txt", "rt");
	FILE * fp2 = fopen("/Users/ykong/C_Workspace/hello.txt", "wt");
	if (fp == NULL||fp2 ==NULL) {
		printf("file open failed");
		return -1;
	}
	int ch;
	while((ch = fgetc(fp)) != EOF)
		fputc(ch, fp2);
	if (feof(fp)!= 0)
		puts("파일복사 완료");
	else
		puts("파일 복사 실패");
	fclose(fp);   // 스트림 닫기
	fclose(fp2);
	return 0;
}

*/
/* 파일 출력
int main(void) {
	FILE * fp = fopen("/Users/ykong/C_Workspace/hello.txt", "wt");
	if (fp == NULL) {
		printf("file open failed");
		return -1;
	}
	fputc('a', fp);
	fputc('b\n', fp);
	fputs("hello world\n", fp);
	fputs("My name is Hong", fp);
	fclose(fp);   // 스트림 닫기
	return 0;
}
*/
/*파일 입력
int main(void) {
	FILE * fp = fopen("/Users/ykong/C_Workspace/hello.txt", "rt");
	int i, ch;
	char str[30];
	if (fp == NULL) {
		printf("file open failed");
		return -1;
	}
	/*
	for (i = 1; i<40; i++){
		ch =fgetc(fp);
		printf("%c\n",ch);
	}
	*/
	/*
	ch = fgetc(fp);
	printf("%c\n", ch);
	ch = fgetc(fp);
	printf("%c\n", ch);
	fgets(str, sizeof(str),fp);
	// sizeof str 이게 30개를 읽어오라는 거지만 \n을 만날때 까지만 읽어온다.
	printf("%s\n", str);
	fgets(str, sizeof(str),fp);
	printf("%s\n", str);
	fclose(fp);   // 스트림 닫기
	return 0;
}

*/
///????????????질문 이거 한줄씩 읽어 나가는 건지 다음 글자가 아니라 줄씩으로 읽는 건지??????????????????????
//문자 하나식 읽어 나가는 데 아마 내가 잘못 만든거 같다.







/*
그동안 한것
변수는 메모리에 선언이 되고 메모리에 데이터가 저장된걸 출력함 메모리 = ram random access meemory 휘발성이다 컴퓨터가 끄면 메모리에 데이터가 날라감 <memory = ram = main storage = 주기억장치>
표준 입출력 printf scanf 
ㄴ std in std out 표준 스트림 

========================================================================================================
지금 할것
<디스크 = 2nd storage = ssd = harddisk =  보조기억장치> 컴퓨터를 꺼도 데이터가 없어지지 않음
파일에다가 데이터 저장하고 그 파일에서 데이터를 불러오는 작업

파일 입출력
파일에 데이터 저장 또한 출력이라 한다.
파일에서 데이터를 불러오는 것을 입력이라고 한다
ㄴ 스트림이 형성이 되어있어야 한다.
* 스트림 = 통로 / 프로그램과 파일을 오고갈수 잇게 하는 통로


파일에 포인터 타입으로 변수 생성
		File * fp1 = fopen(); => fopen 함수는 파일의 제일 첫번째 위치 파일의 주소를 반환해줌
				ㄴ> 파일을 가르키는 화살표
		==> 스트림 형성

		fopen 결과 
		파일의 위치 반환 파일을 여는 함수
		File *fopen ( const char * filename, const char *mode )
		ㄴ const를 통해 파일명을 상수화 해서 문자열된것을 상수로 넘겨줌 ㄴmode 파일을 쓸건지 오픈할건지 write read 인지 목적을 전달.
		성공시 파일 구조체 변수의 주소값 실패시 null 포인터 반환


출력 스트림 
File * fp = fopen("hello.txt", "wt")
ㄴ 파일 hello.txt 이랑 스트림을 형성하되 wt 모드로 Write Txt 모드로 스트림을 형성해라
만약에 파일이 없다면 새로 생성하고 파일 초기 값이 있다면 삭제후 출력한다.

예시///////////////////////////////////////////////////////////////////////////////////////////
int main(void) {																		/
	FILE * fp = fopen("hello.txt", "wt");												\
	if (fp == NULL) {																	/
		printf("file open failed");														\	
		return -1;																		/
	}																					\
	fputc('a', fp);																		/	
	fputc('b', fp);																		\	
	fclose(fp);   // 스트림 닫기 fclose 성공시 0 실패시 EOF = end of file = -1 반환 안하면		 /	 
	return 0;																			\
}																						/
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


fputs으로 파일 첫위치 ( 첫위치는 문서에서 글을 쓸때 | 가 점등하는 위치)에 a 를 작성
이후 b 작성
그리고 닫아줘야함 ! 
절대 경로를 통해 상대경로(프로잭트가 실행되는 폴더)가 아니라 다른 폴더에 파일에도 접근 가능
FILE * fp = fopen("/Users/ykong/C_Workspace/hello.txt", "wt");
해주면 됨

???????????????????? 질문 ????????????????????
\\가 필요한 이유가 뭔지 다시 한번만 설명해주세요
백슬래쉬가 2개여야하는 이유
\의 경우 개행 문자로도 사용 될수 잇기 때문에 혼동의 이유로 

같은 이유로 100% 출력 시에도 10%%로 적어야 한다.,

fflash 
를 통해서 fclose없이도출력 버퍼를 비울수 잇다






입력 스트림
File *fp = fopen("hello.txt", "rt")
ㄴ 파일 hello.txt 이랑 스트림을 형성하되 rt 모드로 Reda Txt 모드로 스트림을 형성해라 

예시///////////////////////////////////////////////////////////////////////////////////////////
int main(void) {																		/
	FILE * fp = fopen("hello.txt", "rt");												\	
	int i, ch;																			/
	if (fp == NULL) {																	/
		printf("file open failed");														\	
		return -1;																		/
	}																					\
	for (i=1; i< 12; i++){																/	
		ch= fgetc(fp);																	\	
		printf("%c",ch);																/	
	}																					\																		\	
	fclose(fp);   // 스트림 닫기 fclose 성공시 0 실패시 EOF = end of file = -1 반환 안하면		 /	 
	return 0;																			\
}																						/
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

파일 모드
wt rt
wb rb
write read binary text

추가로
a append
파일의 끝에 덧붙여 쓰기 가능

r+ 
읽기 쓰기 가능 하지만 파일이 없으면 에러 주목적이 read 여서

w+
읽기 쓰기 가능 파일이 없으면 생성 주목적이 write여서

a+
일기 덧붙여 쓰기 가능 파일이 없으면 생성

r+t w+t a+t
로 사용

텍스트 모드는 문자 데이터를 저장하는 스트림
바이너리 모드는 바이너리 데이터를 저장하는 스트림
바이너리 데이터 이진수 데이터 => 이미지라든가 신호 라든가 그러한 데이터 컴퓨터가 인식할수 잇는 유형의 데이터

텍스트 스트림이 존재하는 이유는 
개행문자 \n 을 사용하지 않은 개행을 오해석 할수잇다
윈도우는 \r\n 이고 맥은 \r 리눅스는 \n 이라서 

개행이란 (enter란)
ㅁㅍㅇ |
첫번째>| 	
| <--- 2번째
다음줄로 가는 carrage return action  앞으로가는 line feed action 이렇게 두개로 나뉘어 진다.


파일 입출력 함수의 기분
문자
int fputc (int c, File *stream)
int fgetc (File *stream)
문자열
int fputs (const char *s, File *stream )
char *fgets(char *s, int n, File *stream )


feof 현재 파일의 끝엥 도달햇는지 확인하는 함수
int feof(File *stream);
	파일에 끝일때 0이 아닌 값 반환



바이너리 데이터의 입출력	
size_t fread(저장하고자하는 배열, 몇바이트단위로 가져올건지, 그 단위로 몇번 읽을 건지 , 그 파일)
fread(const void *buf, sizeof , 12,fp)
fp파일에서 인트는 4바이트이므로 12번 가져와서 48바이트를 buf에 저장하겠다
왜 int 가 아니라 보이드로 매게변수를 쓰는가 ?
버퍼에 몇바이트인지 모르기에  보이드 포인트로 강제 형변환 하여 전달해야한다.

fwrite(void *buf, sizeofint,12,fp)
버퍼에서 읽어와서 int size만큼 12번 가져와서 fp에 write 하겠다.

















<main memory>		<=================>		<secondary storage>
program					Write stream			harddisk
memory					Read stream				   ssd









/// binary, txt 파일이 있다. 
binary는 메모장에서 pdf 열었을때 처럼 알아 볼수 없는 문서의 경우 binary 파일이다. 이진수로 변환해서 반환 하기 때문에














*/