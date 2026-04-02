# [Diamond V] Up Above the World So High - 22644 

[문제 링크](https://www.acmicpc.net/problem/22644) 

### 성능 요약

메모리: 2188 KB, 시간: 0 ms

### 분류

브루트포스 알고리즘, 기하학, 3차원 기하학, 최소 외접원

### 제출 일자

2026년 4월 2일 17:22:06

### 문제 설명

<p>One of the questions children often ask is "How many stars are there in the sky?" Under ideal conditions, even with the naked eye, nearly eight thousands are observable in the northern hemisphere. With a decent telescope, you may find many more, but, as the sight field will be limited, you may find much less at a time.</p>

<p>Children may ask the same questions to their parents in a spaceship billions of light-years away from the Earth. Their telescopes are similar to ours with circular sight field. It can be rotated freely, that is, the sight vector can take an arbitrary value.</p>

<p>Given a set of positions of stars and the spec of a telescope, your task is to determine the maximum number of stars that can be seen through the telescope at a time.</p>

### 입력 

 <p>The first line of a test case contains a positive integer <i>N</i> not exceeding 100, meaning the number of stars. Each of the <i>N</i> lines following it contains three integers, <i>s<sub>x</sub></i>, <i>s<sub>y</sub></i> and <i>s<sub>z</sub></i>. They give the position (<i>s<sub>x</sub></i>, <i>s<sub>y</sub></i>, <i>s<sub>z</sub></i>) of the star described in Euclidean coordinates. You may assume that -1000 ≤ <i>s<sub>x</sub></i> ≤ 1000, -1000 ≤ <i>s<sub>y</sub></i> ≤ 1000, -1000 ≤ <i>s<sub>z</sub></i> ≤ 1000 and (<i>s<sub>x</sub></i>, <i>s<sub>y</sub></i>, <i>s<sub>z</sub></i>) ≠ (0, 0, 0).</p>

<p>Then comes a line containing a positive integer <i>ψ</i> (0 < <i>ψ</i> < 90), which represents the angular radius, in degrees, of the sight field of the telescope. The telescope is at the origin of the coordinate system (0, 0, 0).</p>

<p>You may assume that change of the angular radius <i>ψ</i> by less than 0.01 degrees does not affect the answer, and that ∠POQ is greater than 0.01 degrees for any pair of distinct stars P and Q and the origin O.</p>

### 출력 

 <p>One line containing an integer meaning the maximum number of stars observable through the telescope should be output. No other characters should be contained in the output.</p>

