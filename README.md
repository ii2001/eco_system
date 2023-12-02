# eco_system

## 공통
- world에 윈도우, rabbit, wolf, grass Vector 있습니다 생성하고 여따 추가하면 update, draw 자동으로 됨
- world에서 가져다 쓸때 함수 인자에 Type 부분에 RABBIT, WOLF, GRASS 넣으면 알아서 그 벡터에서 찾아서 반환해줌
- 전역 변수로 필요한 것들 world 클래스에 추가하고 필요한 파일에 include 해서 사용하시면 됩니당

- entity 하위 클래스들 모두 get_type으로 어떤 종류인지 확인 가능 ( 근데 성능면에서는 클래스별로 벡터 분리해주는게 좋을수도 )

- Wolf, hunt 구현 (보완 예정)
- 현재 늑대가 토끼를 마구 잡아먹는데 wolf update함수에서 hunt() 만 주석처리하면 안먹음
- dt 받아서 배고픔 감소하고 움직이는 거 짜놨으니까 참고해도 좋을듯
- wolf에 target 잡고 움직이는 것도 짜둠

## dt 관련 참고
- dt는 밀리초단위로 들어옴
- dt기준으로 모든 변수들 직관적으로 통일했으면 좋겠음
  예를 들어서 Wolf의 speed는 300.0 인데 1초에 300 픽셀 움직이도록 move함수 구성했음

  현재 Wolf의 max_hunger는 10000 인데 1밀리초에 1씩 감소함
  이는 10000 hunger가 0이 되는데 10초가 걸리는 걸 의미함
  이것도 초단위로 통일하려고 함
  ex)max_hunger가 100이면 1초에 1씩 줄어들어서 100초가 걸린다.

- 추가로 시뮬 속도는 1배속 기준 조금 느린 느낌이 맞을듯
  배속 기능이 있으니까 1배속은 천천히 뭔일이 벌어지는지 볼수있도록 하기 위해서
  테스트 편하려고 배고픔도 10초만에 엄청 빨리 줄어들도록 해놨는데 실제로는 100초 정도 생각중 (하루를 2분 정도로)
  

## 환경파트
- [ ] 풀, 연못 추가,,,,풀 : hasEaten시 사라지고 연못은 특정 횟수 이상 다른 동물이 섭취 시 사라지도록, 이미지 도트 말고 sprite로 대체할 수 있는지
      
## 동물파트
- [ ] 토끼가 풀을 먹음
- [ ] 배가 고파지면 풀쪽으로 이동함
- [ ] 목이 말라지면 물쪽으로 이동함
- [ ] 늑대 생성
- [ ] 늑대가 배고파지면 토끼 사냥
- [ ] 짝짓기, mate
- [ ] 유전

## 그래픽파트
- [ ] to_do
      
## 카메라
- [o] 포커스 대상 따라가기
- [o] 휠로 줌 in/out
- [ ] 마우스 클릭 게임 좌표로 포커스 대상 찾기
- [ ] 미니맵

## 디버그
- 경로에 기본 폰트 ariel.ttf 파일 넣으면 디버그 사용가능
