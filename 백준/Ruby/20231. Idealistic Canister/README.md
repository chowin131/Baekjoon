# [Ruby IV] Idealistic Canister - 20231 

[문제 링크](https://www.acmicpc.net/problem/20231) 

### 성능 요약

메모리: 2276 KB, 시간: 1864 ms

### 분류

수학, 기하학, 이분 탐색, 많은 조건 분기, 매개 변수 탐색, 볼록 껍질, 삼분 탐색, 최소 외접원

### 제출 일자

2026년 4월 16일 12:53:46

### 문제 설명

<p>The Ideally Compact Packaging Canisters (ICPC) corporation is a package manufacturer specialized in canisters (cylindrical containers), designing and manufacturing canisters satisfying clients' demands.</p>

<p>The corporation has taken an order of a canister to pack two different products together. Both products have shapes of convex polygonal prisms with the same height. The inside of the canister should be precisely a cylinder whose height is equal to the height of the products.</p>

<p>Products must be placed vertically in the canister, that is, the bottoms of the products must meet the inner bottom of the canister. Products can be placed at an arbitrary position and with an arbitrary direction in the canister, but they should not be laid upside-down nor stacked one on the other. Products and the inner surface of the canister may touch one another.</p>

<p>The customer requests to make the canister as small as possible. Your task is to find the smallest possible diameter of the canister bottom that can contain the two products.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/c565f9d5-45dc-43c6-9439-24ac2ef8b9d3/-/preview/" style="width: 400px; height: 300px;"></p>

<p style="text-align: center;">Figure H-1 Example of two products packed in the minimum-sized canister.</p>

### 입력 

 <p>The input consists of at most 50 datasets, each in the following format.</p>

<blockquote><i>n</i> <i>x</i><sub><i>a</i>,1</sub> <i>y</i><sub><i>a</i>,1</sub> ... <i>x</i><sub><i>a</i>,<i>n</i></sub> <i>y</i><sub><i>a</i>,<i>n</i></sub> <i>m</i> <i>x</i><sub><i>b</i>,1</sub> <i>y</i><sub><i>b</i>,1</sub> ... <i>x</i><sub><i>b</i>,<i>m</i></sub> <i>y</i><sub><i>b</i>,<i>m</i></sub></blockquote>

<p><i>n</i> (3 ≤ <i>n</i> ≤ 40) is the number of vertices of the bottom polygon of one of the products. The following <i>n</i> lines have two integers each, which are the <i>x-</i> and <i>y-</i>coordinates of the vertices of the bottom polygon. They are between −1000 and 1000, inclusive. The vertices are listed in a counter-clockwise order. The bottom polygon is guaranteed to be convex.</p>

<p>Then comes the description of the bottom polygon of the other product in exactly the same manner.</p>

<p>The end of the input is indicated by a line containing a zero.</p>

### 출력 

 <p>For each dataset, output the smallest possible <b>diameter</b> of the bottom circle of the canister that accommodates the two products together. The output must not contain an error greater than 10<sup>−6</sup>.</p>

