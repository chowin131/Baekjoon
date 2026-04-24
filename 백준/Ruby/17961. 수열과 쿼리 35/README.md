# [Ruby V] 수열과 쿼리 35 - 17961 

[문제 링크](https://www.acmicpc.net/problem/17961) 

### 성능 요약

메모리: 11400 KB, 시간: 3660 ms

### 분류

자료 구조, 트리, 세그먼트 트리, 제곱근 분할법, 스플레이 트리

### 제출 일자

2026년 4월 24일 16:25:50

### 문제 설명

<p>길이가 N인 수열 A<sub>1</sub>, A<sub>2</sub>, ..., A<sub>N</sub>이 주어진다. 수열의 모든 수는 1 이상 N 이하이며 서로 다르다. 이때, 다음 쿼리를 수행하는 프로그램을 작성하시오. </p>

<ul>
	<li><code>l r k</code>: 부분배열 [A<sub>l</sub>, A<sub>l+1</sub>, ..., A<sub>r</sub>] 을 k만큼 오른쪽으로 시프트한다. 고로, A<sub>l</sub> 은 A<sub>l+k</sub>, A<sub>r-k</sub> 는 A<sub>r</sub>, A<sub>r-k+1</sub> 은 A<sub>l</sub>, A<sub>r</sub> 은 A<sub>l+k-1</sub> 이 된다. 이후, 수열에 길이 3의 증가하는 부분 수열 (subsequence) 이 있다면 <code>YES</code>, 아니면 <code>NO</code>를 출력한다. </li>
</ul>

### 입력 

 <section id="input">
<p>첫째 줄에 수열의 크기 N이 주어진다. (1 ≤ N ≤ 120,000)</p>

<p>둘째 줄에는 A<sub>1</sub>, A<sub>2</sub>, ..., A<sub>N</sub>이 주어진다. 모든 수는 서로 다르다. (1 ≤ A<sub>i</sub> ≤ N)</p>

<p>셋째 줄에는 쿼리의 개수 M이 주어진다. (1 ≤ M ≤ 120,000)</p>

<p>넷째 줄부터 M개의 줄에는 쿼리가 한 줄에 하나씩 주어진다. (1 ≤ L ≤ R ≤ N, 0 ≤ K ≤ R-L+1)</p>
</section>

### 출력 

 <section id="output">
<p>쿼리의 결과를 한 줄에 하나씩 출력한다.</p>
</section>

