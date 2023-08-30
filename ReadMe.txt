블랙홀 PostProcess때문에 기능을 몇개 수정했다.
F8, F9번으로 게임을 Play,Stop으로 전환할 수 있는데,
만약 Collider가 플레이어를 따라가게 하고 싶으면
RenderMgr에서 render_play()에서 render_editor()기능을 켜줘야한다.

또한, Release버전이 아닌 Debug모드로 바꾸고 싶으면 Engine에서 