파싱 현황

	0. 개행 전까지 한 줄 받아옴     (o)
	1. 따옴표 스플릿                (o)
	2. 환경 변수 처리               (o)
	3. q 토큰 처리                  (o)
	4. 2차원 배열을 리스트에 담기   (o)
	5. 리스트 스플릿 (;)            (o)
	6. 리스트 스플릿 (|)            (o)
	7. 리다이렉션 파싱              (o)
	9. quote 없애기                 (o)
	10. 이스케이프문자(\\) 처리     (x)

추가로 구현해야 할 기능 (평가표 기준 필수)

	3. 터미널 제어	(커서, 히스토리, 시그널(ctrl + c,d,\))
	4. 명령어 리턴값 ($?)
	5. $PATH에 경로 추가
	6. 외부 명령어 절대경로로 실행
	8. exit 함수
	7. 엔터 입력시 command not found 출력
	4. 함수 다듬기
		static 함수 처리, 인자로 넘겨받는 문자열 const로 처리하고 옮겨서 사용
	5. 환경변수 처리
		$USERa 입력시 세그폴트



평가표 

Mandatory part (Bonus 제외)

	1. Simple Command & global
		- /bin/ls와 같이 절대경로로 명령어를 입력하더라도 실행되어야 함(argument 없이)
		- 전역변수를 몇개 썼는가? 왜? 왜 사용해야 했는지 구체적인 예시

	2. Arguments
		- /bin/ls와 같이 절대경로로 명령어를 입력하더라도 실행되어야 함(argument 포함, ", ' 없이)
		- 다른 명령어와 다른 인자들로 반복해라

	3. echo
		- 옵션 있고 없고 모두 포함해서 실행해보시오
		- 다른 명령어와 다른 인자들로 반복해라
		
	4. exit
		- 인자 있고 없고 모두 포함해서 실행
		- 다른 인자들로 여러 번 반복
		- 미니셸 다시 실행하는 것을 잊지 마라

	5. Return value of a process
		- ', "를 사용하지 않고 절대경로의 /bin/ls나 인자를 포함한 다른 명령어를 실행하고, echo $?			를 실행해봐라
		- 출력된 값을 확인해라. 배쉬에서 반복해보고 값을 비교해 볼 수 있다
		- 여러 번 반복해보고, /bin/ls/asklefj 같이 잘못된 명령어로도 해봐라

	6. Semicolons
		- 인자를 가지고 세미콜론으로 분리된 절대경로의 다중 명령어를 실행해보라
		- 다른 명령어로도 여러 번 반복해보고, 세미콜론 앞뒤로 공백을 활용하는 것을 잊지마라

	7. Signals
		- 빈 프롬프트에 ctrl-C
		- 빈 프롬프트에 ctrl-\	(실행중인 동작 종료함)
		- 빈 프롬프트에 ctrl-D
		- 프롬프트에 글자 좀 쓰고 ctrl-C
		- 프롬프트에 글자 좀 쓰고 ctrl-\
		- 프롬프트에 글자 좀 쓰고 ctrl-D
		- 인자 없이 cat이나 grep 같은 명령어를 입력하고 동작 중일 때 ctrl-C
		- 인자 없이 cat이나 grep 같은 명령어를 입력하고 동작 중일 때 ctrl-\
		- 인자 없이 cat이나 grep 같은 명령어를 입력하고 동작 중일 때 ctrl-D
		- 다른 커맨드로도 여러 번 반복

	8. Double Quotes
		- 인자를 가진 절대경로의 명령어를 실행하라, 하지만 이번에는 쌍따옴표를 사용하라 (쌍따옴표 안에는 세미콜론과 공백을 포함해야 한다)
		- 빈 인자나 \를 이상하게 사용하는 것도 고려해보라
		- 여러 줄 명령어는 시도하지 말라

	9. env
		- env 명령어가 현재 환경 변수를 보여주는지 체크해보라

	10. export
		- 환경변수를 export 해서, 새로운 환경변수를 만들어보고 기존의 것을 대체하도록 해보라
		- 그것들을 env로 확인해보라

	11. unset
		- 환경변수를 export 해서, 새로운 환경변수를 만들어보고 기존의 것을 대체하도록 해보라
		- unset을 사용해서 그 중 몇몇을 제거하라
		- env로 결과를 확인해보라

	12. Environment Variables
		- 인자로 $ 변수를 사용해서 echo를 실행해보라
		- $변수 주변에서 "를 사용해서 정확하게 동작하는지 확인해보라 (배쉬처럼)

	13. cd
		- cd 명령어를 사용해서 작업 디렉토리를 변경하고 /bin/ls 를 이용해서 올바른 디렉토리에 있는지 확인하라
		- 동작하는 cd와 동작하지 않는(잘못된) cd로 여러 번 반복하라
		- .과 ..같은 인자들로도 실행해보라

	14. pwd
		- pwd 명령어를 사용해보라
		- 다양한 디렉토리에서 반복해보라

	15. Relative Path
		- 이번에는 상대경로를 사용해서 명령어들을 실행해보라
		- 복잡한 상대경로(..을 많이 사용하는)를 사용한 명령어들을 반복해보라

	16. Environment Path
		- 이번에는 경로 없이 명령어들을 실행해보라 (ls, wc, awk 등등...)
		- $PATH를 unset해보고 더이상 작동하지 않는지 확인해보라
		- $PATH에 여러 값을 설정하고(directorty1:directory2), 왼쪽 경로에서 오른쪽 경로 순서로 체크			하는지 확인해보라

	17. Simple Quotes
		- 인자로 '(따옴표)를 사용하여 명령어를 실행해보라
		- 텅빈 인자로 해보라 ('' 말하는 것 같음)
		- 환경변수로 시도해보라, 따옴표 안에 공백과 세미콜론도 활용해보고

	18. Redirection
		- 명령어에 < >을 가지고 실행해보라
		- 다른 명령어들과 다른 인자들로도 반복해보고, >를 >>로 바꿔서도 해보라
		- 같은 리다이렉션을 여러 번 사용하는 실패하는지도 확인해보라

	19. Pipes
		- 'cat file | grep bla | more' 같이 파이프를 사용하는 명령어들을 실행해보라
		- 다른 명령어들과 다른 인자들로도 반복해보라
		- 'ls fiejaisl | grep bla | more' 같이 안되는 명령어들로도 실행해보라
		- 파이프와 리다이렉션을 조합해서 시도해보라

	20. Go Crazy and history
		- 아래, 위 키로 히스토리를 이동하고 명령어들을 다시 사용할 수 있는가
		- dsjakljasl 같이 작동하지 않는 명령어들로도 사용해보고 충돌하지 않고 에러를 잘 출력하는지 확인해보라
		- 정말 정말 정말 긴 여러 인자들로도 시도해보라
		- 미니셸을 즐기시오 (이것저것 다양하게 해보라는 뜻인듯)
