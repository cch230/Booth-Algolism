#include <stdio.h>

int main()
{
//x : 피승수, y : 승수, M : 피승수b, A : 승수b, Q : (q,q-1) 판별, cal : 누적부분곱, R : 결과  
	int x, y, i = 0, j = 0, count = 4; 
	int M[4] = { 0 }, A[4] = { 0 };
	int Q[5] = { 0 }, cal[8] = { 0 }, R[8] = { 0 };

	printf("4비트 Booth 알고리즘입니다.\n");
	printf("(-8) ~ (8)사이의 정수를 입력해주세요.\n\n");
	printf("입력 받을 첫번째 수 : ");
	scanf("%d", &x);
	printf("입력 받을 두번째 수 : ");
	scanf("%d", &y);

	j = x;
	if (x >= -8 && x <= 7){
		for (i = 3; i >= 0; i--) {
			M[i] = j % 2;
			j /= 2;
		}
	}
	else {
		printf("\n초과된 범위입니다.\n\n");
		return 0;
	}

	j = y;

	if (y >= -8 && y <= 7) {
		for (i = 3; i >= 0; i--) {
			A[i] = j % 2;
			j /= 2;
		}
	}
	else {
		printf("\n초과된 범위입니다.\n\n");
		return 0;
	}
	//2의 보수로 만들기 
	if (x < 0)
	{
		for (i = 0; i < 4; i++) {
			if (M[i] == 0)
				M[i] = 1;

			else 
				M[i] = 0;
		}
		M[3]++;
	}
	//2의 보수로 만들기 
	if (y < 0){
		for (i = 0; i < 4; i++) {
			if (A[i] == 0)
				A[i] = 1;

			else 
				A[i] = 0;
		}
		A[3]++;
	}
	
	for (i = 3; i >= 0; i--) {
			if (M[i] == 2) {
				if (i > 0) {
					M[i - 1]++;
				}
				M[i] = 0;

			}
			if (A[i] == 2) {
				if (i > 0) {
					A[i - 1] ++;
				}
				A[i] = 0;
			}
	}
	
	printf("\n정수 %d 의 2진수 표현:\n", x);
	for (i = 0; i < 4; i++) {
		printf("%d ", M[i]);
	}
	printf("\n정수 %d 의 2진수 표현:\n", y);
	for (i = 0; i < 4; i++) {
		printf("%d ", A[i]);
	}
	Q[i] = A[i];
	Q[4] = 0;
	printf("\n\n\n [Booth 알고리즘 곱]\n\n");
	printf("\t    ");
	for (i = 0; i < 4; i++) {
		printf("%d ", M[i]);
	}
	printf("\n   X\t    ");
	for (i = 0; i < 4; i++) {
		printf("%d ", A[i]);
		Q[i] = A[i];
	}
	printf("\n-------------------\tQ  Q-1\n");
	//count가 0일때 까지 반복 실행
	while (count > 0) {
		
		// Q레지스터의 3번과 4번 배열이 1, 0 이면
		if (Q[3] == 1 && Q[4] == 0) {
				//초기화된 누적 부분곱에 피승수를 저장
				for (i = 0; i < 4; i++) {
					cal[i + count] = M[i];
				}
				//피승수가 양수일때(-(+))2의 보수로 만들기
				if (M[0] == 0) {
					for (i = 0; i < 8; i++) {
						if (cal[i] == 0)
							cal[i] = 1;
						else
							cal[i] = 0;
					}
					cal[7]++;
					for (i = 7; i >= 0; i--) {
						if (cal[i] == 2) {
							if (i > 0) {
								cal[i - 1]++;
							}
							cal[i] = 0;
						}
					}
				}
			//누적부분곱를 R에 저장
			for (i = 0; i < 8; i++) {
				R[i] += cal[i];
			}
			for (i = 7; i >= 0; i--) {
				if (R[i] == 2) {
					if (i > 0) {
						R[i - 1]++;
					}
					R[i] = 0;
				}
				if (R[i] == 3) {
					if (i > 0) {
						R[i - 1]++;
					}
					R[i] = 1;
				}
			}
			//누적부분곱 출력&누적부분곱 초기화
			printf("    ");
			for (i = 0; i < 8; i++) {
				printf("%d ", cal[i]);
				cal[i] = 0;
			}
			printf("\t"); 
			//(q,q-1)출력
			printf("%d   %d\n", Q[3],Q[4]);

			//(q,q-1)판별 배열 산술적 우측 Shift
			for (i = 4; i >0; i--) {
				Q[i] = Q[i - 1];
			}
			Q[0] = 0;

			count--; //작업 완료 후 count를 1 감소
		}
		
		//Q레지스터의 3번과 4번 배열이 1, 1 이면
		else if (Q[3] == 1 && Q[4] == 1) {
			
			//누적부분곱 출력&누적부분곱 초기화
			printf("    ");
			for (i = 0; i < 8; i++) {
				printf("%d ", cal[i]);
				cal[i] = 0;
			}
			printf("\t");
			//(q,q-1)출력
			printf("%d   %d\n", Q[3], Q[4]);

			//(q,q-1)판별 배열 산술적 우측 Shift
			for (i = 4; i >0; i--) {
				Q[i] = Q[i - 1];
			}
			Q[0] = 0;

			count--; //작업 완료 후 count를 1 감소
		}
		//Q레지스터의 3번과 4번 배열이 0, 0 이면
		else if (Q[3] == 0 && Q[4] == 0) {
			
			//누적부분곱 출력&누적부분곱 초기화
			printf("    ");
			for (i = 0; i < 8; i++) {
				printf("%d ", cal[i]);
				cal[i] = 0;

			}
			printf("\t");
			//(q,q-1)출력
			printf("%d   %d\n", Q[3], Q[4]);

			//(q,q-1)판별 배열 산술적 우측 Shift
			for (i = 4; i >0; i--) {
				Q[i] = Q[i - 1];
			}
			Q[0] = 0;

			count--; //작업 완료 후 count를 1 감소
		}
		//Q레지스터의 3번과 4번 배열이 0, 1 이면
		else {
			// 누적 부분곱에 피승수를 shift하고 누적 부분곱를 더하여 저장
			for (i = 0; i < 4; i++) {
				cal[i + count] = M[i];
			}
			//피승수가 음수일때(+(-)) 2의 보수로 만들기
			if (M[0] == 1) {
				for (i = 0; i < 8; i++) {
					if (cal[i] == 0)
						cal[i] = 1;
					else
						cal[i] = 0;
				}
				cal[7]++;
				for (i = 7; i >= 0; i--) {
					if (cal[i] == 2) {
						if (i > 0) {
							cal[i - 1]++;
						}
						cal[i] = 0;
					}
				}
			}
						
			//누적부분곱를 R에 저장
			for (i = 0; i < 8; i++) {
				R[i] += cal[i];
			}
			for (i = 7; i >= 0; i--) {
				if (R[i] == 2) {
					if (i > 0) {
						R[i - 1]++;
					}
					R[i] = 0;
				}
				if (R[i] == 3) {
					if (i > 0) {
						R[i - 1]++;
					}
					R[i] = 1;
				}
			}
			
			//누적부분곱 출력&누적부분곱 초기화
			printf("    ");
			for (i = 0; i < 8; i++) {
				printf("%d ", cal[i]);
				cal[i] = 0;

			}
			printf("\t");
			//(q,q-1)출력
			printf("%d   %d\n", Q[3], Q[4]);

			//(q,q-1)판별 배열 산술적 우측 Shift
			for (i = 4; i >0; i--) {
				Q[i] = Q[i - 1];
			}
			Q[0] = 0;

			count--; //작업 완료 후 count를 1 감소
		}
	}
	printf("-------------------\n");
	//결과 출력
	printf("    ");
	for (i = 0; i < 8; i++) {
		printf("%d ",R[i]);
	}
	printf("\n\n");	

}
