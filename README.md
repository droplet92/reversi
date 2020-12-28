# reversi

간단한 오셀로(othello, reversi) 게임입니다.   
SFML(Simple and Fast Multimedia Library)과 C++17을 이용하여 구현했습니다.  

개발 환경: Visual Studio 2019 (https://www.sfml-dev.org/tutorials/2.5/start-vc.php)

---
AI 구현에 minimax 알고리즘(https://en.wikipedia.org/wiki/Minimax) 을 사용했습니다.   
   
오셀로는 매 턴 돌을 둘 때마다 게임판 위에 놓여있던 돌들이 다시 뒤집힙니다.   
따라서 자기가 돌을 둔 시점에 우위 여부를 판단하기 어렵습니다.   
그래서 AI는 다음 차례에 상대방이 놓을 수 있는 돌의 개수를 최소화하는 것을 목적으로 삼도록 구현했습니다.   
   
AI가 생성한 경우의 수 트리의 leaf node는 상대방(플레이어)의 차례에 놓을 수 있는 돌의 개수(l)가 됩니다.   
leaf node들의 parent node들은 group node라고 부릅니다.   
해당 group node의 값 g는 child node들의 값 l 중 최댓값을 선택합니다. g = max(l1, l2, ..., ln)   
   
AI의 차례에는 child node의 g값들이 최소가 되도록 선택합니다. c = min(g1, g2, ..., gn)   
해당 과정을 반복하여 다음 차례에 둘 돌을 선택합니다.
