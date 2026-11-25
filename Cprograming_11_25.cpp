#pragma warning(disable:4996)
#include <stdio.h>

//바이너리 파일 복사
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

//파일 복사
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


// 파일 출력
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

//파일 입력
int main(void) {
	FILE * fp = fopen("/Users/ykong/C_Workspace/hello.txt", "rt");
	int i, ch;
	char str[30];
	if (fp == NULL) {
		printf("file open failed");
		return -1;
	}
	// 각 문자별 40자 내로 가져오기
	for (i = 1; i<40; i++){
		ch =fgetc(fp);
		printf("%c\n",ch);
	}
	
	// 문자, 문자열 줄 별로 가져오기
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

/* 개요 및 내용
=====================================================================================================================================================================================
그동안 한것
변수는 메모리에 선언이 되고 메모리에 데이터가 저장된걸 출력함 
< 메모리 = ram random access meemory = main storage = 주기억장치 >
메모리는 휘발성이다 컴퓨터가 끄면 메모리에 데이터가 날라감 

표준 입출력 printf scanf 
ㄴ std in std out 표준 스트림 
을 통해 프로그램 cpp 파일 등에 변수를 생성 저장 했다. 


=====================================================================================================================================================================================
이제부터 할것
<디스크 = 2nd storage = ssd = harddisk =  보조기억장치> 
컴퓨터를 꺼도 데이터가 없어지지 않음
파일에다가 데이터 저장하고 그 파일에서 데이터를 불러오는 작업

파일 입출력																						=========================================================================
파일에 데이터 저장 또한 출력이라 한다.																	|							  <stream>									|
파일에서 데이터를 불러오는 것을 입력이라고 한다																|	<main memory>		<=================>		<secondary storage>		|
ㄴ 스트림이 형성이 되어있어야 한다.																		|	   program				Write stream			hard disk			|
* 스트림 = 통로 / 프로그램과 파일을 오고갈수 잇게 하는 통로													|	   memory				Read stream			 	  ssd				|
																								=========================================================================

파일에 포인터 타입으로 변수 생성
	File * fp1 = fopen(); => fopen 함수는 파일의 제일 첫번째 위치 파일의 주소를 반환해줌									=====================================================
			ㄴ> 파일을 가르키는 화살표																				|						<FILE.txt>					|
		==> 스트림 형성																						|Hello World										|
																											|ㄴ> first address									|
	fopen 결과 																								|fopen(FILE.txt) => H의 위치주소						|
	파일의 위치 반환 (파일을 여는 함수)																				|실패시 NULL											|
	File *fopen ( const char * filename, const char *mode )													=====================================================
	ㄴ const를 통해 파일명을 상수화 해서 문자열된것을 상수로 넘겨줌 
	ㄴ mode 파일을 쓸건지(write) 오픈할건지(read) 인지 목적을 전달.
	성공시 파일 구조체 변수의 주소값 / 실패시 null 포인터 반환


=====================================================================================================================================================================================
																						출력 스트림 
========================================== 예시 ==========================================
|int main(void) {																		|		출력 스트림 
|	FILE * fp = fopen("hello.txt", "wt");												|		File * fp = fopen("hello.txt", "wt")
|	if (fp == NULL) {																	|		ㄴ 파일 hello.txt 이랑 스트림을 형성하되 wt 모드= Write Txt 모드로 스트림을 형성해라
|		printf("file open failed");														|		만약에 파일이 없다면 새로 생성하고 파일 초기 값이 있다면 삭제후 출력한다.
|		return -1;																		|		fputs으로 파일 첫위치 ( 첫위치는 문서에서 글을 쓸때 | 가 점등하는 위치)에 a 를 작성, 이후 다음 위치에 b 작성
|	}																					|		fclose로 닫아줘야함 
|	fputc('a', fp);																		|		상대경로를 통해 fopen("hello.txt", "wt"); 로 동일 폴더 내의 파일에 접근 가능
|	fputc('b', fp);																		|		또한, 절대 경로를 통해 다른 폴더에 파일에도 접근 가능
|	fclose(fp);   // 스트림 닫기 fclose 성공시 0 실패시 EOF = end of file = -1 반환 안하면		|	 	FILE * fp = fopen("/Users/ykong/C_Workspace/hello.txt", "wt");		* 윈도우에서는\\ 백슬래쉬 2개 사용 타 개형 문자 등과 혼동의 이유로 같은 사유로 100% 또한 100%%로 작성 
|	return 0;																			|
|}																						|
=========================================================================================

fflash 
를 통해서 fclose없이도출력 버퍼를 비울수 잇다

=====================================================================================================================================================================================
																						입력 스트림
========================================== 예시 ==========================================
|int main(void) {																		|		입력스트림
|	FILE * fp = fopen("hello.txt", "rt");												|		FILE * fp = fopen("hello.txt", "rt")
|	int i, ch;																			|		ㄴ 파일 hello.txt 이랑 스트림을 형성하되 rt 모드= Read Txt 모드로 스트림을 형성해라
|	if (fp == NULL) {																	|		파일이 없다면 새로 생성하진 않음
|		printf("file open failed");														|		fgetc으로 문자 하나하나 출력
|		return -1;																		|
|	}																					|
|	for (i=1; i< 12; i++){																|	
|		ch= fgetc(fp);																	|	
|		printf("%c",ch);																|	
|	}																					|																		\	
|	fclose(fp);   // 스트림 닫기 fclose 성공시 0 실패시 EOF = end of file = -1 반환 안하면		|	 
|	return 0;																			|
|}																						|
=========================================================================================

=====================================================================================================================================================================================
파일 모드
		=============================================================
		|		Write		|		Read		| 		Append		|
		|------------------------------------------------------------
		|	  문서 쓰기 기능	|	 문서 읽기 기능		|  문서 덧붙여 쓰기 기능 |
txt파일	|		  wt		|		 rt			|		  at		|		text mode는 문자 데이터를 저장하는 스트림
binary	|		  wb		|		 rb			|		  ab		|		binary mode는 바이너리 데이터를 저장하는 스트림		*binary data란 이미지, 신호 등의 2진수로 컴퓨터가 인식가능한 유형의 데이터 예를 들어 pdf를 메모장에서 열면 나오는 것들
		|---------------------------- + ----------------------------|
 		|	 w+(w+t,w+b)	|	 r+(r+t,r+b) 	|		  a+		|
		|-----------------------------------------------------------|
		| 			파일 읽기 쓰기 모두 가능			|  읽기 덧붙여 쓰기 가능	|
		|	파일 부재시 생성	|	 파일 부재시 오류	|	파일 부재시 생성	|
		=============================================================

텍스트 스트림이 존재하는 이유는 					|		*개행이란 (enter란)
개행문자 \n 을 사용하지 않은 개행을 오해석 할수잇다		|		어떠한 텍스트	'|' < 글자 입력 점등	엔터 입력시
각 운영체제 마다 개행 문자의 유형 또한 다르다  		|		첫번째 행동 >	'|'	//Carrage Retrun action
윈도우는 \r\n 이고 맥은 \r 리눅스는 \n 			|		'|' < 두번째 행동	//Line Feed action 2가지로 나누어 실행된다.


=====================================================================================================================================================================================
																		파일 입출력 함수의 기분
파일 내 대상이 문자일때
int fputc (int c, File *stream)
int fgetc (File *stream)
파일 내 대상이 문자열일때
int fputs (const char *s, File *stream )
char *fgets(char *s, int n, File *stream )
+
feof 현재 파일의 끝엥 도달햇는지 확인하는 함수
int feof(File *stream)
	파일에 끝일때 0이 아닌 값 반환


바이너리 데이터의 입출력	
size_t fread(저장하고자하는 배열, 몇바이트단위로 가져올건지, 그 단위로 몇번 읽을 건지 , 그 파일)
fread(const void *buf, sizeof , 12,fp)
fp파일에서 인트는 4바이트이므로 12번 가져와서 48바이트를 buf에 저장하겠다
왜 int 가 아니라 보이드로 매게변수를 쓰는가 ?
버퍼에 몇바이트인지 모르기에  보이드 포인트로 강제 형변환 하여 전달해야한다.

fwrite(void *buf, sizeofint,12,fp)
버퍼에서 읽어와서 int size만큼 12번 가져와서 fp에 write 하겠다.

*/
