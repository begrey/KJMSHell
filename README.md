추가로 구현해야 할 기능 (필수)

	키
		$? (최근 커맨드가 정상적으로 실행되었는지)

	커서
		왼, 오른 화살표(<-, ->)	커서 이동
		위, 아래 화살표(^ , ~^)	커맨드 히스토리

	토큰
		<>	(리다이렉션)
		|	(파이프)


서브젝트, 평가표에 명시되지는 않은 기능

		~ (경로, 에시 : cd ~)





평가표 

Mandatory part

	1. Simple Command & global
	2. Arguments
	3. echo
	4. exit
	5. Return value of a process
	6. Semicolons
	7. Signals
	8. Double Quotes
	9. env
	10. export
	11. unset
	12. Environment Variables
	13. cd
	14. pwd
	15. Relative Path
	16. Environment Path
	17. Simple Quotes
	18. Redirection
	19. Pipes
	20. Go Crazy and history

BONUS
	

생각해볼 문제
	전역변수(구조체)에 들어가야 할 것들 (환경변수, 시그널 함수 인자, $?에서의 리턴 값)
	함수를 어느정도로 쪼개야 하는지(프로젝트의 규모에 맞춰서?)	
