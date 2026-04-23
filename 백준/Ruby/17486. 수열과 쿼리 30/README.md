# [Ruby IV] 수열과 쿼리 30 - 17486 

[문제 링크](https://www.acmicpc.net/problem/17486) 

### 성능 요약

메모리: 316920 KB, 시간: 1824 ms

### 분류

자료 구조, 트리, 세그먼트 트리, 느리게 갱신되는 세그먼트 트리, 스플레이 트리

### 제출 일자

2026년 4월 23일 17:19:13

### 문제 설명

<p>길이가 N인 수열 A<sub>1</sub>, A<sub>2</sub>, ..., A<sub>N</sub>이 주어진다. 이때, 다음 쿼리를 수행하는 프로그램을 작성하시오. </p>

<ul>
	<li><code>1 L R X</code>: 모든 L ≤ i ≤ R에 대해서 A<sub>i</sub> = A<sub>i</sub> + X를 적용한다.</li>
	<li><code>2 L R S E</code>: A의 [L, R] 구간을 [S, E]에 있는 수로 변경한다. 즉, 이 쿼리의 결과를 수열 B라고 했을 때, B<sub>L</sub> = A<sub>S</sub>, B<sub>L+1</sub> = A<sub>S+1</sub>, ..., B<sub>R</sub> = A<sub>E</sub>가 되는 것이고, L ≤ i ≤ R에 포함되지 않은 모든 i의 B<sub>i</sub> = A<sub>i</sub>이다.</li>
	<li><code>3 L R</code>: A<sub>L</sub> + A<sub>L+1</sub> + ... + A<sub>R</sub>을 출력한다.</li>
</ul>

### 입력 

 <p>첫째 줄에 수열의 크기 N이 주어진다. (1 ≤ N ≤ 200,000)</p>

<p>둘째 줄에는 A<sub>1</sub>, A<sub>2</sub>, ..., A<sub>N</sub>이 주어진다. (-10<sup>6</sup> ≤ A<sub>i</sub> ≤ 10<sup>6</sup>)</p>

<p>셋째 줄에는 쿼리의 개수 M이 주어진다. (1 ≤ M ≤ 200,000)</p>

<p>넷째 줄부터 M개의 줄에는 쿼리가 한 줄에 하나씩 주어진다. (1 ≤ L ≤ R ≤ N, 1 ≤ S ≤ E ≤ N, E-S = R-L, -10<sup><span style="font-size: 10.8333px;">6</span></sup> ≤ X ≤ 10<sup>6</sup>) 3번 쿼리는 한 번 이상 주어진다.</p>

### 출력 

 <p>3번 쿼리의 결과를 한 줄에 하나씩 출력한다.</p>

